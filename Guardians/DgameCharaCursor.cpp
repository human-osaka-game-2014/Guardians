/*--------------------------------------------------------------

	�������e:�J�[�\��(�L�����N�^�[)�̐���
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

--------------------------------------------------------------*/
CGameCharaCursor::CGameCharaCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get( TEX_CHARA_MENU );
	m_rect.left		= 0;
	m_rect.top		= 128;
	m_rect.right	= 140;
	m_rect.bottom   = 268;
}