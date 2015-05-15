class CLogo
{
public:
	enum FadeType	//点滅状態
	{
		FADE_IN,
		FADE_STOP,
		FADE_OUT,
		FADE_END,
	};
private:
	LPDIRECT3DDEVICE9			m_pDevice;	//描画デバイス
	CVertex						m_vertex;
	CTexture					m_texture;

	FadeType					m_fadeType;		// 点滅状態
	State						m_state;		// 状態　フェードイン・フェードアウトの管理
	int							m_alpha;		// α値
	int							m_addAlpha;		// α値の増加量
	int							m_timeCount;	// 時間計測用
	bool						m_transition;	// スキップするかどうかのフラグ(現在未使用)
public:
	CLogo(LPDIRECT3DDEVICE9 _pDevice);
	~CLogo();
	void Control();
	void Draw();

	bool GetFlag();
};