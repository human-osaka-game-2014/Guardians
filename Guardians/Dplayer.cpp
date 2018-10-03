//12/18 �s���̊֐�����

#include "stdafx.h"

// �ÓI�ȃ����o�[�ϐ��̎��̐錾
const float CPlayer::JUMP_SPD_MAX = 0.35f;	// �W�����v�����x

const float CPlayer::INIT_HEIGHT_POSITION = -0.5f;

D3DXVECTOR3 CPlayer::m_position = INIT_PLAYER_POSITION;

//float CPlayer::m_alpha = 1.0f; // ���f���̃A���t�@�l


/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X�A���W�A�g�p��u��ID���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`�悷��ʒu(x,y)

--------------------------------------------------------------*/
CPlayer::CPlayer(LPDIRECT3DDEVICE9 _pDevice) : CCharacter(_pDevice,RIGHT_ANGLE) , m_jumpMove(0.f, -1.f), m_jumpStartPoint(-1.f),m_jumpFlag(false),m_isPlay(false)
{
	//m_step = STEP_FADE_IN;
	//m_position(D3DXVECTOR3(0.f,-1.f,-17.f));
	CScene::m_keyStateOn = 0;
	m_motionID = 0;
}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CPlayer::~CPlayer()
{
	
}
/*--------------------------------------------------------------

	����
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::Control()
{
	// �퓬�J�n���o���͈ړ��ړ����Ȃ�
	if( m_step != STEP_MOVE ) return;
	// �ҋ@���[�V�����Đ����͏�Ԃ�ҋ@��
	if( m_curMotionID == MOTION_WAIT ) m_motionState = MSTATE_WAIT;

	// ���[�V�����̏��
	switch( m_motionState ){
	case MSTATE_WAIT:
		Run();	  // ����
		avoid();  // ���
		Squat();  // ���Ⴊ��
		Jump();   // �W�����v
		Attack(); // �U��
		break;
	case MSTATE_JUMP:
		Jump();
		Run();
		break;
	case MSTATE_SQUAT:
		Squat();
		Attack();
		break;
	case MSTATE_AVOID:
		avoid();
		break;
	case MSTATE_IN_MOTION:
		Attack();
		Flinch();
		break;
	case MSTATE_AERIAL:
		Move();
		Aerial();
		Jump();
		break;
	}

	// ���S���[�V�������I����Ă����烂�[�V������i�߂Ȃ�
	if( (m_curMotionID == MOTION_DEAD &&  m_animList[MOTION_DEAD].endTime <= m_time) || (m_curMotionID == MOTION_APPEAL2 &&  m_animList[MOTION_APPEAL2].endTime <= m_time) ){
		m_motionStop = true;
	}
	// ���[�V������ύX
	if( !m_motionStop ) SetMotion( m_motionID );
	// �v���C���[�̍��W��ύX
	m_position.x += m_move.x;
	// �E��
	if( m_position.x >= CCharacter::RIGHT_WALL )
		m_position.x = CCharacter::RIGHT_WALL;
	// ����
	if( m_position.x <= CCharacter::LEFT_WALL ) 
		m_position.x = CCharacter::LEFT_WALL;


	if( m_curMotionID == MOTION_WAIT ) m_HitCount = 0;
	CScene::m_keyStateOn = 0;
	m_motionID = MOTION_WAIT;
}
void CPlayer::Flinch()
{
	// ���G
	m_invincible = true;
	// ���ݏ�Ԃ�������[�V�����̒l���g�p����
	float MOVE_DISTANCE = 5.f; // ������[�V�����ňړ����鋗��
	int TOTAL_FRAME = (int)(m_animList[MOTION_FLINCH].endTime - m_animList[MOTION_FLINCH].startTime); // ������[�V�����̃t���[����
	// 1f�̈ړ���
	float add = -0.1f;

	// ���[�V�������Ȃ烂�f����_�ł�����
	if( m_time > m_animList[MOTION_FLINCH].startTime && m_time < m_animList[MOTION_FLINCH].endTime){
		if( m_alpha > 1.0f) 
			add = add * -1;
		else if( m_alpha < 0.5f) 
			add = add * -1;
		m_alpha += add;
	// ���[�V�������I�����Ă����烿�l��߂�
	}else{
		m_alpha = 1.0f;
		// ���G����
		m_invincible = false;
	}
}
/*--------------------------------------------------------------

	�W�����v
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::Jump()
{
	// ���[�V������ύX����܂ł̃t���[��
	int DELAY_FRAME = 10;
	// �W�����v���x
	float INIT_JUMP_SPEED = 0.006f;
	static bool keyPush = false;
	static int TOTAL_FRAME = 0; // �o�ߎ���

	// �W�����v���̓W�����v�ł��Ȃ����
	if( m_motionState == MSTATE_WAIT && !m_jumpFlag && (CScene::m_keyStateOn & UP) != 0){	
		TOTAL_FRAME++;
		// �{�^���������Ă��鎞�Ԃ����ȏ�(��{�U���L�[��D�悳����)
		if(TOTAL_FRAME == DELAY_FRAME)
			m_motionID = MOTION_JUMP;
	}

	if( m_curMotionID == MOTION_JUMP && !m_jumpFlag){
		m_jumpFlag = true;
		m_jumpSpeed = JUMP_SPD_MAX;
		// �W�����v�J�n�����n�_��ۑ�
		m_jumpStartPoint = m_position.y;
	}
	// �W�����v���Ă��鎞
	if(m_jumpFlag){
		m_position.y += m_jumpSpeed;
		m_motionID = MOTION_JUMP;
		// �W�����v���x�͏�Ɉ��ʃ}�C�i�X
		m_jumpSpeed -= INIT_JUMP_SPEED;
		// �W�����v�����L�[��������Ă����痎�����x�����Z
		if( ((CScene::m_keyStateOn & DOWN) != 0) && (m_jumpSpeed < 0)) m_position.y += m_jumpSpeed;
		// ���n
		if(m_position.y <= m_jumpStartPoint){
			m_position.y = m_jumpStartPoint;
			ResetMotion(MOTION_WAIT);
			m_motionID = MOTION_WAIT;
			m_jumpFlag = false;
			TOTAL_FRAME = 0;
		}
	}


}
/*--------------------------------------------------------------

	���Ⴊ��
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::Squat()
{	
	// ���Ⴊ�ݏ�ԃt���O
	static bool isSquat = false;

	// ���Ⴊ�ݏ�Ԃ���L�[��b���Ƃ��Ⴊ�݉���
	if(  isSquat && (CScene::m_keyStateOn & DOWN) == 0 ){
		isSquat = false;
		m_motionID = MOTION_STAND_UP;
		m_motionStop = false;
	}

	if( (CScene::m_keyStateOn & DOWN) == 0) return;

	m_motionID = MOTION_SQUAT_START;
	//���Ⴊ�ݎn�߃��[�V�������I����Ă��L�[��������Ă�����
	if( m_animList[MOTION_SQUAT_START].endTime <= m_time ) 
		isSquat = true;
	// ���Ⴊ�݃��[�V�����ŃX�g�b�v
	if( isSquat ){
		m_motionID = MOTION_SQUAT;
		m_motionStop = true;
		m_move.x = 0; // �ړ��Ɠ��������x���ňړ��l��0��
	}
}
/*--------------------------------------------------------------

	����
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::Run()
{
	// �~�܂郂�[�V�����ֈȍ~����t���[����(����o�����[�V�����@�{�@���胂�[�V����)
	int STOP_FRAME = (int)((m_animList[MOTION_START_RUN].endTime - m_animList[MOTION_START_RUN].startTime) + (m_animList[MOTION_RUN].endTime - m_animList[MOTION_RUN].startTime));
	// ���[�V������ύX����܂ł̃t���[��
	int DELAY_FRAME = 5;
	static int TOTAL_FRAME = 0;
	m_move.x = 0; // �ړ��ʂ�0��
	// ���L�[�������ꂽ�Ƃ�
	if( (CScene::m_keyStateOn & LEFT) != 0){
		TOTAL_FRAME++;
		// 5�t���[��������Ă����瑖��o�����[�V������
		if( m_curMotionID != MOTION_RUN && TOTAL_FRAME >= DELAY_FRAME ) m_motionID = MOTION_START_RUN;

		if( m_curMotionID == MOTION_RUN || m_curMotionID == MOTION_START_RUN){
			Move();		// �ړ�
			m_angle = LEFT_ANGLE;		// ���胂�[�V�������̃A���O��
		}
	}

	//// �E�L�[�������ꂽ�Ƃ�
	if( (CScene::m_keyStateOn & RIGHT) != 0){
		TOTAL_FRAME++;
		// 5�t���[��������Ă����瑖��o�����[�V������
		if( m_curMotionID != MOTION_RUN && TOTAL_FRAME >= DELAY_FRAME ) m_motionID = MOTION_START_RUN;
		// ���胂�[�V�������̃A���O��
		if( m_curMotionID == MOTION_RUN || m_curMotionID == MOTION_START_RUN){
			Move();
			m_angle = RIGHT_ANGLE;
		}
	}

	// ���肾�����[�V�������I����Ă����瑖�胂�[�V�����Ɉڍs
	if( TOTAL_FRAME && m_animList[MOTION_START_RUN].endTime <= m_time ) m_motionID = MOTION_RUN;
	
	static float tmpAngle = 0; // �~�܂郂�[�V�������̈ꎟ�ۑ��p�A���O��
	// �L�[�������ꂽ��
	if( (CScene::m_keyStateOn & LEFT || CScene::m_keyStateOn & RIGHT ) == 0 ){ 
		// ���胂�[�V�������Ȃ�~�܂郂�[�V�����ֈڍs
		if( m_curMotionID == MOTION_RUN && TOTAL_FRAME >= STOP_FRAME){
			// �X�g�b�v���[�V����
			m_motionID = MOTION_STOP_RUN;
			tmpAngle = m_angle;
		}
		TOTAL_FRAME = 0; // ������Ă����t���[������0��
	}

	// �~�܂郂�[�V������
	if( m_curMotionID == MOTION_STOP_RUN ){
		m_move.x = 0;		// �ړ����Ȃ�
		m_angle = tmpAngle; // ������ς��Ȃ�
	}
}
void CPlayer::Aerial()
{
	// �r�{���L�[
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & DOWN) ){
		m_motionID = MOTION_AIR;
		ResetMotion(MOTION_AIR);
	}

}
/*--------------------------------------------------------------

	�U��
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::Attack()
{
	int oldMotion = m_motionID;
	if( m_motionState == MSTATE_IN_MOTION )
		m_move.x = 0;
	// �c�L�[
	if( (CScene::m_keyStateOn & KEY_D ) != 0 ){
		m_motionID = MOTION_SKILL;
	}
	// �c�{���L�[
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & LEFT) != 0 ){
		if( m_angle == LEFT_ANGLE )
			m_motionID = MOTION_SKILL2;
	}
	// �c�{���L�[
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & RIGHT) != 0 ){
		if( m_angle == RIGHT_ANGLE )
			m_motionID = MOTION_SKILL2;
	}
	// �c�{���L�[
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & DOWN) != 0 ){
		m_motionID = MOTION_SKILL4;
	}
	// �c�{��L�[
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & UP) != 0 ){
		m_motionID = MOTION_SKILL3;
	}


	// �r�L�[�P��
	if( ( CScene::m_keyStateOn & KEY_S) != 0 ){
		m_motionID = MOTION_ATTACK;
	}

	// �r�{���L�[
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & DOWN) != 0 ){
		m_motionID = MOTION_LOWER;
	}
	// �r�{��L�[
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & UP) ){
		//m_motionID = MOTION_UPPER;
	}

	// ���[�V������~���������[�V�����ȊO�̓t���O������
	if( m_motionStop && m_motionID != oldMotion)
		m_motionStop = false;

}
/*--------------------------------------------------------------

	���
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::avoid()
{
	float MOVE_DISTANCE = 5.f; // ������[�V�����ňړ����鋗��
	int TOTAL_FRAME = (int)(m_animList[MOTION_AVOID].endTime - m_animList[MOTION_AVOID].startTime); // ������[�V�����̃t���[����
	int MOVE_FRAME = TOTAL_FRAME - 12; // �ړ�����t���[��( ���[�V�������̈ړ����[�V������TOTAL - 12)
	float add = 0; // 1f�̈ړ���
	// ���G�t���[��
	float INVICIBLE_FRAME = 25.f;

	if( CScene::m_keyStateOn & RIGHT && CScene::m_keyStateOn & KEY_S &&  m_angle != RIGHT_ANGLE ){
		m_motionID = MOTION_AVOID;
	}

	if( CScene::m_keyStateOn & LEFT && CScene::m_keyStateOn & KEY_S && m_angle != LEFT_ANGLE ){
		m_motionID = MOTION_AVOID;
	}

	if( m_motionID == MOTION_AVOID) add = MOVE_DISTANCE / TOTAL_FRAME;
	
	SetMotion(m_motionID);

	// 25�t���[���ڂ܂ł͖��G
	if( m_curMotionID == MOTION_AVOID && m_time - m_animList[MOTION_AVOID].startTime <= INVICIBLE_FRAME )
		 m_invincible = true;
	 else
		 m_invincible = false;

	// ������[�V�������̈ړ�
	if( m_curMotionID == MOTION_AVOID && m_time - m_animList[MOTION_AVOID].startTime <= MOVE_FRAME){
		m_move.x = 0;
		if( m_angle == LEFT_ANGLE ) m_move.x += add;
		else m_move.x -= add;
	}
}
void CPlayer::Move()
{
	// ���L�[�������ꂽ�Ƃ�
	if( (CScene::m_keyStateOn & LEFT) != 0){
		m_move.x = -m_speed.x;		// �ړ���
		m_angle = LEFT_ANGLE;		// ���胂�[�V�������̃A���O��
	}
	// �E�L�[�������ꂽ�Ƃ�
	if( (CScene::m_keyStateOn & RIGHT) != 0){
		m_move.x = m_speed.x;
		m_angle = RIGHT_ANGLE;
	}
}
void CPlayer::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
/*--------------------------------------------------------------

	���
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
D3DXVECTOR3 CPlayer::GetPosition()
{
	return m_position;
}
/*--------------------------------------------------------------

	���
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CPlayer::SetEnemyPos(D3DXVECTOR3 _position)
{
	m_enemyPos = _position;
}
/*--------------------------------------------------------------

	�h��ђʃt���O
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
int CPlayer::Getflag()
{
	return !(int)true;	
}
void CPlayer::addAlpha(float _value)
{
	m_alpha += _value;
	if( m_alpha >= 1.0f ) m_alpha = 1.0f;
	if( m_alpha <= 0.f ) m_alpha = 0.f;
}