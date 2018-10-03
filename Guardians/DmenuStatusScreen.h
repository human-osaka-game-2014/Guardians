#ifndef _MENU_STATUS_SCREEN_H_
#define _MENU_STATUS_SCREEN_H_

class CMenuStatusScreen : public CMenuScreen
{
private:


	static const int CURSOR_TYPE_NUM = 3;	// �J�[�\���̎�ނ�2��
	static const int TELOP_TYPE_NUM =  2;	// �e���b�v�̎�ނ�2��
	static const int WINDOW_TYPE_NUM = 3;	// �E�B���h�E�̎�ނ�3��
	//10/6 �ǉ�
	static const int EQUIP_SELECT_NUM = 6;	//�����I����ʂ̍��ڂ�6��



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
		STATE_SELECT = 2,	// �L����/����/����I��
		STATE_WINDOW_MOVE,	// �E�B���h�E�ړ�
		STATE_CHANGE,		// ����/����ύX
	};
	enum ChangeType
	{
		add,
		subtract,
	};
//	CGameWindow		m_window;


	float	m_equipPos;		// �����I���J�[�\���̈ʒu����ۑ�
	int		m_changeID;		// �ύX���悤�Ƃ��Ă��鑕��
	int		m_drawID;		// �`��ԍ�
	int		m_charaID;		// �I������Ă���L�����ԍ�
	int		m_itemNum;		// �������Ă���A�C�e���̎�ސ�
	State	m_state;		// ���
public:
	CMenuStatusScreen(LPDIRECT3DDEVICE9 _pDevice, CGameData* _gameData);
	~CMenuStatusScreen();
	void Control(int _keyState);
	void Draw();

	//��
	int GetSelectID();
private:
	void ChangeStatus(int _equipID,ChangeType _type);
};

#endif