#ifndef _GAME_ITEM_CURSOR_H_
#define _GAME_ITEM_CURSOR_H_


class CGameItemCursor : public CGameCursor
{
public:
	enum CursorType
	{
		CUR_EQUIP,
		CUR_ITEM,
		CUR_SHOP,
	};


	static const int TEX_SHOPMENU_CURSOR	= 1;
	static const int TEX_SHOPLIST_CURSOR	= 2;
	static const int TEX_EQUIP_CURSOR		= 3;
	static const int TEX_CHAGE_EQUIP_CURSOR = 4;
public:
	CGameItemCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType);	// コンストラクタ(デバイス、座標、使用画像IDをセット)
	
	void Draw(int _changeID);
};

#endif