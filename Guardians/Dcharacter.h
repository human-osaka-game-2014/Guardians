class CCharacter
{
public:
	#define			PLAYER_MAX 3  // 操作できるキャラクターは3体
	#define			ENEMY_MAX 4		// 敵のキャラクターは4体

	static const int ACTION_GAUGE_MAX = 100; // アクションゲージの最大値(100)

	static const float RIGHT_WALL;
	static const float LEFT_WALL;

	static const float LEFT_ANGLE;	// キャラクターの向き　左
	static const float RIGHT_ANGLE;	// キャラクターの向き 右

	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};

	enum STEP{ // 戦闘開始演出
		STEP_FADE_IN,
		STEP_MOVE,
	};

	enum EFFECT{
		MAIN_EFK,
		SUB_EFK,
	};
protected:

	struct EFFECT_LIST{
		LPCWSTR name;		// ファイル名
		LPCWSTR subName;	// 2つエフェクトを生成する技の場合(配列で持ちたくないのでsubNameとする) 
		D3DXVECTOR3 scale;	// 倍率
		D3DXVECTOR3 move;	// 移動量
		float  damage;
	};

	enum STATE{ // キャラクターの状態
		STATE_WAIT,
		STATE_RUN,
		STATE_JUMP,
		STATE_SQUAT,
		STATE_SQUAT2,
		STATE_AVOID,
		STATE_INVICIBLE,
		STATE_ATTACK,
		STATE_PROJECTILE,
	};

	enum MOTION_STATE{
		MSTATE_WAIT,
		MSTATE_JUMP,
		MSTATE_SQUAT,
		MSTATE_AVOID,
		MSTATE_IN_MOTION,	// モーション中は動けない状態
		MSTATE_AERIAL,
	};

	LPDIRECT3DDEVICE9		m_pDevice; //描画デバイス
	XFileAnimationMesh*		m_model;

	D3DXVECTOR3			m_scale;    // モデルのスケール
	static float		m_alpha;	// モデルのアルファ値
	
	D3DXVECTOR2			 m_speed;	// キャラクターの移動速度
	D3DXVECTOR2			 m_move;    // キャラクターの移動量
	float				 m_angle;		// キャラクターの向き

	STEP				 m_step; 
	int					m_curEffect;

	MOTION_STATE		 m_motionState;		// キャラクターの状態
	STATE				 m_state;		// キャラクターの状態
	int					 m_motionID;			// セットするモーションID

	double				 m_time;		// 現在のアニメーション時間
	int					 m_curMotionID;	// 現在再生しているモーション番号
	int					 m_nowEffect; // 現在生成しているエフェクト
	int					 m_HitCount; // １つの技のヒット回数

	int					m_damage; // 技のダメージ

	bool				m_isHit;		// 衝突判定用
	bool				m_takeDamage;	// ダメージを受けた時
	bool				m_motionStop;	// モーション停止フラグ
	bool				m_invincible;   // 無敵

	bool				m_endMotion;
	// 以下2つは構造体にする予定
	int					m_actionGauge; // 行動値
	float				m_correctionValue;	// 技補正値

	//std::vector<XFileAnimationMesh::SPHERE>		m_sphere; // 衝突判定用矩形
	std::vector<XFileAnimationMesh::BOX>		m_box;	  // 衝突判定用矩形
	std::vector<XFileAnimationMesh::BOX>		m_unhitting_box;	  // やられ判定用
	std::vector<XFileAnimationMesh::BOX>		m_hitting_box;	  // 攻撃判定用

	std::vector<XFileAnimationMesh::ANIMLIST> m_animList;	// アニメーション用リスト

private:

	int				m_turnNo;
public:
	CCharacter(LPDIRECT3DDEVICE9 _pDevice , float _angle);	// コンストラクタ
	~CCharacter();											// デストラクタ

	virtual void Control() = 0; // 制御
	virtual void Draw() = 0;	// 描画

	void SetRect();				// 衝突判定に使用する矩形のセット

	D3DXMATRIX GetMatrix(LPCTSTR);

	void ResetMotion(int _motionID);	// 割り込んでモーションを変更する
	bool CheckMotionEnd(int _motioniD);			// モーションが終わっているか
	
	virtual void ChangeEffect() = 0; // エフェクトの生成
	// セッタ
	virtual void SetMotion(int _motionID) = 0;						// モーションIDをセット
	//void SetPosition(D3DXVECTOR3 _position);			// characterの位置をセットする
	void SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame);		// ボーンの位置をセットする
	//void SetFieldSpeed(D3DXVECTOR2 _spd);
	void SetCharaSpeed(int);
	void SetHitFlag(bool);
	void SetTakeDamageFlg();
	
	//void AddAlpha(float _value);

	// ゲッタ
	std::vector<XFileAnimationMesh::BOX> GetHittingBox();
	std::vector<XFileAnimationMesh::BOX> GetunHittingBox();
	std::vector<XFileAnimationMesh::SPHERE> GetSphere();

	D3DXVECTOR3 GetBonePos(LPCTSTR _name);


	float		GetDamage();	// ダメージを取得
	D3DXVECTOR2 GetCharaSpeed();								// キャラクターの移動速度を返す
	STATE		GetState();
	STEP		GetStep();
	bool		GetMotionEnd();
protected:
	void UpdateAnimTime(float _time = (1.0f/60.f));
	// 衝突判定矩形の更新
	void UpdateRect(D3DXVECTOR3 _position , int _ID,float radian = 0);
	void UpdateRect(LPCTSTR _name , int _ID );
	void UpdateSphere(D3DXVECTOR3 _position , XFileAnimationMesh::SPHERE* _sphere);							// スフィアの位置情報を更新
	void DrawSphere(XFileAnimationMesh::SPHERE _sphere);
	void UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box,float radian = 0);							// スフィアの位置情報を更新
	// 矩形の描画
	void DrawBox(XFileAnimationMesh::BOX _box);

	virtual void PlayEffect(int) = 0; //エフェクトを再生
};
