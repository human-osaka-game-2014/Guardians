/**
 * @file Dcharacter.cpp
 * @brief �������e:
 * @author �h��
 * @date �쐬��: 11/6
 * @date �X�V��: 11/6
 */

#include "stdafx.h"

const float CCharacter::RIGHT_WALL = 58.f;
const float CCharacter::LEFT_WALL  = -34.f;

const float CCharacter::LEFT_ANGLE  = 90;	// �L�����N�^�[�̌����@��
const float CCharacter::RIGHT_ANGLE = -90;	// �L�����N�^�[�̌��� �E

float CCharacter::m_alpha = 1.0f;

/**
 * �R���X�g���N�^(�f�o�C�X���Z�b�g)
 * @param _pDevice �`��f�o�C�X
 * @param[in] _angle
 */
CCharacter::CCharacter(LPDIRECT3DDEVICE9 _pDevice,float _angle) : m_pDevice(_pDevice) , m_state(STATE_WAIT)
,m_curMotionID(0),m_speed(0.f,0.f) , m_isHit(false) , m_damage(0)
, m_scale(0.f,0.f,0.f) , m_step(STEP_MOVE) , m_move(0.f,0.f) , m_actionGauge(ACTION_GAUGE_MAX),m_box(0) , m_curEffect(0)
, m_time(0),m_invincible(false)
{
	
}

/**
 * �f�X�g���N�^
 */
CCharacter::~CCharacter()
{

}

/**
 * �Փ˔���Ɏg�p�����`�̐������߂�
 */
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
/**
 * �A�j���[�V�������Ԃ�i�߂�
 * @param[in] _time �i�߂鎞��(��{�I��1.0f/60.f)
 */
void CCharacter::UpdateAnimTime(float _time)
{
	// ���Ⴊ�ݒ��ƃ|�[�Y���̓A�j���[�V�������Ԃ�i�߂Ȃ�
	if( CBattleScene::m_pause || m_motionStop ) return;
	// �A�j���[�V�����o�ߎ���
	m_time = m_model->AdvanceTime(_time);
}
/**
 * �{�[���̈ʒu���擾����
 * @param[in] _name �{�[���̖��O
 */
D3DXVECTOR3 CCharacter::GetBonePos(LPCTSTR _name)
{
	MYFRAME* m_frame;	// �t���[��
	D3DXVECTOR3 position;	// �{�[���̈ʒu�i�[�p
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );

	SetBonePos(&position,m_frame);

	return position;
}
/**
 * ��`���X�V
 * @param[in] _name �{�[���̖��O
 * @param[in] _ID	�{�b�N�X��index
 */
void CCharacter::UpdateRect(LPCTSTR _name , int _ID )
{
	UpdateBox(GetBonePos(_name),&m_box[_ID]);	// ��`�̈ʒu���X�V
}
/**
 * �{�[���̈ʒu���Z�b�g
 * @param[out] _position �{�[���̈ʒu
 * @param[in] _pFrame
 */
D3DXMATRIX CCharacter::GetMatrix(LPCTSTR _name )
{
	MYFRAME* m_frame;	// �t���[��
	D3DXVECTOR3 position;	// �{�[���̈ʒu�i�[�p
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );
	return m_frame->CombinedTransformationMatrix;
}
/**
 * �{�[���̈ʒu���Z�b�g
 * @param[in] _position �{�[���̈ʒu
 * @param[in] _pFrame
 * @param[in] _radian
 */
void CCharacter::UpdateRect(D3DXVECTOR3 _position , int _ID)
{
	UpdateBox(_position,&m_box[_ID]);
	// ��`�̕`��(�f�o�b�O�p)
	#ifdef _DEBUG
		DrawBox(m_box);
	#endif
}

/**
 * �{�b�N�X���W�̍X�V
 * @param[in] _position �ʒu(x.y)
 * @param[in] _box �{�b�N�X
 * @param[in] _radian
 */
void CCharacter::UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box)
{
	_box->min =  (_box->center + _position) - (_box->length / 2);
	_box->max = _box->length  + _box->min;

	_box->position = _position + _box->center;

}
/**
 * �{�[���̈ʒu���Z�b�g
 * @param[out] _position �{�[���̈ʒu
 * @param[in] _pFrame
 */
void CCharacter::SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame)
{
	_position->x = _pFrame->CombinedTransformationMatrix._41;
	_position->y = _pFrame->CombinedTransformationMatrix._42;
	_position->z = _pFrame->CombinedTransformationMatrix._43;
}

/**
 * �U�������`�̎擾
 * @return �{�b�N�X�z��
 */
std::vector<XFileAnimationMesh::BOX> CCharacter::GetHittingBox()
{
	return m_hitting_box;
}

/**
 * ���ꔻ���`�̎擾
 * @return �{�b�N�X�z��
 */
std::vector<XFileAnimationMesh::BOX> CCharacter::GetunHittingBox()
{
	return m_unhitting_box;
}
/**
 * �L�����N�^�[�̏�Ԃ��擾
 * @return ���C
 */
XFileAnimationMesh::RAY_PARAM CCharacter::GetRay()
{
	return m_ray;
}

/**
 * �L�����N�^�[�̏�Ԃ��擾
 * @return ���
 */
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}

/**
 * �L�����N�^�[�̈ړ����x���擾.
 * �L�����N�^�[�̈ړ��ʂ���t�B�[���h�̈ړ��ʂ����߂鎞�Ɏg�p
 * @return �ړ����x
 */
D3DXVECTOR2 CCharacter::GetCharaSpeed()
{
	return m_move;
}
/**
 * �L�����N�^�[�̈ړ��ʂ��Z�b�g
 * @return float �_���[�W
 */
float CCharacter::GetDamage()
{
	m_HitCount++;
	// �q�b�g����@�������́@���G��ԂȂ�_���[�W��0
	if( m_HitCount > 1 || m_invincible ){
		return 0;
	}
	return m_correctionValue;	// �_���[�W���擾
}
/**
 * �L�����N�^�[�̈ړ��ʂ��Z�b�g
 * @param[in] _spd �ړ���
 */
void CCharacter::SetCharaSpeed(int _spd)
{
	m_speed.x = _spd * 0.015f;
}

/**
 * �Փ˔���p�̃t���O���Z�b�g
 * @param[in] _flag �t���O
 */
void CCharacter::SetHitFlag(bool _flag)
{
	m_isHit = _flag;
}

/**
 * ���[�V���������Z�b�g����
 * @param[in] _motionID ���[�V����ID
 */
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

/**
 * ���[�V�������I�����Ă��邩�`�F�b�N����
 * @param[in] _motionID ���[�V�����ԍ�
 * @retval true ���[�V�����I��
 * @retval false ���[�V�����Đ���
 */
bool CCharacter::CheckMotionEnd(int _motionID)
{
	if( m_animList[_motionID].endTime <= m_time )
		return true;
	
	return false;
}

/**
 * ��Ԃ��擾(�퓬�J�n���o�����̔���)
 * @return �X�e�b�v
 */
CCharacter::STEP CCharacter::GetStep()
{
	return m_step;
}

/**
 * �{�b�N�X�̕`��f�o�b�O�p
 * @param[in] _box �{�b�N�X
 */
void CCharacter::DrawBox(std::vector<XFileAnimationMesh::BOX> _box)
{
#ifdef DEBUG
	for(unsigned i = 0; i < _box.size(); i++){
		D3DXMATRIX matTrans,matWorld,matScale;
		D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
		D3DXMatrixTranslation(&matTrans,_box[i].position.x ,_box[i].position.y,_box[i].position.z);
		D3DXMatrixIdentity(&matWorld);
		matWorld = matWorld * matScale * matTrans;
		m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
		// �{�b�N�X�̕\��
		m_pDevice->SetMaterial( _box[i].pMaterials );
		_box[i].pMesh->DrawSubset(0);

		m_pDevice->SetTexture( 0, NULL );
	}
#endif
}
/**
 * ���C�̕`��
 * @param[in] _pos	�@�`��ʒu
 * @param[in] _rayDir ���C�̃x�N�g��
 */
void CCharacter::DrawRay(D3DXVECTOR3 _pos,D3DXVECTOR3 _rayDir)
{
#ifdef DEBUG
	m_pDevice->SetVertexShader(NULL);
	m_pDevice->SetFVF(D3DFVF_XYZ);
	
	D3DXVECTOR3 vec[2]; // ���C�̊J�n�n�_�ƏI���n�_

	vec[0] = D3DXVECTOR3(0,0,0);
	vec[1] = _rayDir;

	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld,_pos.x,_pos.y,_pos.z);
	// ���C�̊J�n�n�_���Z�b�g����
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//���C�̃}�e���A��
	D3DMATERIAL9 mat;
	ZeroMemory(&mat,sizeof(mat));	

	mat.Diffuse.a = 255;
	mat.Diffuse.r = 255;
	mat.Diffuse.g = 255;
	mat.Diffuse.b = 255;
	mat.Ambient = mat.Diffuse;
	m_pDevice->SetMaterial( &mat );
	//���C�̃����_�����O
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vec, sizeof(D3DXVECTOR3));
#endif
}
