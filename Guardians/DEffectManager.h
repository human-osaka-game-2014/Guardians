class CEffectManager
{
public:
	
private:
	
protected:
	CVertex					m_vertex;			 // Vertexクラスオブジェクト
	CTexture				m_texture;			 // テクスチャクラスオブジェクト
	LPDIRECT3DDEVICE9		m_pDevice; // 描画デバイス
	CEffect*				m_efk;
	D3DXVECTOR3				m_position;

	float					m_angle;	// 移動方向
	int						m_drawTime;	// 描画時間
	int						m_endTime;	// 描画終了時間

	bool					m_isPlay;
public:
	CEffectManager(LPDIRECT3DDEVICE9 _pDevice); // コンストラクタ
	~CEffectManager(); // デストラクタ

	bool GetExists();			// エフェクトが再生されているかどうか

	virtual void Run() = 0;

	virtual void Play(float _angle,D3DXVECTOR3 _position) = 0;
	// エフェクトの位置を返す
	D3DXVECTOR3 GetPosition();

	// エフェクトの削除命令
	void Erase();
};