/**
 * @file DmenuSelectScreen.h
 */

/**
 * ショップ画面の管理
 */

#ifndef _MENU_SHOP_SCREEN_H_
#define _MENU_SHOP_SCREEN_H_

class CMenuShopScreen : public CMenuScreen
{
public:
	static const int CURSOR_TYPE_NUM = 2;	// カーソルの種類は2個
	static const int TELOP_TYPE_NUM = 1;	// テロップの種類は1個
	static const int WINDOW_TYPE_NUM = 2;	// ウィンドウの種類は2個
	static const int MAX_POSSESSION = 9;	// アイテムの最大所持数
	enum TelopType
	{
		TELOP_EXPLAIN,
	};

	enum CursorType
	{
		CUR_MENU,
		CUR_SHOP,
	};

	enum WindowType
	{
		WND_SHOPMENU,
		WND_SHOPLIST,
	};

	enum ShopState
	{
		STATE_SELECT_SHOPMENU = 2,	// ショップメニュー選択
		STATE_WINDOW_SHOPLIST,		// ショップリスト選択
		STATE_OPEN_SHOPLIST,		// ショップリストが開いていく
	};
	// 選択された項目
	enum SELECT_ITEM
	{
		TOOLS,
		EQUIP,
	};
private:
	int		m_drawID;		// 描画番号
	int		m_charaID;		// 選択されているキャラ番号
	int		m_itemNum;		// 所持しているアイテムの種類数
	int		m_oldID;		// 選択されていた項目の番号
	
	ShopState m_state;		// 状態
public:
	CMenuShopScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData);
	~CMenuShopScreen();
	void Control(int _keyState);
	void Draw();
private:
	void Search(int _oldID,int _No); // 購入時に所持しているか調べる

	void OpenWindow();		// ウインドウの生成
	void DeleteWindow();	// ウインドウの削除
};

#endif