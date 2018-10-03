#ifndef _MENU_SELECT_SCREEN_H_
#define _MENU_SELECT_SCREEN_H_


class CMenuSelectScreen : public CMenuScreen
{
private:
	static const D3DXVECTOR2 BOSS_POSITION;	// �u�{�X�v�`��ʒu
	
	static const int CURSOR_TYPE_NUM = 2;	// �J�[�\���̎�ނ�1��
	static const int TELOP_TYPE_NUM  = 4;	// �e���b�v�̎�ނ�2��
	static const int WINDOW_TYPE_NUM = 2;	// �E�B���h�E�̎�ނ�2��

	// �L�����J�[�\���̏����ʒu(�o���I�����͑��̃J�[�\���Ƃ̈ʒu���Ⴄ�ׂ����Ő錾)
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

	int		m_selectID;		// �͂��A�������I��p
	int		m_charaID;
	bool	m_selectWndFlag;	// �I�������o����Ă��邩�ǂ���
	int		m_selectCount;		// ���l���Ԃ����肳�ꂽ��
	int		m_oldID[3];  //�o���I�����̃L�����Z���p
public:
	CMenuSelectScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData);
	~CMenuSelectScreen();
	void Control(int _keyState);
	void Draw();

	bool GetBattleFlag();
};

#endif