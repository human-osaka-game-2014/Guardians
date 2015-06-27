/**
 * @file DgameMenuCursor.cpp
 */

#include "stdafx.h"

CGameMenuCursor::CGameMenuCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_FIELD_MENU );
	m_flickFlag = false;	// このカーソルは点滅させない
	m_rect.left		= 140;
	m_rect.top		= 200;
	m_rect.right	= 185;
	m_rect.bottom	= 345;
}