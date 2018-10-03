#include "stdafx.h"

/*--------------------------------------------------------------

�R���X�g���N�^
@param	LPDIRECT3DDEVICE9 �`��f�o�C�X
@return �Ȃ�

--------------------------------------------------------------*/
CFenrir::CFenrir(LPDIRECT3DDEVICE9 _pDevice) : CEnemy(_pDevice), m_speed(0.00f)
{
	//�X�e�[�^�X�ݒ�
	m_status.hp = m_status.maxHP = 1000;
	//DEF = 25;
	//actionGauge = 100;
	//actionGaugeRecover = 25;

	TimeCount = 0;

	m_model = new XFileAnimationMesh(_T("image\\xfile\\Enemy\\StageBoss2.X"), m_pDevice, D3DXVECTOR3(0.025f, 0.075f, 0.025f));

	// �{�b�N�X�̐���
	CreateBox();

	// ���[�V�����̊J�n���ԂƏI������
	double Animation[MOTION_MAX_NUM][2] = {
		{ 0, 100 },  // 00) �ҋ@
		{ 100, 200 }, // 01) �Ђ��
		{ 200, 295 }, // 02) ���S
		{ 300, 345 }, // 03) �W�����v���߁�����
		{ 345, 345 }, // 04) �W�����v�؋�i�����ň�[�Œ�
		{ 345, 400 }, // 05) �W�����v���n
		{ 400, 460 }, // 06) �������] (415-445�Œ��яオ���180����]�@�����ۂɃ_���[�W����)
		{ 465, 520 }, // 07) �W�����v���n���݂�
		{ 520, 580 }, // 08) ���݂� (540-555�Ō��ɓ����蔻��)
		{ 580, 650 }, // 09) �Ή��e (625�Ŕ���)
		{ 650, 690 }, // 10) �����ۍU���i675�ŃG�t�F�N�g�j
		{ 690, 730 }, // 11) �Ή����ˑO
		{ 730, 730 }, // 12) �Ή����˒�
		{ 730, 770 }, // 13) �Ή����ˌ�
		{ 770, 800 }, // 14) ���i���O
		{ 800, 800 }, // 15) ���i����
		{ 800, 860 }, // 16) ���i����
		{ 0, 100 }, // 16) ���i����ҋ@
		{ 860, 930 }, // 17) �̓�����O
		{ 930, 930 }, // 18) �̓����蒆
		{ 930, 960 }, // 19) �̓������
	};

	m_animList.resize(MOTION_MAX_NUM);
	// �z��Ƀ��[�V�������Ԃ��i�[
	for (int i = 0; i < MOTION_MAX_NUM; i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = false;
		
	}
	m_animList[MOTION_WAIT].chancel = true;
	
	// �A�j���[�V�������Z�b�g
	m_model->SetAnimList(&m_animList);
	m_model->ChangeMotion(0);

	SetMotion(MOTION_WAIT);


	m_sidePos[0] = -11.f;
	m_sidePos[1] = 9.f;
}
/*--------------------------------------------------------------

�f�X�g���N�^



--------------------------------------------------------------*/
CFenrir::~CFenrir()
{
	SAFE_DELETE(m_model);
	//	SAFE_DELETE(m_sphere[0].pShereMaterials);
	for (unsigned i = 0; i < m_box.size(); i++)
		SAFE_DELETE(m_box[i].pMaterials)

}
/*--------------------------------------------------------------

����
@param	�Ȃ�
@return �Ȃ�

--------------------------------------------------------------*/
void CFenrir::Control()
{
	static bool countFlag = false;
	static bool	interval = false;		//�x�e����
	static unsigned	actionFlag = 0;		//�s������p
	static DWORD MotionStart, MotionEnd;
	static int LoadCount;				//�ꎞ�ϐ��n
	srand((unsigned int)time(NULL));

	TimeCount++;

	// ���S���[�V�������I����Ă����烂�[�V������i�߂Ȃ�
	if( m_curMotionID == MOTION_DEATH &&  m_animList[MOTION_DEATH].endTime <= m_time )
		m_motionStop = true;

	 // ����̃��[�V�����I�����ɋx�e���łȂ����
	if(!interval){
		if( CheckInterval() ){
			MotionStart = timeGetTime(); // �C���^�[�o�����̎��Ԃ��v���J�n
			interval = true;
		}
	}

	// �G��AI

	// ��苗����Player�𔭌�����
	if( fabsf(m_position.x - m_playerPos.x ) >= 25.f ){
		m_discovered = false; // Player����������
		m_motionID = MOTION_WAIT; // �ҋ@���[�V������
	}
	else{
		m_discovered = true;	// �v���C���[�𔭌�
	}

	// �v���C���[�𔭌����Ď������ҋ@���[�V�������Ȃ�s������
	if ( m_discovered && m_curMotionID == MOTION_WAIT ){

		if ((m_position.x - m_playerPos.x) * m_angle > 0)			//�v���C���[���w��ɂ�����
			if (fabsf(m_position.x - m_playerPos.x) < 10.f){		//�@�ߋ���
				if (actionFlag == 2){							//�@���]���K�������]�̎�
					m_motionID = MOTION_TAIL;
					actionFlag = 1;
				}
				else if (!actionFlag && rand() % 10 < 4){		//�@�@�K���g���ĂȂ�������40���Ŏg��
					m_motionID = MOTION_TAIL;
					actionFlag = 1;
				}
				else {											//�@�@����ȊO�͔��]
					m_motionID = MOTION_TURN;
					actionFlag = 0;
				}
			}
			else m_motionID = MOTION_TURN;
		else {	//�v���C���[���O�ɂ��鎞
			if ( rand() % 20 < 3){			//�@�s���l������Ȃ�ɂ�������15���ŉ��i��
				m_motionID = MOTION_HOWL1;
			}
			// �ߋ����̎�
			else if (fabsf(m_position.x - m_playerPos.x) < 10.f){
				if (rand() % 10 < 2){							//�@�@20���Ŕ��]���K�������]���g�p
					m_motionID = MOTION_TURN;
					actionFlag = 2;
				}
			//�@�������̎�
			} else if (fabsf(m_position.x - m_playerPos.x) < 15.f){
				if (rand() % 10 < 4)							//�@�@�@40���Ńt�@�C�A�u���X�@�c��ł�����Ƒҋ@
					m_motionID = MOTION_FIRE1;
				else if (rand() % 10 < 5)						//�@�@�@50���ő̓�����@�c��ł�����Ƒҋ@
					m_motionID = MOTION_ATTACK1;
			//�@�������̎�
			} else {								
				if ( rand() % 10 < 2)		//�@�@�s���l������Ȃ�ɂ�������20���Ń^�b�N��
					m_motionID = MOTION_ATTACK1;
				else
					m_motionID = MOTION_JUMP1;					//�@�@80���ŃW�����v(�X��50%�Œ�����)�@�c��Ŋ��݂��W�����v
			}
		}
	}
		
	switch(m_curMotionID){
	case MOTION_JUMP1:
	case MOTION_JUMP2:
	case MOTION_JUMP_BITE:
	case MOTION_JUMP3:
		Jump();
		break;
	case MOTION_TURN:
		Turn();
		break;
	case MOTION_ATTACK1:
	case MOTION_ATTACK2:
	case MOTION_ATTACK3:
		Attack();
	case MOTION_HOWL1:
	case MOTION_HOWL2:
	case MOTION_HOWL3:
		Howl();
		break;
	case MOTION_FIRE1:
	case MOTION_FIRE2:
	case MOTION_FIRE3:
		Fire();
		break;
	}
	

	// ���[�V�����ƃ��[�V�����̊Ԃ͑ҋ@
	if(interval){
		m_HitCount = 0;
		m_motionID = MOTION_WAIT;
		MotionEnd = timeGetTime();
		if( (MotionEnd - MotionStart) /1000 >= 2 ){ // ���[�V�����ƃ��[�V�����̊Ԃ�4�b�҂�
			interval = false;
		}
	}

	SetMotion(m_motionID);

	// �E��
	if( m_position.x >= CCharacter::RIGHT_WALL )
		m_position.x = CCharacter::RIGHT_WALL;
	// ����
	if( m_position.x <= CCharacter::LEFT_WALL ) 
		m_position.x = CCharacter::LEFT_WALL;
}
bool CFenrir::CheckInterval()
{
	// ����̃��[�V������͑ҋ@���Ԃ�݂���
	switch(m_curMotionID){
	case MOTION_JUMP3:
	case MOTION_TURN:
	case MOTION_BITE:
	case MOTION_JUMP_BITE:
	case MOTION_FIRE3:
	case MOTION_HOWL3:
	case MOTION_FIREBALL:
	case MOTION_TAIL:
		if( m_time >= m_animList[m_curMotionID].endTime )
			return true;
		break;
	};
	return false;

}
/*--------------------------------------------------------------

�`��
@param	�Ȃ�
@return �Ȃ�

--------------------------------------------------------------*/
void CFenrir::Draw()
{
	if (!m_motionStop) // ���[�V�����X�g�b�v�t���O�������Ă��Ȃ��ꍇ�̓��[�V�������Ԃ�i�߂�
		m_time = m_model->AdvanceTime(1.0f / 60.f);

	D3DXMATRIX rotation;							// ��]
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(m_angle), D3DXToRadian(-90), D3DXToRadian(0));

	m_model->Draw(m_position, rotation);

	SetRect();
	// �{�f�B�̋�`
	UpdateRect("BaseBone",0);

	//for(int i = 0; i < m_box.size(); i++){
	//	DrawBox(m_box[i]);
	//}
}
/*--------------------------------------------------------------

�A�j���[�V�����ύX
@param	int �L�[���
@return �Ȃ�

--------------------------------------------------------------*/
void CFenrir::SetMotion(int _motionID)
{
		// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID <= MOTION_DEATH )
		m_state = STATE_WAIT;
	else
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
float CFenrir::GetCharaSpeed()
{
	return m_speed;
}

int CFenrir::GetDamage()
{
	return 30;
}


void CFenrir::TailHammer(){
	m_curEffect = MOTION_TAIL;
	MYFRAME* m_frame;
	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "Tail_3");
	SetBonePos(&effectPos[0], m_frame);
}
void CFenrir::Attack()
{
	float m_move;
	if( m_curMotionID ==  MOTION_ATTACK1 ){
		m_move = 0.1f;
		if ( m_angle == LEFT_ANGLE )
			m_move = m_move * -1.f;

		m_position.x += m_move;

		if (m_time >= m_animList[MOTION_ATTACK1].endTime)
			m_motionID = MOTION_ATTACK3;
	}
	if( m_curMotionID == MOTION_ATTACK3 ){
		m_move = 1.2f;
		if ( m_angle == RIGHT_ANGLE )
			m_move = m_move * -1;

		m_position.x += m_move;

		if (m_time >= m_animList[MOTION_ATTACK3].endTime)
			m_motionID = MOTION_TURN;
		
	}
	m_hitting_box[0] = m_box[BODY];
	//if (!m_isPlay){
	//	m_curEffect = MOTION_ATTACK2;
	//	if (m_angle < 0) e_position = -0.7f; else e_position = 0.7f;
	//	MYFRAME* m_frame;
	//	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "TopJaw");
	//	SetBonePos(&effectPos[0], m_frame);
	//	effectPos[0].x += e_position * 4;
	//	m_isPlay = true;
	//}
	//else if (m_curMotionID == MOTION_ATTACK2){
	//	m_effectList[m_curEffect].move.x = 0.7f;
	//	MYFRAME* m_frame;
	//	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "TopJaw");
	//	SetBonePos(&effectPos[0], m_frame);
	//}
	//else {
	//	if (e_position > 0)	e_position -= 0.05f;
	//	else if (e_position < 0)	e_position += 0.05f;
	//}
	//m_position.x += e_position;
	//return;
}

/*--------------------------------------------------------------

�{�b�N�X�𐶐�
@param �Ȃ�
@return �Ȃ�

--------------------------------------------------------------*/
void CFenrir::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// �X�t�B�A�̐���
	// ���ݖ��g�p
	//sphere.center = D3DXVECTOR3(0.f,0.f,0.f);
	//sphere.radius = 10.f;
	//m_sphere.push_back(sphere);
	//m_model->CreateSphere(&m_sphere[0]);
	//��
	box.max = D3DXVECTOR3(160.0f, 100.0f, 100.0f);
	box.min = D3DXVECTOR3(0.f, 0.f, 0.f);
	box.center = D3DXVECTOR3(0.f, 0.f, 0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//��
	box.max = D3DXVECTOR3(75.0f, 65.0f, 80.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//��
	box.max = D3DXVECTOR3(80.0f, 70.0f, 80.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//�G�t�F�N�g�p
	box.max = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	box.length = box.max - box.min;
	for (int i = 0; i < EFFECT_MAX_NUM; i++)
		m_box.push_back(box);
	for (unsigned i = 0; i < m_box.size(); i++)
		m_model->CreateBox(&m_box[i]);

}

void CFenrir::BoxControl()
{
	//BOX�̊Ǘ�
	MYFRAME* m_frame;
	D3DXVECTOR3 position;
	// �̂̋�`
	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "Back");
	SetBonePos(&position, m_frame);
	position.y -= 2.f;
	UpdateRect(position, BODY);

}

void CFenrir::Jump()
{
	static float INIT_VELOCITY = 0.5f; // ����

	static float VELOCITY = INIT_VELOCITY;
	// �����x
	float ACCELERATE = 0.002f;
	
	// �W�����v�J�n�t���[��
	const int JUMP_START_FRAME = 335;

	switch(m_curMotionID){
	case MOTION_JUMP1:
		if( m_time >= JUMP_START_FRAME ){ // �W�����v�J�n�t���[���ɂȂ��Ă�����
			if (m_angle != RIGHT_ANGLE) m_position.x += 0.4f;
			else  m_position.x -= 0.4f;
			VELOCITY -= ACCELERATE; // jump���x�����ʁ|
			m_position.y += VELOCITY;  
		}
		if (m_time >= m_animList[m_curMotionID].endTime){ // �W�����v���[�V�������I����Ă�����
			m_motionID = MOTION_JUMP2; // ���[�V������؋��
		}
		break;
	case MOTION_JUMP2:
		// �W�����v�̍ō��_�̎��͉����x��0��
		VELOCITY = 0;
		if ( rand() % 10 < 5 ) {
			m_motionID = MOTION_JUMP_BITE;
		}
		else m_motionID = MOTION_JUMP3;
		break;
	case MOTION_JUMP3:
	case MOTION_JUMP_BITE:
		// �󒆂ɂ��鎞
		if (m_position.y > INIT_ENEMY_POSITION.y){
			VELOCITY -= ACCELERATE * 10; // ���ʃ}�C�i�X
			m_position.y += VELOCITY;
			if (m_angle != RIGHT_ANGLE ) m_position.x += 0.3f;
			else  m_position.x -= 0.3f;
		}// �n�ʂɂ��Ă�����
		else
			m_position.y = INIT_ENEMY_POSITION.y;

		// ���[�V�������I�����Ă�����
		if (m_time >= m_animList[m_curMotionID].endTime){
			// �ҋ@���[�V�����ɖ߂��A���x�Aposition�������l��
			m_motionID = MOTION_WAIT;
			VELOCITY = INIT_VELOCITY;
			m_position.y = INIT_ENEMY_POSITION.y;
		}
		break;
	}
	// ���̋�`���X�V
	UpdateRect("Head", HEAD);
	m_hitting_box[0] = m_box[HEAD];
}
void CFenrir::Turn()
{
	int TOTAL_FRAME = (int)(m_time - m_animList[MOTION_TURN].startTime);
	if (TOTAL_FRAME < 15){
		e_position = 0.45f;
	}
	else if (TOTAL_FRAME < 45){	//�W�����v�����]
		m_angle -= 6;
		m_position.y += e_position;
		e_position -= 0.03f;
	}
	else if (m_time >= m_animList[MOTION_TURN].endTime){
		//actionGauge -= 10;
		m_motionID = MOTION_WAIT;
		if (m_angle == -270) m_angle = 90;
		m_position.y = INIT_ENEMY_POSITION.y;
		//STR = 0;
	}
	//m_curMotionID == MOTION_ATTACK1;
}
void CFenrir::Tail()
{
	int LoadCount = (int)(m_time - m_animList[MOTION_TAIL].startTime);
	//STR = 40;
	//addState = 0;
	if (LoadCount == 25) {
		//actionGauge -= 15;
		TailHammer();
		//STR = 60;
		//addState = 1;
	}
	if (m_time >= m_animList[MOTION_TAIL].endTime){
		m_curMotionID = MOTION_WAIT;
		//STR = 0;
		//addState = 0;
	}
	UpdateRect("Tail_3",TAIL);
	m_hitting_box[0] = m_box[TAIL];

}
void CFenrir::Howl()
{
	if( m_curMotionID == MOTION_HOWL1 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_HOWL2;

	if( m_curMotionID == MOTION_HOWL2 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_HOWL3;

	if( m_curMotionID == MOTION_HOWL3 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_WAIT;

}
void CFenrir::Fire()
{
	if( m_curMotionID == MOTION_FIRE1 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_FIRE2;

	if( m_curMotionID == MOTION_FIRE2 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_FIRE3;

	if( m_curMotionID == MOTION_FIRE3 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_WAIT;

}
/*--------------------------------------------------------------

BaseBone
Breast
Back
Head
Tail_1~3

---------------------------------------------------------------*/
