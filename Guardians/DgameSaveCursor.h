/**
 * @file DgameSaveCursor.h
 */

/**
 * �Z�[�u��ʑI��p�̃J�[�\���̐���
 */


#ifndef _GAME_SAVE_CURSOR_H_
#define _GAME_SAVE_CURSOR_H_


class CGameSaveCursor : public CGameCursor
{
private:
	
public:
	CGameSaveCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// �R���X�g���N�^(�f�o�C�X�A���W���Z�b�g)
};

#endif