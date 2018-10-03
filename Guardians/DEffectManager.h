class CEffectManager
{
public:
	
private:
	
protected:
	CVertex					m_vertex;			 // Vertex�N���X�I�u�W�F�N�g
	CTexture				m_texture;			 // �e�N�X�`���N���X�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pDevice; // �`��f�o�C�X
	CEffect*				m_efk;
	D3DXVECTOR3				m_position;

	float					m_angle;	// �ړ�����
	int						m_drawTime;	// �`�掞��
	int						m_endTime;	// �`��I������

	bool					m_isPlay;
public:
	CEffectManager(LPDIRECT3DDEVICE9 _pDevice); // �R���X�g���N�^
	~CEffectManager(); // �f�X�g���N�^

	bool GetExists();			// �G�t�F�N�g���Đ�����Ă��邩�ǂ���

	virtual void Run() = 0;

	virtual void Play(float _angle,D3DXVECTOR3 _position) = 0;
	// �G�t�F�N�g�̈ʒu��Ԃ�
	D3DXVECTOR3 GetPosition();

	// �G�t�F�N�g�̍폜����
	void Erase();
};