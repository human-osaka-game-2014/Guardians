/*--------------------------------------------------------------

	�������e:���C���[1(��)�̐���A�`��
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

CLayer1::CLayer1(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer( _pDevice, D3DXVECTOR3(-100.f,30.f,3.f), _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane1.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_SKY+(_stageID*7) ); // stageID*7�����邱�ƂŃX�e�[�W���Ƃ̃��C���[�ω�
	m_plane->SetScale(D3DXVECTOR3( 80.f,160.f,1.f));
}
void CLayer1::SetCharaSpeed(D3DXVECTOR2 _speed) 
{
	m_speed.x = _speed.x * 0.9f;
	m_speed.y = _speed.y * 0.55f;
}

