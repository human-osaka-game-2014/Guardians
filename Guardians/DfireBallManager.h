class CFireBallManager : public CEffectManager
{
public:
	static const int PARTICLE_MAX_NUM = 200;
	// 初期サイズ
	static const float INIT_SCALE;
	// エフェクトの移動量
	static const float FIRE_MOVE;

private:
	CEffect::PARTICLE m_particle[PARTICLE_MAX_NUM];

	CTexture m_texture;
	float		m_fireMove;
public:
	CFireBallManager(LPDIRECT3DDEVICE9 _pDevice);
	~CFireBallManager();
	
	void Run();
	void Play(float _angle,D3DXVECTOR3 _position);
};