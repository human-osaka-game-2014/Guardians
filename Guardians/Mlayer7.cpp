/*--------------------------------------------------------------

	�������e:���C���[7(��)�̐���A�`��
	�쐬��:�O�Y
	�쐬��:10/24
	�X�V��:
	�X�V���e:
		
	�֐��@
		�R���X�g���N�^
		SetCharaSpeed 
		�@�L�����̃X�s�[�h�ɂ���ă��C���[�̈ړ����x�v�Z�A�o�^
		Control
		�@���C���[���ړ�������
		Draw
	�ϐ��@

--------------------------------------------------------------*/
#include "stdafx.h"

CLayer7::CLayer7(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer(_pDevice, D3DXVECTOR3(-90.f,-1.2f,3.f), _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane7.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_STONE+(_stageID*7) );
	m_plane->SetScale(D3DXVECTOR3( 13.f,140.f,1.f));
}


void CLayer7::SetCharaSpeed(D3DXVECTOR2 _speed)
{
	//m_speed.x = _speed.x*1.f;
	//m_speed.y = _speed.y*1.f;
}
