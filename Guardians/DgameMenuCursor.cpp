/*--------------------------------------------------------------

	�������e:�J�[�\��(���j���[)�̐���
	�쐬��:�h��
	�쐬��:9/23
	�X�V��:9/23
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
	@param int					�g�p����摜ID

--------------------------------------------------------------*/
CGameMenuCursor::CGameMenuCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_FIELD_MENU );
	m_flickFlag = false;	// ���̃J�[�\���͓_�ł����Ȃ�
	m_rect.left		= 140;
	m_rect.top		= 200;
	m_rect.right	= 185;
	m_rect.bottom	= 345;
}