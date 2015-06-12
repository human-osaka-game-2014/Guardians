/*--------------------------------------------------------------

	処理内容: キャラクターの管理
	作成者:檀上
	作成日: 11/20

	更新日: 12/18
		
		メモ
			現状boxのみで衝突判定を行う予定

	更新内容:
		衝突判定用関数の追加

		衝突を検知する関数を追加
		
	関数
		HitCheck
	変数　                


--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	コンストラクタ(デバイスをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス

--------------------------------------------------------------*/

CCharacterManager::CCharacterManager(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,MODELDATA* _chara) : m_pDevice(_pDevice),m_pGameData(_pGameData) , m_moveFlag(false) , m_hitWall(false) , isHit(false)
{	
	// モデルデータを保存
	m_pModel = _chara;
	m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
	// 戦闘開始時の演出の位置をセット
	if( m_activePlayer->GetStep() == CCharacter::STEP_FADE_IN )
		m_activePlayer->SetPosition(INIT_PLAYER_POSITION);
	// チェックポイント２以降は演出を挟まない
	else if( m_activePlayer->GetStep() == CCharacter::STEP_MOVE )
		m_activePlayer->SetPosition(INIT_PLAYER_POSITION);
	
	m_activePlayer->SetPosition( INIT_PLAYER_POSITION );

	m_activePlayer->SetCharaSpeed( m_pGameData->m_chara[ m_pGameData->m_turnNo[0] ].spd );
	// 待機モーションをセット
	m_activePlayer->SetPosition( INIT_PLAYER_POSITION );
	m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT);


	if( (m_pGameData->m_selectStageNum + 1) % 4 == 0 )
		m_activeEnemy = _chara->enemy[3];
	else 
		m_activeEnemy = _chara->enemy[0];
	m_activeEnemy->SetPosition( INIT_ENEMY_POSITION );

	//m_activeEnemy->SetPosition( D3DXVECTOR3(5.f,0.f,2.f) );
	m_activeEnemy->ResetMotion(CPlayer::MOTION_WAIT);

}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CCharacterManager::~CCharacterManager()
{

}
/*--------------------------------------------------------------

	制御
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CCharacterManager::Control()
{

	// プレイヤーの制御
	m_activePlayer->Control(); 

	// 敵の制御
	m_activeEnemy->SetPlayerPos( m_activePlayer->GetPosition() );	// プレイヤーの位置をセット
	m_activeEnemy->Control();	// 敵の制御

	// プレイヤーと敵の状態を取得
	m_playerState =  m_activePlayer->GetState();
	m_enemyState  =	 m_activeEnemy->GetState();

	// 両方のキャラクターが攻撃状態以外なら衝突判定を行わない
	if( m_enemyState < STATE_ATTACK && m_playerState < STATE_ATTACK ) return;

	//// Playerの攻撃判定
	// 敵の攻撃判定
	if ( m_playerState >= STATE_ATTACK ){
		// 敵のやられ判定とプレイヤーの攻撃判定をチェック
		if( m_pGameData->m_turnNo[m_pGameData->m_playerCharaNo] == 2 ) 
			// 戦っているキャラがミネルツァの時はレイとメッシュで判定を行う
			isHit = RayToBox(m_activePlayer->GetRay(),m_activeEnemy->GetunHittingBox());
		else 
			isHit = HitCheck( m_activePlayer->GetHittingBox(),m_activeEnemy->GetunHittingBox() );
		// ヒットしているかどうかをセットする
		m_activePlayer->SetHitFlag(isHit);
		// モーション毎のダメージ
		CalcPlayerDamage();
	}


	// 敵の攻撃判定
	if ( m_enemyState >= STATE_ATTACK ){
		isHit = HitCheck( m_activeEnemy->GetHittingBox(),m_activePlayer->GetunHittingBox() );

		m_activeEnemy->SetHitFlag(isHit);
	 
		CalcEnemyDamage();
	}
}
void CCharacterManager::CalcPlayerDamage()
{
	srand((unsigned)time(NULL));
	if( isHit ){

		m_activePlayer->SetHitFlag(isHit);

		int damage = 0; // ダメージ量
		// プレイヤーの攻撃力を取得
		int atk = m_pGameData->m_chara[m_pGameData->m_turnNo[0]].atk;
		//int def = m_activeEnemy->
		// 敵の防御力を取得
		int def = 0;
		// ダメージ計算( ( プレイヤー攻撃力 × 2 ) - 敵防御力 × 防御貫通 ) × 技補正 × ランダム値補正（小数点以下切捨て）
		
		damage = ( ( atk * 2 ) - def * m_activePlayer->Getflag() ) * m_activePlayer->GetDamage() * RAND_FLOAT(0.9f,1.1f);
		if( damage != 0 ) CBattleScene::comboCount++;
		// ボスのHPを減らす
		m_pGameData->m_pDamage.damage += damage;
		isHit = false;
	}
	
	if( m_pGameData->m_win == true ){
		m_activeEnemy->ResetMotion( CEnemy::MOTION_DEATH );
		m_activePlayer->ResetMotion( CPlayer::MOTION_APPEAL2 );
	}

}
void CCharacterManager::CalcEnemyDamage()
{
	if( isHit ){
		int atk = m_activeEnemy->GetDamage();
		int def = 0;// 防御補正値
		int damage = 0;

		//( 敵技攻撃力 - 防御技補正 ) × 2 × (120 - プレイヤー防御力) / 100 × ランダム値補正（小数点以下切捨て）
		//damage = ( atk - def ) * 2 * (120 - m_pGameData->m_chara[m_pGameData->m_turnNo[0]].def ) / 100 * RAND_FLOAT(0.9,1.1);
	
		// 受けたダメージを加算
		m_pGameData->m_pDamage.damageTaken += atk;
		isHit = false;

		// atkが0でない時(ダメージを受けたとき)
		if( atk ){
			m_activePlayer->ResetMotion( CPlayer::MOTION_FLINCH ); // ひるみモーションへ
		}
	}

	// HPが0になったら
	if( m_pGameData->m_chara[m_pGameData->m_turnNo[0]].hp <= m_pGameData->m_pDamage.damageTaken )
		m_pGameData->m_death = true;

	if( m_pGameData->m_death == true ) {
		m_activePlayer->ResetMotion( CPlayer::MOTION_DEAD );	// プレイヤーを死亡	モーションへ
	}
}
CGameData::ENEMY_STATUS CCharacterManager::GetHP()
{
	return m_activeEnemy->GetStatus();
}
/*--------------------------------------------------------------

	制御
	@param	std::vector<XFileAnimationMesh::BOX> 攻撃判定
	@param  std::vector<XFileAnimationMesh::BOX> やられ判定
	@return bool true : 当たっている
				 false : 当たっていない

--------------------------------------------------------------*/
bool CCharacterManager::HitCheck(std::vector<XFileAnimationMesh::BOX> _hitting_box,std::vector<XFileAnimationMesh::BOX> _unhitting_box)
{
	// プレイヤーのやられ判定と敵の攻撃判定をチェック
	//_hitting_box = m_activeEnemy->GetBox();
	//_unhitting_box = m_activePlayer->GetBox();

	for(unsigned i = 0; i < _unhitting_box.size();i++){
		for(unsigned j = 0; j < _hitting_box.size();j++){
			// 一度でもヒットしていればループを抜ける
			if( AABBtoAABB( _hitting_box[j],_unhitting_box[i]) ){
				return true;
			}
		}
	}
	// 当たっていない
	return false;
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CCharacterManager::Draw()
{
	m_activeEnemy->Draw();

	m_activePlayer->Draw();


}
/*--------------------------------------------------------------

	円同士の衝突判定
	@param	SPHERE スフィア
	@param	SPHERE スフィア
	@return true  : 衝突している 
			false : 衝突していない

--------------------------------------------------------------*/
bool CCharacterManager::SphereCollision(XFileAnimationMesh::SPHERE _pSphereA, XFileAnimationMesh::SPHERE _pSphereB)
{
	D3DXVECTOR3 dmy;
	if(D3DXVec3LengthSq( D3DXVec3Subtract(&dmy,&_pSphereA.position,&_pSphereB.position) ) <= (_pSphereA.radius+_pSphereB.radius)*(_pSphereA.radius+_pSphereB.radius))
	{
        return true;    //衝突している
    }
	return false;       //衝突していない
}
/*--------------------------------------------------------------

	ボックス同士の当たり判定
	@param	BOX 　　ボックス
	@param	BOX　　 ボックス
	@return true  : 衝突している 
			false : 衝突していない

--------------------------------------------------------------*/
bool CCharacterManager::AABBtoAABB(XFileAnimationMesh::BOX _box1,XFileAnimationMesh::BOX _box2)
{ 
	if( _box1.min.x < _box2.max.x && _box2.min.x < _box1.max.x && _box1.min.y < _box2.max.y && _box2.min.y < _box1.max.y)
	{
		return true;
	}
	return false;
}
/*--------------------------------------------------------------

	円とボックスの衝突判定
	@param	SPHERE スフィア
	@param	BOX   ボックス
	@return true  : 衝突している 
			false : 衝突していない

--------------------------------------------------------------*/
bool CCharacterManager::SphereToBox(XFileAnimationMesh::SPHERE _pSphere,XFileAnimationMesh::BOX _box)
{
	// 上の円の中心点から矩形の１番近い座標
	float x, y;
	// １番近いx座標を求める
	if ( _pSphere.position.x < _box.min.x )
		x = _box.min.x;
	else if ( _pSphere.position.x > _box.max.x )
		x = _box.max.x;
	else
		x = _pSphere.position.x;
 
	// １番近いy座標を求める
	if ( _pSphere.position.y < _box.min.y )
		y = _box.min.y;
	else if ( _pSphere.position.y > _box.max.y )
		y = _box.max.y;
	else
		y = _pSphere.position.y;
	// x,yの位置から円の距離を求める
	float a = abs( _pSphere.position.x - x );
    float b = abs( _pSphere.position.y - y );
 
    float c = sqrt((a * a) + (b * b));
	// 求めた距離が円の半径より小さいなら
	if ( c < _pSphere.radius){
		return true; // 衝突
	}
	return false;
}
bool CCharacterManager::RayToBox(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box)
{
	// 四角形の4つの辺を保存する
	XFileAnimationMesh::RAY_PARAM EnemyRay[4];
	// 受け取った矩形の数分for文を回す
	for(unsigned i = 0; i < _box.size(); i++){

		// 左下を始点とした辺
		// 縦
		EnemyRay[0].position  = EnemyRay[1].position = D3DXVECTOR3(_box[i].min.x,_box[i].min.y,_box[i].min.z);
		EnemyRay[0].length = D3DXVECTOR3(0,_box[i].length.y,_box[i].min.z);
		// 横
		EnemyRay[1].length = D3DXVECTOR3(_box[i].length.x,0,_box[i].min.z);
		
		// 右上
		// 縦
		EnemyRay[2].position = EnemyRay[3].position =  D3DXVECTOR3(_box[i].max.x,_box[i].max.y,_box[i].max.z);
		EnemyRay[2].length = D3DXVECTOR3(0,_box[i].length.y,_box[i].min.z);
		// 横
		EnemyRay[3].length = D3DXVECTOR3(_box[i].length.x,0,_box[i].min.z);

		bool isHit = false;
		// 各辺とレイが交差していないか調べる
		for(int i = 0; i < 4; i++){
			isHit = ColSegments(_ray,EnemyRay[i]);

			if( isHit )
				return true;

		}
	}
	return false;
}
// 線分の衝突
bool CCharacterManager::ColSegments(XFileAnimationMesh::RAY_PARAM _ray1,XFileAnimationMesh::RAY_PARAM _ray2)
{
	CVector v;
	D3DXVECTOR3 vector = _ray2.position - _ray1.position;
	float CrossProduct = v.D3DXVecCross( &_ray1.length,&_ray2.length );
	if ( CrossProduct == 0.0f ) {
      // 平行状態
      return false;
   }

   float Crs_v_v1 = v.D3DXVecCross( &vector, &_ray1.length );
   float Crs_v_v2 = v.D3DXVecCross( &vector, &_ray2.length );

   float t1 = Crs_v_v2	/ CrossProduct;
   float t2 = Crs_v_v1 / CrossProduct;

   const float eps = 0.00001f;
   if ( t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1 ) {
      // 交差していない
      return false;
   }

   return true;
}

bool CCharacterManager::RayToMesh(XFileAnimationMesh::RAY_PARAM _ray,std::vector<XFileAnimationMesh::BOX> _box)
{
	BOOL isHit = false;
	DWORD index,pCountOfHits;
	float p,v,d;
    LPD3DXBUFFER *ppAllHits = NULL;

	// 受け取ったboxのメッシュの数だけfor文を回す
	for(unsigned i = 0; i < _box.size(); i++){
		// ローカル座標系に変換
		//D3DXVECTOR3 length =  _ray.position + _ray.length;
		D3DXMATRIX matTrans, matWorld, invWorld, invRotation,matScale;
		//  拡大（縮小）行列を作成する
		D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
		//D3DXMatrixIdentity(&meshRotate);
		D3DXMatrixTranslation(&matTrans,_box[i].position.x, _box[i].position.y, _box[i].position.z);
		matWorld = matScale * matTrans;
		// 逆行列を求める
		D3DXMatrixInverse(&invWorld, 0, &matWorld);
		//D3DXMatrixInverse(&invRotation, 0, &meshRotate);

		D3DXVECTOR3 invRayPos,invRayDir;
		D3DXVec3TransformCoord(&invRayPos, &_ray.position, &invWorld);
		
		D3DXVec3TransformCoord(&invRayDir,&_ray.length,&invWorld);

		// ローカル座標に変換して衝突判定を行う
		D3DXIntersect( _box[i].pMesh,&invRayPos,&invRayDir,&isHit,&index,&p,&v,&d,ppAllHits,&pCountOfHits);
		if( isHit ){
			return true;
		}
	}
	// 当たっていない
	return false;
}
void CCharacterManager::setMoveFlag(bool _flag)
{
	m_moveFlag = _flag;
}
bool CCharacterManager::GetMoveFlag()
{
	return m_moveFlag;
}
bool CCharacterManager::GetHitWall()
{
	return m_hitWall;
}
void CCharacterManager::SetPosition(D3DXVECTOR2 _position)
{
	m_fieldPosition = _position;
}

CPlayer* CCharacterManager::GetPlayer()
{
	return m_activePlayer;
}
D3DXVECTOR2 CCharacterManager::GetCharaSpeed()
{
	return m_activePlayer->GetCharaSpeed();
}
D3DXVECTOR3 CCharacterManager::GetCharaPosition()
{
	return m_activePlayer->GetPosition();
}



/*-------------------------------------------------------------------------

	モーションが終了しているか調べる
	@param motionID
	@return true  終了
			false 終了していない

	バトルシーンからリザルトシーンへの遷移タイミングを調べる時に必要

----------------------------------------------------------------------*/
bool CCharacterManager::GetMotionEnd(int _motionID)
{
	return m_activePlayer->CheckMotionEnd(_motionID);
}
/*-------------------------------------------------------------------------------------------------
	

	キャラクター変更時の制御(モーションを入れ替える・キャラクターの移動速度をセットする・モデルを半透明に)
	@param	_time 経過時間

----------------------------------------------------------------------------------------------------*/
void CCharacterManager::CharacterChange(int _time)
{
	// モデルは半透明
	float MAX_ALPHA = 0.5f;
	const int ERASE_FRAME = 10;
	float addAlpha = MAX_ALPHA / ERASE_FRAME;

	m_activePlayer->SetCharaSpeed( 0 ); // キャラクターの移動速度を0に

	if( _time <= ERASE_FRAME )
		m_activePlayer->addAlpha(-addAlpha);
	else if ( _time >= CBattleScene::CHANGE_LIMIT ){
		// モデルデータを先頭のキャラへ入れ替える
		m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
		m_activePlayer->SetCharaSpeed( m_pGameData->m_chara[ m_pGameData->m_playerCharaNo ].spd ); // キャラクターの移動速度をセット
		m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT); // 待機モーションをセット
	}else{
		// モデルデータを先頭のキャラへ入れ替える
		m_activePlayer = m_pModel->player[m_pGameData->m_playerCharaNo];
		m_activePlayer->ResetMotion(CPlayer::MOTION_WAIT); // 待機モーションをセット
	}
}
/*--------------------------------------

	モデルのアルファ値を変更する
	@param  なし
	@return なし

---------------------------------------*/
void CCharacterManager::SetAlpha()
{
	m_activePlayer->addAlpha(1.0f);
}