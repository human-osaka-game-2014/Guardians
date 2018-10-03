class CLogo
{
public:
	enum FadeType	//�_�ŏ��
	{
		FADE_IN,
		FADE_STOP,
		FADE_OUT,
		FADE_END,
	};
private:
	LPDIRECT3DDEVICE9			m_pDevice;	//�`��f�o�C�X
	CVertex						m_vertex;
	CTexture					m_texture;

	FadeType					m_fadeType;		// �_�ŏ��
	State						m_state;		// ��ԁ@�t�F�[�h�C���E�t�F�[�h�A�E�g�̊Ǘ�
	int							m_alpha;		// ���l
	int							m_addAlpha;		// ���l�̑�����
	int							m_timeCount;	// ���Ԍv���p
	bool						m_transition;	// �X�L�b�v���邩�ǂ����̃t���O(���ݖ��g�p)
public:
	CLogo(LPDIRECT3DDEVICE9 _pDevice);
	~CLogo();
	void Control();
	void Draw();

	bool GetFlag();
};