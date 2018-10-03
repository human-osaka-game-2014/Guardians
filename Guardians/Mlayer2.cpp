/*--------------------------------------------------------------

	�������e:���C���[2(�R)�̐���A�`��
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

CLayer2::CLayer2(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer( _pDevice, D3DXVECTOR3(-90.f,0.5f,3.f), _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane2.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_MOUNTAIN+(_stageID*7) );
	m_plane->SetScale(D3DXVECTOR3(8.f,140.f,1.f));
}

void CLayer2::SetCharaSpeed(D3DXVECTOR2 _speed)
{
	m_speed.x = _speed.x*0.7f;
	m_speed.y = _speed.y*0.5f;
}
