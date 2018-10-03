class CCharacterManager
{
public:

	typedef struct _MODELDATA{
		CPlayer* player[3];
		CEnemy*  enemy[4];
	}MODELDATA;

	enum STATE{ // �v���C���[�̏��
		STATE_WAIT,
		STATE_WALK,
		STATE_DASH,
		STATE_SQUAT,
		STATE_JUMP,
		STATE_ATTACK,

	};

private:
	MODELDATA* m_pModel;

	LPDIRECT3DDEVICE9	m_pDevice; //�`��f�o�C�X
	CGameData*			m_pGameData;				// �Q�[���f�[�^

	CPlayer*			m_activePlayer;				// �A�N�e�B�u�L�����N�^�[�i�[�p
	CEnemy*				m_activeEnemy;				// �A�N�e�B�u�G�l�~�[�i�[�p

	// �G�ƃv���C���[�̃X�e�[�^�X
	CGameData::Character m_player;
	CGameData::Character m_enemy;

	int				m_turnNo;
	int				m_enemyState;	// �G�̏��
	int				m_playerState;	// �v���C���[�̏��
	bool			isHit;			// �Փ˔���m�F�p
	bool			m_moveFlag;		// �ړ��\���ǂ���
	bool			m_hitWall;
	D3DXVECTOR2			m_speed;	// �L�����N�^�[�̈ړ����x
	D3DXVECTOR2			m_fieldPosition;
public:
	// �R���X�g���N�^
	CCharacterManager(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,MODELDATA* _chara);
	// �f�X�g���N�^
	~CCharacterManager();
	// ����
	virtual void Control();

	bool HitCheck(std::vector<XFileAnimationMesh::BOX>,std::vector<XFileAnimationMesh::BOX>);
	// �`��
	virtual void Draw();

	// �ړ��t���O���Z�b�g
	void setMoveFlag(bool _flag);
	bool GetMoveFlag();
	bool GetHitWall();
	void SetFieldPosition(D3DXVECTOR2 _position);
	CPlayer* GetPlayer();
	void SetPosition(D3DXVECTOR2 _position);
	void SetFieldSpeed(D3DXVECTOR2 _spd);

	D3DXVECTOR2 CCharacterManager::GetCharaSpeed();

	D3DXVECTOR3 GetCharaPosition();

	CGameData::ENEMY_STATUS GetHP();

	bool		GetMotionEnd(int _motionID);

	void CharacterChange();
	void SetAlpha();
private:
	void CalcPlayerDamage();
	void CalcEnemyDamage();
	// �~���m�̏Փ˔���
	bool SphereCollision(XFileAnimationMesh::SPHERE _pSphereA, XFileAnimationMesh::SPHERE _pSphereB);
	// �{�b�N�X���m�̏Փ˔���
	bool AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2);
	// �~�ƃ{�b�N�X�̏Փ˔���
	bool SphereToBox(XFileAnimationMesh::SPHERE _pSphere,XFileAnimationMesh::BOX _box);
};
