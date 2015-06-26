
class CEnemy : public CCharacter
{
public:
	enum MOTIONLIST
	{
		MOTION_WAIT,		//0.	// 待機
		MOTION_FALTER,		//2.	//ひるみ
		MOTION_DEATH,		//3.	//死亡
		MOTION_WAIT2,		//1.	// 待機アクション（十秒間何も行動しなかった時の行動／スロー再生
	};
private:
	//float				 m_speed;		// 移動速度
protected:
	D3DXVECTOR3			 m_position;		    // 位置
	LPDIRECT3DDEVICE9	 m_pDevice; //描画デバイス
	D3DXVECTOR3			 m_playerPos;	// プレイヤーの位置(AI用)
//	D3DXVECTOR3			 m_position;	// 位置
	D3DXVECTOR3			 m_fieldPosition;	// フィールド座標
	DWORD				m_curTime;  // 現在時間
	DWORD				m_endTime; // 計測終了時間

	bool				m_discovered; // プレイヤーを発見した
	void DrawEffect(){};
	CGameData::ENEMY_STATUS m_status;

public:
	CEnemy(LPDIRECT3DDEVICE9 _pDevice);
	virtual ~CEnemy() = 0;

	virtual void Control() = 0;
	virtual void Draw() = 0;
	// プレイヤーの位置をセット
	void SetPlayerPos(D3DXVECTOR3 _position);
	//void SetPosition(D3DXVECTOR3 _position) = 0;
	void SetFieldPosition(D3DXVECTOR2 _position);

	void SetPosition(D3DXVECTOR3 _position);
	CGameData::ENEMY_STATUS GetStatus();
private:

};