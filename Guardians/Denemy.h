
class CEnemy : public CCharacter
{
public:
	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// �ҋ@
		MOTION_FALTER,		//2.	//�Ђ��
		MOTION_DEATH,		//3.	//���S
		MOTION_WAIT2,		//1.	// �ҋ@�A�N�V�����i�\�b�ԉ����s�����Ȃ��������̍s���^�X���[�Đ�
	};
private:
	//float				 m_speed;		// �ړ����x
protected:
	D3DXVECTOR3			 m_position;		    // �ʒu
	LPDIRECT3DDEVICE9	 m_pDevice; //�`��f�o�C�X
	D3DXVECTOR3			 m_playerPos;	// �v���C���[�̈ʒu(AI�p)
//	D3DXVECTOR3			 m_position;	// �ʒu
	D3DXVECTOR3			 m_fieldPosition;	// �t�B�[���h���W
	DWORD				m_curTime;  // ���ݎ���
	DWORD				m_endTime; // �v���I������

	bool				m_discovered; // �v���C���[�𔭌�����
	void DrawEffect(){};
	CGameData::ENEMY_STATUS m_status;

public:
	CEnemy(LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CEnemy() = 0;

	virtual void Control() = 0;
	virtual void Draw() = 0;
	// �v���C���[�̈ʒu���Z�b�g
	void SetPlayerPos(D3DXVECTOR3 _position);
	//void SetPosition(D3DXVECTOR3 _position) = 0;
	void SetFieldPosition(D3DXVECTOR2 _position);

	void SetPosition(D3DXVECTOR3 _position);
	CGameData::ENEMY_STATUS GetStatus();
private:

};