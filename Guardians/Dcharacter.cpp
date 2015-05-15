/*--------------------------------------------------------------

	処理内容:
	作成者:檀上
	作成日: 11/6
	更新日: 11/6

	更新内容:
	関数　

	変数　

--------------------------------------------------------------*/
#include "stdafx.h"

const float CCharacter::RIGHT_WALL = 58.f;
const float CCharacter::LEFT_WALL  = -34.f;

const float CCharacter::LEFT_ANGLE  = 90;	// キャラクターの向き　左
const float CCharacter::RIGHT_ANGLE = -90;	// キャラクターの向き 右

float CCharacter::m_alpha = 1.0f;

/*--------------------------------------------------------------

	コンストラクタ(デバイスをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス

--------------------------------------------------------------*/
CCharacter::CCharacter(LPDIRECT3DDEVICE9 _pDevice,float _angle) : m_pDevice(_pDevice) , m_state(STATE_WAIT) , m_angle(_angle) 
,m_curMotionID(0),m_speed(0.f,0.f) , m_isHit(false) , m_damage(0)
, m_scale(0.f,0.f,0.f) , m_step(STEP_MOVE) , m_move(0.f,0.f) , m_actionGauge(ACTION_GAUGE_MAX),m_box(0) , m_curEffect(0)
, m_time(0),m_takeDamage(0),m_invincible(false),m_endMotion(false)
{
	
}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CCharacter::~CCharacter()
{

}
D3DXVECTOR3 CCharacter::GetBonePos(LPCTSTR _name)
{
	MYFRAME* m_frame;	// フレーム
	D3DXVECTOR3 position;	// ボーンの位置格納用
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );

	SetBonePos(&position,m_frame);

	return position;
}
void CCharacter::UpdateRect(LPCTSTR _name , int _ID )
{
	UpdateBox(GetBonePos(_name),&m_box[_ID]);	// 矩形の位置を更新
}

D3DXMATRIX CCharacter::GetMatrix(LPCTSTR _name )
{
	MYFRAME* m_frame;	// フレーム
	D3DXVECTOR3 position;	// ボーンの位置格納用
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );
	return m_frame->CombinedTransformationMatrix;
}
void CCharacter::UpdateRect(D3DXVECTOR3 _position , int _ID,float _radian)
{
	UpdateBox(_position,&m_box[_ID],_radian);
	// 矩形の描画(デバッグ用)
	#ifdef _DEBUG
		DrawBox(m_box[_ID]);
	#endif
}
/*--------------------------------------------------------------

	スフィア座標の更新
	@param D3DXVECTOR3					位置(x.y)
	@param XFileAnimationMesh::SPHERE	スフィア
	@return なし

--------------------------------------------------------------*/
void CCharacter::UpdateSphere(D3DXVECTOR3 _position,XFileAnimationMesh::SPHERE* _sphere)
{
	// 判定用座標の更新
	_sphere->position = _sphere->center + _position;

	D3DXMATRIX matTrans,matWorld,matScale;
	D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
	D3DXMatrixTranslation(&matTrans, _position.x + _sphere->center.x ,_position.y + _sphere->center.y , _position.z + _sphere->center.z);
	D3DXMatrixIdentity(&matWorld);	matWorld = matWorld * matScale * matTrans;
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

}
/*--------------------------------------------------------------

	衝突判定に使用する矩形の数を決める
	@param なし
	@return なし

--------------------------------------------------------------*/
void CCharacter::SetRect()
{
	// キャラクターの行動によって判定する矩形を変える
	// 矩形情報格納用配列は個数が違う場合のみResizeする

	// キャラクターが攻撃状態以外ならやられ判定はボディのみ
	if( m_state < STATE_ATTACK ) {
		if( m_unhitting_box.size() != 1 ) m_unhitting_box.resize(1);
	}
	// 攻撃状態(飛び道具ではない場合)
	else if( m_state == STATE_ATTACK ){
		if( m_hitting_box.size() != 1 ) m_hitting_box.resize(1); // 攻撃判定は1つ
		if( m_unhitting_box.size() != 2 ) m_unhitting_box.resize(2); // やられ判定は二つ
	}

	// 攻撃状態(飛び道具を使用する場合)
	if( m_state == STATE_PROJECTILE ){
		if( m_hitting_box.size() != 1 ) m_hitting_box.resize(1); // 攻撃判定は一つ(飛び道具)
		if( m_unhitting_box.size() != 1 ) m_unhitting_box.resize(1); // やられ判定は一つ
	}
	// やられ判定は常に更新
	m_unhitting_box[0] = m_box[0];
}
/*--------------------------------------------------------------

	スフィアの描画デバッグ用
	@param D3DXVECTOR3					位置(x.y)
	@return なし

--------------------------------------------------------------*/
void CCharacter::DrawSphere(XFileAnimationMesh::SPHERE _sphere)
{
	//スフィアの表示
	m_pDevice->SetMaterial( _sphere.pShereMaterials );
	_sphere.pShereMesh->DrawSubset(0);
}
/*--------------------------------------------------------------

	ボックス座標の更新
	@param D3DXVECTOR3					位置(x.y)
	@param XFileAnimationMesh::BOX		ボックス
	@return なし

--------------------------------------------------------------*/
void CCharacter::UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box,float _radian)
{
	float deg = D3DXToDegree(_radian);
	_box->min =  (_box->center + _position) - (_box->length / 2);
	float x1 = _box->min.x;
	float y1 = _box->min.y;
	_box->min.x = (x1) * cos(-deg) - (y1) * sin(-deg);
	_box->min.y = (x1) * sin(-deg) + (y1) * cos(-deg);

	_box->max = _box->length  + _box->min;
	
	_box->position = _position + _box->center;
}
/*--------------------------------------------------------------

	ボックスの描画デバッグ用
	@param XFileAnimationMesh::BOX		ボックス
	@return なし

--------------------------------------------------------------*/
void CCharacter::DrawBox(XFileAnimationMesh::BOX _box)
{
	D3DXMATRIX matTrans,matWorld,matScale;
	D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
	D3DXMatrixTranslation(&matTrans,_box.position.x ,_box.position.y,_box.position.z);
	D3DXMatrixIdentity(&matWorld);
	matWorld = matWorld * matScale * matTrans;
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// ボックスの表示
	m_pDevice->SetMaterial( _box.pMaterials );
	_box.pMesh->DrawSubset(0);

	m_pDevice->SetTexture( 0, NULL );
}
/*--------------------------------------------------------------

	ボーンの位置をセット
	@param LPDIRECT3DDEVICE9
	@param MYFRAME				

--------------------------------------------------------------*/
void CCharacter::SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame)
{
	_position->x = _pFrame->CombinedTransformationMatrix._41;
	_position->y = _pFrame->CombinedTransformationMatrix._42;
	_position->z = _pFrame->CombinedTransformationMatrix._43;
}
/*--------------------------------------------------------------

	攻撃判定矩形の取得
	@param なし
	@return ボックス配列

--------------------------------------------------------------*/
std::vector<XFileAnimationMesh::BOX> CCharacter::GetHittingBox()
{
	return m_hitting_box;
}
/*--------------------------------------------------------------

	やられ判定矩形の取得
	@param なし
	@return ボックス配列

--------------------------------------------------------------*/
std::vector<XFileAnimationMesh::BOX> CCharacter::GetunHittingBox()
{
	return m_unhitting_box;
}
///*--------------------------------------------------------------
//
//	スフィアの取得
//	@param なし
//	@return スフィア配列
//
//--------------------------------------------------------------*/
//std::vector<XFileAnimationMesh::SPHERE> CCharacter::GetSphere()
//{
//	return m_sphere;
//}
/*--------------------------------------------------------------

	キャラクターの状態を取得
	@param  なし
	@return 状態

--------------------------------------------------------------*/
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}
/*--------------------------------------------------------------

	キャラクターの移動速度を取得
	@param 　	なし
	@return		移動速度

--------------------------------------------------------------*/
D3DXVECTOR2 CCharacter::GetCharaSpeed()
{
	return m_move;
}
/*--------------------------------------------------------------

	キャラクターの移動量をセット(Enemyの座標維持に使用)
	@param float	移動量
	@return			なし

--------------------------------------------------------------*/
void CCharacter::SetCharaSpeed(int _spd)
{
	m_speed.x = _spd * 0.015f;
}
/*--------------------------------------------------------------

	衝突判定用のフラグをセット
	@param bool フラグ
	@return		なし

--------------------------------------------------------------*/
void CCharacter::SetHitFlag(bool _flag)
{
	m_isHit = _flag;
}
/*--------------------------------------------------------------

	被ダメージ自のフラグをセット
	@param		なし
	@return		なし

--------------------------------------------------------------*/
void CCharacter::SetTakeDamageFlg()
{
	m_takeDamage = true;
}
///*--------------------------------------------------------------
//
//	描画位置をセットする
//	@param	D3DXVECTOR3 位置
//	@return なし
//
//--------------------------------------------------------------*/
//void CCharacter::SetPosition(D3DXVECTOR3 _position)
//{
//	m_position = _position;
//}

float CCharacter::GetDamage()
{
	m_HitCount++;
	// ヒット上限　もしくは　無敵状態ならダメージは0
	if( m_HitCount > 1 || m_invincible ){
		return 0;
	}
	return m_correctionValue;	// ダメージを取得
}
/*--------------------------------------------------------------

	モーションをリセットする
	@param	int モーションID
	@return		なし

--------------------------------------------------------------*/
void CCharacter::ResetMotion(int _motionID)
{
	// キャンセル不可のモーションは一時的にキャンセル可能にして
	// モーション変更
	if(!m_animList[m_curMotionID].chancel && m_curMotionID != _motionID ) {
		m_animList[m_curMotionID].chancel = true;
		m_model->SetAnimList(&m_animList);
		m_model->ChangeMotion(_motionID);
		m_animList[m_curMotionID].chancel = false;
		// 現在のモーションを保存
		m_curMotionID  = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;
		m_model->SetAnimList(&m_animList);
	}
	else
		if( m_curMotionID != _motionID ){
			//m_curMotionID = m_model->ChangeMotion(_motionID);
			if(  m_model->ChangeMotion(_motionID) ){
				m_curMotionID = _motionID;
				// モーション時間をリセット
				m_time = m_animList[m_curMotionID].startTime;
			}
		}
	m_motionStop = false;
}
/*--------------------------------------------------------------

	モーションが終了しているかチェックする
	@param  モーション番号
	@return true　: モーション終了
			false : モーション再生中

--------------------------------------------------------------*/
bool CCharacter::CheckMotionEnd(int _motionID)
{
	if( m_animList[_motionID].endTime <= m_time )
		return true;
	
	return false;
}
/*--------------------------------------------------------------

	アニメーション時間を進める
	@param	float 進める時間(基本的に1.0f/60.f)
	@return なし

--------------------------------------------------------------*/
void CCharacter::UpdateAnimTime(float _time)
{
	// しゃがみ中とポーズ時はアニメーション時間を進めない
	if( CBattleScene::m_pause || m_motionStop ) return;
	// アニメーション経過時間
	m_time = m_model->AdvanceTime(_time);
}
/*--------------------------------------------------------------

	状態を取得(戦闘開始演出中等の判定)
	@param	なし
	@return CCharacter ステップ

--------------------------------------------------------------*/
CCharacter::STEP CCharacter::GetStep()
{
	return m_step;
}
bool CCharacter::GetMotionEnd()
{
	return m_endMotion;
}

