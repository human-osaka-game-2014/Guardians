/**
 * @file DNeru.cpp
 * @author �h��
 */

/**
 * �l���̐���
 */
class CNeru : public CPlayer
{
public:
	static float m_charaHeight;	///< �L�����̍���
	static const int EFFECT_MAX_NUM = 2;	// �G�t�F�N�g�̐�
	static const int EFFECT_TYPE_NUM = 9;	///< �G�t�F�N�g���g�p����Z��9���
	
	// �e���|�[�g�̏��
	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_FADE_OUT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
	// �G�t�F�N�g�̎��
	enum EFK
	{
		FIRE_BALL,
		ICE_WALL,
	};
	// ��`�̎��
	enum BOX_TYPE
	{
		BOX_BODY,
		BOX_FIRE_BALL,
	};
private:
	D3DXVECTOR3 DUMMY;			// �Փ˔���
	CMaru* m_maru;				// �}���N���X�I�u�W�F�N�g

	CEffectManager*  m_efk[EFFECT_MAX_NUM];

	D3DXVECTOR3 m_efkPos;		///< �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 m_moveValue;	///< �G�t�F�N�g�̈ړ���

	float		m_efkAngle;		///< �G�t�F�N�g�Đ����̌���
	int			m_teleportState;		///< �e���|�[�g�̏��
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CNeru();									// �f�X�g���N�^
	
	void Draw();								// �`��
	void DrawEffect();
	void SetMotion(int _motionID);				// ���[�V����ID
private:
	void PlayEffect(int _frame = 0);			// �G�t�F�N�g�̍Đ�

	// �U�����[�V����
	void FireBall();
	void IceWall();
	void Teleport();

	// �{�b�N�X�𐶐�
	void CreateBox();	



};
