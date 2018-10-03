#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

class CGameData
{
public:
	static const int MAX_EMBLEM=11;			//�ő�̍���
	static const int MAX_ITEM = 14;			//�ő�A�C�e�����i��
	static const int MAX_EQUIP = 16;			//�ő呕�����i��

	CGameData();

	enum stType{
		HP,
		MP,
		ATK,
		DEF,
		SPD,
		INS,
		TYPE_MAX,
	};

	struct Time
	{
		int year;
		int month;
		int date;
		int hour;
		int minute;
	};

	struct Thing
	{
		int no;			// �ԍ��@10/24�ǉ��@�h��
		int type;			// ���
		int nums;			// ��
		char explainStr[256];		// ����
	};

	struct HaveTool		// ��������
	{
		int no;			// �ԍ��@10/24�ǉ��@�h��
		int type;			// ���
		int nums;			// ��
		char explainStr[256];		// ����
	};
	struct Equip		// ����
	{
		int no;			// �ԍ�
		char name[256];    // ���O     
		int type;			// ���
		int nums;			// ��
		int price;          // ���i
		int stType;			// �ω�����X�e�[�^�X�̎��
		int power;			// �ω���
		int unlockNo;
		char explainStr[256];		// ����
	};
	struct Character		// �L�����N�^�[
	{
		char	name[256];	// ���O
		int		hp;				
		int		mp;				
		int		atk;
		int		def;
		int		spd;
		int		ins;		// �u����
		Equip	equip[2];	// ����
	};
	struct Damage
	{
		// �^�����_���[�W
		int damage;
		// �󂯂��_���[�W
		int damageTaken;
	};
	//�X�e�[�^�X
	struct ENEMY_STATUS 
	{
		int ATK;
		int	DEF;			//�h���
		int	STR;			//�g�p�Z�U����
		int	addState;		//�g�p�Z��Ԉُ�t�^ID
		int	actionGauge;	//�s���l
		int	actionGaugeRecover;	//�s���l�񕜗�
		float hp;
		float maxHP;
	};
	struct EMBLEM
	{
		char name[256];
	};

	enum { HAVE_TOOL_MAX = 4 };		// �������߂铹��̍ő吔
	enum { UNLOCK_TOOL_MAX = 10 };	// �A�����b�N�ł��铹��ő吔(��)
	enum { UNLOCK_EQUIP_MAX = 10 };	// �A�����b�N�ł��鑕���ő吔(��)

	std::vector<Equip>		m_itemList;						// �Q�[���Ŏg�p����A�C�e���ꗗ
	std::vector<Equip>		m_equipList;
	std::vector<HaveTool>	m_hasTools;						// ��������
	std::vector<Equip>		m_hasEquip;						// ���������i
	std::vector<bool>		m_emblemFlag;					// ���сi�̍��j�t���O
	std::vector<EMBLEM>		m_emblemList;					// ���у��X�g
	HaveTool				m_tools[HAVE_TOOL_MAX];			// �������ݓ���(4��)
	Character				m_initchara[PLAYER_MAX];
	Character				m_chara[PLAYER_MAX];			// 3�l��

	Damage					m_pDamage;						// player�_���[�W�v�Z�p
	//Damage					m_eDamage;						// enemy�_���[�W�v�Z�p
	int						m_nowClearStageNum;				// ���݂̃X�e�[�W�N���A��
	int						m_selectStageNum;
	int						m_oldClearStageNum;				// �o�g���o���O�̃X�e�[�W�N���A��(���f���̃����[�h���K�v�����f)
	int						m_turnNo[PLAYER_MAX];			// �o������
	int						m_playerCharaNo;				// �擪�̃L�����̔ԍ�(�o���������߂�Ƃ��ɕۑ�)
	int						m_unlockTools[UNLOCK_TOOL_MAX];	// ���i�A�����b�N���X�g(����)
	int						m_unlockEquip[UNLOCK_EQUIP_MAX];// ���i�A�����b�N���X�g(����)
	Time                    m_time;                         // �Z�[�u���t
	int						m_playTime;						// �v���C����
	int						m_money;						// ������
	int                     m_toolsPer;                     // �擾������
	bool					m_death;						// ���񂾂��ǂ���(�ǉ�)
	int						m_resultMoney;					// �l������
	int						m_stageEmbFlag[6][4][11];		// �X�e�[�W���Ƃ̃G���u�������
	std::vector<HaveTool>	m_getItem;						// �X�e�[�W�ŃQ�b�g�����A�C�e��


	bool					m_win;

	int m_equipPer;
	int m_itemPer;
	int m_emblemPer;
public:
	int Search(int _itemNum,ItemType _type);		//�A�C�e���i���o�[����z��ԍ���T��
	void Load(int _dataID);	// �Z�[�u�t�@�C������ǂݍ���
	void Save(int _dataID);    // �t�@�C�����Z�[�u  10/18�ǉ�
	void newGame();			// �j���[�Q�[���̃f�[�^�����[�h����
};

#endif