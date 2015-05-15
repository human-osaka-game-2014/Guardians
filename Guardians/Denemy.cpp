#include "stdafx.h"

CEnemy::CEnemy(LPDIRECT3DDEVICE9 _pDevice) : CCharacter(_pDevice,0) , m_pDevice(_pDevice) ,m_discovered(false) , m_fieldPosition( D3DXVECTOR3(0.f,0.f,0.f))
{
	m_angle = RIGHT_ANGLE;
	//m_actionGauge++; // 行動値を回復
	//if( m_actionGauge > ACTION_GAUGE_MAX)
	//	m_actionGauge = ACTION_GAUGE_MAX;
		// 行動値が0になった場合
	//if( m_actionGauge <= 0){
	//	ResetMotion( MOTION_HIT );	// 行動値が0になったら怯みモーション
	//	m_actionGauge = 0;
	//}
}
CEnemy::~CEnemy()
{

}
/*--------------------------------------------------------------

	プレイヤーの位置をセット
	@param	D3DXVECTOR3 　位置
	@return なし

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