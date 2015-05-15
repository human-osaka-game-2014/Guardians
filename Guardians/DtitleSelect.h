class CTitleSelect
{
public:
	enum Draw
	{
		DRAW_START,
		//DRAW_LOAD,
		//DRAW_CONFIG,
		//DRAW_EXIT,
		DRAW_PRESS,
	};

private:
	LPDIRECT3DDEVICE9			m_pDevice;	//描画デバイス
	CVertex						m_vertex;
	CTexture					m_texture;

	float						m_move;
	float						m_nextPosition;

	State						m_state;
	int							m_alpha;
	int							m_addalpha;
	FRECT						m_rect;
	D3DXVECTOR2					m_position;
	int							m_timeCount;
	int							m_drawCount;
	int							m_drawID;
	bool						m_flg;
	float						m_size;

public:
	CTitleSelect(LPDIRECT3DDEVICE9 _pDevice);
	~CTitleSelect();

	void Control();
	void Draw(int _selectID,int _skipFlag);
	void SetDrawID(int _drawID);
};