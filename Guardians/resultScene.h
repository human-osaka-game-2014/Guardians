class CResultScene : public CScene
{
// �萔
	// �e�N�X�`�����W(�̍�)�̐擪�ʒu
	static const D3DXVECTOR2 UV_EMB_POSITION;
	// �̍������̕��A����
	static const D3DXVECTOR2 TEX_EMB_SIZE;
	// �̍��\�����W
	static const D3DXVECTOR2 POS_EMB_CHECK;
	// �̍�(�I�t�Z�b�g�l)
	static const D3DXVECTOR2 POS_EMB_OFFSET;
	// �̍��\�����W(�X�e�[�W�N���A����̍�)
	static const D3DXVECTOR2 POS_EMB_CLEAR[];
	// �̍��\�����W(�`�F�b�N�|�C���g��)
	static const D3DXVECTOR2 POS_CHECKPOINT;

	// �e�N�X�`�����W(�̍����)�̈ʒu
	static const D3DXVECTOR2 UV_EMBBAR_POSITION[];
	// �̍�����̕��A����
	static const D3DXVECTOR2 TEX_EMBBAR_SIZE[];
	// �̍����(�I�t�Z�b�g�l)
	static const D3DXVECTOR2 POS_EMBBAR_OFFSET;

	// �̍��ʃA�j���[�V��������
	static const int ANIMNO_LIST[];
	// �̍��ʂ̐�
	static const int EMBBALL_NUMS[];
	// �̍�������̍��ʂ܂ł̃I�t�Z�b�g�l
	static const float EMBTOBALL_OFFSET;

	// �l�������\���ʒu
	static const D3DXVECTOR2 POS_GET_MONEY[];
	// �l�������ő包��
	static const int MONEY_MAX_DIGIT;
	// �{�[�i�X�\���ʒu
	static const D3DXVECTOR2 POS_GET_BONUS[];
	// �{�[�i�X�̔{��(�e�̍�)
	static const float BONUS[];

	// �A�C�e���\���ʒu
	static const D3DXVECTOR2 POS_ITEM[];

	// �X�e�[�W���Ƃ̃`�F�b�N�|�C���g��(���Z�^)
	static const int STAGE_NUMS[];
	// �f�t�H���g�J���[
	static const DWORD DEFAULT_COLOR;
	// BG�ԍ�(��)
	enum BgID{
		BG_CHECK,
		BG_CLEAR,
		BG_LOSE,
	};
	// �̍���
	enum {
		NUM_CHECK_EMB = 7,
		NUM_MAX_EMB = 11,
	};
	// �\����ID
	enum {
		TEX_UI_NO = 3,
		TEX_ICON,
	};
	// �X�e�[�W�^�C�v
	enum {
		STAGE_BOSS,
		STAGE_CHECK,
	};
private:
	CTexture	m_texBG;	// �w�i�p�e�N�X�`��(CP�ʉߎ�/�N���A��/�s�k��)
	CTexture	m_texUI;	// �\�����p�e�N�X�`��
	CTexture	m_texIcon;	// �A�C�e��
	BgID		m_bgID;		// �w�iID(�`�掞�̔��f�Ɏg�p)
	int			m_cntMoney;	// �����J�E���g�p
	int			m_addMoney; // �����̃J�E���g��
	int			m_bonus;	// �{�[�i�X�\���p
	CGameData*	m_pGameData;// �Q�[���f�[�^

	class EmblemBall {
		// �萔
		// �e�N�X�`�����W
		static const FRECT EMBBALL_RECT[];
	public:
		// ��or��
		enum Type {
			TYPE_SILVER,
			TYPE_GOLD,
		};
		// �擾�����^�C�~���O
		enum GetType {
			TYPE_PREV,
			TYPE_NOW,
			TYPE_YET,
		};
	private:
		int m_type;			// ��or��
		int m_getType;		// �擾�^�C�v(��/����/��)
		int m_animNo;		// ���݂̃A�j���[�V�����ԍ�
		int m_animSpd;		// �A�j���[�V�������x
		int m_animCnt;		// �A�j���[�V�����؂�ւ��܂ł̃J�E���g
		FRECT m_rect;		// �e�N�X�`�����W
		D3DXVECTOR2 m_pos;	// �\�����W
	public:
		EmblemBall(int _type, int _getType, D3DXVECTOR2 _pos);
		void Control();
		void Draw(LPDIRECT3DDEVICE9 _pDevice, CTexture _tex);
	};
	// �̍���
	EmblemBall**	m_embBall;
	// �̍��ʂ̌�
	int				m_embBallNum;

	// �{�[�i�X�v�Z
	void CulcBonus(int _stageID);
	// �l������/�{�[�i�X�\��
	void DrawMoney(int _money, D3DXVECTOR2 _pos);
	// �A�C�e����`�v�Z
	FRECT GetItemRect(int _no); 

public:
	// �R���X�g���N�^
	CResultScene(LPDIRECT3DDEVICE9 _pDevice, CGameData* m_pGameData,CInput* _input);
	// �f�X�g���N�^
	~CResultScene();

	// ����
	SceneID Control();
	// �`��
	void Draw();		
};