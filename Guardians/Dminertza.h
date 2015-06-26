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
	void Draw(D3DXVECTOR3 _position,D3DXMATRIX _rotate,float _alpha);
	// メッシュのサイズを取得
	void GetMeshSize(D3DXVECTOR3*,D3DXVECTOR3*);
private:

};


class CMinertza : public CPlayer
{
private:
	// ミネルツァ武器モデル
	CMinertzaWeapon* m_weapon;	
	// ミネルツァの武器行列
	D3DXMATRIX m_matWeapon;		
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
	// 
	void DrawEffect(){}; 
	// エフェクトの再生
	void PlayEffect(int){};
private:
	// 矩形を作成
	void CreateBox();
	// 矩形の制御
	void ControlRect();
	// エフェクトの制御
	void ControlEffect();
};
