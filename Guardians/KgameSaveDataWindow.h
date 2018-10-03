#ifndef _GAME_SAVEDATA_WINDOW_H_
#define _GAME_SAVEDATA_WINDOW_H_



class CGameSaveDataWindow : public CGameWindow
{
private:
	struct Data{
		bool data;			//�f�[�^�̗L��
		int hour;			//����
		int minute;			//��
		int second;			//�b
		int year;			//�N
		int month;			//��
		int date;			//��
		int realhour;		//���A���^�C��(����)
		int realminutes;	//���A���^�C��(��)
		int playtime;		//�v���C����
		int money;			//����
		int stageclear;		//�X�e�[�W�N���A��
		int equipper;		//����������
		int itemper;		//�A�C�e��������
		int achieve;		//���ї�
	};
	int m_drawID;
	int	m_cursorPos;
	int m_cursolpoint;
	int m_drawFirst;
	int m_head;
	int m_tail;
	static const int MAX_ITEM=14;			//�ő�A�C�e�����i��
	static const int MAX_EQUIP=16;			//�ő呕�����i��
	static const int MAX_WIDTH	= 1150;		// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 520;		// �E�B���h�E�ő卂��
	static const int MAX_ITEMNUMBER=14;		//�A�C�e���ő及����
	static const int MAX_STAGENUMBER=6;		//�X�e�[�W�ő吔
	static const int MAX_EMBLEM=11;			//�ő�̍���

	Data    m_Data[10];                     //�f�[�^10��
	CGameData*  m_pGameData;                //�Q�[���f�[�^�̎Q��
	CTexture	m_textureChip;				//�}�b�v�`�b�v�A�C�R��
public:
	CGameSaveDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int m_state);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^,��Ԃ��Z�b�g)
	~CGameSaveDataWindow();
	void Load(int _ID);																	//�Z�[�u�f�[�^���t�@�C������ǂݍ���
	void Control();		// ����
	void Draw();		// �`��
	void SetCursorID(int _cursorID);

};
#endif


