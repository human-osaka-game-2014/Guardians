/**
 * @file DgameCharaCursor.cpp
 */
#include "stdafx.h"

CGameCharaCursor::CGameCharaCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CHARA_MENU );
	m_rect.left		= 0;
	m_rect.top		= 128;
	m_rect.right	= 140;
	m_rect.bottom   = 268;
}