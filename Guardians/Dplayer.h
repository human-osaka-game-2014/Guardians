class CPlayer : public CCharacter
{
public:
	static const int MOTION_MAX_NUM = 26; //モーションの数 現在26個(27個予定)

	static const float INIT_VELOCITY;	 // ジャンプ初速度

	static const float INIT_HEIGHT_POSITION;	// キャラクターの高さ

	enum DIRECTION{ // 向き
		DIR_LEFT,
		DIR_RIGHT,
	};
	// 共通のモーションリスト
	enum MOTIONLIST
	{
		MOTION_WAIT,			//1.	待機
		MOTION_START_RUN,			//2.	走り出し
		MOTION_RUN,			//3.	走る
		MOTION_STOP_RUN,			//4.	止まる
		MOTION_JUMP,			//5.	ジャンプ
		MOTION_JUMP_FALL,
		MOTION_SQUAT_START,		//6.	しゃがむ
		MOTION_SQUAT,		//7.	しゃがみ中
		MOTION_STAND_UP,		//8.	しゃがみ解除
		MOTION_AVOID,		//9.	緊急回避
		MOTION_ATTACK,		//10.	通常攻撃
		MOTION_ATTACK2,		//11.	通常攻撃連撃1
		MOTION_ATTACK3,		//12.	通常攻撃連撃2
		MOTION_UPPER,		//13.	上攻撃
		MOTION_LOWER,		//14.	下攻撃
		MOTION_AIR,			//15.	下攻撃（空中）
		MOTION_SKILL,		//16.	技1
		MOTION_SKILL2,		//17.	前＋技
		MOTION_SKILL3,		//18.	上＋技
		MOTION_SKILL4,		//19.	下＋技
		MOTION_SKILLAIR,		//20.	下＋技（空中）
		//MOTION_SPECIAL,		//21.	必殺技
		MOTION_FLINCH,			//22.	ダメージ喰らい
		MOTION_DEAD,			//23.	死亡
		MOTION_STUN,			//24.	スタン
		MOTION_APPEAL,		//25.	固有モーション1（戦闘開始時用）
		MOTION_APPEAL2,		//26.	固有モーション2（勝利時）
	};
protected:
	static		D3DXVECTOR3 m_position;
	//EFFECT_LIST		m_effectList[MOTION_MAX_NUM]; // エフェクトリスト(モーションの数分確保)
	D3DXVECTOR3			m_enemyPos;			// 敵の位置
	DIRECTION			m_direction;		// キャラクターの向き
	float				m_jumpSpeed;		// ジャンプ速度
	bool				m_jumpFlag;			// ジャンプ中フラグ
	D3DXVECTOR2			m_jumpMove;			// ジャンプ中のy座標
	int					m_jumpStartFrame;

	bool				m_isPlay;
public:
	// コンストラクタ
	CPlayer(LPDIRECT3DDEVICE9 _pDevice);
	// デストラクタ
	virtual ~CPlayer() = 0;
	// 制御
	void Control();
	// 描画
	virtual void Draw() = 0;

	// エフェクトの再生
	virtual void PlayEffect(int) = 0;

	void addAlpha(float _value);
	// ゲッタ

	// 衝突しているか
	void GetHit();
	// 防御貫通フラグ
	int Getflag();

	// 位置を取得
	D3DXVECTOR3 GetPosition();
	// セッタ

	// 敵の位置をセット
	void	SetEnemyPos(D3DXVECTOR3 _position); 
	void	SetPosition(D3DXVECTOR3 _position);
private:
	// ジャンプ
	void Jump();
	// 走る
	void Run();
	// 攻撃
	void Attack();
	// 空中での攻撃
	void Aerial();
	// 回避
	void avoid();
	// しゃがむ
	void Squat();

	// キャラクターの移動
	void Move();
	// 
	void Flinch();
	// 落下
	void Fall(int _frame);
};
