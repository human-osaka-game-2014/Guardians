class CFenrir : public CEnemy
{
public:
	static const int MOTION_MAX_NUM = 21; //モーションの数 現在8個(26個予定)
	static const int EFFECT_MAX_NUM = 10;

	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// 待機
		MOTION_FALTER,		//1.	//ひるみ
		MOTION_DEATH,		//2.	//死亡
		MOTION_JUMP1,		//3.	//ジャンプ溜め	{ 300, 345 }
		MOTION_JUMP2,		//4.	//ジャンプ滞空（ここで一端固定	{ 345, 345 }
		MOTION_JUMP3,		//5.	//ジャンプ着地	{ 345, 400 }
		MOTION_TURN,		//6.	//向き反転 (415-445で跳び上がりつつ180°回転　しっぽにダメージ判定)	{ 400, 460 }
		MOTION_JUMP_BITE,	//7.	//ジャンプ着地噛みつき	{ 465, 520 }
		MOTION_BITE,		//8.	//噛みつき (540-555で口に当たり判定)	{ 520, 580 }
		MOTION_FIREBALL,	//9.	//火炎弾 (625で発射)	{ 580, 650 }
		MOTION_TAIL,		//10.	//しっぽ攻撃	{ 650, 690 }
		MOTION_FIRE1,		//11.	//火炎放射前	{ 690, 730 }
		MOTION_FIRE2,		//12.	//火炎放射中	{ 730, 730 }
		MOTION_FIRE3,		//13.	//火炎放射後	{ 730, 770 }
		MOTION_HOWL1,		//14.	//遠吠え前	{ 770, 800 }
		MOTION_HOWL2,		//15.	//遠吠え中	{ 800, 800 }
		MOTION_HOWL3,		//16.	//遠吠え後	{ 800, 860 }
		MOTION_HOWL4,		//17.	//遠吠え後待機	{ 0, 100 }
		MOTION_ATTACK1,		//18.	//体当たり前	{ 860, 930 }
		MOTION_ATTACK2,		//19.	//体当たり中	{ 930, 930 }
		MOTION_ATTACK3,		//20.	//体当たり後	{ 930, 960 }
	};
	enum BOXNAME
	{
		BODY,		//0.	// 胴体部	キャラの移動制限等
		HEAD,		//1.	// 頭		キャラの移動制限等／噛みつき攻撃
		TAIL,		//2.	// 尾		しっぽ攻撃
		EFFECT0,	//3.	// エフェクト一個目
	};

	bool m_boxFlag[EFFECT0 + EFFECT_MAX_NUM - 1];	//そのボックスを攻撃判定に使うか

private:
	D3DXVECTOR3 effectPos[EFFECT_MAX_NUM];	//エフェクトボックス座標 判定させたくないときはy座標を-3に

	bool	m_isPlay;			// エフェクト再生フラグ
	int		m_teleportState;	// テレポートの状態
	float	m_alpha;			// モデルのα値

	float	m_speed;

	int		TimeCount;	//行動値回復用

	float	e_position;		//エフェクト生成位置調整用


	float	m_sidePos[2];	//修正用

public:
	CFenrir(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CFenrir();									// デストラクタ

	void ChangeEffect(){ };						// エフェクトの生成
	void PlayEffect(int){ };

	void Control();								// 制御
	void Draw();								// 描画
	void SetMotion(int _motionID);				// モーションID

	// ゲッタ
	float GetCharaSpeed();						// キャラのスピードを返す
	int GetDamage();							// 使用技の攻撃力と付与を返す　（/10）攻撃力（%10）付与ID　
	//void SetPosition(D3DXVECTOR3 _position){};


	void CreateBox();							// ボックスを生成
	void BoxControl();							// ボックスを制御
private:
	//技制御
	void TailHammer();							//尻尾攻撃
	void Attack();
	

	void Jump();
	void Tail();
	void Bite();
	void Turn();
	void Howl();
	void Fire();

	bool CheckInterval();
};