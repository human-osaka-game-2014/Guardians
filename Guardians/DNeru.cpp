#include "stdafx.h"

 float CNeru::m_charaHeight = 150.f;
// 消費MP

/*--------------------------------------------------------------

	コンストラクタ
	@param	LPDIRECT3DDEVICE9 描画デバイス
	@return なし

--------------------------------------------------------------*/
CNeru::CNeru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice) , m_teleportState(TPSTATE_WAIT) , m_moveValue(0,0,0) , m_isPlay(false)
{
	m_scale = D3DXVECTOR3(0.06f,0.06f,0.06f);

	m_charaHeight = (m_charaHeight * m_scale.y) / 2;
	
	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_2-1_Neru.X"),m_pDevice,m_scale);
	//m_maru = new CMaru(m_pDevice);

	// 使用する矩形を作成
	CreateBox();

	// モーションの開始時間と終了時間
	double Animation[MOTION_MAX_NUM][2] = {
	// StartTime　,EndTime,　ChancelFlag
		{0,59},			// 待機
		{60,114},			// 走り出し
		{115,169},			// 走り
		{170,219},		// 止まる
		{220,349},		// ジャンプ上昇(230-285上昇　285-300 300-320下降)
		{280,310},				// ジャンプ下降(230-285上昇　285-300 300-320下降)
		{350,359},			// しゃがむ
		{360,389},			// しゃがみ中
		{390,399},		// しゃがみ解除
		{400,430},		//9.	400-430	緊急回避
		{430,460},		//10.	430-460 通常攻撃（-444構え　445-450発射　451-460のモーション後15frameかけて状況に応じた待機時モーションへ移行　連撃時は5frameで440フレーム目のモーションに移行→以降通常時の流れへ）
		{430,460},		//11.	 通常攻撃連撃1：なし
		{430,460},		//12.	 通常攻撃連撃2：なし
		{465,495},		//13.	 465-495 上攻撃（-479構え　480-4985発射　486-495待機へ連撃時の処理は通常攻撃と同じ）
		{500,535},		//14.	 500-535 下攻撃　（510構え　510-520攻撃）
		{540,570},		//15.	 540-570 下攻撃（空中）（550構え　550-555発射　555-565のモーション後15frameかけて状況に応じた待機時モーションへ移行連撃時の処理は通常攻撃と同じ）
		{575, 625 },	// 16) 技1 氷壁　（605で発射）
		{625, 675 },	// 17) 技2 火炎弾　(655で発射)
		{675, 720 },	// 18) 技3 テレポ上(685-700でフェードアウト　700-715でフェードイン)							
		{725, 795 },	// 19) 技4 岩攻撃 (755で発射)
		{800, 845 },	// 20) 技4（空中） テレポ下 (810-825でフェードアウト　825-840でフェードイン)
		{845, 875 },	// 21) ダメージ喰らい
		{875, 990 },	// 22) 死亡
		{995, 1045},	// 23) スタン
		{1050, 1145 },	// 24) 固有モーション1（戦闘開始時用）
		{1145, 1265 },	// 25) 固有モーション2（勝利時）
	};

	SetEffectList();

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

	for( int i = 0; i < EFFECT_MAX_NUM; i++ ){
		m_efk[i] = NULL;
	}
}
/*--------------------------------------------------------------

	ボックスを生成
	@param なし
	@return なし

--------------------------------------------------------------*/
void CNeru::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// ボックスの生成
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(100.0f,100.0f,40.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	box.max    = D3DXVECTOR3(20.0f,150.0f,20.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}

/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CNeru::~CNeru()
{
	SAFE_DELETE(m_model);
	//SAFE_DELETE(m_sphere[0].pShereMaterials);
	for( unsigned i = 0; i < m_box.size();i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}

	for(int i = 0;i < EFFECT_MAX_NUM;i++){
		SAFE_DELETE( m_efk[i] );
	}
	//SAFE_DELETE(m_maru);
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CNeru::Draw()
{
	// モデルのα値をセット
	m_model->SetColor(m_alpha);

	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	
	m_model->Draw(m_position,rotation);

	//m_maru->SetStopMotion(m_motionStop);
	//m_maru->Draw();

	SetRect();

	ControlEffect();

	// ボディ(やられ判定)
	UpdateRect("pelvis",0);
	
	// しゃがみ中とポーズ時はアニメーション時間を進めない
	if( CBattleScene::m_pause || m_motionStop ) return;

	m_time = m_model->AdvanceTime(1.0f/60.f);
}
/*--------------------------------------------------------------

	エフェクトの制御
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CNeru::ControlEffect()
{
	static D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);

	float angle = 0; // エフェクト再生時のアングル保存用
	D3DXVECTOR3 position; // エフェクト再生時の位置

	switch( m_curEffect){
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_UPPER:		//13.	上攻撃
	case MOTION_AIR:			//15.	下攻撃（空中）
	case MOTION_SKILL2:		//17.	前＋技
		FireBall();
		break;
	case MOTION_LOWER:		//14.	下攻撃
		//ThunderWhip();
		break;
	case MOTION_SKILL:		//16.	技1
		IceWall();
		break;
	case MOTION_SKILL4:		//19.	下＋技
		//StoneImpact();
		break;
	case MOTION_SKILL3:		//18.	上＋技
	case MOTION_SKILLAIR:	//20.	下＋技（空中
		Teleport();
		break;
	}
	//// エフェクトの更新
	//m_effect[MAIN_EFK]->Control(m_moveValue,m_efkPos);
	//// sub(主に魔方陣)は移動しない
	//m_effect[SUB_EFK]->Control(D3DXVECTOR3(0.f,0.f,0.f),m_efkPos);

	//// エフェクトが終わっていたら
	//if( m_effect[MAIN_EFK]->checkEnd() ){
	//	//m_isPlay = false;
	//	m_effect[MAIN_EFK]->SetCharaHeight( (m_charaHeight * m_scale.y) / 2);
	//}
	// 技が当たっていたらエフェクト再生停止
	if( m_isHit ) {
		m_isPlay = false;
	}
}

void CNeru::FireBall()
{
	// エフェクト再生中
	if( m_efk[FIRE_BALL] != NULL ){
		m_efk[FIRE_BALL]->Run();
		UpdateRect( m_efk[FIRE_BALL]->GetPosition(),1);
		//通常攻撃
		m_hitting_box[0] = m_box[1];
		m_correctionValue = 1.0f;
	}
	// エフェクトの再生が終わっていたら
	if( (m_isPlay && !m_efk[FIRE_BALL]->GetExists()) || m_isHit ){
		SAFE_DELETE(m_efk[FIRE_BALL]);
		m_isPlay = false;
		m_curEffect = 0;
		UpdateRect( DUMMY,1);
		m_hitting_box[0] = m_box[1];
	}
}
/*--------------------------------------------------------------

	アニメーション変更
	@param	int キー情報
	@return なし

--------------------------------------------------------------*/
void CNeru::SetMotion(int _motionID)
{
	static double endTime = m_animList[MOTION_WAIT].endTime;

	// モーションを変更
	if(  m_model->ChangeMotion(_motionID) ){
		// 再生しているアニメーションを保存
		m_curMotionID = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;

		if( !m_isPlay ){
			PlayEffect();
		}
	}
	//m_maru->Move(m_position,_motionID , m_angle);

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
		m_state = STATE_PROJECTILE;
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
	if( m_isPlay ) m_state = STATE_PROJECTILE;
}
void CNeru::IceWall()
{
	// エフェクト再生中
	if( m_efk[ICE_WALL] != NULL ){
		m_efk[ICE_WALL]->Run();
		UpdateRect( m_efk[ICE_WALL]->GetPosition(),0);
	}
	// エフェクトの再生が終わっていたら
	if( m_isPlay && ! m_efk[ICE_WALL]->GetExists() ){
		SAFE_DELETE(m_efk[ICE_WALL]);
		m_isPlay = false;
		m_curEffect = 0;
	}
	//UpdateRect(m_position,2);	// 衝突判定用矩形の更新
}
void CNeru::Teleport()
{
	int frame = 5;
	static float add = 0;
	static float jumpSpeed = -0.06f;


	switch( m_teleportState ){
	case TPSTATE_WAIT:
				if( m_alpha <= 1.0f )	// モデルが透明なら
			m_alpha -= add;
				m_isPlay = false;

		if( m_curMotionID == MOTION_AIR || m_curMotionID == MOTION_SKILL3){
			m_efkPos = m_position; // エフェクトの出現位置を更新
			if( m_animList[m_curMotionID].startTime == m_time ){ // モーションが変わったフレームなら
				PlayEffect(10);									 // エフェクトの再生
				add = -((m_alpha / 2) / frame);					 // 増加α値を保存
				m_teleportState = TPSTATE_TELEPORT;
			}
		}
		break;

	case TPSTATE_TELEPORT:
		if( (int)m_animList[m_curMotionID].startTime + 10 == (int)m_time )
			m_teleportState = TPSTATE_FADE_OUT;
		break;

	case TPSTATE_FADE_OUT:
		if( m_alpha >= 1.0 / 2)
			m_alpha += add;	// モデルを透明に
		else{
			if( m_alpha == 1.0 / 2 && m_curEffect != MOTION_SKILL3){
				m_position.y += 7;
				m_teleportState = TPSTATE_AERIAL;
				ResetMotion(MOTION_JUMP_FALL); // ごり押し
			}
			// 上技ならキャラクターを空中へ
			if( m_curEffect == MOTION_SKILL3){
				m_position.y += 7;
				m_teleportState = TPSTATE_AERIAL;
				ResetMotion(MOTION_JUMP_FALL); // ごり押し
			}
		}
		break;
	case TPSTATE_AERIAL:
		// 空中にいる時
		if( m_teleportState == TPSTATE_AERIAL ){
			if( m_position.y >= INIT_HEIGHT_POSITION){
				jumpSpeed -= 0.01f;
				m_position.y += jumpSpeed;
				if( m_curMotionID != MOTION_JUMP_FALL ) ResetMotion(MOTION_JUMP_FALL); // ごり押し
			}else{
				// 着地したら待ち状態に
				m_teleportState = TPSTATE_WAIT;
				ResetMotion(MOTION_WAIT);
				jumpSpeed = 0;
			}
		}
		break;

	case TPSTATE_FALL:
		if( m_alpha <= 1.0f )	// モデルが透明なら
			m_alpha -= add;

		break;
	}

			// Teleport_01.efkをキャラ位置に再生＋15Frameかけてフェードイン
			// 発動直後からフェードインが済むまで（45frame間）無敵
}
void CNeru::StoneImpact()
{
	if( m_curMotionID == MOTION_SKILL4 ){
		m_efkPos = m_position;
		PlayEffect();
	}
}
void CNeru::ThunderWhip()
{
	//MYFRAME* m_frame;	// フレーム

	//if( m_curMotionID == MOTION_LOWER ){

	//	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"L_wrist" );
	//	SetBonePos(&m_efkPos,m_frame);

	//	m_effect[MAIN_EFK]->SetCharaHeight(0);
	//	PlayEffect();
	//}

	//if( m_curEffect != MOTION_LOWER ) return;
}


/*--------------------------------------------------------------

	エフェクトを再生
	@param	int 複数のエフェクトを出現させる場合フレームを指定
	@return なし

--------------------------------------------------------------*/
void CNeru::PlayEffect(int _frame)
{
	bool flag = false;

	// モーション変更時にエフェクトを変更
	switch( m_curMotionID ){
	case MOTION_ATTACK:		//10.	通常攻撃
	case MOTION_UPPER:		//13.	上攻撃
	case MOTION_AIR:			//15.	下攻撃（空中）
	case MOTION_SKILL2:		//17.	前＋技
	case MOTION_SKILL3:		//18.	上＋技
		m_efk[FIRE_BALL] = new CFireBallManager(m_pDevice);
		m_efk[FIRE_BALL]->Play(m_angle,D3DXVECTOR3(m_position.x,m_position.y + m_charaHeight,m_position.z));
		flag = true;
		break;
	case MOTION_LOWER:		//14.	下攻撃
		//ThunderWhip();
		break;
	case MOTION_SKILL:		//16.	技1
		m_efk[ICE_WALL] = new CIceWallManager(m_pDevice);
		m_efk[ICE_WALL]->Play(m_angle,D3DXVECTOR3(m_position.x,m_position.y + m_charaHeight,m_position.z));
		flag = true;
		break;
	case MOTION_SKILL4:		//19.	下＋技
		//StoneImpact();
		break;
	case MOTION_SKILLAIR:		//20.	下＋技（空中）
		Teleport();
		break;
	}
	if( flag ){ // エフェクト再生したフレーム
		m_curEffect = m_curMotionID;					// 再生しているモーションを保存
		m_isPlay = true;
		flag = false;
		
		m_efkAngle = m_angle;							// 再生時の向きを保存
		m_actionGauge -= 30;							// アクションゲージを減らす
	}
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
void CNeru::SetEffectList()
{

}