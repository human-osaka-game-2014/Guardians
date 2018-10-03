/**
 * @file DNeru.h
 */

class CNeru : public CPlayer
{
public:
	// test
	CTexture texture;
	CVertex vertex;

	static float m_charaHeight;	///< �L�����̍���

	struct ACTION_VALUE{
		char* name;				///< �Z��
		int   useMP;			///< ����MP
		int	  actionGauge;		///< �s���e���l
		float correctionValue;	///< �Z�␳�l
	};
	static const int EFFECT_MAX_NUM = 2;
	static const int EFFECT_TYPE_NUM = 9; ///< �G�t�F�N�g���g�p����Z��9���
	
	static const ACTION_VALUE actionValue[];

	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_FADE_OUT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
	enum EFK
	{
		FIRE_BALL,
		ICE_WALL,
	};
private:
	D3DXVECTOR3 DUMMY;
	CMaru* m_maru;

	CEffectManager*  m_efk[EFFECT_MAX_NUM];

	bool	m_isPlay;			///< �G�t�F�N�g�Đ��t���O
	int		m_teleportState;		///< �e���|�[�g�̏��

	

	D3DXVECTOR3 m_efkPos;	///< �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 m_moveValue; ///< �G�t�F�N�g�̈ړ���
	float		m_efkAngle;	///< �G�t�F�N�g�Đ����̌���
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CNeru();									// �f�X�g���N�^
	
	void Draw();								// �`��
	//void SetPosition(D3DXVECTOR3 _position);	// �ړ�
	void SetMotion(int _motionID);				// ���[�V����ID
	void Load();

	// �Q�b�^
	float GetCharaSpeed();						// �L�����̃X�s�[�h��Ԃ�

private:
	void ControlEffect();
	void PlayEffect(int _frame = 0);

	// �U�����[�V����
	void FireBall();
	void IceWall();
	void Teleport();
	void ThunderWhip();
	void StoneImpact();



	void CreateBox();	// �{�b�N�X�𐶐�
	void SetEffectList();	// ���X�g����



};
