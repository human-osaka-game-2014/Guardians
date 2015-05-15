class CAru : public CPlayer
{
public:

private:
	CEffect* effect;
public:
	CAru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CAru();									// デストラクタ
	
	void Draw();								// 描画
	//void SetPosition(D3DXVECTOR3 _position);	// 移動
	void SetMotion(int _motionID);				// モーションID
	void Load();
	// ゲッタ
	float GetCharaSpeed();						// キャラのスピードを返す

private:


};