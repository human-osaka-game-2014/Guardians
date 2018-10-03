#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_




class CMenuScreen
{
public:
	enum State		// ��ʂ̏��
	{
		STATE_WAIT,
		STATE_MOVE,
	};
protected:
	LPDIRECT3DDEVICE9	m_pDevice;		// �`��f�o�C�X
	State				m_state;		// ���
	CGameCursor**		m_gameCursor;	// �Q�[���J�[�\��
	CGameWindow**		m_gameWindow;	// �Q�[���E�B���h�E
	CGameTelop**		m_gameTelop;	// �Q�[���e���b�v
	CGameData*			m_pGameData;		// �Q�[���f�[�^�̎Q��
	CMenuBar*			m_menuBar;

	int					m_equipID;
	bool    m_battleFlag;
public:
	CMenuScreen(LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CMenuScreen();
	virtual void Control(int _keyState) = 0;
	virtual void Draw() = 0;
};

#endif