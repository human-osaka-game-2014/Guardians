/*--------------------------------------------------------------

	処理内容:アルドファウトの制御
	作成者:檀上
	更新日:
	更新内容:
	
	関数　

	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

/*--------------------------------------------------------------

	コンストラクタ

--------------------------------------------------------------*/
CMinertza::CMinertza(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice)
{
	// モデルのスケール
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	//m_charaHeight = (m_charaHeight * m_scale.y) / 2;
	
	m_model = new XFileAnimationMesh(_T("image\\xfile\\player\\PC_3_minertza.X"),m_pDevice,m_scale);

	m_weapon = new CMinertzaWeapon(m_pDevice);
	// 使用する矩形を作成
	CreateBox();

		// モーションの開始時間と終了時間
	double Animation[MOTION_MAX_NUM][2] = {
	//{ StartTime,  EndTime,
		{0, 79},		// 00) 待機
		{80, 109},		// 01) 走り出し
		{110, 149},	// 02) 走り
		{150, 200},	// 03) 止まる
		{200, 265},	// 04) ジャンプ(210-265上昇　265-280 280-300下降（繰り返し表示） 320-329 着地)
		{265, 349},	// 05) ジャンプ着地(230-285上昇　285-300 300-320下降（繰り返し表示） 340-349 着地)
		{330, 339},	// 06) しゃがむ
		{340, 369},	// 07) しゃがみ中
		{370, 380},	// 08) しゃがみ解除
		{380, 410},	// 09) 緊急回避 
		{410, 465},	// 10) 通常攻撃：420-430斬り 450までに攻撃ボタン入力で連撃１へ（445-450間に連撃２モーションへ繋げる）
		{470, 515},	// 11) 通常攻撃連撃1：475-485斬り　500までに攻撃入力で連撃２へ（500に連撃２モーションへ繋げる）
		{520, 580},	// 12) 通常攻撃連撃2：545-55斬り
		{580, 630},	// 13) 上攻撃＋ジャンプ：jump_Speedに通常ジャンプ時の3分の2（空中での発動時は半分）の値を加算（590-600,605-615の二回斬り判定）
		{635, 675},	// 14) 下攻撃  645-655斬り
		{680, 735},	// 15) 下攻撃（空中）690で固定　700で接地　モーション終了時にしゃがみ判定に 690-710まで斬り
		{740, 760},// 16) 技1　バリア　750で固定 　
		{760, 800},// 17) 技2 　振り下ろし 775-785斬り
		{800, 855},// 18) 技3 　上昇＋衝撃波 820-835に上昇
		{860, 930},// 19) 技4　槍　880-910発動   
		{935, 960},// 20) 技4（空中） 前面槍バリア（ダメージ＋攻撃状態ならダメージ上乗せ） 940-960　判定
		{965, 995},// 21) ダメージ喰らい
		{955, 1135},	// 22) 死亡  
		{1140, 1189},	// 23) スタン
		{1195, 1290},	// 24) 固有モーション1（戦闘開始時用）
		{1290, 1410},	// 25) 固有モーション2（勝利時）
		//{1260, , },	// 26) 必殺技
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
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CMinertza::~CMinertza()
{
	SAFE_DELETE(m_model);
	SAFE_DELETE(m_weapon);


	for(unsigned i = 0; i < m_box.size(); i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CMinertza::Draw()
{
	// モデルのα値をセット
	m_model->SetColor(m_alpha);
	// モデル向き
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	// モデルの描画の
	m_model->Draw(m_position,rotation);

	m_weapon->Draw(D3DXVECTOR3(m_ray.position.x,m_ray.position.y + -200.f,m_ray.position.z),m_matWeapon,m_alpha); // 武器の描画

	D3DXVECTOR3 rayStart,rayDir,pos1,pos2;

	// レイを描画する
	DrawRay(m_ray.position,m_ray.length);


	// 矩形の描画
	for(unsigned i = 0; i < m_box.size(); i++)
		DrawBox(m_box[i]);
	// アニメーション時間の更新
	UpdateAnimTime();
}
/*--------------------------------------------------------------

	モーションを変更
	@param int	モーション番号
	@return なし

--------------------------------------------------------------*/
void CMinertza::SetMotion(int _motionID)
{
	// モーションを変更
	if(  m_model->ChangeMotion(_motionID) ){
		// 再生しているアニメーションを保存
		m_curMotionID = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;

		if( !m_isPlay ){
			PlayEffect(1);
		}
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
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_ATTACK2:		//11.	通常攻撃連撃1
	case MOTION_ATTACK3:		//12.	通常攻撃連撃2
	case MOTION_UPPER:		//13.	上攻撃
	case MOTION_LOWER:		//14.	下攻撃
	case MOTION_AIR:			//15.	下攻撃（空中）
	case MOTION_SKILL:		//16.	技1
	case MOTION_SKILL2:		//17.	前＋技
	case MOTION_SKILL3:		//18.	上＋技
	case MOTION_SKILL4:		//19.	下＋技
	case MOTION_SKILLAIR:		//20.	下＋技（空中）
	//case MOTION_SPECIAL:		//21.	必殺技
		m_state = STATE_ATTACK;
		m_motionState = MSTATE_IN_MOTION;
		break;
	case MOTION_FLINCH:			//22.	ダメージ喰らい
	case MOTION_DEAD:			//23.	死亡
	case MOTION_STUN:			//24.	スタン
	case MOTION_APPEAL:		//25.	固有モーション1（戦闘開始時用）
	case MOTION_APPEAL2:		//26.	固有モーション2（勝利時）
		m_motionState = MSTATE_IN_MOTION;
		m_state = STATE_WAIT;
		break;
	}
	// 無敵状態ならStateを無敵に
	if( m_invincible ) 
		m_state = STATE_INVICIBLE;

	SetRect();
	// エフェクトの制御
	ControlEffect();
	ControlRect();
}
/*--------------------------------------------------------------

	衝突判定矩形の制御
	@param なし
	@return なし

--------------------------------------------------------------*/
void CMinertza::ControlRect()
{
	m_matWeapon = GetMatrix("GripPosition"); // GripPositionのMatrixを取得
	D3DXVECTOR3 pos1,pos2;
	// 2点のボーンの位置から剣のベクトルを求める
	pos1 = GetBonePos("R_p1");
	pos2 = GetBonePos("R_i1");
	// レイの長さを保存
	m_ray.length = pos2 - pos1;
	D3DXVec3Normalize(&m_ray.length,&m_ray.length);
	m_ray.length = m_ray.length * 10;
	// レイの開始地点を保存
	m_ray.position = GetBonePos("R_wrist");
	
		// モーション毎に状態を変える
	switch( m_curMotionID )
	{
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_ATTACK2:	//11.	通常攻撃連撃1
	case MOTION_ATTACK3:	//12.	通常攻撃連撃2
		m_correctionValue = 1.f;
		break;
	case MOTION_SKILL:		//16.	技1
		m_correctionValue = 1.2f;
		break;
	case MOTION_SKILL2:		//17.	前＋技
		m_correctionValue = 1.3f;
		break;
	case MOTION_UPPER:		//13.	上攻撃
		m_correctionValue = 0.f;
		break;
	case MOTION_LOWER:		//14.	下攻撃
		m_correctionValue = 1.0f;
		break;
	case MOTION_AIR:		//15.	下攻撃（空中）
		m_correctionValue = 0.f;
		break;
	case MOTION_SKILL3:		//18.	上＋技
		m_correctionValue = 1.0f;
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
	UpdateRect("Back",0);
}
/*--------------------------------------------------------------

	エフェクトの制御
	@param なし
	@return なし

--------------------------------------------------------------*/
void CMinertza::ControlEffect()
{
	switch( m_curEffect){
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_UPPER:		//13.	上攻撃
	case MOTION_AIR:			//15.	下攻撃（空中）
	case MOTION_SKILL2:		//17.	前＋技
			
		break;
	case MOTION_LOWER:		//14.	下攻撃
		
		break;
	case MOTION_SKILL:		//16.	技1
		
		break;
	case MOTION_SKILL4:		//19.	下＋技
		break;
	case MOTION_SKILL3:		//18.	上＋技
	case MOTION_SKILLAIR:	//20.	下＋技（空中
		
		break;
	}
	//if( m_isHit ) {
	//for(int i = 0; i < EFFECT_MAX_NUM;i++)
	//		m_effect[i]->StopEffect();
	//	m_isPlay = false;
	//}
}
/*--------------------------------------------------------------

	衝突判定に使用するボックスを生成
	@param なし
	@return なし

--------------------------------------------------------------*/
void CMinertza::CreateBox()
{
	XFileAnimationMesh::BOX		box;
	// ボックスの生成
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(40.0f,50.0f,20.0f);
	box.center = D3DXVECTOR3(0.f,80.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(100.0f,20.0f,20.0f);
	box.center = D3DXVECTOR3(50.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}
/*-----------------------------------------------------------------

	Breast
	Back

	R_wrist
	GripPosition
-------------------------------------------------------------------*/



// ミネルツァ武器クラス
CMinertzaWeapon::CMinertzaWeapon(LPDIRECT3DDEVICE9 _pDevice)
{
	m_model = new C3DModel(_T("image\\xfile\\Player\\ken.X"),_pDevice);

	m_model->SetAngle(D3DXVECTOR3(0,0,0));
}
CMinertzaWeapon::~CMinertzaWeapon()
{
	SAFE_DELETE(m_model);
}
void CMinertzaWeapon::Draw(D3DXVECTOR3 _position,D3DXMATRIX _mat,float _alpha)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	m_model->SetScale(D3DXVECTOR3(50,50,50));

	if( _alpha == 1.0 )
		m_model->Draw(_position,_mat);

}
void CMinertzaWeapon::GetMeshSize(D3DXVECTOR3* _min,D3DXVECTOR3* _max)
{
	m_model->GetMeshSize(_min,_max);
}