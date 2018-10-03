class CTitleMenu
{
public:
	enum Draw // �`�悷�镶��
	{
		DRAW_START,
		//DRAW_LOAD,
		//DRAW_CONFIG,
		//DRAW_EXIT,
		DRAW_PRESS,
	};
private:
	LPDIRECT3DDEVICE9			m_pDevice;	//�`��f�o�C�X
	CVertex						m_vertex;
	CTexture					m_texture;

	float						m_move;				// ���̈ړ���
	float						m_nextPosition;		// �ړ���̈ʒu

	State						m_state;			// �ړ����
	int							m_alpha;			// ���l
	int							m_addalpha;			// ��������
	D3DXVECTOR2					m_position;			// ���W(x,y)
	int							m_timeCount;		// ���Ԍv���p
	bool						m_sceneChange;		// �V�[���J�ڃt���O

	int							m_drawID;			//
	bool						m_flg;				
	float						m_size;				// �`�掞�̃T�C�Y

public:
	CTitleMenu(LPDIRECT3DDEVICE9 _pDevice);
	~CTitleMenu();

	void Control();
	void Draw(int _selectID,int _skipFlag);
	void SetDrawID(int _drawID);
};