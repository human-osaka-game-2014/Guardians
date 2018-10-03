#include  "stdafx.h"

/*------------------------------------------
   
    �R���X�g���N�^(�f�o�C�X���̃R�s�[)       
	@param LPDIRECT3DDEVICE9  �`��f�o�C�X

------------------------------------------*/
CCamera::CCamera(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice)
{
	m_pDevice->GetTransform( D3DTS_VIEW, &m_InitMatView );
	m_pDevice->GetTransform( D3DTS_PROJECTION, &m_InitMatProj );
}
CCamera::~CCamera()
{
	m_pDevice->SetTransform( D3DTS_VIEW, &m_InitMatView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &m_InitMatProj );
}
/*------------------------------------------
   
    �J�����̈ʒu�ƒ����_�̐ݒ�    
	@param D3DXVECTOR3  �J�����̈ʒu
	@oaram D3DXVECTOR3  �����_

------------------------------------------*/
void CCamera::Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos)
{
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // �J�����̏������ݒ�
	float viewAngle = D3DXToRadian(50);       // ����p
	float aspect = 1280.f/720.f;              // �A�X�y�N�g��
	float nearZ = 10.f;                       // �ŋߓ_
	float farZ = 100.f;                       // �ŉ��_

	// �r���[�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &_eyePos, &_lookAtPos, &upVec);
	// �ˉe�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	//�f�o�C�X�ɓo�^
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}