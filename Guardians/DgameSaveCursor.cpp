/*--------------------------------------------------------------

	�������e : �Z�[�u��ʂ̃J�[�\���̐���
	�쐬��:�h��
	�쐬��:10/6
	�X�V��:10/6
	�X�V���e:
	�֐��@
		�R���X�g���N�^�̒ǉ�
	�ϐ��@

--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X�A���W�A�g�p�摜ID���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`�悷��ʒu(x,y)
	@param D3DXVECTOR2			�E�C���h�E�̍ő�T�C�Y(x,y)

--------------------------------------------------------------*/
CGameSaveCursor::CGameSaveCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CURSOR );
	m_rect.left		= 0;
	m_rect.top		= 108;
	m_rect.right    = 789;
	m_rect.bottom	= 237;

}