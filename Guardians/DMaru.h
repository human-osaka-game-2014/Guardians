class CMaru : public CPlayer
{
public:
	static const int EFFECT_MAX_NUM = 2;

	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
private:

	bool	m_isPlay;			// エフェクト再生フラグ
	int		m_teleportState;		// テレポートの状態
	float	m_alpha;			// モデルのα値
	D3DXVECTOR3 m_neruPos;
public:
	CMaru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CMaru();									// デストラクタ
		void ChangeEffect(){};						// エフェクトの生成

	void Draw();								// 描画
	void Move( D3DXVECTOR3 _position , int _motionID , int _angle);
	//void SetPosition(D3DXVECTOR3 _position);	// 移動
	void SetMotion(int _motionID);				// モーションID
	void SetPosition( D3DXVECTOR3 _position);
	void SetStopMotion(bool _flag);
	
	void UpdateRect(LPCTSTR _name , int _ID );
	void UpdateRect(D3DXVECTOR3 _position , int _ID );

private:

	void CreateBox();	// ボックスを生成
	void SetEffectList(){};	// リスト生成
	void PlayEffect(int){};

};