class COgre : public CEnemy
{
public:
	static const int MOTION_MAX_NUM = 9; //モーションの数

	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// 待機
		MOTION_FALTER,		//2.	//ひるみ
		MOTION_DEATH,		//3.	//死亡
		MOTION_WAIT2,		//1.	// 待機アクション（十秒間何も行動しなかった時の行動／スロー再生
		MOTION_BITE,		//4.	// 噛みつき
		MOTION_STONE,		//5.	//石つぶて攻撃
		MOTION_POISON_FOG,	//6.	//毒粉（330-339→340-369（スロー再生繰り返し）→370-379)
		MOTION_L_WHISK,		//7.	//はたく（左）
		MOTION_R_WHISK,		//8.	//はたく（右）
	};

private:
	int							motionID;
	float						m_speed;
public:
	COgre(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~COgre();									// デストラクタ

	void SetEffectList(){};
	void ChangeEffect(){ };						// エフェクトの生成
	void PlayEffect(int){};

	void Control();								// 制御
	void Draw();								// 描画
	void SetMotion(int _motionID);				// モーションID

	// ゲッタ
	float GetCharaSpeed();						// キャラのスピードを返す
	//void SetPosition(D3DXVECTOR3 _position){};

private:


};