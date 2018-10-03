/*--------------------------------------------------------------

	�������e:�{�X�e���b�v�̕`��
	�쐬��:�O�Y
	�쐬��:9/27
	�X�V��:9/27
	�X�V���e:
	    9/27  Draw�ǉ�
		10/11 �e�N�X�`�����W�̒���
	�֐��@
		�R���X�g���N�^
		Control
		Draw
	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"

CGameBossTelop::CGameBossTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID) :
	CGameTelop(_pDevice, _position, 640.f), m_stageID( _stageID )
{
	m_bossTex = CTexMgr.Get( TEX_BOSS );
}
CGameBossTelop::~CGameBossTelop()
{

}
void CGameBossTelop::Control()
{
	CGameTelop::Control();
}

void CGameBossTelop::Draw()
{
	CGameTelop::Draw();

//	m_vertex.SetSizeY(50.f);
//	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y, 0, 0, 300, 680 );  // �e�N�X�`���̐؂�����W�ǉ�

	switch( m_stageID ){
	case 0:
		m_vertex.SetSizeY(1.0f);
		m_vertex.SetSizeX(1.0f);
		m_vertex.DrawTextureLT( m_pDevice,  m_bossTex, m_position.x, m_position.y, 0 ,0, 300, 680 );
		m_vertex.SetSizeY(0.5f);
     	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x-310.f, m_position.y+510.f, 0, 0, 604, 100 );  // �{�X���e���b�v
		m_vertex.SetSizeY(1.0f);
		m_vertex.DrawTextureLT( m_pDevice, m_bossTex, m_position.x+15.f, m_position.y+520.f, 0, 680, 128, 712 );
		m_vertex.DrawTextureLT( m_pDevice, m_bossTex, m_position.x+145.f, m_position.y+520.f, 0, 713, 128, 746 );
		break;

	default:
		break;
	}
	//switch( m_stageID ){
	//case 0:
	//	m_vertex.SetSizeY(50.f);
	//	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x-310.f, m_position.y+510.f, 0, 0, 604, 100 );  // �e�N�X�`���̐؂�����W�ǉ�
	//	break;

	//default:
	//	break;
	//}
}
