#ifndef _GAME_MAP_POINTER_H_
#define _GAME_MAP_POINTER_H_


class CGameMapPointer:public CChip
{
public:
		enum State	// マップポインタの状態
	{
		STATE_WAIT,		// 動いていない状態(上下に揺れる/アニメーションは行う)
		STATE_MOVE,
		STATE_MOVE_RIGHT,		// チップ間を移動している状態
		STATE_MOVE_LEFT,
	};
private:
	static const int ANIM_TIME = 60 * 1;	// １枚の画像が表示される時間(仕様にないのであとで聞く)
	static const int SLIDE_TIME = 5;		// 点間移動時間(5frame)
	static const int MOVE_TIME = 60*3;		// 上下移動時間(3秒=180frame)
	static const FRECT	pointAnimRect[];
	static const int POINT_ANIM_NO[];			// アニメーションの順番

	static const int POINTER_MOVE_FRAME = 60;	// ポインターの移動時間
	static const D3DXVECTOR2 m_checkPointPos[CHECK_POINT_NUM];
	static const D3DXVECTOR2 POINTER_SIZE;
//	std::vector<D3DXVECTOR2>			m_position;			//動的な座標
	std::vector<D3DXVECTOR2>			m_staticPosition;	//静的な座標
	D3DXVECTOR2			m_nextPosition;	// 移動先座標
	D3DXVECTOR2			m_move;			// 一回(1frame)の移動量
	State				m_state;		// 状態
	float				m_shake;		// 上or下揺れる量
	float				m_shakeSpeed;	// ゆれる量の増減
	int					m_shakeCount;	// 上or下揺れるカウント
	int					m_animID;		// アニメーション番号(現在何枚目の画像か)
	int					m_animCount;	// アニメーションカウント
	int					m_pCount;		//ポインタの画像番号
	int					m_pTime;		//ポインタ点滅時間間隔
	int					m_clearCount;	//チェックポイントクリア記憶
	int					m_checkPointNum;	//チェックポイントの番号
	int					m_nextCheckPointNum;	//次のチェックポイントの番号
	int					m_backCount;			//戻るときの移動先座標決定のため
	//int					m_selectStageNum;
	int					m_pMoveTime;
	CTexture			m_pointTexture;
	CVertex				m_vertex;

	CGameData*			m_pGameData;
public:
	CGameMapPointer(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int clearStageNum,CGameData* _pGameData);	// コンストラクタ(デバイス、座標をセット)
	void Control();														// 制御
	void Draw();														// 描画

	// アクセッサ
	void SetNextPosition(D3DXVECTOR2 _nextPosition);					// 移動先の座標をセット
	void SetClearCount(int _clearCount);								//チェックポイントクリア記録セット
	void SetMoveDirection(State _state);								//進行方向セット
	State GetState();													//ポインタの状態をセット
};

#endif