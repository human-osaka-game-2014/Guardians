/**
 * @file DgameSelecCursor.cpp
 */

#include "stdafx.h"

CGameSelectCursor::CGameSelectCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get(TEX_CURSOR);

	switch(_curType){
	case CUR_SELECT:
		m_rect.left		= 384;
		m_rect.top		= 237;
		m_rect.right    = 768;
		m_rect.bottom	= 305;
		break;
	case CUR_DATA:
		m_rect.left		= 229;
		m_rect.top		= 0;
		m_rect.right    = 403;
		m_rect.bottom	= 49;
		break;
	case CUR_SHOP:
		m_rect.left		= 0;
		m_rect.top		= 0;
		m_rect.right    = 229;
		m_rect.bottom	= 54;
	}
}