class CAru : public CPlayer
{
public:

private:
	CEffect* effect;
public:
	CAru(LPDIRECT3DDEVICE9 _pDevice);			// �R���X�g���N�^
	~CAru();									// �f�X�g���N�^
	
	void Draw();								// �`��
	//void SetPosition(D3DXVECTOR3 _position);	// �ړ�
	void SetMotion(int _motionID);				// ���[�V����ID
	void Load();
	// �Q�b�^
	float GetCharaSpeed();						// �L�����̃X�s�[�h��Ԃ�

private:


};