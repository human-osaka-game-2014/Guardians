/**
 * @file DmenuSelectScreen.h
 */

/**
 * �V���b�v��ʂ̊Ǘ�
 */

#ifndef _MENU_SHOP_SCREEN_H_
#define _MENU_SHOP_SCREEN_H_

class CMenuShopScreen : public CMenuScreen
{
public:
	static const int CURSOR_TYPE_NUM = 2;	// �J�[�\���̎�ނ�2��
	static const int TELOP_TYPE_NUM = 1;	// �e���b�v�̎�ނ�1��
	static const int WINDOW_TYPE_NUM = 2;	// �E�B���h�E�̎�ނ�2��
	static const int MAX_POSSESSION = 9;	// �A�C�e���̍ő及����
	enum TelopType
	{
		TELOP_EXPLAIN,
	};

	enum CursorType
	{
		CUR_MENU,
		CUR_SHOP,
	};

	enum WindowType
	{
		WND_SHOPMENU,
		WND_SHOPLIST,
	};

	enum ShopState
	{
		STATE_SELECT_SHOPMENU = 2,	// �V���b�v���j���[�I��
		STATE_WINDOW_SHOPLIST,		// �V���b�v���X�g�I��
		STATE_OPEN_SHOPLIST,		// �V���b�v���X�g���J���Ă���
	};
	// �I�����ꂽ����
	enum SELECT_ITEM
	{
		TOOLS,
		EQUIP,
	};
private:
	int		m_drawID;		// �`��ԍ�
	int		m_charaID;		// �I������Ă���L�����ԍ�
	int		m_itemNum;		// �������Ă���A�C�e���̎�ސ�
	int		m_oldID;		// �I������Ă������ڂ̔ԍ�
	
	ShopState m_state;		// ���
public:
	CMenuShopScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData);
	~CMenuShopScreen();
	void Control(int _keyState);
	void Draw();
private:
	void Search(int _oldID,int _No); // �w�����ɏ������Ă��邩���ׂ�

	void OpenWindow();		// �E�C���h�E�̐���
	void DeleteWindow();	// �E�C���h�E�̍폜
};

#endif