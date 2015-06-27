/**
 * @file DgameCharaCursor.h
 */

/**
 * キャラクター選択用のカーソルの制御
 */

#ifndef _GAME_CHARA_CURSOR_H_
#define _GAME_CHARA_CURSOR_H_

class CGameCharaCursor : public CGameCursor
{
private:
#define TEX_GAME_CHARA_CURSOR 6
public:
	CGameCharaCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// コンストラクタ(デバイス、座標をセット)

};

#endif