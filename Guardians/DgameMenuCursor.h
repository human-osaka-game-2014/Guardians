/**
 * @file DgameMenuCursor.h
 */

/**
 * ���j���[��ʑI��p�̃J�[�\���̐���
 */


#ifndef _GAME_MENU_CURSOR_H_
#define _GAME_MENU_CURSOR_H_


class CGameMenuCursor : public CGameCursor
{
private:
	static const int TEX_GAME_MENU_CURSOR = 5;
public:
	CGameMenuCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// �R���X�g���N�^(�f�o�C�X�A���W���Z�b�g)
};

#endif