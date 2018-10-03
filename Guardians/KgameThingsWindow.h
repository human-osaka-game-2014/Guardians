#ifndef _GAME_THINGS_WINDOW_H_
#define _GAME_THINGS_WINDOW_H_


class CGameThingsWindow : public CGameWindow
{	
private:
	static const D3DXVECTOR2 CURSOR_INIT_POSITION;	// �J�[�\���������W
	static const D3DXVECTOR2 SCROLLBAR_POSITION;	// �X�N���[���o�[�`����W
	static const D3DXVECTOR2 SELECT_THING1_POSITION;// �u1�ڂ̑I�𑕔�(����)�v�`����W

	static const int MAX_ITEM_NUMBER = 8;			// �ő區�ڕ\����
	static const int SCROLL_BAR_HEIGHT= 240;        // �X�N���[���o�[�̍����@�@�@10/13 �ǉ�
	static const int MAX_WIDTH	= 465;				// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 500;				// �E�B���h�E�ő卂��

	CGameData*			m_pGameData;				// �Q�[���f�[�^�̎Q��
	CGameItemCursor*	m_pCursor;					// �I��p�J�[�\��
	int					m_type;						// �I�����ꂽ�^�C�v(����or����)
	int					m_charaID;					// �L�����N�^�[ID
	int					m_cursorPos;				//�����ŃJ�[�\���ʒu�̎擾
	int					m_drawID;


	CTexture					m_textureicon[2];
public:
	CGameThingsWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type, int _charaID = -1);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A�I�����ꂽ�^�C�v�A(�L����ID)���Z�b�g)
	~CGameThingsWindow();
	void Control();																								// ����
	void Draw();																								// �`��

	// �J�[�\���̈ʒu���Z�b�g
	void SetCursorPosition(int _pos);	
	// �I������Ă���L������ID���Z�b�g
	void SetSelectID(int _select);
	// �`�悳��Ă���ʒu���Z�b�g
	void SetDrawID(int _drawID);
	// �Q�[���f�[�^���擾
	CGameData* GetGameData();
};

#endif