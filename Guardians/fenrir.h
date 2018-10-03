class CFenrir : public CEnemy
{
public:
	static const int MOTION_MAX_NUM = 21; //���[�V�����̐� ����8��(26�\��)
	static const int EFFECT_MAX_NUM = 10;

	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// �ҋ@
		MOTION_FALTER,		//1.	//�Ђ��
		MOTION_DEATH,		//2.	//���S
		MOTION_JUMP1,		//3.	//�W�����v����	{ 300, 345 }
		MOTION_JUMP2,		//4.	//�W�����v�؋�i�����ň�[�Œ�	{ 345, 345 }
		MOTION_JUMP3,		//5.	//�W�����v���n	{ 345, 400 }
		MOTION_TURN,		//6.	//�������] (415-445�Œ��яオ���180����]�@�����ۂɃ_���[�W����)	{ 400, 460 }
		MOTION_JUMP_BITE,	//7.	//�W�����v���n���݂�	{ 465, 520 }
		MOTION_BITE,		//8.	//���݂� (540-555�Ō��ɓ����蔻��)	{ 520, 580 }
		MOTION_FIREBALL,	//9.	//�Ή��e (625�Ŕ���)	{ 580, 650 }
		MOTION_TAIL,		//10.	//�����ۍU��	{ 650, 690 }
		MOTION_FIRE1,		//11.	//�Ή����ˑO	{ 690, 730 }
		MOTION_FIRE2,		//12.	//�Ή����˒�	{ 730, 730 }
		MOTION_FIRE3,		//13.	//�Ή����ˌ�	{ 730, 770 }
		MOTION_HOWL1,		//14.	//���i���O	{ 770, 800 }
		MOTION_HOWL2,		//15.	//���i����	{ 800, 800 }
		MOTION_HOWL3,		//16.	//���i����	{ 800, 860 }
		MOTION_HOWL4,		//17.	//���i����ҋ@	{ 0, 100 }
		MOTION_ATTACK1,		//18.	//�̓�����O	{ 860, 930 }
		MOTION_ATTACK2,		//19.	//�̓����蒆	{ 930, 930 }
		MOTION_ATTACK3,		//20.	//�̓������	{ 930, 960 }
	};
	enum BOXNAME
	{
		BODY,		//0.	// ���̕�	�L�����̈ړ�������
		HEAD,		//1.	// ��		�L�����̈ړ��������^���݂��U��
		TAIL,		//2.	// ��		�����ۍU��
		EFFECT0,	//3.	// �G�t�F�N�g���
	};

	bool m_boxFlag[EFFECT0 + EFFECT_MAX_NUM - 1];	//���̃{�b�N�X���U������Ɏg����

private:
	D3DXVECTOR3 effectPos[EFFECT_MAX_NUM];	//�G�t�F�N�g�{�b�N�X���W ���肳�������Ȃ��Ƃ���y���W��-3��

	bool	m_isPlay;			// �G�t�F�N�g�Đ��t���O
	int		m_teleportState;	// �e���|�[�g�̏��
	float	m_alpha;			// ���f���̃��l

	float	m_speed;

	int		TimeCount;	//�s���l�񕜗p

	float	e_position;		//�G�t�F�N�g�����ʒu�����p


	float	m_sidePos[2];	//�C���p

public:
	CFenrir(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CFenrir();									// �f�X�g���N�^

	void ChangeEffect(){ };						// �G�t�F�N�g�̐���
	void PlayEffect(int){ };

	void Control();								// ����
	void Draw();								// �`��
	void SetMotion(int _motionID);				// ���[�V����ID

	// �Q�b�^
	float GetCharaSpeed();						// �L�����̃X�s�[�h��Ԃ�
	int GetDamage();							// �g�p�Z�̍U���͂ƕt�^��Ԃ��@�i/10�j�U���́i%10�j�t�^ID�@
	//void SetPosition(D3DXVECTOR3 _position){};


	void CreateBox();							// �{�b�N�X�𐶐�
	void BoxControl();							// �{�b�N�X�𐧌�
private:
	//�Z����
	void TailHammer();							//�K���U��
	void Attack();
	

	void Jump();
	void Tail();
	void Bite();
	void Turn();
	void Howl();
	void Fire();

	bool CheckInterval();
};