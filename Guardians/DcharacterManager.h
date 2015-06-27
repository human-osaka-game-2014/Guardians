/**
 * @file DcharacterManager.h
 * @author 檀上
 */

/**
 * キャラクターの衝突判定やダメージ計算などを管理する
 */
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
	// 衝突しているか調べる
	bool HitCheck(std::vector<XFileAnimationMesh::BOX>,std::vector<XFileAnimationMesh::BOX>);
	// 描画
	virtual void Draw();
	// 移動フラグをセット
	CPlayer* GetPlayer();
	// キャラクターの移動速度を取得する
	D3DXVECTOR2 CCharacterManager::GetCharaSpeed();
	// キャラクたーの位置を取得する
	D3DXVECTOR3 GetCharaPosition();
	// HPを取得する
	CGameData::ENEMY_STATUS GetHP();
	// モーションが終了しているか調べる
	bool GetMotionEnd(int _motionID);
	// キャラクターを変更する
	void CharacterChange(int _time);
	// アルファ値をセットする
	void SetAlpha();
private:
	// プレイヤーのダメージを計算する
	void CalcPlayerDamage();
	// 敵のダメージを計算する
	void CalcEnemyDamage();
	// 円同士の衝突判定
	bool SphereCollision(XFileAnimationMesh::SPHERE _sphereA, XFileAnimationMesh::SPHERE _sphereB);
	// ボックス同士の衝突判定
	bool AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2);
	// 円とボックスの衝突判定
	bool SphereToBox(XFileAnimationMesh::SPHERE _sphere,XFileAnimationMesh::BOX _box);
	// レイとメッシュの衝突判定
	bool RayToMesh(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box);
	// レイとボックスの衝突判定
	bool RayToBox(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box);
	// 線分と線分の衝突判定
	bool ColSegments(XFileAnimationMesh::RAY_PARAM _ray1,XFileAnimationMesh::RAY_PARAM _ray2);

};
