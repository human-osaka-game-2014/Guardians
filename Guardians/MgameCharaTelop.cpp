/*--------------------------------------------------------------

	�������e:�L�����N�^�[�̕`��
	�쐬��:�O�Y
	�쐬��:9/27
	�X�V��:9/27
	�X�V���e:
	   9/27    Draw�̒ǉ�
	   10/11   ���j���[�̔ԍ��ɂ��L�����N�^�[�`��ʒu��switch��
	�֐��@
		�R���X�g���N�^�̒ǉ�
		Control
		Draw
	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"

// �R���X�g���N�^
CGameCharaTelop::CGameCharaTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID) :
	CGameTelop(_pDevice, _position, 1280.f), m_menuID( _menuID ), m_pGameData(_pGameData)
{
	m_charaTex = CTexMgr.Get( TEX_CHARA_MENU );
}
CGameCharaTelop::~CGameCharaTelop()
{

}
void CGameCharaTelop::Control()
{
	CGameTelop::Control();
}

void CGameCharaTelop::Draw()
{
	CGameTelop::Draw();
	switch( m_menuID ){
	case 0:
	        // m_vertex.DrawTextureLT( m_pDevice,  m_charaTex, 110.f, 45.f, 0, 0, 128, 128 ); // ���݂͏o�����ԌŒ�i��ŕύX����j
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x,m_position.y, 0, 0, 128, 128 );  // �A���h�t�@�E�g
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x+(128.f+42.f),m_position.y, 128, 0, 256, 128 );  // �l���}��
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x+(256.f+42*2.f),m_position.y, 256, 0, 384, 128 );  // �~�l���c�@

		break;
	case 1:
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x,m_position.y, 0, 0, 128, 128 );  // �A���h�t�@�E�g
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x+170.f,m_position.y, 128, 0, 256, 128 );  // �l���}��
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x+340.f,m_position.y, 256, 0, 384, 128 );  // �~�l���c�@
							for(int i = 0; i < 3; i++){
		switch(	m_pGameData->m_turnNo[i]){
		case 0:
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x + (i * (128.f+42.f)),m_position.y, 140,128,204,192 );  
			break;
		case 1:
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x + (i * (128.f+42.f)),m_position.y, 204,128,268,192 );  
			break;
		case 2:
			m_vertex.DrawTextureLT( m_pDevice, m_charaTex, m_position.x + (i * (128.f+42.f)),m_position.y, 268,128,332,192 );
			break;
		}
	}
		break;

	default: 
		break;
	}

}