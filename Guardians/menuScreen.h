#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_




class CMenuScreen
{
public:
	enum State		// 画面の状態
	{
		STATE_WAIT,
		STATE_MOVE,
	};
protected:
	LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	State				m_state;		// 状態
	CGameCursor**		m_gameCursor;	// ゲームカーソル
	CGameWindow**		m_gameWindow;	// ゲームウィンドウ
	CGameTelop**		m_gameTelop;	// ゲームテロップ
	CGameData*			m_pGameData;		// ゲームデータの参照
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