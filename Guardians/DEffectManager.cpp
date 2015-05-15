#include "stdafx.h"
#include <time.h>

CEffectManager::CEffectManager(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice) ,m_drawTime(0),m_isPlay(false),m_endTime(0),m_angle(0)
{
	m_efk = new CEffect(m_pDevice);
}
CEffectManager::~CEffectManager()
{
	SAFE_DELETE(m_efk);
}
bool CEffectManager::GetExists()
{
	return  m_drawTime > 0 && m_drawTime < m_endTime;
}
D3DXVECTOR3 CEffectManager::GetPosition()
{
	return m_position;
}
void CEffectManager::Erase()
{

}