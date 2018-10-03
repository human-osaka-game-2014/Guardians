/*--------------------------------------------------------------

	�������e:�A���h�t�@�E�g�̐���
	�쐬��:�h��
	�X�V��:
	�X�V���e:
	
	�֐��@

	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"

/*--------------------------------------------------------------

	�R���X�g���N�^

--------------------------------------------------------------*/
CMinertza::CMinertza(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	// ���f���̃X�P�[��
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	//m_charaHeight = (m_charaHeight * m_scale.y) / 2;
	
	m_model = new XFileAnimationMesh(_T("image\\xfile\\player\\PC_3_minertza.X"),m_pDevice,m_scale);

	m_weapon = new CMinertzaWeapon(m_pDevice);
	// �g�p�����`���쐬
	CreateBox();

		// ���[�V�����̊J�n���ԂƏI������
	double Animation[MOTION_MAX_NUM][2] = {
	//{ StartTime,  EndTime,
		{0, 79},		// 00) �ҋ@
		{80, 109},		// 01) ����o��
		{110, 149},	// 02) ����
		{150, 200},	// 03) �~�܂�
		{200, 265},	// 04) �W�����v(210-265�㏸�@265-280 280-300���~�i�J��Ԃ��\���j 320-329 ���n)
		{265, 349},	// 05) �W�����v���n(230-285�㏸�@285-300 300-320���~�i�J��Ԃ��\���j 340-349 ���n)
		{330, 339},	// 06) ���Ⴊ��
		{340, 369},	// 07) ���Ⴊ�ݒ�
		{370, 380},	// 08) ���Ⴊ�݉���
		{380, 410},	// 09) �ً}��� 
		{410, 465},	// 10) �ʏ�U���F420-430�a�� 450�܂łɍU���{�^�����͂ŘA���P�ցi445-450�ԂɘA���Q���[�V�����֌q����j
		{470, 515},	// 11) �ʏ�U���A��1�F475-485�a��@500�܂łɍU�����͂ŘA���Q�ցi500�ɘA���Q���[�V�����֌q����j
		{520, 580},	// 12) �ʏ�U���A��2�F545-55�a��
		{580, 630},	// 13) ��U���{�W�����v�Fjump_Speed�ɒʏ�W�����v����3����2�i�󒆂ł̔������͔����j�̒l�����Z�i590-600,605-615�̓��a�蔻��j
		{635, 675},	// 14) ���U��  645-655�a��
		{680, 735},	// 15) ���U���i�󒆁j690�ŌŒ�@700�Őڒn�@���[�V�����I�����ɂ��Ⴊ�ݔ���� 690-710�܂Ŏa��
		{740, 760},// 16) �Z1�@�o���A�@750�ŌŒ� �@
		{760, 800},// 17) �Z2 �@�U�艺�낵 775-785�a��
		{800, 855},// 18) �Z3 �@�㏸�{�Ռ��g 820-835�ɏ㏸
		{860, 930},// 19) �Z4�@���@880-910����   
		{935, 960},// 20) �Z4�i�󒆁j �O�ʑ��o���A�i�_���[�W�{�U����ԂȂ�_���[�W��悹�j 940-960�@����
		{965, 995},// 21) �_���[�W��炢
		{955, 1135},	// 22) ���S  
		{1140, 1189},	// 23) �X�^��
		{1195, 1290},	// 24) �ŗL���[�V����1�i�퓬�J�n���p�j
		{1290, 1410},	// 25) �ŗL���[�V����2�i�������j
		//{1260, , },	// 26) �K�E�Z
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
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CMinertza::~CMinertza()
{
	SAFE_DELETE(m_model);
	SAFE_DELETE(m_weapon);


	for(unsigned i = 0; i < m_box.size(); i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}
/*--------------------------------------------------------------

	�`��
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMinertza::Draw()
{
	// ���f���̃��l���Z�b�g
	m_model->SetColor(m_alpha);
	// ���f������
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	// ���f���̕`���
	m_model->Draw(m_position,rotation);

	m_weapon->Draw(D3DXVECTOR3(m_ray.position.x,m_ray.position.y + -200.f,m_ray.position.z),m_matWeapon,m_alpha); // ����̕`��

	D3DXVECTOR3 rayStart,rayDir,pos1,pos2;

	// ���C��`�悷��
	DrawRay(m_ray.position,m_ray.length);


	// ��`�̕`��
	for(unsigned i = 0; i < m_box.size(); i++)
		DrawBox(m_box[i]);
	// �A�j���[�V�������Ԃ̍X�V
	UpdateAnimTime();
}
/*--------------------------------------------------------------

	���[�V������ύX
	@param int	���[�V�����ԍ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMinertza::SetMotion(int _motionID)
{
	// ���[�V������ύX
	if(  m_model->ChangeMotion(_motionID) ){
		// �Đ����Ă���A�j���[�V������ۑ�
		m_curMotionID = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;

		if( !m_isPlay ){
			PlayEffect(1);
		}
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
		m_state = STATE_ATTACK;
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
	// ���G��ԂȂ�State�𖳓G��
	if( m_invincible ) 
		m_state = STATE_INVICIBLE;

	SetRect();
	// �G�t�F�N�g�̐���
	ControlEffect();
	ControlRect();
}
/*--------------------------------------------------------------

	�Փ˔����`�̐���
	@param �Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMinertza::ControlRect()
{
	m_matWeapon = GetMatrix("GripPosition"); // GripPosition��Matrix���擾
	D3DXVECTOR3 pos1,pos2;
	// 2�_�̃{�[���̈ʒu���猕�̃x�N�g�������߂�
	pos1 = GetBonePos("R_p1");
	pos2 = GetBonePos("R_i1");
	// ���C�̒�����ۑ�
	m_ray.length = pos2 - pos1;
	D3DXVec3Normalize(&m_ray.length,&m_ray.length);
	m_ray.length = m_ray.length * 10;
	// ���C�̊J�n�n�_��ۑ�
	m_ray.position = GetBonePos("R_wrist");
	
		// ���[�V�������ɏ�Ԃ�ς���
	switch( m_curMotionID )
	{
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_ATTACK2:	//11.	�ʏ�U���A��1
	case MOTION_ATTACK3:	//12.	�ʏ�U���A��2
		m_correctionValue = 1.f;
		break;
	case MOTION_SKILL:		//16.	�Z1
		m_correctionValue = 1.2f;
		break;
	case MOTION_SKILL2:		//17.	�O�{�Z
		m_correctionValue = 1.3f;
		break;
	case MOTION_UPPER:		//13.	��U��
		m_correctionValue = 0.f;
		break;
	case MOTION_LOWER:		//14.	���U��
		m_correctionValue = 1.0f;
		break;
	case MOTION_AIR:		//15.	���U���i�󒆁j
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILL3:		//18.	��{�Z
		m_correctionValue = 1.0f;
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
	UpdateRect("Back",0);
}
/*--------------------------------------------------------------

	�G�t�F�N�g�̐���
	@param �Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMinertza::ControlEffect()
{
	switch( m_curEffect){
	case MOTION_ATTACK:		//10.	�ʏ�U��
	case MOTION_UPPER:		//13.	��U��
	case MOTION_AIR:			//15.	���U���i�󒆁j
	case MOTION_SKILL2:		//17.	�O�{�Z
			
		break;
	case MOTION_LOWER:		//14.	���U��
		
		break;
	case MOTION_SKILL:		//16.	�Z1
		
		break;
	case MOTION_SKILL4:		//19.	���{�Z
		break;
	case MOTION_SKILL3:		//18.	��{�Z
	case MOTION_SKILLAIR:	//20.	���{�Z�i��
		
		break;
	}
	//if( m_isHit ) {
	//for(int i = 0; i < EFFECT_MAX_NUM;i++)
	//		m_effect[i]->StopEffect();
	//	m_isPlay = false;
	//}
}
/*--------------------------------------------------------------

	�Փ˔���Ɏg�p����{�b�N�X�𐶐�
	@param �Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CMinertza::CreateBox()
{
	XFileAnimationMesh::BOX		box;
	// �{�b�N�X�̐���
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(40.0f,50.0f,20.0f);
	box.center = D3DXVECTOR3(0.f,80.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(100.0f,20.0f,20.0f);
	box.center = D3DXVECTOR3(50.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}
/*-----------------------------------------------------------------

	Breast
	Back

	R_wrist
	GripPosition
-------------------------------------------------------------------*/



// �~�l���c�@����N���X
CMinertzaWeapon::CMinertzaWeapon(LPDIRECT3DDEVICE9 _pDevice)
{
	m_model = new C3DModel(_T("image\\xfile\\Player\\ken.X"),_pDevice);

	m_model->SetAngle(D3DXVECTOR3(0,0,0));
}
CMinertzaWeapon::~CMinertzaWeapon()
{
	SAFE_DELETE(m_model);
}
void CMinertzaWeapon::Draw(D3DXVECTOR3 _position,D3DXMATRIX _mat,float _alpha)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	m_model->SetScale(D3DXVECTOR3(50,50,50));

	if( _alpha == 1.0 )
		m_model->Draw(_position,_mat);

}
void CMinertzaWeapon::GetMeshSize(D3DXVECTOR3* _min,D3DXVECTOR3* _max)
{
	m_model->GetMeshSize(_min,_max);
}