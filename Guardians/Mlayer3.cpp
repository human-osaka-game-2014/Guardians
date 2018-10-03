/*--------------------------------------------------------------

	�������e:���C���[3(�u)�̐���A�`��
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

CLayer3::CLayer3(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer(_pDevice,D3DXVECTOR3(-90.f,8.5f,3.f), _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane3.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_HILL_TREE+(_stageID*7) );
	m_plane->SetScale(D3DXVECTOR3( 15.f,140.f,1.f));
}

void CLayer3::SetCharaSpeed(D3DXVECTOR2 _speed)
{
	m_speed.x = _speed.x*0.2f;
//	m_speed.y = _speed.y*0.7f;
	m_speed.y = _speed.y;
}

