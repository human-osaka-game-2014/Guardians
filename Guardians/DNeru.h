/**
 * @file DNeru.h
 */

class CNeru : public CPlayer
{
public:
	// test
	CTexture texture;
	CVertex vertex;

	static float m_charaHeight;	///< キャラの高さ

	struct ACTION_VALUE{
		char* name;				///< 技名
		int   useMP;			///< 消費MP
		int	  actionGauge;		///< 行動影響値
		float correctionValue;	///< 技補正値
	};
	static const int EFFECT_MAX_NUM = 2;
	static const int EFFECT_TYPE_NUM = 9; ///< エフェクトを使用する技は9種類
	
	static const ACTION_VALUE actionValue[];

	enum TELEPORT
	{
		TPSTATE_WAIT,
		TPSTATE_TELEPORT,
		TPSTATE_FADE_OUT,
		TPSTATE_AERIAL,
		TPSTATE_FALL,
	};
	enum EFK
	{
		FIRE_BALL,
		ICE_WALL,
	};
private:
	D3DXVECTOR3 DUMMY;
	CMaru* m_maru;

	CEffectManager*  m_efk[EFFECT_MAX_NUM];

	bool	m_isPlay;			///< エフェクト再生フラグ
	int		m_teleportState;		///< テレポートの状態

	

	D3DXVECTOR3 m_efkPos;	///< エフェクトの位置
	D3DXVECTOR3 m_moveValue; ///< エフェクトの移動量
	float		m_efkAngle;	///< エフェクト再生時の向き
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CNeru();									// デストラクタ
	
	void Draw();								// 描画
	//void SetPosition(D3DXVECTOR3 _position);	// 移動
	void SetMotion(int _motionID);				// モーションID
	void Load();

	// ゲッタ
	float GetCharaSpeed();						// キャラのスピードを返す

private:
	void ControlEffect();
	void PlayEffect(int _frame = 0);

	// 攻撃モーション
	void FireBall();
	void IceWall();
	void Teleport();
	void ThunderWhip();
	void StoneImpact();



	void CreateBox();	// ボックスを生成
	void SetEffectList();	// リスト生成



};
