class CTitle
{
public:
static const int 			MOVE_TIME  = 60;

	enum State
	{
		STATE_WAIT,
		STATE_MOVE,
		STATE_MOVE_END,
		STATE_TRANSITION,
	};
private:
	LPDIRECT3DDEVICE9			m_pDevice;	//描画デバイス
	CVertex						m_vertex;
	CTexture					m_texture;

	float						m_move;
	float						m_nextPosition;

	State						m_state;
	int							m_alpha;
	int							m_addAlpha;
	FRECT						m_rect;
	D3DXVECTOR2					m_position;
	int							m_timeCount;
	bool						m_sceneChange;
public:
	CTitle(LPDIRECT3DDEVICE9 _pDevice);
	~CTitle();

	void Control(int _skipFlag);
	void SetMovement();
	void Draw( );

	State GetState();
	void SetState(State _state);
};