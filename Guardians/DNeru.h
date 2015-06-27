/**
 * @file DNeru.cpp
 * @author 檀上
 */

/**
 * ネルの制御
 */
class CNeru : public CPlayer
{
public:
	static float m_charaHeight;	///< キャラの高さ
	static const int EFFECT_MAX_NUM = 2;	// エフェクトの数
	static const int EFFECT_TYPE_NUM = 9;	///< エフェクトを使用する技は9種類
	
	// テレポートの状態
	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_FADE_OUT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
	// エフェクトの種類
	enum EFK
	{
		FIRE_BALL,
		ICE_WALL,
	};
	// 矩形の種類
	enum BOX_TYPE
	{
		BOX_BODY,
		BOX_FIRE_BALL,
	};
private:
	D3DXVECTOR3 DUMMY;			// 衝突判定
	CMaru* m_maru;				// マルクラスオブジェクト

	CEffectManager*  m_efk[EFFECT_MAX_NUM];

	D3DXVECTOR3 m_efkPos;		///< エフェクトの位置
	D3DXVECTOR3 m_moveValue;	///< エフェクトの移動量

	float		m_efkAngle;		///< エフェクト再生時の向き
	int			m_teleportState;		///< テレポートの状態
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CNeru();									// デストラクタ
	
	void Draw();								// 描画
	void DrawEffect();
	void SetMotion(int _motionID);				// モーションID
private:
	void PlayEffect(int _frame = 0);			// エフェクトの再生

	// 攻撃モーション
	void FireBall();
	void IceWall();
	void Teleport();

	// ボックスを生成
	void CreateBox();	



};
