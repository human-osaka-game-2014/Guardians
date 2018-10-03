#include "stdafx.h"

CEnemy::CEnemy(LPDIRECT3DDEVICE9 _pDevice) : CCharacter(_pDevice,0) , m_pDevice(_pDevice) ,m_discovered(false) , m_fieldPosition( D3DXVECTOR3(0.f,0.f,0.f))
{
	m_angle = RIGHT_ANGLE;
	//m_actionGauge++; // �s���l����
	//if( m_actionGauge > ACTION_GAUGE_MAX)
	//	m_actionGauge = ACTION_GAUGE_MAX;
		// �s���l��0�ɂȂ����ꍇ
	//if( m_actionGauge <= 0){
	//	ResetMotion( MOTION_HIT );	// �s���l��0�ɂȂ����狯�݃��[�V����
	//	m_actionGauge = 0;
	//}
}
CEnemy::~CEnemy()
{

}
/*--------------------------------------------------------------

	�v���C���[�̈ʒu���Z�b�g
	@param	D3DXVECTOR3 �@�ʒu
	@return �Ȃ�

--------------------------------------------------------------*/
void CEnemy::SetPlayerPos(D3DXVECTOR3 _position)
{
	m_playerPos = _position;
}
void CEnemy::SetFieldPosition(D3DXVECTOR2 _position)
{
	m_fieldPosition.x = _position.x;
	m_fieldPosition.y = _position.y;
}
void CEnemy::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
CGameData::ENEMY_STATUS CEnemy::GetStatus()
{
	return m_status;
}