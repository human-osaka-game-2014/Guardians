#ifndef _GAME_SELECT_CURSOR_H_
#define _GAME_SELECT_CURSOR_H_

class CGameSelectCursor : public CGameCursor
{
private:
	static const int TEX_GAME_SELECT_CURSOR = 0;
public:
	enum CursorType
	{
		CUR_SELECT,
		CUR_DATA,
		CUR_SHOP,
	};
	// コンストラクタ(デバイス、座標をセット)
	CGameSelectCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType);	
};

#endif