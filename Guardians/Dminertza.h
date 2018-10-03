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
	void Draw(D3DXVECTOR3 _position,D3DXMATRIX _rotate,float _alpha);
	// ���b�V���̃T�C�Y���擾
	void GetMeshSize(D3DXVECTOR3*,D3DXVECTOR3*);
private:

};


class CMinertza : public CPlayer
{
private:
	// �~�l���c�@���탂�f��
	CMinertzaWeapon* m_weapon;	
	// �~�l���c�@�̕���s��
	D3DXMATRIX m_matWeapon;		
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
	// 
	void DrawEffect(){}; 
	// �G�t�F�N�g�̍Đ�
	void PlayEffect(int){};
private:
	// ��`���쐬
	void CreateBox();
	// ��`�̐���
	void ControlRect();
	// �G�t�F�N�g�̐���
	void ControlEffect();
};
