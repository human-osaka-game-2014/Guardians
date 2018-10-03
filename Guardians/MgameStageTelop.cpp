/*--------------------------------------------------------------

	�������e:�e���b�v��ɃX�e�[�W����`��
	�쐬��:�O�Y
	�쐬��:9/27
	�X�V��:9/27
	       10/11
	�X�V���e:
	   9/27  Draw�̒ǉ�
	   10/11 �e�N�X�`�����W�̒���
	�֐��@
		�R���X�g���N�^�̒ǉ�
		Control
		Draw
	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"

CGameStageTelop::CGameStageTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID) :
	CGameTelop( _pDevice, _position, 1280.f ) , m_stageID( _stageID)
{
	m_stageTex = CTexMgr.Get( TEX_FIELD_MENU );
}
CGameStageTelop::~CGameStageTelop()
{

}
void CGameStageTelop::Control()
{
	CGameTelop::Control();
}

void CGameStageTelop::Draw()
{
	CGameTelop::Draw();
//			m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y );
//			m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x+640.f, m_position.y ); // �e�N�X�`���̐؂�����W�ǉ�
	switch(m_stageID){ // �X�e�[�WID�ɂ���ăX�e�[�W����ω�������
	case 0:
		m_vertex.DrawTextureLT( m_pDevice, m_stageTex, 730.f, 630.f, 500, 0, 954, 64 ); 
		break;

	default: // �X�e�[�W���ǉ������ƃP�[�X�𑝂₵�Ă���
		break;
	}
}