/*--------------------------------------------------------------

	�������e:�J�[�\��(�I�����)�̐���
	�쐬��:�h��
	�쐬��:9/23
	�X�V��:10/6
	�X�V���e:
	�֐��@
		10/6
		�R���X�g���N�^�̒ǉ�
		�R���X�g���N�^���Ńe�N�X�`�����̌Ăяo��
		rect�Ƀe�N�X�`�����W���i�[
		�E�C���h�E���L����t���O��true��
	�ϐ��@
		m_rect


--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X�A���W�A�g�p�摜ID���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`�悷��ʒu(x,y)
	@param D3DXVECTOR2			�E�C���h�E�̍ő�T�C�Y(x,y)

--------------------------------------------------------------*/
CGameSelectCursor::CGameSelectCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get(TEX_CURSOR);

	switch(_curType){
	case CUR_SELECT:
		m_rect.left		= 384;
		m_rect.top		= 237;
		m_rect.right    = 768;
		m_rect.bottom	= 305;
		break;
	case CUR_DATA:
		m_rect.left		= 229;
		m_rect.top		= 0;
		m_rect.right    = 403;
		m_rect.bottom	= 49;
		break;
	case CUR_SHOP:
		m_rect.left		= 0;
		m_rect.top		= 0;
		m_rect.right    = 229;
		m_rect.bottom	= 54;
	}
}