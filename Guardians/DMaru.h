/**
 * @file DMaru.h
 */

class CMaru : public CPlayer
{
public:

private:
	int		m_teleportState;		///< テレポートの状態
	float	m_alpha;			///< モデルのα値
	D3DXVECTOR3 m_neruPos;
public:
	void DrawEffect(){};
	CMaru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CMaru();									// デストラクタ

	void ChangeEffect(){};						// エフェクトの生成
	void Draw();								// 描画
	void Move( D3DXVECTOR3 _position , int _motionID , int _angle);
	//void SetPosition(D3DXVECTOR3 _position);	// 移動
	void SetMotion(int _motionID);				// モーションID
	void SetPosition( D3DXVECTOR3 _position);
	void SetStopMotion(bool _flag);
private:
	void CreateBox();	// ボックスを生成
	void SetEffectList(){};	// リスト生成
	void PlayEffect(int){};

};
