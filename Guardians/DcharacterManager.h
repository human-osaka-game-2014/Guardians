class CCharacterManager
{
public:

	typedef struct _MODELDATA{
		CPlayer* player[3];
		CEnemy*  enemy[4];
	}MODELDATA;

	enum STATE{ // プレイヤーの状態
		STATE_WAIT,
		STATE_WALK,
		STATE_DASH,
		STATE_SQUAT,
		STATE_JUMP,
		STATE_ATTACK,

	};

private:
	MODELDATA* m_pModel;

	LPDIRECT3DDEVICE9	m_pDevice; //描画デバイス
	CGameData*			m_pGameData;				// ゲームデータ

	CPlayer*			m_activePlayer;				// アクティブキャラクター格納用
	CEnemy*				m_activeEnemy;				// アクティブエネミー格納用

	// 敵とプレイヤーのステータス
	CGameData::Character m_player;
	CGameData::Character m_enemy;

	int				m_turnNo;
	int				m_enemyState;	// 敵の状態
	int				m_playerState;	// プレイヤーの状態
	bool			isHit;			// 衝突判定確認用
	bool			m_moveFlag;		// 移動可能かどうか
	bool			m_hitWall;
	D3DXVECTOR2			m_speed;	// キャラクターの移動速度
	D3DXVECTOR2			m_fieldPosition;
public:
	// コンストラクタ
	CCharacterManager(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,MODELDATA* _chara);
	// デストラクタ
	~CCharacterManager();
	// 制御
	virtual void Control();

	bool HitCheck(std::vector<XFileAnimationMesh::BOX>,std::vector<XFileAnimationMesh::BOX>);
	// 描画
	virtual void Draw();

	// 移動フラグをセット
	void setMoveFlag(bool _flag);
	bool GetMoveFlag();
	bool GetHitWall();
	void SetFieldPosition(D3DXVECTOR2 _position);
	CPlayer* GetPlayer();
	void SetPosition(D3DXVECTOR2 _position);
	void SetFieldSpeed(D3DXVECTOR2 _spd);

	D3DXVECTOR2 CCharacterManager::GetCharaSpeed();

	D3DXVECTOR3 GetCharaPosition();

	CGameData::ENEMY_STATUS GetHP();

	bool		GetMotionEnd(int _motionID);

	void CharacterChange();
	void SetAlpha();
private:
	void CalcPlayerDamage();
	void CalcEnemyDamage();
	// 円同士の衝突判定
	bool SphereCollision(XFileAnimationMesh::SPHERE _pSphereA, XFileAnimationMesh::SPHERE _pSphereB);
	// ボックス同士の衝突判定
	bool AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2);
	// 円とボックスの衝突判定
	bool SphereToBox(XFileAnimationMesh::SPHERE _pSphere,XFileAnimationMesh::BOX _box);
};
