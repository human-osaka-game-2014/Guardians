#ifndef _GAME_SHOPLIST_WINDOW_H_
#define _GAME_SHOPLIST_WINDOW_H_


class CGameShopListWindow : public CGameWindow
{
private:
	
	D3DXVECTOR2 CURSOR_INIT_POSITION;	// �J�[�\���������W
	static const D3DXVECTOR2 SHOP_MONEY_POSITON;	// �u���z�v�`����W
	static const D3DXVECTOR2 SHOP_HAS_POSITION;		// �u�������v�`����W
	static const D3DXVECTOR2 SHOP_TOOL1_POSITION;	// �u1�ڂ̃A�C�e�����v�`����W
	static const D3DXVECTOR2 SHOP_MONEY1_POSITION;	// �u1�ڂ̃A�C�e�����z�v�`����W
	static const D3DXVECTOR2 SHOP_HAS1_POSITION;	// �u1�ڂ̃A�C�e���������v�`����W

	static const int MAX_ITEM_NUMBER = 9;			// �ő區�ڕ\����
	static const int SCHROLLBAR_HIGHT =305;			//�X�N���[���o�[�g�̒��̍���

	static const int MAX_WIDTH	= 740;				// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 585;				// �E�B���h�E�ő卂��

	int m_type;
	unsigned int	m_cursorPos;											
	unsigned int m_drawID;
									// �I������Ă���L������ID���Z�b�g


	CGameData*			m_pGameData;				// �Q�[���f�[�^�̎Q��
	CGameItemCursor*	m_pCursor;					// �I��p�J�[�\��
public:
	CGameShopListWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A�I�����ꂽ�^�C�v���Z�b�g)
	~CGameShopListWindow();
	void Control();																										// ����
	void Draw();																										// �`��

	void SetCursorPosition(int _pos);// �I������Ă��鑕����ID���Z�b�g
	void SetSelectID(int _select);
	int Sarch(int _oldID,int _No);
};

#endif