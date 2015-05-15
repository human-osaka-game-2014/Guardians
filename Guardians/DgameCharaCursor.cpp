/*--------------------------------------------------------------

	処理内容:カーソル(キャラクター)の制御
	作成者:檀上
	作成日:9/23
	更新日:9/23
	更新内容:
	関数　
		コンストラクタの追加
	変数　

--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	コンストラクタ(デバイス、座標、使用画像IDをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス
	@param D3DXVECTOR2			描画する位置(x,y)

--------------------------------------------------------------*/
CGameCharaCursor::CGameCharaCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CHARA_MENU );
	m_rect.left		= 0;
	m_rect.top		= 128;
	m_rect.right	= 140;
	m_rect.bottom   = 268;
}