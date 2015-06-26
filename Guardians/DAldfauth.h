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
	enum BOX_TYPE{
		BOX_BODY,
		BOX_ATTACK,
		BOX_HAND_STRIKE,
	};
private:
	CAldEffect* m_efk;
public:
	// コンストラクタ
	CAldfauth(LPDIRECT3DDEVICE9 _pDevice);
	// デストラクタ
	~CAldfauth();

	void DrawEffect();
	// 描画
	void Draw();

	// モーション変更
	void SetMotion(int _motionID);

	// 再生するエフェクの生成
	void ChangeEffect(){};
	// エフェクトの再生
	void PlayEffect();

private:
	// 矩形を作成
	void CreateBox();
	// 矩形の制御
	void ControlRect();

	// アルドファウトモーション
	void Rush();	// 突進
};
