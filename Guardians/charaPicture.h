#ifndef _CHARA_PICTURE_H_
#define _CHARA_PICTURE_H_

class CCharaPicture
{
public:
enum Type
{
	TYPE_STAGE_SELECT,		// ����-�X�e�[�W�I��-
	TYPE_STATUS,			// ����-�X�e�[�^�X-
	TYPE_SHOP,				// ����-�V���b�v-
	TYPE_SAVE,				// ����-�Z�[�u-

	TYPE_MAX,
};
private:
	LPDIRECT3DDEVICE9	m_pDevice;		// �`��f�o�C�X
	D3DXVECTOR2			m_position;		// ���W
	int					m_textureID;	// �e�N�X�`��ID
	CVertex             m_vertex;    
	CTexture            m_tex;
	Type				m_typeID;

private:

public:


	CCharaPicture(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _textureID, Type _typeID);	// �R���X�g���N�^(�f�o�C�X�A���W�A�e�N�X�`��ID���Z�b�g)
	void Draw();																		// �`��
};

#endif