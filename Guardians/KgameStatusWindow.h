#ifndef _GAME_STATUS_WINDOW_H_
#define _GAME_STATUS_WINDOW_H_


class CGameStatusWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 STT_NAME_POSITION;		// 「名前」描画座標
	static const D3DXVECTOR2 STT_MAXHP_POSITION;	// 「最大HP」描画座標
	static const D3DXVECTOR2 STT_MAXMP_POSITION;	// 「最大MP」描画座標
	static const D3DXVECTOR2 STT_ATK_POSITION;		// 「攻撃力」描画座標
	static const D3DXVECTOR2 STT_DEF_POSITION;		// 「防御力」描画座標
	static const D3DXVECTOR2 STT_SPD_POSITION;		// 「速度」描画座標
	static const D3DXVECTOR2 STT_INS_POSITION;		// 「瞬発力」描画座標
	static const D3DXVECTOR2 STT_CHARA_POSITION;	// 「キャラ画像」描画座標
	static const int MAX_WIDTH	= 560;				// ウィンドウ最大幅
	static const int MAX_HEIGHT = 520;				// ウィンドウ最大高さ

	enum ChangeType			// 能力変化タイプ
	{
		UP,
		DOWN,
	};

	enum StatusType			// 能力タイプ
	{
		STT_HP,
		STT_MP,
		STT_ATTACK,			// 攻撃力
		STT_DEFENCE,		// 防御力
		STT_SPEED,			// 速度
		STT_INSTANTANEOUS,	// 瞬発力
		STT_TYPE_MAX,		// 能力の種類
	};
	struct ChangeStatus		// 能力変化
	{
		ChangeType	type;		// 変化タイプ(上昇or下降)
		bool		isDecide;	// 決定されているかどうか
		int			power;		// 変化量
	};

	CGameData*			m_pGameData;				// ゲームデータの参照
	ChangeStatus		m_chgStatus[STT_TYPE_MAX];	// 能力変化
	int					m_charaID;					// キャラクターID
	int					m_selectEquipID;			// 選択されている装備のID
	int					m_hp;						//HP
	int					m_mp;						//MP
	int					m_atk;						//攻撃力	
	int					m_def;						//守備力
	int					m_spd;						//速度力
	int					m_ins;						//瞬発力

	// 11/1 追加
	CTexture			m_texChara;					// キャラクターイメージ
public:
	CGameStatusWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData);	// コンストラクタ(デバイス、座標、ゲームデータをセット)
	~CGameStatusWindow();
	void Control();																					// 制御
	void Draw();																					// 描画

	// アクセッサ
	void SetSelectEquipID(int _selectEquipID);														// 選択されている装備のIDをセット
	void SetCharaID(int _charaID);																	// キャラクターIDをセット
};

#endif