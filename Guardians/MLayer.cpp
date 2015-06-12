#include "stdafx.h"

CLayer::CLayer(LPDIRECT3DDEVICE9 _pDevice,  D3DXVECTOR3 _position, int _stageID) : m_pDevice( _pDevice ), m_position( _position ), m_speed( 0.f, 0.f ), m_plane( nullptr ), m_initPosition( _position ),m_angle(0,0,-90)
{


}

CLayer::~CLayer()
{
	SAFE_DELETE(m_plane);
}

void CLayer::Control()
{
	m_position.x += m_speed.x;
	m_position.y += m_speed.y;
}

void CLayer::Draw()
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	//static D3DXVECTOR3 m_vecScale = D3DXVECTOR3( 15.f,140.f,1.f);
	//m_plane->SetScale(m_vecScale);

	//static float scale = 0;
	//static D3DXVECTOR3 m_position = D3DXVECTOR3(-90,17,1);
	//m_plane->SetPosition(m_position);
	m_plane->SetAngle(m_angle);
	m_plane->Draw( m_position, matrix);
}

void CLayer::SetPosition(D3DXVECTOR2 _position)
{
	m_position = m_initPosition;
}

D3DXVECTOR3 CLayer::GetPosition()
{
	return m_position;
}

void CLayer::SetInitPosition()
{
	// y‚¾‚¯
	m_position.y = m_initPosition.y;
}