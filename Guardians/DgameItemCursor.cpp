/**
 * @file DgameItemCursor.cpp
 */

#include "stdafx.h"
CGameItemCursor::CGameItemCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CURSOR );
	
	switch( _curType ){
	case CUR_EQUIP:			//装備選択カーソル
		m_rect.left		= 0;
		m_rect.top		= 237;	
		m_rect.right    = 384;
		m_rect.bottom	= 305;
		break;
	case CUR_ITEM:			//装備変更カーソル
		m_rect.left		= 403;
		m_rect.top		= 0;
		m_rect.right    = 757;
		m_rect.bottom	= 54;
		break;
	case CUR_SHOP:
		m_rect.left		= 0;
		m_rect.top		= 54;
		m_rect.right    = 604;
		m_rect.bottom	= 108;
		break;
	}
}
void CGameItemCursor::Draw(int _changeID)
{
	if( _changeID < 2 ){
		m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
	}else{
		m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,403,0,757,54,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
	}
}