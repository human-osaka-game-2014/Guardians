class CMinertzaWeapon
{
private:
	C3DModel* m_model;	// 3dmodel class object
public:
	// コンストラクタ
	CMinertzaWeapon(LPDIRECT3DDEVICE9 _pDevice);
	// デストラクタ
	~CMinertzaWeapon();
	// 描画
	void Draw(D3DXVECTOR3 _position,D3DXMATRIX _rotate);

	void GetMeshSize(D3DXVECTOR3*,D3DXVECTOR3*);
private:

};


class CMinertza : public CPlayer
{
public:

private:
	CMinertzaWeapon* m_weapon;	// ミネルツァ武器モデル

	bool	m_isPlay;			// エフェクト再生フラグ

	D3DXMATRIX m_matWeapon;		// ミネルツァの武器のマテリアル
public:
	// コンストラクタ
	CMinertza(LPDIRECT3DDEVICE9 _pDevice);
	// デストラクタ
	~CMinertza();

	// 描画
	void Draw();
	// モーション変更
	void SetMotion(int _motionID);

	// 再生するエフェクの生成
	void ChangeEffect(){};
	// エフェクトの再生
	void PlayEffect(int){};


	
private:
	// 矩形を作成
	void CreateBox();
	// 矩形の制御
	void ControlRect();
	// エフェクトの制御
	void ControlEffect();

	D3DXVECTOR3 GetYawPitchRoll(D3DXMATRIX _mat);
};
