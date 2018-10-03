/**
 * @file DMaru.cpp
 */

#include "stdafx.h"
/**
 * �R���X�g���N�^
 * @param _pDevice �`��f�o�C�X
 * @return �Ȃ�
 */
CMaru::CMaru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)  , m_alpha(1.0f)
{
	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_2-2_Maru.X"),m_pDevice,m_scale);

	m_motionStop = false;

	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	m_position = D3DXVECTOR3(-5.f,-0.5f,0.f);

	// �g�p�����`���쐬
	CreateBox();

	// ���[�V�����̊J�n���ԂƏI������
	double Animation[MOTION_MAX_NUM][2] = {
	// StartTime�@,EndTime,�@ChancelFlag
		{0,59},			// �ҋ@
		{60,114},			// ����o��
		{115,169},			// ����
		{170,219},		// �~�܂�
		{220,285},		// �W�����v�㏸(230-285�㏸�@285-300 300-320���~)
		{285,320},				// �W�����v���~(230-285�㏸�@285-300 300-320���~)
		{350,359},			// ���Ⴊ��
		{360,389},			// ���Ⴊ�ݒ�
		{390,399},		// ���Ⴊ�݉���
		{400,430},		//9.	400-430	�ً}���
		{430,460},		//10.	430-460 �ʏ�U���i-444�\���@445-450���ˁ@451-460�̃��[�V������15frame�����ď󋵂ɉ������ҋ@�����[�V�����ֈڍs�@�A������5frame��440�t���[���ڂ̃��[�V�����Ɉڍs���ȍ~�ʏ펞�̗���ցj
		{430,460},		//11.	 �ʏ�U���A��1�F�Ȃ�
		{430,460},		//12.	 �ʏ�U���A��2�F�Ȃ�
		{465,495},		//13.	 465-495 ��U���i-479�\���@480-4985���ˁ@486-495�ҋ@�֘A�����̏����͒ʏ�U���Ɠ����j
		{500,535},		//14.	 500-535 ���U���@�i510�\���@510-520�U���j
		{540,570},		//15.	 540-570 ���U���i�󒆁j�i550�\���@550-555���ˁ@555-565�̃��[�V������15frame�����ď󋵂ɉ������ҋ@�����[�V�����ֈڍs�A�����̏����͒ʏ�U���Ɠ����j
		{575, 625 },	// 16) �Z1 �X�ǁ@�i605�Ŕ��ˁj
		{625, 675 },	// 17) �Z2 �Ή��e�@(655�Ŕ���)
		{675, 720 },	// 18) �Z3 �e���|��(685-700�Ńt�F�[�h�A�E�g�@700-715�Ńt�F�[�h�C��)							
		{725, 795 },	// 19) �Z4 ��U�� (755�Ŕ���)
		{800, 845 },	// 20) �Z4�i�󒆁j �e���|�� (810-825�Ńt�F�[�h�A�E�g�@825-840�Ńt�F�[�h�C��)
		{845, 875 },	// 21) �_���[�W��炢
		{875, 990 },	// 22) ���S
		{995, 1045},	// 23) �X�^��
		{1050, 1145 },	// 24) �ŗL���[�V����1�i�퓬�J�n���p�j
		{1145, 1265 },	// 25) �ŗL���[�V����2�i�������j
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

}
void CMaru::SetStopMotion(bool _flag)
{
	m_motionStop = _flag;
}

/**
 * �{�b�N�X�𐶐�
 */
void CMaru::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}

/**
 * �f�X�g���N�^
 */
CMaru::~CMaru()
{
	SAFE_DELETE(m_model);

	for( unsigned i = 0; i < m_box.size();i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}

/**
 * �`��
 */
void CMaru::Draw()
{
	// ��]
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	
	m_model->Draw(m_position,rotation);

	//SetRect();
	// �{�f�B(���ꔻ��)
	UpdateRect("pelvis",0);
	
	UpdateAnimTime();
}

void CMaru::Move( D3DXVECTOR3 _position , int _motionID ,int _angle)
{
	m_neruPos = _position;
	// ���[�V������ύX
	SetMotion( _motionID );

	// �l���Ƃ̊Ԋu
	static int SPACE = 1;
	static float moveSpeed = 0.06f;

	if( m_motionStop ) return;

	if( _angle == LEFT_ANGLE ){
		if( m_position.x  <= _position.x + SPACE )
			m_position.x += moveSpeed;
		else 
			m_position.x = _position.x + SPACE;
		m_angle = LEFT_ANGLE;
	}else{
		if( m_position.x  >= _position.x - SPACE )
			m_position.x -= moveSpeed;
		else 
			m_position.x = _position.x - SPACE;

		m_angle = RIGHT_ANGLE;
	}

	// �v���C���[�̍��W��ύX
	//m_position.x += m_move.x;

	// �E��
	if( m_position.x <= -10.f ) m_position.x = -10.f;
	// ����
	if( m_position.x >= 8.f ) m_position.x = 8.f;
	// �`��ʒu���Z�b�g
	SetPosition(D3DXVECTOR3(m_position.x,m_position.y,m_position.z));

}

/**
 * �A�j���[�V�����ύX
 * @param _motionID �L�[���
 */
void CMaru::SetMotion(int _motionID)
{
	// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID == MOTION_WAIT ) m_state = STATE_WAIT;
	else if( m_curMotionID > MOTION_WAIT && m_curMotionID <= MOTION_STOP_RUN ) m_state = STATE_RUN;
	else if( m_curMotionID == MOTION_AVOID ) m_state = STATE_AVOID;
	else if( m_curMotionID == MOTION_JUMP ) m_state = STATE_JUMP;
	else if( m_curMotionID == MOTION_SQUAT_START ) m_state = STATE_SQUAT;
	else if( m_curMotionID == MOTION_SQUAT ) m_state = STATE_SQUAT2;
	else if( m_curMotionID >= MOTION_ATTACK ) m_state = STATE_ATTACK;

}

void CMaru::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
