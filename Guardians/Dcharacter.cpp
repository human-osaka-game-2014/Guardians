/**
 * @file Dcharacter.cpp
 * @brief 処理内容:
 * @author 檀上
 * @date 作成日: 11/6
 * @date 更新日: 11/6
 */

#include "stdafx.h"

const float CCharacter::RIGHT_WALL = 58.f;
const float CCharacter::LEFT_WALL  = -34.f;

const float CCharacter::LEFT_ANGLE  = 90;	// キャラクターの向き　左
const float CCharacter::RIGHT_ANGLE = -90;	// キャラクターの向き 右

float CCharacter::m_alpha = 1.0f;

/**
 * コンストラクタ(デバイスをセット)
 * @param _pDevice 描画デバイス
 * @param[in] _angle
 */
CCharacter::CCharacter(LPDIRECT3DDEVICE9 _pDevice,float _angle) : m_pDevice(_pDevice) , m_state(STATE_WAIT)
,m_curMotionID(0),m_speed(0.f,0.f) , m_isHit(false) , m_damage(0)
, m_scale(0.f,0.f,0.f) , m_step(STEP_MOVE) , m_move(0.f,0.f) , m_actionGauge(ACTION_GAUGE_MAX),m_box(0) , m_curEffect(0)
, m_time(0),m_invincible(false)
{
	
}

/**
 * デストラクタ
 */
CCharacter::~CCharacter()
{

}

/**
 * 衝突判定に使用する矩形の数を決める
 */
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
/**
 * アニメーション時間を進める
 * @param[in] _time 進める時間(基本的に1.0f/60.f)
 */
void CCharacter::UpdateAnimTime(float _time)
{
	// しゃがみ中とポーズ時はアニメーション時間を進めない
	if( CBattleScene::m_pause || m_motionStop ) return;
	// アニメーション経過時間
	m_time = m_model->AdvanceTime(_time);
}
/**
 * ボーンの位置を取得する
 * @param[in] _name ボーンの名前
 */
D3DXVECTOR3 CCharacter::GetBonePos(LPCTSTR _name)
{
	MYFRAME* m_frame;	// フレーム
	D3DXVECTOR3 position;	// ボーンの位置格納用
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );

	SetBonePos(&position,m_frame);

	return position;
}
/**
 * 矩形を更新
 * @param[in] _name ボーンの名前
 * @param[in] _ID	ボックスのindex
 */
void CCharacter::UpdateRect(LPCTSTR _name , int _ID )
{
	UpdateBox(GetBonePos(_name),&m_box[_ID]);	// 矩形の位置を更新
}
/**
 * ボーンの位置をセット
 * @param[out] _position ボーンの位置
 * @param[in] _pFrame
 */
D3DXMATRIX CCharacter::GetMatrix(LPCTSTR _name )
{
	MYFRAME* m_frame;	// フレーム
	D3DXVECTOR3 position;	// ボーンの位置格納用
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );
	return m_frame->CombinedTransformationMatrix;
}
/**
 * ボーンの位置をセット
 * @param[in] _position ボーンの位置
 * @param[in] _pFrame
 * @param[in] _radian
 */
void CCharacter::UpdateRect(D3DXVECTOR3 _position , int _ID)
{
	UpdateBox(_position,&m_box[_ID]);
	// 矩形の描画(デバッグ用)
	#ifdef _DEBUG
		DrawBox(m_box);
	#endif
}

/**
 * ボックス座標の更新
 * @param[in] _position 位置(x.y)
 * @param[in] _box ボックス
 * @param[in] _radian
 */
void CCharacter::UpdateBox(D3DXVECTOR3 _position , XFileAnimationMesh::BOX* _box)
{
	_box->min =  (_box->center + _position) - (_box->length / 2);
	_box->max = _box->length  + _box->min;

	_box->position = _position + _box->center;

}
/**
 * ボーンの位置をセット
 * @param[out] _position ボーンの位置
 * @param[in] _pFrame
 */
void CCharacter::SetBonePos(D3DXVECTOR3* _position , MYFRAME* _pFrame)
{
	_position->x = _pFrame->CombinedTransformationMatrix._41;
	_position->y = _pFrame->CombinedTransformationMatrix._42;
	_position->z = _pFrame->CombinedTransformationMatrix._43;
}

/**
 * 攻撃判定矩形の取得
 * @return ボックス配列
 */
std::vector<XFileAnimationMesh::BOX> CCharacter::GetHittingBox()
{
	return m_hitting_box;
}

/**
 * やられ判定矩形の取得
 * @return ボックス配列
 */
std::vector<XFileAnimationMesh::BOX> CCharacter::GetunHittingBox()
{
	return m_unhitting_box;
}
/**
 * キャラクターの状態を取得
 * @return レイ
 */
XFileAnimationMesh::RAY_PARAM CCharacter::GetRay()
{
	return m_ray;
}

/**
 * キャラクターの状態を取得
 * @return 状態
 */
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}

/**
 * キャラクターの移動速度を取得.
 * キャラクターの移動量からフィールドの移動量を求める時に使用
 * @return 移動速度
 */
D3DXVECTOR2 CCharacter::GetCharaSpeed()
{
	return m_move;
}
/**
 * キャラクターの移動量をセット
 * @return float ダメージ
 */
float CCharacter::GetDamage()
{
	m_HitCount++;
	// ヒット上限　もしくは　無敵状態ならダメージは0
	if( m_HitCount > 1 || m_invincible ){
		return 0;
	}
	return m_correctionValue;	// ダメージを取得
}
/**
 * キャラクターの移動量をセット
 * @param[in] _spd 移動量
 */
void CCharacter::SetCharaSpeed(int _spd)
{
	m_speed.x = _spd * 0.015f;
}

/**
 * 衝突判定用のフラグをセット
 * @param[in] _flag フラグ
 */
void CCharacter::SetHitFlag(bool _flag)
{
	m_isHit = _flag;
}

/**
 * モーションをリセットする
 * @param[in] _motionID モーションID
 */
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

/**
 * モーションが終了しているかチェックする
 * @param[in] _motionID モーション番号
 * @retval true モーション終了
 * @retval false モーション再生中
 */
bool CCharacter::CheckMotionEnd(int _motionID)
{
	if( m_animList[_motionID].endTime <= m_time )
		return true;
	
	return false;
}

/**
 * 状態を取得(戦闘開始演出中等の判定)
 * @return ステップ
 */
CCharacter::STEP CCharacter::GetStep()
{
	return m_step;
}

/**
 * ボックスの描画デバッグ用
 * @param[in] _box ボックス
 */
void CCharacter::DrawBox(std::vector<XFileAnimationMesh::BOX> _box)
{
#ifdef DEBUG
	for(unsigned i = 0; i < _box.size(); i++){
		D3DXMATRIX matTrans,matWorld,matScale;
		D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
		D3DXMatrixTranslation(&matTrans,_box[i].position.x ,_box[i].position.y,_box[i].position.z);
		D3DXMatrixIdentity(&matWorld);
		matWorld = matWorld * matScale * matTrans;
		m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
		// ボックスの表示
		m_pDevice->SetMaterial( _box[i].pMaterials );
		_box[i].pMesh->DrawSubset(0);

		m_pDevice->SetTexture( 0, NULL );
	}
#endif
}
/**
 * レイの描画
 * @param[in] _pos	　描画位置
 * @param[in] _rayDir レイのベクトル
 */
void CCharacter::DrawRay(D3DXVECTOR3 _pos,D3DXVECTOR3 _rayDir)
{
#ifdef DEBUG
	m_pDevice->SetVertexShader(NULL);
	m_pDevice->SetFVF(D3DFVF_XYZ);
	
	D3DXVECTOR3 vec[2]; // レイの開始地点と終了地点

	vec[0] = D3DXVECTOR3(0,0,0);
	vec[1] = _rayDir;

	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld,_pos.x,_pos.y,_pos.z);
	// レイの開始地点をセットする
	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//レイのマテリアル
	D3DMATERIAL9 mat;
	ZeroMemory(&mat,sizeof(mat));	

	mat.Diffuse.a = 255;
	mat.Diffuse.r = 255;
	mat.Diffuse.g = 255;
	mat.Diffuse.b = 255;
	mat.Ambient = mat.Diffuse;
	m_pDevice->SetMaterial( &mat );
	//レイのレンダリング
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vec, sizeof(D3DXVECTOR3));
#endif
}
