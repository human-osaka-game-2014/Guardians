#include "stdafx.h"


CMenuBar::CMenuBar(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_oldState( m_state )
{
	m_texture[TEX_BAR] = CTexMgr.Get( TEX_FIELD_MENU );
	
	m_texture[TEX_ICON] = CTexMgr.Get( TEX_BUTTON_ICON );


}
CMenuBar::~CMenuBar()
{ 
}
void CMenuBar::Draw(int _state)
{
	// 上メニューバーの描画
	m_vertex.SetSizeX(1.1f);
	m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_BAR],70,0,0,925,605,966);
	m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_BAR],670,0,0,967,605,1008);
	m_vertex.SetSizeX(1.0f);
	// 横メニューバーの描画
	m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_BAR],0,0,70,200,140,920);

}