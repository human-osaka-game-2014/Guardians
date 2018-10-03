#include "stdafx.h"

 float CNeru::m_charaHeight = 150.f;
// ����MP

/*--------------------------------------------------------------

	�R���X�g���N�^
	@param	LPDIRECT3DDEVICE9 �`��f�o�C�X
	@return �Ȃ�

--------------------------------------------------------------*/
CNeru::CNeru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice) , m_teleportState(TPSTATE_WAIT) , m_moveValue(0,0,0) , m_isPlay(false)
{
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	m_charaHeight = (m_charaHeight * m_scale.y) / 2;
	
	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_2-1_Neru.X"),m_pDevice,m_scale);
	//m_maru = new CMaru(m_pDevice);

	// �g�p�����`���쐬
	CreateBox();

	// ���[�V�����̊J�n���ԂƏI������
	double Animation[MOTION_MAX_NUM][2] = {
	// StartTime�@,EndTime,�@ChancelFlag
		{0,59},			// �ҋ@
		{60,114},			// ����o��
		{115,169},			// ����
		{170,219},		// �~�܂�
		{220,349},		// �W�����v�㏸(230-285�㏸�@285-300 300-320���~)
		{280,310},				// �W�����v���~(230-285�㏸�@285-300 300-320���~)
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

	SetEffectList();

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

	for( int i = 0; i < EFFECT_MAX_NUM; i++ ){
		m_efk[i] = NULL;
	}
}
/*--------------------------------------------------------------

	�{�b�N�X�𐶐�
	@param �Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CNeru::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(100.0f,100.0f,40.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(20.0f,150.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}

/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CNeru::~CNeru()
{
	SAFE_DELETE(m_model);
	//SAFE_DELETE(m_sphere[0].pShereMaterials);
	for( unsigned i = 0; i < m_box.size();i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}

	for(int i = 0;i < EFFECT_MAX_NUM;i++){
		SAFE_DELETE( m_efk[i] );
	}
	//SAFE_DELETE(m_maru);
}
/*--------------------------------------------------------------

	�`��
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CNeru::Draw()
{
	// ���f���̃��l���Z�b�g
	m_model->SetColor(m_alpha);

	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	
	m_model->Draw(m_position,rotation);

	//m_maru->SetStopMotion(m_motionStop);
	//m_maru->Draw();

	SetRect();

	ControlEffect();

	// �{�f�B(���ꔻ��)
	UpdateRect("pelvis",0);
	
	// ���Ⴊ�ݒ��ƃ|�[�Y���̓A�j���[�V�������Ԃ�i�߂Ȃ�
	if( CBattleScene::m_pause || m_motionStop ) return;

	m_time = m_model->AdvanceTime(1.0f/60.f);
}
/*--------------------------------------------------------------

	�G�t�F�N�g�̐���
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CNeru::ControlEffect()
{
	static D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);

	float angle = 0; // �G�t�F�N�g�Đ����̃A���O���ۑ��p
	D3DXVECTOR3 position; // �G�t�F�N�g�Đ����̈ʒu

	switch( m_curEffect){
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_UPPER:		//13.	��U��
	case MOTION_AIR:			//15.	���U���i�󒆁j
	case MOTION_SKILL2:		//17.	�O�{�Z
		FireBall();
		break;
	case MOTION_LOWER:		//14.	���U��
		//ThunderWhip();
		break;
	case MOTION_SKILL:		//16.	�Z1
		IceWall();
		break;
	case MOTION_SKILL4:		//19.	���{�Z
		//StoneImpact();
		break;
	case MOTION_SKILL3:		//18.	��{�Z
	case MOTION_SKILLAIR:	//20.	���{�Z�i��
		Teleport();
		break;
	}
	//// �G�t�F�N�g�̍X�V
	//m_effect[MAIN_EFK]->Control(m_moveValue,m_efkPos);
	//// sub(��ɖ����w)�͈ړ����Ȃ�
	//m_effect[SUB_EFK]->Control(D3DXVECTOR3(0.f,0.f,0.f),m_efkPos);

	//// �G�t�F�N�g���I����Ă�����
	//if( m_effect[MAIN_EFK]->checkEnd() ){
	//	//m_isPlay = false;
	//	m_effect[MAIN_EFK]->SetCharaHeight( (m_charaHeight * m_scale.y) / 2);
	//}
	// �Z���������Ă�����G�t�F�N�g�Đ���~
	if( m_isHit ) {
		m_isPlay = false;
	}
}

void CNeru::FireBall()
{
	// �G�t�F�N�g�Đ���
	if( m_efk[FIRE_BALL] != NULL ){
		m_efk[FIRE_BALL]->Run();
		UpdateRect( m_efk[FIRE_BALL]->GetPosition(),1);
		//�ʏ�U��
		m_hitting_box[0] = m_box[1];
		m_correctionValue = 1.0f;
	}
	// �G�t�F�N�g�̍Đ����I����Ă�����
	if( (m_isPlay && !m_efk[FIRE_BALL]->GetExists()) || m_isHit ){
		SAFE_DELETE(m_efk[FIRE_BALL]);
		m_isPlay = false;
		m_curEffect = 0;
		UpdateRect( DUMMY,1);
		m_hitting_box[0] = m_box[1];
	}
}
/*--------------------------------------------------------------

	�A�j���[�V�����ύX
	@param	int �L�[���
	@return �Ȃ�

--------------------------------------------------------------*/
void CNeru::SetMotion(int _motionID)
{
	static double endTime = m_animList[MOTION_WAIT].endTime;

	// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;

		if( !m_isPlay ){
			PlayEffect();
		}
	}
	//m_maru->Move(m_position,_motionID , m_angle);

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
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_ATTACK2:		//11.	�ʏ�U���A��1
	case MOTION_ATTACK3:		//12.	�ʏ�U���A��2
	case MOTION_UPPER:		//13.	��U��
	case MOTION_LOWER:		//14.	���U��
	case MOTION_AIR:			//15.	���U���i�󒆁j
	case MOTION_SKILL:		//16.	�Z1
	case MOTION_SKILL2:		//17.	�O�{�Z
	case MOTION_SKILL3:		//18.	��{�Z
	case MOTION_SKILL4:		//19.	���{�Z
	case MOTION_SKILLAIR:		//20.	���{�Z�i�󒆁j
	//case MOTION_SPECIAL:		//21.	�K�E�Z
		m_state = STATE_PROJECTILE;
		m_motionState = MSTATE_IN_MOTION;
		break;
	case MOTION_FLINCH:			//22.	�_���[�W��炢
	case MOTION_DEAD:			//23.	���S
	case MOTION_STUN:			//24.	�X�^��
	case MOTION_APPEAL:		//25.	�ŗL���[�V����1�i�퓬�J�n���p�j
	case MOTION_APPEAL2:		//26.	�ŗL���[�V����2�i�������j
		m_motionState = MSTATE_IN_MOTION;
		m_state = STATE_WAIT;
		break;
	}
	if( m_isPlay ) m_state = STATE_PROJECTILE;
}
void CNeru::IceWall()
{
	// �G�t�F�N�g�Đ���
	if( m_efk[ICE_WALL] != NULL ){
		m_efk[ICE_WALL]->Run();
		UpdateRect( m_efk[ICE_WALL]->GetPosition(),0);
	}
	// �G�t�F�N�g�̍Đ����I����Ă�����
	if( m_isPlay && ! m_efk[ICE_WALL]->GetExists() ){
		SAFE_DELETE(m_efk[ICE_WALL]);
		m_isPlay = false;
		m_curEffect = 0;
	}
	//UpdateRect(m_position,2);	// �Փ˔���p��`�̍X�V
}
void CNeru::Teleport()
{
	int frame = 5;
	static float add = 0;
	static float jumpSpeed = -0.06f;


	switch( m_teleportState ){
	case TPSTATE_WAIT:
				if( m_alpha <= 1.0f )	// ���f���������Ȃ�
			m_alpha -= add;
				m_isPlay = false;

		if( m_curMotionID == MOTION_AIR || m_curMotionID == MOTION_SKILL3){
			m_efkPos = m_position; // �G�t�F�N�g�̏o���ʒu���X�V
			if( m_animList[m_curMotionID].startTime == m_time ){ // ���[�V�������ς�����t���[���Ȃ�
				PlayEffect(10);									 // �G�t�F�N�g�̍Đ�
				add = -((m_alpha / 2) / frame);					 // �������l��ۑ�
				m_teleportState = TPSTATE_TELEPORT;
			}
		}
		break;

	case TPSTATE_TELEPORT:
		if( (int)m_animList[m_curMotionID].startTime + 10 == (int)m_time )
			m_teleportState = TPSTATE_FADE_OUT;
		break;

	case TPSTATE_FADE_OUT:
		if( m_alpha >= 1.0 / 2)
			m_alpha += add;	// ���f���𓧖���
		else{
			if( m_alpha == 1.0 / 2 && m_curEffect != MOTION_SKILL3){
				m_position.y += 7;
				m_teleportState = TPSTATE_AERIAL;
				ResetMotion(MOTION_JUMP_FALL); // ���艟��
			}
			// ��Z�Ȃ�L�����N�^�[���󒆂�
			if( m_curEffect == MOTION_SKILL3){
				m_position.y += 7;
				m_teleportState = TPSTATE_AERIAL;
				ResetMotion(MOTION_JUMP_FALL); // ���艟��
			}
		}
		break;
	case TPSTATE_AERIAL:
		// �󒆂ɂ��鎞
		if( m_teleportState == TPSTATE_AERIAL ){
			if( m_position.y >= INIT_HEIGHT_POSITION){
				jumpSpeed -= 0.01f;
				m_position.y += jumpSpeed;
				if( m_curMotionID != MOTION_JUMP_FALL ) ResetMotion(MOTION_JUMP_FALL); // ���艟��
			}else{
				// ���n������҂���Ԃ�
				m_teleportState = TPSTATE_WAIT;
				ResetMotion(MOTION_WAIT);
				jumpSpeed = 0;
			}
		}
		break;

	case TPSTATE_FALL:
		if( m_alpha <= 1.0f )	// ���f���������Ȃ�
			m_alpha -= add;

		break;
	}

			// Teleport_01.efk���L�����ʒu�ɍĐ��{15Frame�����ăt�F�[�h�C��
			// �������ォ��t�F�[�h�C�����ςނ܂Łi45frame�ԁj���G
}
void CNeru::StoneImpact()
{
	if( m_curMotionID == MOTION_SKILL4 ){
		m_efkPos = m_position;
		PlayEffect();
	}
}
void CNeru::ThunderWhip()
{
	//MYFRAME* m_frame;	// �t���[��

	//if( m_curMotionID == MOTION_LOWER ){

	//	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"L_wrist" );
	//	SetBonePos(&m_efkPos,m_frame);

	//	m_effect[MAIN_EFK]->SetCharaHeight(0);
	//	PlayEffect();
	//}

	//if( m_curEffect != MOTION_LOWER ) return;
}


/*--------------------------------------------------------------

	�G�t�F�N�g���Đ�
	@param	int �����̃G�t�F�N�g���o��������ꍇ�t���[�����w��
	@return �Ȃ�

--------------------------------------------------------------*/
void CNeru::PlayEffect(int _frame)
{
	bool flag = false;

	// ���[�V�����ύX���ɃG�t�F�N�g��ύX
	switch( m_curMotionID ){
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_UPPER:		//13.	��U��
	case MOTION_AIR:			//15.	���U���i�󒆁j
	case MOTION_SKILL2:		//17.	�O�{�Z
	case MOTION_SKILL3:		//18.	��{�Z
		m_efk[FIRE_BALL] = new CFireBallManager(m_pDevice);
		m_efk[FIRE_BALL]->Play(m_angle,D3DXVECTOR3(m_position.x,m_position.y + m_charaHeight,m_position.z));
		flag = true;
		break;
	case MOTION_LOWER:		//14.	���U��
		//ThunderWhip();
		break;
	case MOTION_SKILL:		//16.	�Z1
		m_efk[ICE_WALL] = new CIceWallManager(m_pDevice);
		m_efk[ICE_WALL]->Play(m_angle,D3DXVECTOR3(m_position.x,m_position.y + m_charaHeight,m_position.z));
		flag = true;
		break;
	case MOTION_SKILL4:		//19.	���{�Z
		//StoneImpact();
		break;
	case MOTION_SKILLAIR:		//20.	���{�Z�i�󒆁j
		Teleport();
		break;
	}
	if( flag ){ // �G�t�F�N�g�Đ������t���[��
		m_curEffect = m_curMotionID;					// �Đ����Ă��郂�[�V������ۑ�
		m_isPlay = true;
		flag = false;
		
		m_efkAngle = m_angle;							// �Đ����̌�����ۑ�
		m_actionGauge -= 30;							// �A�N�V�����Q�[�W�����炷
	}
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
void CNeru::SetEffectList()
{

}