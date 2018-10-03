class COgre : public CEnemy
{
public:
	static const int MOTION_MAX_NUM = 9; //���[�V�����̐�

	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// �ҋ@
		MOTION_FALTER,		//2.	//�Ђ��
		MOTION_DEATH,		//3.	//���S
		MOTION_WAIT2,		//1.	// �ҋ@�A�N�V�����i�\�b�ԉ����s�����Ȃ��������̍s���^�X���[�Đ�
		MOTION_BITE,		//4.	// ���݂�
		MOTION_STONE,		//5.	//�΂ԂčU��
		MOTION_POISON_FOG,	//6.	//�ŕ��i330-339��340-369�i�X���[�Đ��J��Ԃ��j��370-379)
		MOTION_L_WHISK,		//7.	//�͂����i���j
		MOTION_R_WHISK,		//8.	//�͂����i�E�j
	};

private:
	int							motionID;
	float						m_speed;
public:
	COgre(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~COgre();									// �f�X�g���N�^

	void SetEffectList(){};
	void ChangeEffect(){ };						// �G�t�F�N�g�̐���
	void PlayEffect(int){};

	void Control();								// ����
	void Draw();								// �`��
	void SetMotion(int _motionID);				// ���[�V����ID

	// �Q�b�^
	float GetCharaSpeed();						// �L�����̃X�s�[�h��Ԃ�
	//void SetPosition(D3DXVECTOR3 _position){};

private:


};