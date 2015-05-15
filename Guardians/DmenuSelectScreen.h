#ifndef _MENU_SELECT_SCREEN_H_
#define _MENU_SELECT_SCREEN_H_


class CMenuSelectScreen : public CMenuScreen
{
private:
	static const D3DXVECTOR2 BOSS_POSITION;	// 「ボス」描画位置
	
	static const int CURSOR_TYPE_NUM = 2;	// カーソルの種類は1個
	static const int TELOP_TYPE_NUM  = 4;	// テロップの種類は2個
	static const int WINDOW_TYPE_NUM = 2;	// ウィンドウの種類は2個

	// キャラカーソルの初期位置(出撃選択時は他のカーソルとの位置が違う為ここで宣言)
	static const D3DXVECTOR2 INIT_CHARA_CURSOR_POSITION;
	static const D3DXVECTOR2 INIT_CHARA_READY_POSITION;
	static const D3DXVECTOR2 INIT_SELECT_CURSOR_POSITION;

	int m_turnNo[3];
	enum WindowType
	{
		WND_EQUIP,
		WND_SELECT,
	};

	enum CursorType
	{
		CUR_CHARA,
		CUR_SELECT,
	};

	enum TelopType
	{
		TELOP_CHARA,
		TELOP_STAGE,
		STAGE_NAME,
		TELOP_BOSS,
	};

	int		m_selectID;		// はい、いいえ選択用
	int		m_charaID;
	bool	m_selectWndFlag;	// 選択肢が出されているかどうか
	int		m_selectCount;		// 何人順番が決定されたか
	int		m_oldID[3];  //出撃選択時のキャンセル用
public:
	CMenuSelectScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData);
	~CMenuSelectScreen();
	void Control(int _keyState);
	void Draw();

	bool GetBattleFlag();
};

#endif