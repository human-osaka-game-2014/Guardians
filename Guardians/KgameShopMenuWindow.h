#ifndef _GAME_SHOPMENU_WINDOW_H_
#define _GAME_SHOPMENU_WINDOW_H_


class CGameShopMenuWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 CURSOR_INIT_POSITION;		// カーソル初期座標
	static const D3DXVECTOR2 MENU_TOOLS_POSITION;		// メニュー「アイテム」描画座標
	static const D3DXVECTOR2 MENU_ACCESSORY_POSITION;	// メニュー「アクセサリ」描画座標

	static const int MAX_WIDTH	= 290;			// ウィンドウ最大幅
	static const int MAX_HEIGHT = 250;			// ウィンドウ最大高さ

	CGameItemCursor*	m_pCursor;			// 選択用カーソル
	SelectType			m_type;				// 選択されたタイプ(アイテムorアクセサリ)
public:
	CGameShopMenuWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);		// コンストラクタ(デバイス、座標をセット)
	void Control();																// 制御
	void Draw();																// 描画

	// アクセッサ
	SelectType GetItemType();													// 選択されている項目のタイプを取得
};

#endif