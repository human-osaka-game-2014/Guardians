class CResultScene : public CScene
{
// 定数
	// テクスチャ座標(称号)の先頭位置
	static const D3DXVECTOR2 UV_EMB_POSITION;
	// 称号文字の幅、高さ
	static const D3DXVECTOR2 TEX_EMB_SIZE;
	// 称号表示座標
	static const D3DXVECTOR2 POS_EMB_CHECK;
	// 称号(オフセット値)
	static const D3DXVECTOR2 POS_EMB_OFFSET;
	// 称号表示座標(ステージクリア限定称号)
	static const D3DXVECTOR2 POS_EMB_CLEAR[];
	// 称号表示座標(チェックポイント時)
	static const D3DXVECTOR2 POS_CHECKPOINT;

	// テクスチャ座標(称号台座)の位置
	static const D3DXVECTOR2 UV_EMBBAR_POSITION[];
	// 称号台座の幅、高さ
	static const D3DXVECTOR2 TEX_EMBBAR_SIZE[];
	// 称号台座(オフセット値)
	static const D3DXVECTOR2 POS_EMBBAR_OFFSET;

	// 称号玉アニメーション順番
	static const int ANIMNO_LIST[];
	// 称号玉の数
	static const int EMBBALL_NUMS[];
	// 称号名から称号玉までのオフセット値
	static const float EMBTOBALL_OFFSET;

	// 獲得資金表示位置
	static const D3DXVECTOR2 POS_GET_MONEY[];
	// 獲得資金最大桁数
	static const int MONEY_MAX_DIGIT;
	// ボーナス表示位置
	static const D3DXVECTOR2 POS_GET_BONUS[];
	// ボーナスの倍率(各称号)
	static const float BONUS[];

	// アイテム表示位置
	static const D3DXVECTOR2 POS_ITEM[];

	// ステージごとのチェックポイント数(加算型)
	static const int STAGE_NUMS[];
	// デフォルトカラー
	static const DWORD DEFAULT_COLOR;
	// BG番号(列挙)
	enum BgID{
		BG_CHECK,
		BG_CLEAR,
		BG_LOSE,
	};
	// 称号数
	enum {
		NUM_CHECK_EMB = 7,
		NUM_MAX_EMB = 11,
	};
	// 表示物ID
	enum {
		TEX_UI_NO = 3,
		TEX_ICON,
	};
	// ステージタイプ
	enum {
		STAGE_BOSS,
		STAGE_CHECK,
	};
private:
	CTexture	m_texBG;	// 背景用テクスチャ(CP通過時/クリア時/敗北時)
	CTexture	m_texUI;	// 表示物用テクスチャ
	CTexture	m_texIcon;	// アイテム
	BgID		m_bgID;		// 背景ID(描画時の判断に使用)
	int			m_cntMoney;	// お金カウント用
	int			m_addMoney; // お金のカウント量
	int			m_bonus;	// ボーナス表示用
	CGameData*	m_pGameData;// ゲームデータ

	class EmblemBall {
		// 定数
		// テクスチャ座標
		static const FRECT EMBBALL_RECT[];
	public:
		// 金or銀
		enum Type {
			TYPE_SILVER,
			TYPE_GOLD,
		};
		// 取得したタイミング
		enum GetType {
			TYPE_PREV,
			TYPE_NOW,
			TYPE_YET,
		};
	private:
		int m_type;			// 銀or金
		int m_getType;		// 取得タイプ(済/今回/未)
		int m_animNo;		// 現在のアニメーション番号
		int m_animSpd;		// アニメーション速度
		int m_animCnt;		// アニメーション切り替えまでのカウント
		FRECT m_rect;		// テクスチャ座標
		D3DXVECTOR2 m_pos;	// 表示座標
	public:
		EmblemBall(int _type, int _getType, D3DXVECTOR2 _pos);
		void Control();
		void Draw(LPDIRECT3DDEVICE9 _pDevice, CTexture _tex);
	};
	// 称号玉
	EmblemBall**	m_embBall;
	// 称号玉の個数
	int				m_embBallNum;

	// ボーナス計算
	void CulcBonus(int _stageID);
	// 獲得資金/ボーナス表示
	void DrawMoney(int _money, D3DXVECTOR2 _pos);
	// アイテム矩形計算
	FRECT GetItemRect(int _no); 

public:
	// コンストラクタ
	CResultScene(LPDIRECT3DDEVICE9 _pDevice, CGameData* m_pGameData,CInput* _input);
	// デストラクタ
	~CResultScene();

	// 制御
	SceneID Control();
	// 描画
	void Draw();		
};