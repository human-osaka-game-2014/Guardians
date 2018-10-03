/*--------------------------------------------------------------

	�������e:�e���b�v�̕`��
	�쐬��:�O�Y
	�쐬��:9/27
	�X�V��:9/27
	�X�V���e:
		9/27     Draw�ǉ�
		10/11�@�@�w�b�_�[��Control,Draw��virtual�Ő錾
	�֐��@
		�R���X�g���N�^�̒ǉ�
		Control
		Draw
	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"

CGameTelop::CGameTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth) : 
	m_pDevice( _pDevice ), m_position( _position ), m_maxWidth( _maxWidth )
{
	m_tex = CTexMgr.Get( TEX_TELOP );
}
void CGameTelop::Draw()
{
	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y, 0, 0, 604, 100 );
		m_vertex.SetSizeX(1.1f);
	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x+604.f, m_position.y, 0, 101, 604, 200 );
		m_vertex.SetSizeX(1.0f);
}