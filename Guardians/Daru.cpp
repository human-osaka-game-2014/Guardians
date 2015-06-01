/**
 * @file Daru.cpp
 */

#include  "stdafx.h"
/**
 * コンストラクタ
 * @param _pDevice 描画デバイス
 */
CAru::CAru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	m_scale = D3DXVECTOR3(0.01f,0.02f,0.01f);
	m_model = new XFileAnimationMesh(_T("image\\neru\\PC_2-1_Neru.X"),m_pDevice,m_scale);
	
	XFileAnimationMesh::BOX		box;

	// ボックスの生成
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(20.0f,20.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	m_model->CreateBox(&m_box[0]);
	m_model->CreateBox(&m_box[1]);
	m_time = 0;

	// モーションの開始時間と終了時間
	int Animation[MOTION_MAX_NUM][3] = {
	// StartTime　,EndTime,　ChancelFlag
		{0,59,true},			// 待機
		{60,114,true},			// 走り出し
		{115,169,true},			// 走り
		{170,219,false},		// 止まる
		{220,349,false},		// ジャンプ上昇(230-285上昇　285-300 300-320下降)
//		{340,349},				// ジャンプ下降(230-285上昇　285-300 300-320下降)
		{350,359,true},			// しゃがむ
		{360,389,true},			// しゃがみ中
		{390,399,false},		// しゃがみ解除
		{400,430,false},		//9.	400-430	緊急回避
		{430,460,false},		//10.	430-460 通常攻撃（-444構え　445-450発射　451-460のモーション後15frameかけて状況に応じた待機時モーションへ移行　連撃時は5frameで440フレーム目のモーションに移行→以降通常時の流れへ）
		{430,460,false},		//11.	 通常攻撃連撃1：なし
		{430,460,false},		//12.	 通常攻撃連撃2：なし
		{465,495,false},		//13.	 465-495 上攻撃（-479構え　480-4985発射　486-495待機へ連撃時の処理は通常攻撃と同じ）
		{500,535,false},		//14.	 500-535 下攻撃　（510構え　510-520攻撃）
		{540,570,false},		//15.	 540-570 下攻撃（空中）（550構え　550-555発射　555-565のモーション後15frameかけて状況に応じた待機時モーションへ移行連撃時の処理は通常攻撃と同じ）

	};
	m_animList.resize(MOTION_MAX_NUM);
	// 配列にモーション時間を格納
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = Animation[i][2];
	}
	// アニメーション配列をセット
	m_model->SetAnimList(&m_animList);
	// 待機モーションをセット
	m_model->ChangeMotion( MOTION_WAIT );

	effect = new CEffect(m_position , m_pDevice);
}
void CAru::Load()
{

}

/**
 * デストラクタ
 */
CAru::~CAru()
{
	SAFE_DELETE(m_model);
	//SAFE_DELETE(m_sphere[0].pShereMaterials);
	SAFE_DELETE(m_box[0].pMaterials);
	SAFE_DELETE(effect);
}

/**
 * 描画
 */
void CAru::Draw()
{
	//effect->Create(L"Effect\\WolfHead.efk",m_position,D3DXVECTOR3(1,1,1));

	//// しゃがみ中とポーズ時はアニメーション時間を進めない
	////if( m_state != MOTION_SQUAT2
	//if(!CBattleScene::m_pause)
	//	m_time = m_model->AdvanceTime(1.0f/60.f);
	//// 回転
	//D3DXMATRIX rotation;							
	//D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(-90 + m_angle), D3DXToRadian(-90), D3DXToRadian(-90));
	//
	//m_model->Draw(m_position,rotation);

	//MYFRAME* m_frame;	// フレーム
	//D3DXVECTOR3 position;	// ボーンの位置格納用
	//// 攻撃状態なら矩形をボーンに付随させる
	//if( m_state == STATE_ATTACK ){
	//	// 衝突判定用矩形の描画
	//	if( (m_animList[m_curMotionID].startTime + 5) < m_time ){ // 技発生から10F経過していたら衝突判定
	//		m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"L_wrist" );
	//		SetBonePos(&position,m_frame);
	//		UpdateBox(position,&m_box[1]);
	//		//DrawBox(m_box[1]);
	//		
	//		/*SetBonePos(&position,m_frame);
	//		UpdateSphere( position , &m_sphere[0]);
	//		DrawSphere(m_sphere[0]);*/
	//	}
	//}

	//m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"pelvis" );
	//SetBonePos(&position,m_frame);
	//UpdateBox(position,&m_box[0]);
	////DrawBox(m_box[0]);
	////effect->Play();
	//effect->Control(D3DXVECTOR3(0.f,-0.1f,0.f),m_position);

}

/**
 * アニメーション変更
 * @param[in] _motionID キー情報
 */
void CAru::SetMotion(int _motionID)
{
	static double endTime = m_animList[MOTION_WAIT].endTime;

	// 再生しているアニメーションを格納
	//m_curMotionID = m_model->ChangeMotion(_motionID);

	if( m_curMotionID == MOTION_WAIT ) m_state = STATE_WAIT;
	if( m_curMotionID > MOTION_WAIT && m_curMotionID <= MOTION_RUN3 ) m_state = STATE_RUN;
	if( m_curMotionID == MOTION_JUMP ) m_state = STATE_JUMP;
	if( m_curMotionID == MOTION_SQUAT_START ) m_state = STATE_SQUAT;
	if( m_curMotionID == MOTION_SQUAT ) m_state = STATE_SQUAT2;
	if( m_curMotionID >= MOTION_ATTACK ) m_state = STATE_ATTACK;

	// ヒット時のダメージ量( 基本的には1段ヒット)
	if( m_state == STATE_ATTACK && m_HitCount == 0 ){
		m_damage = 30;
	}else{
		m_damage = 0;
	}
}

/**
 * キャラの移動速度を返す
 * @return 移動速度
 */
float CAru::GetCharaSpeed()
{
	return m_speed.x;
}
/*-----------------------------------------------------------------
	
	ネル　ボーン
	右手　R_wrist
	左手  L_wrist

	胸　chest
	腹　back
	腰　pelvis

	足(つま先)
	右　L_toe(mirrored)
	左　L_toe
------------------------------------------------------------------*/
