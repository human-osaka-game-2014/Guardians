class CEffect
{
public:
	typedef struct{
		D3DXVECTOR3				position;   // 位置
		D3DXVECTOR3				move;		// 移動量
		float					addAlpha;
		int						drawFrame;	// 描画開始フレーム
		int						totalFrame;
		float					scale;
		D3DXCOLOR				color;
		float					rotate;
	} PARTICLE;

private:
	PARTICLE*				m_particle;
	CVertex					m_vertex;			 // Vertexクラスオブジェクト
	CTexture				m_texture;			 // テクスチャクラスオブジェクト
	LPDIRECT3DDEVICE9		m_pDevice; // 描画デバイス
	CBillBoard				m_billBoard;

	
	float					m_angle;	// 移動方向
	int						m_drawTime;	// 描画時間
	int						m_endTime;	// 描画終了時間

public:
	CEffect(LPDIRECT3DDEVICE9 _pDevice);
	~CEffect();

	void SetParameter(PARTICLE* _particle);
	void SetRotate(float _angle);
	void Control();
	void Draw(CTexture _texture);
};