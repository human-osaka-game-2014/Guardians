/**
 * @file DAldfauth.h
 * @author 檀上
 */

/**
 * アルドファウトの制御
 */
class CAldfauth : public CPlayer
{
public:

private:
	CBillBoard vertex;
	CTexture tex;
public:
	// コンストラクタ
	CAldfauth(LPDIRECT3DDEVICE9 _pDevice);
	// デストラクタ
	~CAldfauth();

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

	// アルドファウトモーション
	void Rush();	// 突進
	void Upper();	// アッパー
};
