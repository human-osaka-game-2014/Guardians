/**
 * @file DcharacterManager.h
 * @author �h��
 */

/**
 * �L�����N�^�[�̏Փ˔����_���[�W�v�Z�Ȃǂ��Ǘ�����
 */
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
	// �Փ˂��Ă��邩���ׂ�
	bool HitCheck(std::vector<XFileAnimationMesh::BOX>,std::vector<XFileAnimationMesh::BOX>);
	// �`��
	virtual void Draw();
	// �ړ��t���O���Z�b�g
	CPlayer* GetPlayer();
	// �L�����N�^�[�̈ړ����x���擾����
	D3DXVECTOR2 CCharacterManager::GetCharaSpeed();
	// �L�����N���[�̈ʒu���擾����
	D3DXVECTOR3 GetCharaPosition();
	// HP���擾����
	CGameData::ENEMY_STATUS GetHP();
	// ���[�V�������I�����Ă��邩���ׂ�
	bool GetMotionEnd(int _motionID);
	// �L�����N�^�[��ύX����
	void CharacterChange(int _time);
	// �A���t�@�l���Z�b�g����
	void SetAlpha();
private:
	// �v���C���[�̃_���[�W���v�Z����
	void CalcPlayerDamage();
	// �G�̃_���[�W���v�Z����
	void CalcEnemyDamage();
	// �~���m�̏Փ˔���
	bool SphereCollision(XFileAnimationMesh::SPHERE _sphereA, XFileAnimationMesh::SPHERE _sphereB);
	// �{�b�N�X���m�̏Փ˔���
	bool AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2);
	// �~�ƃ{�b�N�X�̏Փ˔���
	bool SphereToBox(XFileAnimationMesh::SPHERE _sphere,XFileAnimationMesh::BOX _box);
	// ���C�ƃ��b�V���̏Փ˔���
	bool RayToMesh(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box);
	// ���C�ƃ{�b�N�X�̏Փ˔���
	bool RayToBox(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box);
	// �����Ɛ����̏Փ˔���
	bool ColSegments(XFileAnimationMesh::RAY_PARAM _ray1,XFileAnimationMesh::RAY_PARAM _ray2);

};
