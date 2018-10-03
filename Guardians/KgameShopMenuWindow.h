#ifndef _GAME_SHOPMENU_WINDOW_H_
#define _GAME_SHOPMENU_WINDOW_H_


class CGameShopMenuWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 CURSOR_INIT_POSITION;		// �J�[�\���������W
	static const D3DXVECTOR2 MENU_TOOLS_POSITION;		// ���j���[�u�A�C�e���v�`����W
	static const D3DXVECTOR2 MENU_ACCESSORY_POSITION;	// ���j���[�u�A�N�Z�T���v�`����W

	static const int MAX_WIDTH	= 290;			// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 250;			// �E�B���h�E�ő卂��

	CGameItemCursor*	m_pCursor;			// �I��p�J�[�\��
	SelectType			m_type;				// �I�����ꂽ�^�C�v(�A�C�e��or�A�N�Z�T��)
public:
	CGameShopMenuWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);		// �R���X�g���N�^(�f�o�C�X�A���W���Z�b�g)
	void Control();																// ����
	void Draw();																// �`��

	// �A�N�Z�b�T
	SelectType GetItemType();													// �I������Ă��鍀�ڂ̃^�C�v���擾
};

#endif