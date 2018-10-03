class CBattleScene : public CScene
{
public:
	static int			comboCount;		// �R���{��
	static bool			m_pause;		// �|�[�Y�t���O
	static const float RIGHT_WALL;		// �E��
	static const float LEFT_WALL;		// ����

	enum STATE{
		STATE_BATTLE,
		STATE_CHARA_CHANGE,
	};

	static const int	CHANGE_LIMIT = 120;	// �L�������̐�������(120�t���[��)
private:

	#define FIELD_TYPE_NUM 2

	enum FieldType{
		FIELD_1,
		FIELD_2,
	};

	CField*		m_field;		// �t�B�[���h�N���X�I�u�W�F�N�g
	CCamera*    m_camera;		// �J�����N���X�I�u�W�F�N�g
	CCharacterManager*	m_character;	// �L�����N�^�[�N���X�I�u�W�F�N�g
	CGameData*			m_pGameData;	// �Q�[���f�[�^
	CBattleUI*			m_ui;			// UI

	D3DXVECTOR2			m_cameraPos;    // �J�����̈ʒu
	D3DXVECTOR2			m_move;			// �J�����̈ړ���

	D3DXVECTOR2			charaSpeed;		// �L�����N�^�[�̃X�s�[�h
	D3DXVECTOR3			m_playerPos;

	//===============�L�����ύX���̐���p�ϐ�===================//
	
	STATE				m_charaChange;	// �L�����`�F���W���
	int					m_changeTime;	// �L�����`�F���W���̌o�ߎ���
	static const int	CC_MAX_ALPHA = 150;	// �L�����ύX���̃A���t�@���
	static const int	CC_ADDALPHA_FRAME = 20; // �L�����ύX���̃A���t�@��������

	//===============�t�F�[�h�C��or�t�F�[�h�A�E�g����p�ϐ�===================//
	
	CTexture			m_feed;			// �t�F�[�h�p�摜
	int					m_alpha;		// ���l
	int					m_add;			// �A���t�@�l������

public:

	CBattleScene(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGamedata,CInput* _input,CCharacterManager::MODELDATA* _chara,CField* _field);
	~CBattleScene();
	SceneID Control();
	void Draw();
	
private:
	void DrawBlackPic(int _alpha);
};