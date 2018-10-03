class CPlayer : public CCharacter
{
public:
	static const int MOTION_MAX_NUM = 26; //���[�V�����̐� ����26��(27�\��)

	static const float INIT_VELOCITY;	 // �W�����v�����x

	static const float INIT_HEIGHT_POSITION;	// �L�����N�^�[�̍���

	enum DIRECTION{ // ����
		DIR_LEFT,
		DIR_RIGHT,
	};
	// ���ʂ̃��[�V�������X�g
	enum MOTIONLIST
	{
		MOTION_WAIT,			//1.	�ҋ@
		MOTION_START_RUN,			//2.	����o��
		MOTION_RUN,			//3.	����
		MOTION_STOP_RUN,			//4.	�~�܂�
		MOTION_JUMP,			//5.	�W�����v
		MOTION_JUMP_FALL,
		MOTION_SQUAT_START,		//6.	���Ⴊ��
		MOTION_SQUAT,		//7.	���Ⴊ�ݒ�
		MOTION_STAND_UP,		//8.	���Ⴊ�݉���
		MOTION_AVOID,		//9.	�ً}���
		MOTION_ATTACK,		//10.	�ʏ�U��
		MOTION_ATTACK2,		//11.	�ʏ�U���A��1
		MOTION_ATTACK3,		//12.	�ʏ�U���A��2
		MOTION_UPPER,		//13.	��U��
		MOTION_LOWER,		//14.	���U��
		MOTION_AIR,			//15.	���U���i�󒆁j
		MOTION_SKILL,		//16.	�Z1
		MOTION_SKILL2,		//17.	�O�{�Z
		MOTION_SKILL3,		//18.	��{�Z
		MOTION_SKILL4,		//19.	���{�Z
		MOTION_SKILLAIR,		//20.	���{�Z�i�󒆁j
		//MOTION_SPECIAL,		//21.	�K�E�Z
		MOTION_FLINCH,			//22.	�_���[�W��炢
		MOTION_DEAD,			//23.	���S
		MOTION_STUN,			//24.	�X�^��
		MOTION_APPEAL,		//25.	�ŗL���[�V����1�i�퓬�J�n���p�j
		MOTION_APPEAL2,		//26.	�ŗL���[�V����2�i�������j
	};
protected:
	static		D3DXVECTOR3 m_position;
	//EFFECT_LIST		m_effectList[MOTION_MAX_NUM]; // �G�t�F�N�g���X�g(���[�V�����̐����m��)
	D3DXVECTOR3			m_enemyPos;			// �G�̈ʒu
	DIRECTION			m_direction;		// �L�����N�^�[�̌���
	float				m_jumpSpeed;		// �W�����v���x
	bool				m_jumpFlag;			// �W�����v���t���O
	D3DXVECTOR2			m_jumpMove;			// �W�����v����y���W
	int					m_jumpStartFrame;

	bool				m_isPlay;
public:
	// �R���X�g���N�^
	CPlayer(LPDIRECT3DDEVICE9 _pDevice);
	// �f�X�g���N�^
	virtual ~CPlayer() = 0;
	// ����
	void Control();
	// �`��
	virtual void Draw() = 0;

	// �G�t�F�N�g�̍Đ�
	virtual void PlayEffect(int) = 0;

	void addAlpha(float _value);
	// �Q�b�^

	// �Փ˂��Ă��邩
	void GetHit();
	// �h��ђʃt���O
	int Getflag();

	// �ʒu���擾
	D3DXVECTOR3 GetPosition();
	// �Z�b�^

	// �G�̈ʒu���Z�b�g
	void	SetEnemyPos(D3DXVECTOR3 _position); 
	void	SetPosition(D3DXVECTOR3 _position);
private:
	// �W�����v
	void Jump();
	// ����
	void Run();
	// �U��
	void Attack();
	// �󒆂ł̍U��
	void Aerial();
	// ���
	void avoid();
	// ���Ⴊ��
	void Squat();

	// �L�����N�^�[�̈ړ�
	void Move();
	// 
	void Flinch();
	// ����
	void Fall(int _frame);
};
