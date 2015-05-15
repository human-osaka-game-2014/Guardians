#include "stdafx.h"

/*--------------------------------------------------------------

	処理内容:アイテム、アクセサリーの表示
	作成者:岸
	作成日:10/07
	更新日:10/09
	  描画座標の修正

	関数　
		drawの作成
	変数　
		追加なし

--------------------------------------------------------------*/

CGameShopMenuWindow::CGameShopMenuWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) :
CGameWindow( _pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT) )
{
}

void CGameShopMenuWindow::Control()
{
	CGameWindow::Control();
}

void CGameShopMenuWindow::Draw()
{
	CGameWindow::Draw();
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-55, m_position.y-65,0,620,256,652);		//アイテムの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-85, m_position.y+5,0,652,256,684);		//アクセサリーの表示
}