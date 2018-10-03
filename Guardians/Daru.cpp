/**
 * @file Daru.cpp
 */

#include  "stdafx.h"
/**
 * �R���X�g���N�^
 * @param _pDevice �`��f�o�C�X
 */
CAru::CAru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	m_scale = D3DXVECTOR3(0.01f,0.02f,0.01f);
	m_model = new XFileAnimationMesh(_T("image\\neru\\PC_2-1_Neru.X"),m_pDevice,m_scale);
	
	XFileAnimationMesh::BOX		box;

	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(20.0f,20.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	m_model->CreateBox(&m_box[0]);
	m_model->CreateBox(&m_box[1]);
	m_time = 0;

	// ���[�V�����̊J�n���ԂƏI������
	int Animation[MOTION_MAX_NUM][3] = {
	// StartTime�@,EndTime,�@ChancelFlag
		{0,59,true},			// �ҋ@
		{60,114,true},			// ����o��
		{115,169,true},			// ����
		{170,219,false},		// �~�܂�
		{220,349,false},		// �W�����v�㏸(230-285�㏸�@285-300 300-320���~)
//		{340,349},				// �W�����v���~(230-285�㏸�@285-300 300-320���~)
		{350,359,true},			// ���Ⴊ��
		{360,389,true},			// ���Ⴊ�ݒ�
		{390,399,false},		// ���Ⴊ�݉���
		{400,430,false},		//9.	400-430	�ً}���
		{430,460,false},		//10.	430-460 �ʏ�U���i-444�\���@445-450���ˁ@451-460�̃��[�V������15frame�����ď󋵂ɉ������ҋ@�����[�V�����ֈڍs�@�A������5frame��440�t���[���ڂ̃��[�V�����Ɉڍs���ȍ~�ʏ펞�̗���ցj
		{430,460,false},		//11.	 �ʏ�U���A��1�F�Ȃ�
		{430,460,false},		//12.	 �ʏ�U���A��2�F�Ȃ�
		{465,495,false},		//13.	 465-495 ��U���i-479�\���@480-4985���ˁ@486-495�ҋ@�֘A�����̏����͒ʏ�U���Ɠ����j
		{500,535,false},		//14.	 500-535 ���U���@�i510�\���@510-520�U���j
		{540,570,false},		//15.	 540-570 ���U���i�󒆁j�i550�\���@550-555���ˁ@555-565�̃��[�V������15frame�����ď󋵂ɉ������ҋ@�����[�V�����ֈڍs�A�����̏����͒ʏ�U���Ɠ����j

	};
	m_animList.resize(MOTION_MAX_NUM);
	// �z��Ƀ��[�V�������Ԃ��i�[
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = Animation[i][2];
	}
	// �A�j���[�V�����z����Z�b�g
	m_model->SetAnimList(&m_animList);
	// �ҋ@���[�V�������Z�b�g
	m_model->ChangeMotion( MOTION_WAIT );

	effect = new CEffect(m_position , m_pDevice);
}
void CAru::Load()
{

}

/**
 * �f�X�g���N�^
 */
CAru::~CAru()
{
	SAFE_DELETE(m_model);
	//SAFE_DELETE(m_sphere[0].pShereMaterials);
	SAFE_DELETE(m_box[0].pMaterials);
	SAFE_DELETE(effect);
}

/**
 * �`��
 */
void CAru::Draw()
{
	//effect->Create(L"Effect\\WolfHead.efk",m_position,D3DXVECTOR3(1,1,1));

	//// ���Ⴊ�ݒ��ƃ|�[�Y���̓A�j���[�V�������Ԃ�i�߂Ȃ�
	////if( m_state != MOTION_SQUAT2
	//if(!CBattleScene::m_pause)
	//	m_time = m_model->AdvanceTime(1.0f/60.f);
	//// ��]
	//D3DXMATRIX rotation;							
	//D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(-90 + m_angle), D3DXToRadian(-90), D3DXToRadian(-90));
	//
	//m_model->Draw(m_position,rotation);

	//MYFRAME* m_frame;	// �t���[��
	//D3DXVECTOR3 position;	// �{�[���̈ʒu�i�[�p
	//// �U����ԂȂ��`���{�[���ɕt��������
	//if( m_state == STATE_ATTACK ){
	//	// �Փ˔���p��`�̕`��
	//	if( (m_animList[m_curMotionID].startTime + 5) < m_time ){ // �Z��������10F�o�߂��Ă�����Փ˔���
	//		m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"L_wrist" );
	//		SetBonePos(&position,m_frame);
	//		UpdateBox(position,&m_box[1]);
	//		//DrawBox(m_box[1]);
	//		
	//		/*SetBonePos(&position,m_frame);
	//		UpdateSphere( position , &m_sphere[0]);
	//		DrawSphere(m_sphere[0]);*/
	//	}
	//}

	//m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"pelvis" );
	//SetBonePos(&position,m_frame);
	//UpdateBox(position,&m_box[0]);
	////DrawBox(m_box[0]);
	////effect->Play();
	//effect->Control(D3DXVECTOR3(0.f,-0.1f,0.f),m_position);

}

/**
 * �A�j���[�V�����ύX
 * @param[in] _motionID �L�[���
 */
void CAru::SetMotion(int _motionID)
{
	static double endTime = m_animList[MOTION_WAIT].endTime;

	// �Đ����Ă���A�j���[�V�������i�[
	//m_curMotionID = m_model->ChangeMotion(_motionID);

	if( m_curMotionID == MOTION_WAIT ) m_state = STATE_WAIT;
	if( m_curMotionID > MOTION_WAIT && m_curMotionID <= MOTION_RUN3 ) m_state = STATE_RUN;
	if( m_curMotionID == MOTION_JUMP ) m_state = STATE_JUMP;
	if( m_curMotionID == MOTION_SQUAT_START ) m_state = STATE_SQUAT;
	if( m_curMotionID == MOTION_SQUAT ) m_state = STATE_SQUAT2;
	if( m_curMotionID >= MOTION_ATTACK ) m_state = STATE_ATTACK;

	// �q�b�g���̃_���[�W��( ��{�I�ɂ�1�i�q�b�g)
	if( m_state == STATE_ATTACK && m_HitCount == 0 ){
		m_damage = 30;
	}else{
		m_damage = 0;
	}
}

/**
 * �L�����̈ړ����x��Ԃ�
 * @return �ړ����x
 */
float CAru::GetCharaSpeed()
{
	return m_speed.x;
}
/*-----------------------------------------------------------------
	
	�l���@�{�[��
	�E��@R_wrist
	����  L_wrist

	���@chest
	���@back
	���@pelvis

	��(�ܐ�)
	�E�@L_toe(mirrored)
	���@L_toe
------------------------------------------------------------------*/
