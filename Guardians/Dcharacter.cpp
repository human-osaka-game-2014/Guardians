/*--------------------------------------------------------------

	�������e:
	�쐬��:�h��
	�쐬��: 11/6
	�X�V��: 11/6

	�X�V���e:
	�֐��@

	�ϐ��@

--------------------------------------------------------------*/
#include "stdafx.h"

const float CCharacter::RIGHT_WALL = 58.f;
const float CCharacter::LEFT_WALL  = -34.f;

const float CCharacter::LEFT_ANGLE  = 90;	// �L�����N�^�[�̌����@��
const float CCharacter::RIGHT_ANGLE = -90;	// �L�����N�^�[�̌��� �E

float CCharacter::m_alpha = 1.0f;

/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X

--------------------------------------------------------------*/
CCharacter::CCharacter(LPDIRECT3DDEVICE9 _pDevice,float _angle) : m_pDevice(_pDevice) , m_state(STATE_WAIT) , m_angle(_angle) 
,m_curMotionID(0),m_speed(0.f,0.f) , m_isHit(false) , m_damage(0)
, m_scale(0.f,0.f,0.f) , m_step(STEP_MOVE) , m_move(0.f,0.f) , m_actionGauge(ACTION_GAUGE_MAX),m_box(0) , m_curEffect(0)
, m_time(0),m_takeDamage(0),m_invincible(false),m_endMotion(false)
{
	
}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CCharacter::~CCharacter()
{

}
D3DXVECTOR3 CCharacter::GetBonePos(LPCTSTR _name)
{
	MYFRAME* m_frame;	// �t���[��
	D3DXVECTOR3 position;	// �{�[���̈ʒu�i�[�p
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );

	SetBonePos(&position,m_frame);

	return position;
}
void CCharacter::UpdateRect(LPCTSTR _name , int _ID )
{
	UpdateBox(GetBonePos(_name),&m_box[_ID]);	// ��`�̈ʒu���X�V
}

D3DXMATRIX CCharacter::GetMatrix(LPCTSTR _name )
{
	MYFRAME* m_frame;	// �t���[��
	D3DXVECTOR3 position;	// �{�[���̈ʒu�i�[�p
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );
	return m_frame->CombinedTransformationMatrix;
}
void CCharacter::UpdateRect(D3DXVECTOR3 _position , int _ID,float _radian)
{
	UpdateBox(_position,&m_box[_ID],_radian);
	// ��`�̕`��(�f�o�b�O�p)
	#ifdef _DEBUG
		DrawBox(m_box[_ID]);
	#endif
}
/*--------------------------------------------------------------

	�X�t�B�A���W�̍X�V
	@param D3DXVECTOR3					�ʒu(x.y)
	@param XFileAnimationMesh::SPHERE	�X�t�B�A
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::UpdateSphere(D3DXVECTOR3 _position,XFileAnimationMesh::SPHERE* _sphere)
{
	// ����p���W�̍X�V
	_sphere->position = _sphere->center + _position;

	D3DXMATRIX matTrans,matWorld,matScale;
	D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
	D3DXMatrixTranslation(&matTrans, _position.x + _sphere->center.x ,_position.y + _sphere->center.y , _position.z + _sphere->center.z);
	D3DXMatrixIdentity(&matWorld);	matWorld = matWorld * matScale * matTrans;
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

}
/*--------------------------------------------------------------

	�Փ˔���Ɏg�p�����`�̐������߂�
	@param �Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::SetRect()
{
	// �L�����N�^�[�̍s���ɂ���Ĕ��肷���`��ς���
	// ��`���i�[�p�z��͌����Ⴄ�ꍇ�̂�Resize����

	// �L�����N�^�[���U����ԈȊO�Ȃ���ꔻ��̓{�f�B�̂�
	if( m_state < STATE_ATTACK ) {
		if( m_unhitting_box.size() != 1 ) m_unhitting_box.resize(1);
	}
	// �U�����(��ѓ���ł͂Ȃ��ꍇ)
	else if( m_state == STATE_ATTACK ){
		if( m_hitting_box.size() != 1 ) m_hitting_box.resize(1); // �U�������1��
		if( m_unhitting_box.size() != 2 ) m_unhitting_box.resize(2); // ���ꔻ��͓��
	}

	// �U�����(��ѓ�����g�p����ꍇ)
	if( m_state == STATE_PROJECTILE ){
		if( m_hitting_box.size() != 1 ) m_hitting_box.resize(1); // �U������͈��(��ѓ���)
		if( m_unhitting_box.size() != 1 ) m_unhitting_box.resize(1); // ���ꔻ��͈��
	}
	// ���ꔻ��͏�ɍX�V
	m_unhitting_box[0] = m_box[0];
}
/*--------------------------------------------------------------

	�X�t�B�A�̕`��f�o�b�O�p
	@param D3DXVECTOR3					�ʒu(x.y)
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::DrawSphere(XFileAnimationMesh::SPHERE _sphere)
{
	//�X�t�B�A�̕\��
	m_pDevice->SetMaterial( _sphere.pShereMaterials );
	_sphere.pShereMesh->DrawSubset(0);
}
/*--------------------------------------------------------------

	�{�b�N�X���W�̍X�V
	@param D3DXVECTOR3					�ʒu(x.y)
	@param XFileAnimationMesh::BOX		�{�b�N�X
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box,float _radian)
{
	float deg = D3DXToDegree(_radian);
	_box->min =  (_box->center + _position) - (_box->length / 2);
	float x1 = _box->min.x;
	float y1 = _box->min.y;
	_box->min.x = (x1) * cos(-deg) - (y1) * sin(-deg);
	_box->min.y = (x1) * sin(-deg) + (y1) * cos(-deg);

	_box->max = _box->length  + _box->min;
	
	_box->position = _position + _box->center;
}
/*--------------------------------------------------------------

	�{�b�N�X�̕`��f�o�b�O�p
	@param XFileAnimationMesh::BOX		�{�b�N�X
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::DrawBox(XFileAnimationMesh::BOX _box)
{
	D3DXMATRIX matTrans,matWorld,matScale;
	D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
	D3DXMatrixTranslation(&matTrans,_box.position.x ,_box.position.y,_box.position.z);
	D3DXMatrixIdentity(&matWorld);
	matWorld = matWorld * matScale * matTrans;
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// �{�b�N�X�̕\��
	m_pDevice->SetMaterial( _box.pMaterials );
	_box.pMesh->DrawSubset(0);

	m_pDevice->SetTexture( 0, NULL );
}
/*--------------------------------------------------------------

	�{�[���̈ʒu���Z�b�g
	@param LPDIRECT3DDEVICE9
	@param MYFRAME				

--------------------------------------------------------------*/
void CCharacter::SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame)
{
	_position->x = _pFrame->CombinedTransformationMatrix._41;
	_position->y = _pFrame->CombinedTransformationMatrix._42;
	_position->z = _pFrame->CombinedTransformationMatrix._43;
}
/*--------------------------------------------------------------

	�U�������`�̎擾
	@param �Ȃ�
	@return �{�b�N�X�z��

--------------------------------------------------------------*/
std::vector<XFileAnimationMesh::BOX> CCharacter::GetHittingBox()
{
	return m_hitting_box;
}
/*--------------------------------------------------------------

	���ꔻ���`�̎擾
	@param �Ȃ�
	@return �{�b�N�X�z��

--------------------------------------------------------------*/
std::vector<XFileAnimationMesh::BOX> CCharacter::GetunHittingBox()
{
	return m_unhitting_box;
}
///*--------------------------------------------------------------
//
//	�X�t�B�A�̎擾
//	@param �Ȃ�
//	@return �X�t�B�A�z��
//
//--------------------------------------------------------------*/
//std::vector<XFileAnimationMesh::SPHERE> CCharacter::GetSphere()
//{
//	return m_sphere;
//}
/*--------------------------------------------------------------

	�L�����N�^�[�̏�Ԃ��擾
	@param  �Ȃ�
	@return ���

--------------------------------------------------------------*/
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}
/*--------------------------------------------------------------

	�L�����N�^�[�̈ړ����x���擾
	@param �@	�Ȃ�
	@return		�ړ����x

--------------------------------------------------------------*/
D3DXVECTOR2 CCharacter::GetCharaSpeed()
{
	return m_move;
}
/*--------------------------------------------------------------

	�L�����N�^�[�̈ړ��ʂ��Z�b�g(Enemy�̍��W�ێ��Ɏg�p)
	@param float	�ړ���
	@return			�Ȃ�

--------------------------------------------------------------*/
void CCharacter::SetCharaSpeed(int _spd)
{
	m_speed.x = _spd * 0.015f;
}
/*--------------------------------------------------------------

	�Փ˔���p�̃t���O���Z�b�g
	@param bool �t���O
	@return		�Ȃ�

--------------------------------------------------------------*/
void CCharacter::SetHitFlag(bool _flag)
{
	m_isHit = _flag;
}
/*--------------------------------------------------------------

	��_���[�W���̃t���O���Z�b�g
	@param		�Ȃ�
	@return		�Ȃ�

--------------------------------------------------------------*/
void CCharacter::SetTakeDamageFlg()
{
	m_takeDamage = true;
}
///*--------------------------------------------------------------
//
//	�`��ʒu���Z�b�g����
//	@param	D3DXVECTOR3 �ʒu
//	@return �Ȃ�
//
//--------------------------------------------------------------*/
//void CCharacter::SetPosition(D3DXVECTOR3 _position)
//{
//	m_position = _position;
//}

float CCharacter::GetDamage()
{
	m_HitCount++;
	// �q�b�g����@�������́@���G��ԂȂ�_���[�W��0
	if( m_HitCount > 1 || m_invincible ){
		return 0;
	}
	return m_correctionValue;	// �_���[�W���擾
}
/*--------------------------------------------------------------

	���[�V���������Z�b�g����
	@param	int ���[�V����ID
	@return		�Ȃ�

--------------------------------------------------------------*/
void CCharacter::ResetMotion(int _motionID)
{
	// �L�����Z���s�̃��[�V�����͈ꎞ�I�ɃL�����Z���\�ɂ���
	// ���[�V�����ύX
	if(!m_animList[m_curMotionID].chancel && m_curMotionID != _motionID ) {
		m_animList[m_curMotionID].chancel = true;
		m_model->SetAnimList(&m_animList);
		m_model->ChangeMotion(_motionID);
		m_animList[m_curMotionID].chancel = false;
		// ���݂̃��[�V������ۑ�
		m_curMotionID  = _motionID;
		// ���[�V�������Ԃ����Z�b�g
		m_time = m_animList[m_curMotionID].startTime;
		m_model->SetAnimList(&m_animList);
	}
	else
		if( m_curMotionID != _motionID ){
			//m_curMotionID = m_model->ChangeMotion(_motionID);
			if(  m_model->ChangeMotion(_motionID) ){
				m_curMotionID = _motionID;
				// ���[�V�������Ԃ����Z�b�g
				m_time = m_animList[m_curMotionID].startTime;
			}
		}
	m_motionStop = false;
}
/*--------------------------------------------------------------

	���[�V�������I�����Ă��邩�`�F�b�N����
	@param  ���[�V�����ԍ�
	@return true�@: ���[�V�����I��
			false : ���[�V�����Đ���

--------------------------------------------------------------*/
bool CCharacter::CheckMotionEnd(int _motionID)
{
	if( m_animList[_motionID].endTime <= m_time )
		return true;
	
	return false;
}
/*--------------------------------------------------------------

	�A�j���[�V�������Ԃ�i�߂�
	@param	float �i�߂鎞��(��{�I��1.0f/60.f)
	@return �Ȃ�

--------------------------------------------------------------*/
void CCharacter::UpdateAnimTime(float _time)
{
	// ���Ⴊ�ݒ��ƃ|�[�Y���̓A�j���[�V�������Ԃ�i�߂Ȃ�
	if( CBattleScene::m_pause || m_motionStop ) return;
	// �A�j���[�V�����o�ߎ���
	m_time = m_model->AdvanceTime(_time);
}
/*--------------------------------------------------------------

	��Ԃ��擾(�퓬�J�n���o�����̔���)
	@param	�Ȃ�
	@return CCharacter �X�e�b�v

--------------------------------------------------------------*/
CCharacter::STEP CCharacter::GetStep()
{
	return m_step;
}
bool CCharacter::GetMotionEnd()
{
	return m_endMotion;
}

