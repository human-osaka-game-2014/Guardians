/*--------------------------------------------------------------

	�������e:
	�쐬��:�h��
	�쐬��:10/8
	�X�V��:10/8
	�X�V���e:
	�֐��@

	�ϐ��@

--------------------------------------------------------------*/


#include "stdafx.h"

CCharaPicture::CCharaPicture(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _textureID, Type _typeID) :
m_pDevice( _pDevice ), m_position( _position ), m_textureID( _textureID ), m_typeID( _typeID )
{
	m_tex = CTexMgr.Get(m_textureID);
}
void CCharaPicture::Draw()
{
	FRECT rect;
	switch( m_typeID ) {
	case TYPE_STAGE_SELECT:		// ����-�X�e�[�W�I��-
		rect.left	= 0;
		rect.right	= 256;
		rect.top	= 0;
		rect.bottom = 41;
		break;
	case TYPE_STATUS:
		rect.left	= 0;
		rect.right	= 256;
		rect.top	= 41;
		rect.bottom = 82;
		break;
	case TYPE_SHOP:
		rect.left	= 0;
		rect.right	= 256;
		rect.top	= 82;
		rect.bottom = 123;
		break;
	case TYPE_SAVE:
		rect.left	= 0;
		rect.right	= 256;
		rect.top	= 123;
		rect.bottom = 164;
		break;
	default:
		rect.left	= 0;
		rect.right	= 256;
		rect.top	= 0;
		rect.bottom = 41;
		break;

	}
	
	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y, rect );
}