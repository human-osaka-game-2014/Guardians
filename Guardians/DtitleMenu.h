class CTitleMenu
{
public:
	enum Draw // 描画する文字
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

	float						m_move;				// 一回の移動量
	float						m_nextPosition;		// 移動先の位置

	State						m_state;			// 移動状態
	int							m_alpha;			// α値
	int							m_addalpha;			// α増加量
	D3DXVECTOR2					m_position;			// 座標(x,y)
	int							m_timeCount;		// 時間計測用
	bool						m_sceneChange;		// シーン遷移フラグ

	int							m_drawID;			//
	bool						m_flg;				
	float						m_size;				// 描画時のサイズ

public:
	CTitleMenu(LPDIRECT3DDEVICE9 _pDevice);
	~CTitleMenu();

	void Control();
	void Draw(int _selectID,int _skipFlag);
	void SetDrawID(int _drawID);
};