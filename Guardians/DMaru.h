class CMaru : public CPlayer
{
public:
	static const int EFFECT_MAX_NUM = 2;

	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
private:

	bool	m_isPlay;			// �G�t�F�N�g�Đ��t���O
	int		m_teleportState;		// �e���|�[�g�̏��
	float	m_alpha;			// ���f���̃��l
	D3DXVECTOR3 m_neruPos;
public:
	CMaru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CMaru();									// �f�X�g���N�^
		void ChangeEffect(){};						// �G�t�F�N�g�̐���

	void Draw();								// �`��
	void Move( D3DXVECTOR3 _position , int _motionID , int _angle);
	//void SetPosition(D3DXVECTOR3 _position);	// �ړ�
	void SetMotion(int _motionID);				// ���[�V����ID
	void SetPosition( D3DXVECTOR3 _position);
	void SetStopMotion(bool _flag);
	
	void UpdateRect(LPCTSTR _name , int _ID );
	void UpdateRect(D3DXVECTOR3 _position , int _ID );

private:

	void CreateBox();	// �{�b�N�X�𐶐�
	void SetEffectList(){};	// ���X�g����
	void PlayEffect(int){};

};