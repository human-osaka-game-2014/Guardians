#include "stdafx.h"

/*--------------------------------------------------------------

	�������e:�A�C�e���A�A�N�Z�T���[�̕\��
	�쐬��:��
	�쐬��:10/07
	�X�V��:10/09
	  �`����W�̏C��

	�֐��@
		draw�̍쐬
	�ϐ��@
		�ǉ��Ȃ�

--------------------------------------------------------------*/

CGameShopMenuWindow::CGameShopMenuWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) :
CGameWindow( _pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT) )
{
}

void CGameShopMenuWindow::Control()
{
	CGameWindow::Control();
}

void CGameShopMenuWindow::Draw()
{
	CGameWindow::Draw();
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-55, m_position.y-65,0,620,256,652);		//�A�C�e���̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-85, m_position.y+5,0,652,256,684);		//�A�N�Z�T���[�̕\��
}