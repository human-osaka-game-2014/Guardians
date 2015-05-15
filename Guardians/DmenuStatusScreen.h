#ifndef _MENU_STATUS_SCREEN_H_
#define _MENU_STATUS_SCREEN_H_

class CMenuStatusScreen : public CMenuScreen
{
private:


	static const int CURSOR_TYPE_NUM = 3;	// カーソルの種類は2個
	static const int TELOP_TYPE_NUM =  2;	// テロップの種類は2個
	static const int WINDOW_TYPE_NUM = 3;	// ウィンドウの種類は3個
	//10/6 追加
	static const int EQUIP_SELECT_NUM = 6;	//装備選択画面の項目は6個



	enum WindowType
	{
		WND_STATUS,
		WND_EQUIP,
		WND_THING,
	};

	enum CursorType
	{
		CUR_CHARA,
		CUR_EQUIP,
		CUR_CHANGE,
		CUR_ITEM,
	};

	enum TelopType
	{
		TELOP_CHARA,
		TELOP_EXPLAIN,
	};

	enum State
	{
		STATE_SELECT = 2,	// キャラ/装備/道具選択
		STATE_WINDOW_MOVE,	// ウィンドウ移動
		STATE_CHANGE,		// 装備/道具変更
	};
	enum ChangeType
	{
		add,
		subtract,
	};
//	CGameWindow		m_window;


	float	m_equipPos;		// 装備選択カーソルの位置情報を保存
	int		m_changeID;		// 変更しようとしている装備
	int		m_drawID;		// 描画番号
	int		m_charaID;		// 選択されているキャラ番号
	int		m_itemNum;		// 所持しているアイテムの種類数
	State	m_state;		// 状態
public:
	CMenuStatusScreen(LPDIRECT3DDEVICE9 _pDevice, CGameData* _gameData);
	~CMenuStatusScreen();
	void Control(int _keyState);
	void Draw();

	//仮
	int GetSelectID();
private:
	void ChangeStatus(int _equipID,ChangeType _type);
};

#endif