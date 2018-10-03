/**
 * @file Dcharacter.h
 * @author �h��
 */

/**
 * @file �L�����N�^�[�̐���
 */

class CCharacter
{
public:
	#define			PLAYER_MAX 3  ///< ����ł���L�����N�^�[��3��
	#define			ENEMY_MAX 4		///< �G�̃L�����N�^�[��4��

	static const int ACTION_GAUGE_MAX = 100; ///< �A�N�V�����Q�[�W�̍ő�l(100)

	static const float RIGHT_WALL;
	static const float LEFT_WALL;

	static const float LEFT_ANGLE;	///< �L�����N�^�[�̌����@��
	static const float RIGHT_ANGLE;	///< �L�����N�^�[�̌��� �E

	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};

	enum STEP{ // �퓬�J�n���o
		STEP_FADE_IN,
		STEP_MOVE,
	};
protected:
	enum STATE{ // �L�����N�^�[�̏��
		STATE_WAIT,
		STATE_RUN,
		STATE_JUMP,
		STATE_SQUAT,
		STATE_SQUAT2,
		STATE_AVOID,
		STATE_INVICIBLE,	///< ���G���
		STATE_ATTACK,		///< �����U�����
		STATE_PROJECTILE,	///< ��ѓ�����g�p���Ă�����
	};

	enum MOTION_STATE{
		MSTATE_WAIT,
		MSTATE_JUMP,
		MSTATE_SQUAT,
		MSTATE_AVOID,
		MSTATE_IN_MOTION,	///< ���[�V�������͓����Ȃ����
		MSTATE_AERIAL,
	};

	LPDIRECT3DDEVICE9		m_pDevice; ///< �`��f�o�C�X
	XFileAnimationMesh*		m_model;

	D3DXVECTOR3			m_scale;    ///< ���f���̃X�P�[��
	static float		m_alpha;	///< ���f���̃A���t�@�l
	
	D3DXVECTOR2			 m_speed;	///< �L�����N�^�[�̈ړ����x
	D3DXVECTOR2			 m_move;    ///< �L�����N�^�[�̈ړ���
	float				 m_angle;		///< �L�����N�^�[�̌���

	STEP				 m_step; 
	int					m_curEffect;

	MOTION_STATE		 m_motionState;		///< �L�����N�^�[�̏��
	STATE				 m_state;		///< �L�����N�^�[�̏��
	int					 m_motionID;			///< �Z�b�g���郂�[�V����ID

	double				 m_time;		///< ���݂̃A�j���[�V��������
	int					 m_curMotionID;	///< ���ݍĐ����Ă��郂�[�V�����ԍ�
	int					 m_nowEffect; ///< ���ݐ������Ă���G�t�F�N�g
	int					 m_HitCount; ///< �P�̋Z�̃q�b�g��

	int					m_damage; ///< �Z�̃_���[�W

	bool				m_isHit;		///< �Փ˔���p
	bool				m_motionStop;	///< ���[�V������~�t���O
	bool				m_invincible;   ///< ���G

	bool				m_endMotion;
	// �ȉ�2�͍\���̂ɂ���\��
	int					m_actionGauge; ///< �s���l
	float				m_correctionValue;	///< �Z�␳�l
	std::vector<XFileAnimationMesh::BOX>		m_box;					// �Փ˔���p��`
	std::vector<XFileAnimationMesh::BOX>		m_unhitting_box;		// ���ꔻ��p
	std::vector<XFileAnimationMesh::BOX>		m_hitting_box;			// �U������p
	XFileAnimationMesh::RAY_PARAM				m_ray;					// ���C�̏��	


	std::vector<XFileAnimationMesh::ANIMLIST> m_animList;	///< �A�j���[�V�����p���X�g


	CVector m_vector;
private:

//	int				m_turnNo;
public:
	CCharacter(LPDIRECT3DDEVICE9 _pDevice , float _angle);	// �R���X�g���N�^
	~CCharacter();											// �f�X�g���N�^

	virtual void Control() = 0; // ����
	virtual void Draw() = 0;	// �`��
	virtual void DrawEffect() = 0;

	void SetRect();				// �Փ˔���Ɏg�p�����`�̃Z�b�g

	void ResetMotion(int _motionID);		// ���荞��Ń��[�V������ύX����
	bool CheckMotionEnd(int _motioniD);		// ���[�V�������I����Ă��邩
	
	//=================�Z�b�^===========================================================
	virtual void SetMotion(int _motionID) = 0;						// ���[�V����ID���Z�b�g
	void SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame);		// �{�[���̈ʒu���Z�b�g����
	void SetCharaSpeed(int);
	void SetHitFlag(bool);
	void SetTakeDamageFlg();
	//=================�Q�b�^=============================================================
	std::vector<XFileAnimationMesh::BOX> GetHittingBox();		// �U�������`���擾
	std::vector<XFileAnimationMesh::BOX> GetunHittingBox();		// ��_���[�W�����`���擾
	XFileAnimationMesh::RAY_PARAM GetRay();

	D3DXMATRIX GetMatrix(LPCTSTR);
	D3DXVECTOR2 GetCharaSpeed();								// �L�����N�^�[�̈ړ����x��Ԃ�
	D3DXVECTOR3 GetBonePos(LPCTSTR _name);
	STATE		GetState();
	STEP		GetStep();
	float		GetDamage();	// �_���[�W���擾
protected:
	// �A�j���[�V�������Ԃ��X�V����
	void UpdateAnimTime(float _time = (1.0f/60.f));
	// �Փ˔����`�̍X�V
	void UpdateRect(D3DXVECTOR3 _position , int _ID);
	void UpdateRect(LPCTSTR _name , int _ID );
	void UpdateSphere(D3DXVECTOR3 _position , XFileAnimationMesh::SPHERE* _sphere);							// �X�t�B�A�̈ʒu�����X�V
	void UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box);							// �X�t�B�A�̈ʒu�����X�V
	// ��`�̕`��
	void DrawBox(std::vector<XFileAnimationMesh::BOX> _box);
	void DrawRay(D3DXVECTOR3 _pos,D3DXVECTOR3 _rayDir);

	void SetHitFlag();
};
