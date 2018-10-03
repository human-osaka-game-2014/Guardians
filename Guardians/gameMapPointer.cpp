#include "stdafx.h"

// �ÓI�ȃ����o�ϐ��̎��̉�
const FRECT CGameMapPointer::pointAnimRect[] = {
	FRECT(0.f, 0.f, 160.f, 180.f),
	FRECT(160.f, 0.f, 320.f, 180.f),
	FRECT(320.f, 0.f, 480.f, 180.f),
	FRECT(480.f, 0.f, 640.f, 180.f),
};

const int CGameMapPointer::POINT_ANIM_NO[] = {
	0, 1, 2, 3, 2, 1,
};
const D3DXVECTOR2 CGameMapPointer::m_checkPointPos[CHECK_POINT_NUM] = {
	D3DXVECTOR2(520, 2540),	// �`�F�b�N�|�C���g�X�^�[�g
	D3DXVECTOR2(570, 2482),		// �`�F�b�N�|�C���g1
	D3DXVECTOR2(656, 2406),		// �`�F�b�N�|�C���g2
	D3DXVECTOR2(715, 2300),		// �`�F�b�N�|�C���g3
	D3DXVECTOR2(772, 2120),		// �`�F�b�N�|�C���g4
	D3DXVECTOR2(794, 2027),		// �`�F�b�N�|�C���g5
	D3DXVECTOR2(771, 1951),		// �`�F�b�N�|�C���g6
	D3DXVECTOR2(856, 1735),		// �`�F�b�N�|�C���g7
	D3DXVECTOR2(700, 1663),		// �`�F�b�N�|�C���g8
	D3DXVECTOR2(627, 1518),		// �`�F�b�N�|�C���g9
	D3DXVECTOR2(604, 1281),		// �`�F�b�N�|�C���g10
	D3DXVECTOR2(706, 1151),		// �`�F�b�N�|�C���g11
	D3DXVECTOR2(794, 981),		// �`�F�b�N�|�C���g12
	D3DXVECTOR2(1028, 877),		// �`�F�b�N�|�C���g13
	D3DXVECTOR2(894, 767),	// �`�F�b�N�|�C���g14
	D3DXVECTOR2(780, 677),		// �`�F�b�N�|�C���g3
	D3DXVECTOR2(910, 505),	// �`�F�b�N�|�C���g1
	D3DXVECTOR2(882, 365),		// �`�F�b�N�|�C���g2
	D3DXVECTOR2(864, 223),		// �`�F�b�N�|�C���g3
};
const D3DXVECTOR2 CGameMapPointer::POINTER_SIZE = D3DXVECTOR2(60.f,130.f);

CGameMapPointer::CGameMapPointer(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int _clearStageNum,CGameData* _pGameData):
	CChip( _pDevice, _position, CChip::START, true ),	m_pCount(0),m_pTime(POINT_ANIME_TIME),m_state(STATE_WAIT),m_shake(0.0f),
	m_shakeSpeed(0.1f),m_shakeCount(0),m_clearCount(_clearStageNum),m_move(1.0f,1.0f)
	,m_nextPosition(595.f,2280.f),m_checkPointNum(0),m_nextCheckPointNum(1),m_backCount(1),m_pMoveTime(0),m_pGameData(_pGameData)
{
	m_position = D3DXVECTOR2(m_checkPointPos[_clearStageNum].x - 60,m_checkPointPos[_clearStageNum].y - 130);
	m_pointTexture = CTexMgr.Get( TEX_MAP_CHIP );

	//m_position.push_back(D3DXVECTOR2(510.f, 2360.f));
	//m_position.push_back(D3DXVECTOR2(595.f, 2280.f));
	//m_position.push_back(D3DXVECTOR2(655.f, 2170.f));

	//m_staticPosition.push_back(D3DXVECTOR2(510.f, 2360.f));
	//m_staticPosition.push_back(D3DXVECTOR2(595.f, 2280.f));
	//m_staticPosition.push_back(D3DXVECTOR2(655.f, 2170.f));
}

void CGameMapPointer::Control()
{
	//�|�C���^�_�ŃA�j���[�V����
	m_pTime--;
	if(m_pTime == 0){
		m_pCount = (m_pCount+1)%( sizeof(POINT_ANIM_NO) / sizeof(int) );
		m_pTime = ANIME_TIME;
	}
	//�|�C���^�㉺�ړ�
	m_shakeCount++;
	m_shake -= m_shakeSpeed;
	if(m_shakeCount == MOVE_TIME/2){
		m_shakeSpeed *= -1.0f;
		m_shakeCount = 0;
	}
	switch( m_state ){
	// �|�C���^���ړ�
	case STATE_MOVE:
		m_position += m_move;
		m_pMoveTime++;
		if( m_pMoveTime >= POINTER_MOVE_FRAME )
			m_position = m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE;
		break;
	case STATE_MOVE_RIGHT:
		// �|�C���^�̈ړ��ʂ����߂�
		m_move = ((m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE) - m_position) / POINTER_MOVE_FRAME;

		// ��Ԃ��ړ���Ԃ�
		m_state = STATE_MOVE;
		break;
	case STATE_MOVE_LEFT:
		// �|�C���^�̈ړ��ʂ����߂�
		m_move = ( (m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE) - m_position) / POINTER_MOVE_FRAME;

		// ��Ԃ��ړ���Ԃ�
		m_state = STATE_MOVE;

		break;
	};
	// �|�C���^�[�̈ʒu���`�F�b�N�|�C���g�̈ʒu�Ɠ����Ȃ�ҋ@��Ԃɖ߂�
	if( m_position == (m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE)){
		m_state = STATE_WAIT;
		m_pMoveTime = 0;
	}

}

void CGameMapPointer::Draw()
{
	// �ړ���ԈȊO�Ȃ�|�C���^���A�j���[�V����������
	if(m_state != STATE_MOVE){
		m_vertex.DrawTextureLT(m_pDevice, m_pointTexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y + m_shake,
		pointAnimRect[POINT_ANIM_NO[m_pCount]]);
	}else{
		m_vertex.DrawTextureLT(m_pDevice, m_pointTexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, 
		pointAnimRect[0]);
	}
}

void CGameMapPointer:: SetClearCount(int _clearCount)
{
	m_clearCount = _clearCount;
}

void CGameMapPointer::SetMoveDirection(State _state)
{
	// �|�C���^���ҋ@��ԂȂ�ړ���Ԃ�
	if( m_state == STATE_WAIT ) m_state = _state;
	
	if( m_state == STATE_MOVE_LEFT ){
		// �I�����Ă���X�e�[�W�ԍ������炷
		m_pGameData->m_selectStageNum--;
		if( m_pGameData->m_selectStageNum < 0 )
			m_pGameData->m_selectStageNum = 0;
	}else if( m_state == STATE_MOVE_RIGHT ){
		// �I�����Ă���X�e�[�W�ԍ������炷
		m_pGameData->m_selectStageNum++;
		if( m_pGameData->m_selectStageNum > m_pGameData->m_nowClearStageNum )
			m_pGameData->m_selectStageNum = m_pGameData->m_nowClearStageNum;
	}
}

CGameMapPointer::State CGameMapPointer::GetState()
{
	return  m_state;
}