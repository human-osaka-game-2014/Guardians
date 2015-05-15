#ifndef _PREPARE_MISSION_H_
#define _PREPARE_MISSION_H_

class CPrepareMission : public CScene
{
public:
		CGameMapPointer*	m_mapPointa;

	enum {
		CHIP_MAX = 25,		// チップ19+ボス6
		PIC_CHARA_MAX = 20,	// 文字画像種類数
		STAGE_MAX = 18,		// 各ステージチェックポイント2, ボス1で6ステージ分
	};

	enum MenuType		// メニューの種類
	{
		MENU_MAP,
		MENU_STATUS,
		MENU_SHOP,
		MENU_SAVE,

		MENU_MAX,
	};

	enum TelopType
	{
		TELOP_STAGE,
		TELOP_BOSS,
	};
	enum MenuBarType
	{
		BAR,
		BAR_ICON,

		BAR_MAX,
	};

	struct ChipData {
		D3DXVECTOR2 position;
		CChip::ChipType type;
	};

	struct CharaPictureData {
		D3DXVECTOR2 position;
		int textureID;
		CCharaPicture::Type typeID;
	};

	std::vector<CTexString*> m_strLst;
	std::vector<bool> m_isSelLst;

private:
	
	static const ChipData CHIP_DATA[];
	static const CharaPictureData CH_PIC_DATA[];
	static const int 	TELOP_TYPE_NUM = 2;

	LPDIRECT3DDEVICE9	m_pDevice;					// 描画デバイス
	D3DXVECTOR2			m_mapPosition;				// 現在のマップ座標(カメラに使用)
	D3DXVECTOR2			m_nextMapPosition;			// 移動先マップ座標(ステージクリアした際の演出用)
	CGameMenuCursor*	m_pCursor;					// カーソルクラス(メニュー）
	CGameTelop**		m_pTelop;				// ゲームテロップ
	CGameDataWindow*	m_pWindow;					// ゲームウィンドウクラス
	CMenuScreen*		m_pScreen;					// メニュー画面クラス
	CGameMap*			m_pMap;						// マップクラス
	CGameMapPointer*	m_pMapPointer;				// マップポインタ―クラス
	CCharaPicture*		m_pPicChara[PIC_CHARA_MAX];	// 文字画像表示クラス
	CMenuBar**			m_menuBar;
//	CChip				m_chip;
	CGameData*			m_pGameData;				// ゲームデータクラスの参照
	State				m_state;					// 画面の状態
	State				m_oldState;					// １つ前の画面の状態
	bool				m_clearPoint[STAGE_MAX];	// ステージクリアフラグ
	int					m_menuID;					// メニュー番号（キャラ出撃選択/ステータス/ショップ/セーブ)
	int					m_stageID;					// ステージ番号
	int					m_clearCount;
	void SelectStage();								// ステージセレクト
public:
	CPrepareMission(LPDIRECT3DDEVICE9 _pDevice,CGameData* m_pGameData,CInput* _input);	// コンストラクタ(デバイスをセット)
	~CPrepareMission();								// デストラクタ
	SceneID Control();									// 制御
	void Draw();									// 描画

	// アクセッサ
	int* GetTurnNo();								// 出撃順番取得
};

#endif