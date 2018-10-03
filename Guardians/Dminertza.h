class CMinertzaWeapon
{
private:
	C3DModel* m_model;	// 3dmodel class object
public:
	// �R���X�g���N�^
	CMinertzaWeapon(LPDIRECT3DDEVICE9 _pDevice);
	// �f�X�g���N�^
	~CMinertzaWeapon();
	// �`��
	void Draw(D3DXVECTOR3 _position,D3DXMATRIX _rotate);

	void GetMeshSize(D3DXVECTOR3*,D3DXVECTOR3*);
private:

};


class CMinertza : public CPlayer
{
public:

private:
	CMinertzaWeapon* m_weapon;	// �~�l���c�@���탂�f��

	bool	m_isPlay;			// �G�t�F�N�g�Đ��t���O

	D3DXMATRIX m_matWeapon;		// �~�l���c�@�̕���̃}�e���A��
public:
	// �R���X�g���N�^
	CMinertza(LPDIRECT3DDEVICE9 _pDevice);
	// �f�X�g���N�^
	~CMinertza();

	// �`��
	void Draw();
	// ���[�V�����ύX
	void SetMotion(int _motionID);

	// �Đ�����G�t�F�N�̐���
	void ChangeEffect(){};
	// �G�t�F�N�g�̍Đ�
	void PlayEffect(int){};


	
private:
	// ��`���쐬
	void CreateBox();
	// ��`�̐���
	void ControlRect();
	// �G�t�F�N�g�̐���
	void ControlEffect();

	D3DXVECTOR3 GetYawPitchRoll(D3DXMATRIX _mat);
};
