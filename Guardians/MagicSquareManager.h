class CMagicSquare : public CEffectManager
{
public:
	// �g�p����e�N�X�`���̐�
	static const int TEX_TYPE_NUM = 3;

	static const int PARTICLE_NUM = 10;
	// �~�̃p�[�e�B�N����
	static const int CIRCLE_NUM = 3;
	static const float CIRCLE_ADDSCALE[CIRCLE_NUM];

	// �~�̏����X�P�[��
	static const float INIT_CIRCLE_SCALE;
	// �~�̍ő�X�P�[��
	static const float MAX_CIRCLE_SCALE;
	// �����w�̏����X�P�[��
	static const float INIT_MAGIC_SCALE;
	

	enum TEX_TYPE{ // �e�N�X�`���̎��
		SHINY,
		CIRCLE,
		MAGIC,
	};

private:
	CTexture m_tex[TEX_TYPE_NUM];

	// �~�̃p�[�e�B�N��
	CEffect::PARTICLE m_circle[CIRCLE_NUM];
	// �����w
	CEffect::PARTICLE m_magic;

	CEffect::PARTICLE m_particle[PARTICLE_NUM];
public:
	CMagicSquare(LPDIRECT3DDEVICE9 _pDevice);
	~CMagicSquare();

	void Play(float _angle,D3DXVECTOR3 _position);
	void Run();

	float GetSize();
};