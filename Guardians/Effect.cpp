#include "stdafx.h"



CEffect::CEffect(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_angle(0)
{
	srand((unsigned)time(NULL));
}
CEffect::~CEffect()
{

}
void CEffect::SetParameter(PARTICLE* _particle)
{
	m_particle = _particle;
}
void CEffect::SetRotate(float _angle)
{
	m_angle = _angle + 90;
}
void CEffect::Control()
{
	
	// α値を増加
	m_particle->color += D3DCOLOR_ARGB((int)m_particle->addAlpha,0,0,0);

	//// α値が最大値になった時
	//if( m_particle->alpha >= 255 ){
	//	m_particle->alpha = 0;
	//}
	//// α値が0以下の時
	//if( m_particle->alpha <= 0 ) m_particle->alpha = 0;
	
	m_particle->position += m_particle->move;
}
void CEffect::Draw(CTexture _texture)
{
	D3DXMATRIX rotation;
	D3DXVECTOR3 pos = D3DXVECTOR3(m_particle->position.x,m_particle->position.y,0.f);
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(m_particle->rotate));
	m_billBoard.Draw(m_pDevice,_texture,m_particle->position,m_particle->scale,rotation,m_particle->color);
}