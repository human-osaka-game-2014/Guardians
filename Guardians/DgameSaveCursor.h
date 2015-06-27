/**
 * @file DgameSaveCursor.h
 */

/**
 * セーブ画面選択用のカーソルの制御
 */


#ifndef _GAME_SAVE_CURSOR_H_
#define _GAME_SAVE_CURSOR_H_


class CGameSaveCursor : public CGameCursor
{
private:
	
public:
	CGameSaveCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// コンストラクタ(デバイス、座標をセット)
};

#endif