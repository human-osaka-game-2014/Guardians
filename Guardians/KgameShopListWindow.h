#ifndef _GAME_SHOPLIST_WINDOW_H_
#define _GAME_SHOPLIST_WINDOW_H_


class CGameShopListWindow : public CGameWindow
{
private:
	
	D3DXVECTOR2 CURSOR_INIT_POSITION;	// カーソル初期座標
	static const D3DXVECTOR2 SHOP_MONEY_POSITON;	// 「金額」描画座標
	static const D3DXVECTOR2 SHOP_HAS_POSITION;		// 「所持数」描画座標
	static const D3DXVECTOR2 SHOP_TOOL1_POSITION;	// 「1つ目のアイテム名」描画座標
	static const D3DXVECTOR2 SHOP_MONEY1_POSITION;	// 「1つ目のアイテム金額」描画座標
	static const D3DXVECTOR2 SHOP_HAS1_POSITION;	// 「1つ目のアイテム所持数」描画座標

	static const int MAX_ITEM_NUMBER = 9;			// 最大項目表示数
	static const int SCHROLLBAR_HIGHT =305;			//スクロールバー枠の中の高さ

	static const int MAX_WIDTH	= 740;				// ウィンドウ最大幅
	static const int MAX_HEIGHT = 585;				// ウィンドウ最大高さ

	int m_type;
	unsigned int	m_cursorPos;											
	unsigned int m_drawID;
									// 選択されているキャラのIDをセット


	CGameData*			m_pGameData;				// ゲームデータの参照
	CGameItemCursor*	m_pCursor;					// 選択用カーソル
public:
	CGameShopListWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type);	// コンストラクタ(デバイス、座標、ゲームデータ、選択されたタイプをセット)
	~CGameShopListWindow();
	void Control();																										// 制御
	void Draw();																										// 描画

	void SetCursorPosition(int _pos);// 選択されている装備のIDをセット
	void SetSelectID(int _select);
	int Sarch(int _oldID,int _No);
};

#endif