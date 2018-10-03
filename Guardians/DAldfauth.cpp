/**
 * @file DAldfauth.cpp
 * @author �h��
 */

#include "stdafx.h"

/**
 * �R���X�g���N�^
 * @param _pDevice �f�o�C�X�I�u�W�F�N�g
 */
CAldfauth::CAldfauth(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	// ���f���̃X�P�[��
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_1_Aldfauth.X"),m_pDevice,m_scale);

	m_efk = new CAldEffect(m_pDevice);

	// �g�p�����`���쐬
	CreateBox();

		// ���[�V�����̊J�n���ԂƏI������
	double Animation[MOTION_MAX_NUM][2] = {
	// StartTime�@,EndTime
		{0, 69},// 00) �ҋ@
		{70, 99},// 01) ����o��
		{100, 149},	// 02) ����
		{150, 179},	// 03) �~�܂�
		{190, 235},	// 04) �W�����v(190	-235�㏸�@235-250 250-270���~�i�J��Ԃ��\���j 290-299 ���n)
		{235, 270},	// 05) �W�����v���n(190-235�㏸�@235-250 250-270���~�i�J��Ԃ��\���j 290-299 ���n)
		{300, 310},	// 06) ���Ⴊ��
		{310, 339},	// 07) ���Ⴊ�ݒ�
		{340, 349},	// 08) ���Ⴊ�݉���
		{350, 380},	// 09) �ً}���
		{380, 415},	// 10) �ʏ�U�� (390-395-400�Ńp���`�@400�܂łɃ{�^�����͂ŘA��)
		{420, 450},	// 11) �ʏ�U���A��1�F (425-430-435�Ńp���`�@440�܂łɃ{�^�����͂ŘA��)
		{455, 510},	// 12) �ʏ�U���A��2�F (470-475-480�Ńp���`)
		{510, 550},	// 13) ��U�� (525-535�Ńp���`)
		{555, 585},	// 14) ���U��  (560-580�œːi)
		{590, 640},	// 15) ���U���i�󒆁j610�ŌŒ�^�̓�����@�ڒnor�Փ˂ő����Đ��@�Փˎ���625�ōs���\�i���������[�V�����֌q���� �j
		{640, 680},	// 16) �Z1 �@����ł��@655-660�Ŕ���
		{680, 710},	// 17) �Z2 �@�ːi�p���`�@690-700�œːi
		{710, 755},	// 18) �Z3 �@�Ή��A�b�p�[�@720-740�ŏ㏸�{�A�b�p�[�@���[�V�����I�����ɗ������[�V�����Ɍq����
		{760, 815},	// 19) �Z4 �@��U���@780-805�Ŋ�@�I�����͂��Ⴊ�ݏ��
		{820, 855},	// 20) �Z4�i�󒆁j�@������U���@ 835�ŌŒ�{�}�~���@�ڒn�ő����Đ� �ڒn-850�Ɋ�@�I�����͂��Ⴊ�ݏ��
		{860, 890},	// 21) �_���[�W��炢
		{890, 1000},	// 22) ���S
		{1005, 1034},	// 23) �X�^��
		{1040, 1135},	// 24) �ŗL���[�V����1�i�퓬�J�n���p�j
		{1135, 1255},	// 25) �ŗL���[�V����2�i�������j
	};

	m_animList.resize(MOTION_MAX_NUM);
	// �z��Ƀ��[�V�������Ԃ��Z�b�g
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		if( i == MOTION_SQUAT_START || i == MOTION_SQUAT || i == MOTION_WAIT || i == MOTION_START_RUN || i == MOTION_RUN )
			m_animList[i].chancel = true; // ����̃��[�V�����̓L�����Z���\
		else
			m_animList[i].chancel = false;
	}
	// �A�j���[�V�����z����Z�b�g
	m_model->SetAnimList(&m_animList);
	// �ҋ@���[�V�������Z�b�g
	m_model->ChangeMotion( MOTION_WAIT );
	// �W�����v���J�n����t���[��
	m_jumpStartFrame = 3;
}

/**
 * �f�X�g���N�^
 */
CAldfauth::~CAldfauth()
{
	SAFE_DELETE(m_model);
	SAFE_DELETE(m_efk);

	for(unsigned i = 0; i < m_box.size(); i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}

/**
 * �`��
 */
void CAldfauth::Draw()
{
	// ���f���̃��l���Z�b�g
	m_model->SetColor(m_alpha);
	// ���f������
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	// ���f���̕`��
	m_model->Draw(m_position,rotation);
	
	// ��`�̕`��
	DrawBox(m_box);

	UpdateAnimTime();
}
/**
 * �G�t�F�N�g�̕`��
 */
void CAldfauth::DrawEffect()
{
	if( m_isHit ) m_efk->Stop(m_curMotionID);
	// �G�t�F�N�g�̐���
	m_efk->Draw();
}
/**
 * ���[�V������ύX
 * @param _motionID ���[�V�����ԍ�
 */
void CAldfauth::SetMotion(int _motionID)
{
	// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;

		m_efk->Create(GetBonePos("R_wrist"),m_curMotionID,m_angle);
	}

	// ���[�V�������ɏ�Ԃ�ς���
	switch( m_curMotionID )
	{
	case MOTION_WAIT:			//1.	�ҋ@
		m_state = STATE_WAIT;
		m_motionState = MSTATE_WAIT;
		break;
	case MOTION_START_RUN:			//2.	����o��
	case MOTION_RUN:			//3.	����
	case MOTION_STOP_RUN:			//4.	�~�܂�
		m_state = STATE_RUN;
		m_motionState = MSTATE_WAIT;
		break;
	case MOTION_JUMP:			//5.	�W�����v
	case MOTION_JUMP_FALL:
		m_state = STATE_JUMP;
		m_motionState = MSTATE_AERIAL;
		break;
	case MOTION_SQUAT_START:		//6.	���Ⴊ��
	case MOTION_SQUAT:		//7.	���Ⴊ�ݒ�
	case MOTION_STAND_UP:		//8.	���Ⴊ�݉���
		m_state = STATE_SQUAT;
		m_motionState = MSTATE_SQUAT;
		break;
	case MOTION_AVOID:		//9.	�ً}���
		m_state = STATE_AVOID;
		m_motionState = MSTATE_AVOID;
		break;
	case MOTION_FLINCH:			//22.	�_���[�W��炢
	case MOTION_DEAD:			//23.	���S
	case MOTION_STUN:			//24.	�X�^��
	case MOTION_APPEAL:		//25.	�ŗL���[�V����1�i�퓬�J�n���p�j
	case MOTION_APPEAL2:		//26.	�ŗL���[�V����2�i�������j
		m_motionState = MSTATE_IN_MOTION;
		m_state = STATE_WAIT;
		break;
	default:
		m_state = STATE_ATTACK;
		m_motionState = MSTATE_IN_MOTION;
	}
	// ���G��ԂȂ�State�𖳓G��
	if( m_invincible ) 
		m_state = STATE_INVICIBLE;

	SetRect();

	ControlRect();

	m_efk->Control();
}
/**
 * �Փ˔����`�̐���
 */
void CAldfauth::ControlRect()
{
		// ���[�V�������ɏ�Ԃ�ς���
	switch( m_curMotionID )
	{
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_ATTACK2:	//11.	�ʏ�U���A��1
	case MOTION_ATTACK3:	//12.	�ʏ�U���A��2
		m_correctionValue = 1.f;
		UpdateRect("R_wrist",BOX_ATTACK);
		m_hitting_box[0] = m_box[BOX_ATTACK];
		break;
	case MOTION_SKILL:		//16.	�Z1
		m_correctionValue = 0.5f;
		UpdateRect( m_efk->GetPosition(m_curMotionID,(int)(m_animList[m_curMotionID].endTime - m_time)),BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_SKILL2:		//17.	�O�{�Z
		m_correctionValue = 1.3f;
		UpdateRect("R_wrist",BOX_ATTACK);
		m_hitting_box[0] = m_box[BOX_ATTACK];
		break;
	case MOTION_UPPER:		//13.	��U��
		m_correctionValue = 1.3f;
		UpdateRect("R_wrist",BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_LOWER:		//14.	���U��
		m_correctionValue = 0.f;
		Rush();
		break;
	case MOTION_AIR:			//15.	���U���i�󒆁j
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILL3:		//18.	��{�Z
		m_correctionValue = 1.0f;
		UpdateRect("R_wrist",BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_SKILL4:		//19.	���{�Z
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILLAIR:		//20.	���{�Z�i�󒆁j
		m_correctionValue = 0.f;
	//case MOTION_SPECIAL:		//21.	�K�E�Z
		m_state = STATE_ATTACK;
		m_motionState = MSTATE_IN_MOTION;
		break;
	}
	// �{�f�B��`����ɍX�V(���ꔻ��)
	UpdateRect("pelvis",BOX_BODY);
}


/**
 * �ːi
 */
void CAldfauth::Rush()
{
	static float MOVE_DISTANCE = 20.f;	// �ړ�����
	static float MOVE_FRAME = 60;		// �ړ�����
	static float ADD = MOVE_DISTANCE / MOVE_FRAME;	// 1f�̈ړ���
	
	// �ړ�
	if( m_curMotionID == MOTION_LOWER && m_time - m_animList[MOTION_LOWER].startTime <= MOVE_FRAME){
		if( m_angle == LEFT_ANGLE ) m_move.x -= ADD;
		else m_move.x += ADD;
	}
}
/**
 * �Փ˔���Ɏg�p����{�b�N�X�𐶐�
 */
void CAldfauth::CreateBox()
{
	XFileAnimationMesh::BOX	box;
	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(40.0f,20.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(70.0f,120.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}
/*-----------------------------------------------------------------

	R_elbow
	R_uarm

	R_wrist

-------------------------------------------------------------------*/
