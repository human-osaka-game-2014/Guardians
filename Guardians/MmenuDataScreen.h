#ifndef _MENU_DATA_SCREEN_H_
#define _MENU_DATA_SCREEN_H_

class CMenuDataScreen : public CMenuScreen
{
private:
	static const int CURSOR_TYPE_NUM = 3;
	static const int TELOP_TYPE_NUM = 1;
	static const int WINDOW_TYPE_NUM = 2;

	enum WindowType{
		WND_SAVE,
		WND_SELECT,
	};

	enum CursorType{
		CUR_PART,
		CUR_DATA,
		CUR_SELECT
	};

	enum TelopType{
		TELOP_NONE,
	};
	enum SelectType{
		YES,
		NO,
	};

	enum State{
		STATE_PART,
		STATE_DECIDE,
	};

	enum SaveType{
		SAVE,
		LOAD,
	};

	D3DXVECTOR2 m_dataPos;
	int   m_partID;
	int   m_dataID;
	int   m_selectID;
	int   m_page;
	int   m_state;
	int	  m_drawID;
public:
	CMenuDataScreen(LPDIRECT3DDEVICE9 _pDevice, CGameData* _gameData);
	~CMenuDataScreen();
	void Control(int _keyState);
	void Draw();


};

#endif