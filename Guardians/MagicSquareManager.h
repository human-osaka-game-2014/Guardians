class CMagicSquare : public CEffectManager
{
public:
	// 使用するテクスチャの数
	static const int TEX_TYPE_NUM = 3;

	static const int PARTICLE_NUM = 10;
	// 円のパーティクル数
	static const int CIRCLE_NUM = 3;
	static const float CIRCLE_ADDSCALE[CIRCLE_NUM];

	// 円の初期スケール
	static const float INIT_CIRCLE_SCALE;
	// 円の最大スケール
	static const float MAX_CIRCLE_SCALE;
	// 魔方陣の初期スケール
	static const float INIT_MAGIC_SCALE;
	

	enum TEX_TYPE{ // テクスチャの種類
		SHINY,
		CIRCLE,
		MAGIC,
	};

private:
	CTexture m_tex[TEX_TYPE_NUM];

	// 円のパーティクル
	CEffect::PARTICLE m_circle[CIRCLE_NUM];
	// 魔方陣
	CEffect::PARTICLE m_magic;

	CEffect::PARTICLE m_particle[PARTICLE_NUM];
public:
	CMagicSquare(LPDIRECT3DDEVICE9 _pDevice);
	~CMagicSquare();

	void Play(float _angle,D3DXVECTOR3 _position);
	void Run();

	float GetSize();
};