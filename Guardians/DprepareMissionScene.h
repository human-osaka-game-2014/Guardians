#ifndef _PREPARE_MISSION_H_
#define _PREPARE_MISSION_H_

class CPrepareMission : public CScene
{
public:
		CGameMapPointer*	m_mapPointa;

	enum {
		CHIP_MAX = 25,		// �`�b�v19+�{�X6
		PIC_CHARA_MAX = 20,	// �����摜��ސ�
		STAGE_MAX = 18,		// �e�X�e�[�W�`�F�b�N�|�C���g2, �{�X1��6�X�e�[�W��
	};

	enum MenuType		// ���j���[�̎��
	{
		MENU_MAP,
		MENU_STATUS,
		MENU_SHOP,
		MENU_SAVE,

		MENU_MAX,
	};

	enum TelopType
	{
		TELOP_STAGE,
		TELOP_BOSS,
	};
	enum MenuBarType
	{
		BAR,
		BAR_ICON,

		BAR_MAX,
	};

	struct ChipData {
		D3DXVECTOR2 position;
		CChip::ChipType type;
	};

	struct CharaPictureData {
		D3DXVECTOR2 position;
		int textureID;
		CCharaPicture::Type typeID;
	};

	std::vector<CTexString*> m_strLst;
	std::vector<bool> m_isSelLst;

private:
	
	static const ChipData CHIP_DATA[];
	static const CharaPictureData CH_PIC_DATA[];
	static const int 	TELOP_TYPE_NUM = 2;

	LPDIRECT3DDEVICE9	m_pDevice;					// �`��f�o�C�X
	D3DXVECTOR2			m_mapPosition;				// ���݂̃}�b�v���W(�J�����Ɏg�p)
	D3DXVECTOR2			m_nextMapPosition;			// �ړ���}�b�v���W(�X�e�[�W�N���A�����ۂ̉��o�p)
	CGameMenuCursor*	m_pCursor;					// �J�[�\���N���X(���j���[�j
	CGameTelop**		m_pTelop;				// �Q�[���e���b�v
	CGameDataWindow*	m_pWindow;					// �Q�[���E�B���h�E�N���X
	CMenuScreen*		m_pScreen;					// ���j���[��ʃN���X
	CGameMap*			m_pMap;						// �}�b�v�N���X
	CGameMapPointer*	m_pMapPointer;				// �}�b�v�|�C���^�\�N���X
	CCharaPicture*		m_pPicChara[PIC_CHARA_MAX];	// �����摜�\���N���X
	CMenuBar**			m_menuBar;
//	CChip				m_chip;
	CGameData*			m_pGameData;				// �Q�[���f�[�^�N���X�̎Q��
	State				m_state;					// ��ʂ̏��
	State				m_oldState;					// �P�O�̉�ʂ̏��
	bool				m_clearPoint[STAGE_MAX];	// �X�e�[�W�N���A�t���O
	int					m_menuID;					// ���j���[�ԍ��i�L�����o���I��/�X�e�[�^�X/�V���b�v/�Z�[�u)
	int					m_stageID;					// �X�e�[�W�ԍ�
	int					m_clearCount;
	void SelectStage();								// �X�e�[�W�Z���N�g
public:
	CPrepareMission(LPDIRECT3DDEVICE9 _pDevice,CGameData* m_pGameData,CInput* _input);	// �R���X�g���N�^(�f�o�C�X���Z�b�g)
	~CPrepareMission();								// �f�X�g���N�^
	SceneID Control();									// ����
	void Draw();									// �`��

	// �A�N�Z�b�T
	int* GetTurnNo();								// �o�����Ԏ擾
};

#endif