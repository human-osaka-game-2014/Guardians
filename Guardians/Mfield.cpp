#include "stdafx.h"

CField::CField(LPDIRECT3DDEVICE9 _pDevice , int _stageID) : m_isHit(false), m_position(0.f, 0.f) , m_speed(0.f,0.f)
{
	m_layer = new CLayer*[LAYER_TYPE_NUM];
	
	m_layer[LAY_1] = new CLayer1(_pDevice,_stageID);
	m_layer[LAY_2] = new CLayer2(_pDevice,_stageID);
	m_layer[LAY_3] = new CLayer3(_pDevice,_stageID);
	m_layer[LAY_4] = new CLayer4(_pDevice,_stageID);
	m_layer[LAY_5] = new CLayer5(_pDevice,_stageID);
	m_layer[LAY_6] = new CLayer6(_pDevice,_stageID);
	m_layer[LAY_7] = new CLayer7(_pDevice,_stageID);
}
CField::~CField()
{
	for( int i = 0; i < LAYER_TYPE_NUM; i++ ){
		SAFE_DELETE(m_layer[i]);
	}

	SAFE_DELETE_ARRAY(m_layer);

}

void CField::Control()
{
	for( int i = 0; i < LAYER_TYPE_NUM; i++ ){
		m_layer[i]->SetCharaSpeed(m_speed);
		m_layer[i]->Control();
	}

	m_keyStateOn = 0;
}
void CField::Load(LPDIRECT3DDEVICE9 _pDevice,int _stageID)
{
	m_layer = new CLayer*[LAYER_TYPE_NUM];
	
	m_layer[LAY_1] = new CLayer1(_pDevice,_stageID);
	m_layer[LAY_2] = new CLayer2(_pDevice,_stageID);
	m_layer[LAY_3] = new CLayer3(_pDevice,_stageID);
	m_layer[LAY_4] = new CLayer4(_pDevice,_stageID);
	m_layer[LAY_5] = new CLayer5(_pDevice,_stageID);
	m_layer[LAY_6] = new CLayer6(_pDevice,_stageID);
	m_layer[LAY_7] = new CLayer7(_pDevice,_stageID);
}
void CField::Draw()
{
	for( int i = 0; i < LAYER_TYPE_NUM; i++ ){
		m_layer[i]->Draw();
	}

}

void CField::SetCharaSpeed(D3DXVECTOR2 _speed)
{
	m_speed = _speed;
}

void CField::SetKeyState(int _keyState)
{
	m_keyStateOn = _keyState;
}
bool CField::GetHitFlag()
{
	return m_isHit;
}

void CField::SetHitFlag(bool _isHit)
{
	m_isHit = _isHit;

	if( m_position.x <= -6.f ) {
		m_position.x += 0.05f;
	}
	if( m_position.x >= 8.f ) {
		m_position.x -= 0.05f;
	}
}

D3DXVECTOR2 CField::GetPosition()
{
	return m_position;
}
D3DXVECTOR2 CField::GetFieldSpeed()
{
	return m_speed;
}

void CField::SetPlayerInfo(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}
void CField::SetPosition( D3DXVECTOR2 _position ) 
{
	for(int i = 0; i < LAYER_TYPE_NUM; i++){
		m_layer[i]->SetPosition(_position);
	}
}