#include "stdafx.h"

CMenuScreen::CMenuScreen(LPDIRECT3DDEVICE9 _pDevice) :
	m_pDevice( _pDevice ), m_state( STATE_MOVE ),m_equipID( 0 )
{

}

CMenuScreen::~CMenuScreen()
{

}