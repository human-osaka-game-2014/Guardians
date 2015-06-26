/**
 * @file DAldfauth.cpp
 * @author 檀上
 */

#include "stdafx.h"

/**
 * コンストラクタ
 * @param _pDevice デバイスオブジェクト
 */
CAldfauth::CAldfauth(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	// モデルのスケール
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_1_Aldfauth.X"),m_pDevice,m_scale);

	m_efk = new CAldEffect(m_pDevice);

	// 使用する矩形を作成
	CreateBox();

		// モーションの開始時間と終了時間
	double Animation[MOTION_MAX_NUM][2] = {
	// StartTime　,EndTime
		{0, 69},// 00) 待機
		{70, 99},// 01) 走り出し
		{100, 149},	// 02) 走り
		{150, 179},	// 03) 止まる
		{190, 235},	// 04) ジャンプ(190	-235上昇　235-250 250-270下降（繰り返し表示） 290-299 着地)
		{235, 270},	// 05) ジャンプ着地(190-235上昇　235-250 250-270下降（繰り返し表示） 290-299 着地)
		{300, 310},	// 06) しゃがむ
		{310, 339},	// 07) しゃがみ中
		{340, 349},	// 08) しゃがみ解除
		{350, 380},	// 09) 緊急回避
		{380, 415},	// 10) 通常攻撃 (390-395-400でパンチ　400までにボタン入力で連撃)
		{420, 450},	// 11) 通常攻撃連撃1： (425-430-435でパンチ　440までにボタン入力で連撃)
		{455, 510},	// 12) 通常攻撃連撃2： (470-475-480でパンチ)
		{510, 550},	// 13) 上攻撃 (525-535でパンチ)
		{555, 585},	// 14) 下攻撃  (560-580で突進)
		{590, 640},	// 15) 下攻撃（空中）610で固定／体当たり　接地or衝突で続き再生　衝突時は625で行動可能（落下中モーションへ繋げる ）
		{640, 680},	// 16) 技1 　掌底打ち　655-660で発射
		{680, 710},	// 17) 技2 　突進パンチ　690-700で突進
		{710, 755},	// 18) 技3 　火炎アッパー　720-740で上昇＋アッパー　モーション終了時に落下モーションに繋げる
		{760, 815},	// 19) 技4 　岩攻撃　780-805で岩　終了時はしゃがみ状態
		{820, 855},	// 20) 技4（空中）　落下岩攻撃　 835で固定＋急降下　接地で続き再生 接地-850に岩　終了時はしゃがみ状態
		{860, 890},	// 21) ダメージ喰らい
		{890, 1000},	// 22) 死亡
		{1005, 1034},	// 23) スタン
		{1040, 1135},	// 24) 固有モーション1（戦闘開始時用）
		{1135, 1255},	// 25) 固有モーション2（勝利時）
	};

	m_animList.resize(MOTION_MAX_NUM);
	// 配列にモーション時間をセット
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		if( i == MOTION_SQUAT_START || i == MOTION_SQUAT || i == MOTION_WAIT || i == MOTION_START_RUN || i == MOTION_RUN )
			m_animList[i].chancel = true; // 特定のモーションはキャンセル可能
		else
			m_animList[i].chancel = false;
	}
	// アニメーション配列をセット
	m_model->SetAnimList(&m_animList);
	// 待機モーションをセット
	m_model->ChangeMotion( MOTION_WAIT );
	// ジャンプを開始するフレーム
	m_jumpStartFrame = 3;
}

/**
 * デストラクタ
 */
CAldfauth::~CAldfauth()
{
	SAFE_DELETE(m_model);
	SAFE_DELETE(m_efk);

	for(unsigned i = 0; i < m_box.size(); i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}

/**
 * 描画
 */
void CAldfauth::Draw()
{
	// モデルのα値をセット
	m_model->SetColor(m_alpha);
	// モデル向き
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	// モデルの描画
	m_model->Draw(m_position,rotation);
	
	// 矩形の描画
	DrawBox(m_box);

	UpdateAnimTime();
}
/**
 * エフェクトの描画
 */
void CAldfauth::DrawEffect()
{
	if( m_isHit ) m_efk->Stop(m_curMotionID);
	// エフェクトの制御
	m_efk->Draw();
}
/**
 * モーションを変更
 * @param _motionID モーション番号
 */
void CAldfauth::SetMotion(int _motionID)
{
	// モーションを変更
	if(  m_model->ChangeMotion(_motionID) ){
		// 再生しているアニメーションを保存
		m_curMotionID = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;

		m_efk->Create(GetBonePos("R_wrist"),m_curMotionID,m_angle);
	}

	// モーション毎に状態を変える
	switch( m_curMotionID )
	{
	case MOTION_WAIT:			//1.	待機
		m_state = STATE_WAIT;
		m_motionState = MSTATE_WAIT;
		break;
	case MOTION_START_RUN:			//2.	走り出し
	case MOTION_RUN:			//3.	走る
	case MOTION_STOP_RUN:			//4.	止まる
		m_state = STATE_RUN;
		m_motionState = MSTATE_WAIT;
		break;
	case MOTION_JUMP:			//5.	ジャンプ
	case MOTION_JUMP_FALL:
		m_state = STATE_JUMP;
		m_motionState = MSTATE_AERIAL;
		break;
	case MOTION_SQUAT_START:		//6.	しゃがむ
	case MOTION_SQUAT:		//7.	しゃがみ中
	case MOTION_STAND_UP:		//8.	しゃがみ解除
		m_state = STATE_SQUAT;
		m_motionState = MSTATE_SQUAT;
		break;
	case MOTION_AVOID:		//9.	緊急回避
		m_state = STATE_AVOID;
		m_motionState = MSTATE_AVOID;
		break;
	case MOTION_FLINCH:			//22.	ダメージ喰らい
	case MOTION_DEAD:			//23.	死亡
	case MOTION_STUN:			//24.	スタン
	case MOTION_APPEAL:		//25.	固有モーション1（戦闘開始時用）
	case MOTION_APPEAL2:		//26.	固有モーション2（勝利時）
		m_motionState = MSTATE_IN_MOTION;
		m_state = STATE_WAIT;
		break;
	default:
		m_state = STATE_ATTACK;
		m_motionState = MSTATE_IN_MOTION;
	}
	// 無敵状態ならStateを無敵に
	if( m_invincible ) 
		m_state = STATE_INVICIBLE;

	SetRect();

	ControlRect();

	m_efk->Control();
}
/**
 * 衝突判定矩形の制御
 */
void CAldfauth::ControlRect()
{
		// モーション毎に状態を変える
	switch( m_curMotionID )
	{
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_ATTACK2:	//11.	通常攻撃連撃1
	case MOTION_ATTACK3:	//12.	通常攻撃連撃2
		m_correctionValue = 1.f;
		UpdateRect("R_wrist",BOX_ATTACK);
		m_hitting_box[0] = m_box[BOX_ATTACK];
		break;
	case MOTION_SKILL:		//16.	技1
		m_correctionValue = 0.5f;
		UpdateRect( m_efk->GetPosition(m_curMotionID,(int)(m_animList[m_curMotionID].endTime - m_time)),BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_SKILL2:		//17.	前＋技
		m_correctionValue = 1.3f;
		UpdateRect("R_wrist",BOX_ATTACK);
		m_hitting_box[0] = m_box[BOX_ATTACK];
		break;
	case MOTION_UPPER:		//13.	上攻撃
		m_correctionValue = 1.3f;
		UpdateRect("R_wrist",BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_LOWER:		//14.	下攻撃
		m_correctionValue = 0.f;
		Rush();
		break;
	case MOTION_AIR:			//15.	下攻撃（空中）
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILL3:		//18.	上＋技
		m_correctionValue = 1.0f;
		UpdateRect("R_wrist",BOX_HAND_STRIKE);
		m_hitting_box[0] = m_box[BOX_HAND_STRIKE];
		break;
	case MOTION_SKILL4:		//19.	下＋技
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILLAIR:		//20.	下＋技（空中）
		m_correctionValue = 0.f;
	//case MOTION_SPECIAL:		//21.	必殺技
		m_state = STATE_ATTACK;
		m_motionState = MSTATE_IN_MOTION;
		break;
	}
	// ボディ矩形を常に更新(やられ判定)
	UpdateRect("pelvis",BOX_BODY);
}


/**
 * 突進
 */
void CAldfauth::Rush()
{
	static float MOVE_DISTANCE = 20.f;	// 移動距離
	static float MOVE_FRAME = 60;		// 移動時間
	static float ADD = MOVE_DISTANCE / MOVE_FRAME;	// 1fの移動量
	
	// 移動
	if( m_curMotionID == MOTION_LOWER && m_time - m_animList[MOTION_LOWER].startTime <= MOVE_FRAME){
		if( m_angle == LEFT_ANGLE ) m_move.x -= ADD;
		else m_move.x += ADD;
	}
}
/**
 * 衝突判定に使用するボックスを生成
 */
void CAldfauth::CreateBox()
{
	XFileAnimationMesh::BOX	box;
	// ボックスの生成
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(40.0f,20.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(70.0f,120.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}
/*-----------------------------------------------------------------

	R_elbow
	R_uarm

	R_wrist

-------------------------------------------------------------------*/
