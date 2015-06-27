/**
 * @file DgameSaveCursor.cpp
 */

#include "stdafx.h"

CGameSaveCursor::CGameSaveCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CURSOR );
	m_rect.left		= 0;
	m_rect.top		= 108;
	m_rect.right    = 789;
	m_rect.bottom	= 237;

}