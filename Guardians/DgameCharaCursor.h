/**
 * @file DgameCharaCursor.h
 */

/**
 * �L�����N�^�[�I��p�̃J�[�\���̐���
 */

#ifndef _GAME_CHARA_CURSOR_H_
#define _GAME_CHARA_CURSOR_H_

class CGameCharaCursor : public CGameCursor
{
private:
#define TEX_GAME_CHARA_CURSOR 6
public:
	CGameCharaCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// �R���X�g���N�^(�f�o�C�X�A���W���Z�b�g)

};

#endif