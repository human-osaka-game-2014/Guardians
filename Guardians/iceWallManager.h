class CIceWallManager : public CEffectManager
{
public:
	static const int PARTICLE_NUM = 20;
	static float ADD_ROTATE;
private:
	CMagicSquare* m_magic;	// 魔方陣クラスオブジェクト

	CTexture m_tex;


	CEffect::PARTICLE m_particle[PARTICLE_NUM];
	float			  m_maxRotate[PARTICLE_NUM];

public:
	CIceWallManager(LPDIRECT3DDEVICE9 _pDevice);
	~CIceWallManager();

	void Play(float _angle,D3DXVECTOR3 _position);
	void Run();
};