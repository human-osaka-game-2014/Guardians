#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

class CGameMap
{
private:
	enum {
		CHIP_MAX = 32,		// チップ数　	製作が進むにつれて増加予定
		STAGE_MAX = 18,		// ステージ数	製作が進むにつれて増加予定
	};
	enum {
		STATE_CHECKMOVE,	// チェックポイント移動状態
		STATE_MAPMOVE,		// マップ移動状態
		STATE_POINTMOVE,	// マップカーソル移動状態
		STATE_MP,			// マップとカーソルを同時に移動させる
	};
	struct ChipData {
		D3DXVECTOR2 position;
		CChip::ChipType type;
	};
	static const D3DXVECTOR2 INIT_CAMERA_POS;	// 初期カメラ座標

	static const int POINT_MOVE_SPD = 5;	// 進行ポイント描画速度

	static const int   STAGE1_LINE_NUMLIST[];	// ステージ1進行ライン個数リスト
	static const int   STAGE2_LINE_NUMLIST[];	// ステージ2進行ライン個数リスト
	static const int   STAGE3_LINE_NUMLIST[];	// ステージ3進行ライン個数リスト
	static const int   STAGE4_LINE_NUMLIST[];	// ステージ4進行ライン個数リスト
	static const int   STAGE5_LINE_NUMLIST[];	// ステージ5進行ライン個数リスト
	static const int   STAGE6_LINE_NUMLIST[];	// ステージ6進行ライン個数リスト
	static const int* STAGE_LINE_NUMLIST[];		// 全ステージ進行ライン個数リスト

	static const POINT POINT_LIST[];		// ステージごとの進行ポイント表示数
	static const POINT CHIP_NUMLIST[];		// ステージごとのチップ表示数
	
	static const ChipData CHIP_DATA[];
	LPDIRECT3DDEVICE9	m_pDevice;			// 描画デバイス
	D3DXVECTOR2			m_cameraPosition;	// 疑似カメラ座標
	CChip*				m_pChip[CHIP_MAX];	// チップクラス(モンスターチップ含む)
	std::vector<CChip>  m_chipPoint;
	CGameMapPointer*	m_mapPointa;
	CGameData*			m_pGameData;		// ゲームデータ
	int                 m_clearCount;		//チェックポイント記憶
	int					m_pointMin;			// 進行ポイントの描画（最初）
	int					m_pointNow;			// 現在の進行ポイントの描画位置
	int					m_pointMax;			// 進行ポイントの描画（最後）
	int					m_pointMoveCnt;		// 進行ポイントの描画速度
	int					m_state;			// マップの現在の状態
	int					m_chipMin;			// マップチップの描画(最初)
	int					m_chipMax;			// マップチップの描画(最後)
	int					m_stageID;			// ステージ番号
	bool				m_threwBoss;		// ボスチップスルーフラグ
	CGameMapPointer::State	m_dir;

	D3DXVECTOR2			m_mapPosition;		// 現在のマップ座標(カメラに使用)
	D3DXVECTOR2			m_nextMapPosition;	// 移動後のマップ座標(ステージ2以降に使用)
	CVertex				m_vertex;			// 頂点座標管理

	// テクスチャ管理クラスができるまで仮でここに作成
	CTexture			m_texture;	// 画像

	// 全てのチップにカメラ座標セット
	void SetCameraPositionToAllChip(D3DXVECTOR2 _cameraPosition);
public:
	CGameMap(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pgameData,D3DXVECTOR2 _cameraPosition, int _stageID);	// コンストラクタ(デバイス、カメラ座標をセット)
	~CGameMap();
	bool Control();														// 制御
	void Draw();														// 描画
	void SetClearCount(int _clearCount);	
	CGameMapPointer* GetMapPointer();

	void SetNextPosition(int,CGameMapPointer::State _state);
};

#endif
