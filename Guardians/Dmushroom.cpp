#include "stdafx.h"

/*--------------------------------------------------------------

	�R���X�g���N�^
	@param	LPDIRECT3DDEVICE9 �`��f�o�C�X
	@return �Ȃ�

--------------------------------------------------------------*/
CMushroom::CMushroom(LPDIRECT3DDEVICE9 _pDevice) : CEnemy(_pDevice),m_speed(0.00f)
{
	m_model = new XFileAnimationMesh(_T("image\\xfile\\Enemy\\Boss1_PoisonusMushroom.X"),m_pDevice,D3DXVECTOR3(0.07f,0.07f,0.07f));
	
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;

	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(130.0f,130.0f,200.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,30.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(20.0f,140.0f,70.0f);
	box.center = D3DXVECTOR3(0.f,0.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(130.0f,130.0f,200.0f);
	box.center = D3DXVECTOR3(0.f,0.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);	

	for( unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
		// ���[�V�����̊J�n���ԂƏI������
	int Animation[MOTION_MAX_NUM][2] = { 
		{0,0},		// �ҋ@
		{80,129},   //�Ђ��
		{130,209},  //���S
		{0,79},	    // �ҋ@�A�N�V�����i�\�b�ԉ����s�����Ȃ��������̍s���^�X���[�Đ�
		{210,249},  // ���݂�
		{250,329},	//�΂ԂčU��
		{330,379},	//�ŕ��i330-339��340-369�i�X���[�Đ��J��Ԃ��j��370-379)
		{380,439},	//�͂����i���j
		{440,499},	//�͂����i�E�j
	};

	m_animList.resize(MOTION_MAX_NUM);
	// �z��Ƀ��[�V�������Ԃ��i�[
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = false;
	}
	m_animList[MOTION_WAIT].chancel = true;
	m_animList[MOTION_WAIT2].chancel = false;
	//m_animList[2].chancel = true;
	//m_animList[5].chancel = true;
	//m_animList[6].chancel = true;
	// �A�j���[�V�������Z�b�g
	m_model->SetAnimList(&m_animList);
	m_model->ChangeMotion(0);

	SetMotion(MOTION_WAIT);

	m_status.hp = m_status.maxHP =  90;

}
/*--------------------------------------------------------------

	�f�X�g���N�^



--------------------------------------------------------------*/
CMushroom::~CMushroom()
{
	SAFE_DELETE(m_model);
//	SAFE_DELETE(m_sphere[0].pShereMaterials);
	for(unsigned i = 0; i < m_box.size();i++)
	SAFE_DELETE(m_box[i].pMaterials)
}
/*--------------------------------------------------------------

	����
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMushroom::Control()
{
	static bool countFlag = false;
	static bool	interval = false;
	static DWORD MotionStart,MotionEnd;

	srand((unsigned int)time(NULL));

	// ���S���[�V�������I����Ă����烂�[�V������i�߂Ȃ�
	if( m_curMotionID == MOTION_DEATH &&  m_animList[MOTION_DEATH].endTime <= m_time )
		m_motionStop = true;

	// �G��AI
	//SetMotion(MOTION_WAIT);
	if( m_curMotionID > MOTION_WAIT2 && m_time >= m_animList[m_curMotionID].endTime ){
		if(!interval){
			MotionStart = timeGetTime();
			interval = true;
		}
	}
	if( m_curMotionID == MOTION_WAIT2 && m_time >= m_animList[MOTION_WAIT2].endTime){
		m_animList[MOTION_WAIT2].chancel = true;
		m_model->SetAnimList(&m_animList);
		m_curMotionID = MOTION_WAIT;
		SetMotion(m_curMotionID);
		m_animList[MOTION_WAIT2].chancel = false;
		//m_model->SetAnimList(&m_animList);
	}

	if( fabsf(m_position.x - m_playerPos.x ) >= 7.f ){
		m_discovered = false; // Player����������
		if (!countFlag){
			countFlag = true;
			m_curTime = timeGetTime();
		}
		m_endTime = timeGetTime();
		if( (m_endTime - m_curTime) / 1000 >= 10){ //�@Enemy��Player�̋�������ԉ�����Ԃ�10�b�o�߂�����ҋ@
			m_motionID = MOTION_WAIT2;
			m_curTime = timeGetTime();
		}
		else m_motionID = MOTION_WAIT;
	}
	else{
		m_discovered = true;	// �v���C���[�𔭌�
	}
	// �v���C���[�𔭌����Ă����ԂȂ�U�����[�V����
	if(m_discovered){
		if( fabsf(m_position.x - m_playerPos.x ) <= 6.f ){ // �G�Ƃ̋������������H�̏ꍇ(���ݕt��)
			m_motionID = MOTION_BITE;
		}
		if( fabsf(m_position.x - m_playerPos.x ) <= 4.f ){ // �G�Ƃ̋������ߋ����̏ꍇ(�͂����U�� L or R)
			m_motionID = rand()%2+7;
		}


	}
	// ���[�V�����ƃ��[�V�����̊Ԃ͑ҋ@
	if(interval){
		m_HitCount = 0;
		m_motionID = MOTION_WAIT;
		MotionEnd = timeGetTime();
		if( (MotionEnd - MotionStart) /1000 >= 4 ){ // ���[�V�����ƃ��[�V�����̊Ԃ�4�b�҂�
			interval = false;
		}
	}
	SetMotion(m_motionID);
}
/*--------------------------------------------------------------

	�`��
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMushroom::Draw()
{
	UpdateAnimTime();
	
	D3DXMATRIX rotation;							// ��]
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(-90), D3DXToRadian(-90), D3DXToRadian(0));
	m_model->Draw( m_position,rotation);

	// ����Ɏg�p�����`�̐������߂�
	SetRect();
	// �{�f�B�̋�`
	UpdateRect("Body",0);
	// ��̋�`
	 //�E��̃��[�V������
	if( m_curMotionID == MOTION_R_WHISK ){
		m_hitting_box[0] = m_box[1];
		UpdateRect("L_Arm4",1);
	}//����̃��[�V������
	else if( m_curMotionID == MOTION_L_WHISK ){ 
		m_hitting_box[0] = m_box[1];
		UpdateRect("R_Arm4",1);
	}
	// ���ݕt�����[�V����
	else if( m_curMotionID == MOTION_BITE ){
		m_hitting_box[0] = m_box[2];
		//m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"HeadCenter" );

	}

	DrawBox(m_box);
	
}
/*--------------------------------------------------------------

	�A�j���[�V�����ύX
	@param	int �L�[���
	@return �Ȃ�

--------------------------------------------------------------*/
void CMushroom::SetMotion(int _motionID)
{
		// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID <= MOTION_WAIT2 )
		m_state = STATE_WAIT;
	if( m_curMotionID >= MOTION_BITE) 
		m_state = STATE_ATTACK;
	
	if( m_state == STATE_ATTACK && m_HitCount == 0 ){
		m_correctionValue = 20;
	}else{
		m_correctionValue = 0;
	}
}
/*--------------------------------------------------------------

	�L�����̈ړ����x��Ԃ�
	@param	�Ȃ�
	@return �ړ����x
	
--------------------------------------------------------------*/
float CMushroom::GetCharaSpeed()
{
	return m_speed;
}

/*--------------------------------------------------------------

	BasBone
	Body
	Head
	HeadCenter

	L_Arm1~4
	R



---------------------------------------------------------------*/
