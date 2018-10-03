class CEffect
{
public:
	typedef struct{
		D3DXVECTOR3				position;   // �ʒu
		D3DXVECTOR3				move;		// �ړ���
		float					addAlpha;
		int						drawFrame;	// �`��J�n�t���[��
		int						totalFrame;
		float					scale;
		D3DXCOLOR				color;
		float					rotate;
	} PARTICLE;

private:
	PARTICLE*				m_particle;
	CVertex					m_vertex;			 // Vertex�N���X�I�u�W�F�N�g
	CTexture				m_texture;			 // �e�N�X�`���N���X�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pDevice; // �`��f�o�C�X
	CBillBoard				m_billBoard;

	
	float					m_angle;	// �ړ�����
	int						m_drawTime;	// �`�掞��
	int						m_endTime;	// �`��I������

public:
	CEffect(LPDIRECT3DDEVICE9 _pDevice);
	~CEffect();

	void SetParameter(PARTICLE* _particle);
	void SetRotate(float _angle);
	void Control();
	void Draw(CTexture _texture);
};