#ifndef _GAME_THINGS_WINDOW_H_
#define _GAME_THINGS_WINDOW_H_


class CGameThingsWindow : public CGameWindow
{	
private:
	static const D3DXVECTOR2 CURSOR_INIT_POSITION;	// カーソル初期座標
	static const D3DXVECTOR2 SCROLLBAR_POSITION;	// スクロールバー描画座標
	static const D3DXVECTOR2 SELECT_THING1_POSITION;// 「1つ目の選択装備(道具)」描画座標

	static const int MAX_ITEM_NUMBER = 8;			// 最大項目表示数
	static const int SCROLL_BAR_HEIGHT= 240;        // スクロールバーの高さ　　　10/13 追加
	static const int MAX_WIDTH	= 465;				// ウィンドウ最大幅
	static const int MAX_HEIGHT = 500;				// ウィンドウ最大高さ

	CGameData*			m_pGameData;				// ゲームデータの参照
	CGameItemCursor*	m_pCursor;					// 選択用カーソル
	int					m_type;						// 選択されたタイプ(装備or道具)
	int					m_charaID;					// キャラクターID
	int					m_cursorPos;				//ここでカーソル位置の取得
	int					m_drawID;


	CTexture					m_textureicon[2];
public:
	CGameThingsWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type, int _charaID = -1);	// コンストラクタ(デバイス、座標、ゲームデータ、選択されたタイプ、(キャラID)をセット)
	~CGameThingsWindow();
	void Control();																								// 制御
	void Draw();																								// 描画

	// カーソルの位置をセット
	void SetCursorPosition(int _pos);	
	// 選択されているキャラのIDをセット
	void SetSelectID(int _select);
	// 描画されている位置をセット
	void SetDrawID(int _drawID);
	// ゲームデータを取得
	CGameData* GetGameData();
};

#endif