#include "stdafx.h"

/*--------------------------------------------------------------

	コンストラクタ
	@param	LPDIRECT3DDEVICE9 描画デバイス
	@return なし

--------------------------------------------------------------*/
CMushroom::CMushroom(LPDIRECT3DDEVICE9 _pDevice) : CEnemy(_pDevice),m_speed(0.00f)
{
	m_model = new XFileAnimationMesh(_T("image\\xfile\\Enemy\\Boss1_PoisonusMushroom.X"),m_pDevice,D3DXVECTOR3(0.07f,0.07f,0.07f));
	
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;

	// ボックスの生成
	box.max    = D3DXVECTOR3(130.0f,130.0f,200.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,30.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(20.0f,140.0f,70.0f);
	box.center = D3DXVECTOR3(0.f,0.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	box.max    = D3DXVECTOR3(130.0f,130.0f,200.0f);
	box.center = D3DXVECTOR3(0.f,0.f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);	

	for( unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
		// モーションの開始時間と終了時間
	int Animation[MOTION_MAX_NUM][2] = { 
		{0,0},		// 待機
		{80,129},   //ひるみ
		{130,209},  //死亡
		{0,79},	    // 待機アクション（十秒間何も行動しなかった時の行動／スロー再生
		{210,249},  // 噛みつき
		{250,329},	//石つぶて攻撃
		{330,379},	//毒粉（330-339→340-369（スロー再生繰り返し）→370-379)
		{380,439},	//はたく（左）
		{440,499},	//はたく（右）
	};

	m_animList.resize(MOTION_MAX_NUM);
	// 配列にモーション時間を格納
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = false;
	}
	m_animList[MOTION_WAIT].chancel = true;
	m_animList[MOTION_WAIT2].chancel = false;
	//m_animList[2].chancel = true;
	//m_animList[5].chancel = true;
	//m_animList[6].chancel = true;
	// アニメーションをセット
	m_model->SetAnimList(&m_animList);
	m_model->ChangeMotion(0);

	SetMotion(MOTION_WAIT);

	m_status.hp = m_status.maxHP =  90;

}
/*--------------------------------------------------------------

	デストラクタ



--------------------------------------------------------------*/
CMushroom::~CMushroom()
{
	SAFE_DELETE(m_model);
//	SAFE_DELETE(m_sphere[0].pShereMaterials);
	for(unsigned i = 0; i < m_box.size();i++)
	SAFE_DELETE(m_box[i].pMaterials)
}
/*--------------------------------------------------------------

	制御
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CMushroom::Control()
{
	static bool countFlag = false;
	static bool	interval = false;
	static DWORD MotionStart,MotionEnd;

	srand((unsigned int)time(NULL));

	// 死亡モーションが終わっていたらモーションを進めない
	if( m_curMotionID == MOTION_DEATH &&  m_animList[MOTION_DEATH].endTime <= m_time )
		m_motionStop = true;

	// 敵のAI
	//SetMotion(MOTION_WAIT);
	if( m_curMotionID > MOTION_WAIT2 && m_time >= m_animList[m_curMotionID].endTime ){
		if(!interval){
			MotionStart = timeGetTime();
			interval = true;
		}
	}
	if( m_curMotionID == MOTION_WAIT2 && m_time >= m_animList[MOTION_WAIT2].endTime){
		m_animList[MOTION_WAIT2].chancel = true;
		m_model->SetAnimList(&m_animList);
		m_curMotionID = MOTION_WAIT;
		SetMotion(m_curMotionID);
		m_animList[MOTION_WAIT2].chancel = false;
		//m_model->SetAnimList(&m_animList);
	}

	if( fabsf(m_position.x - m_playerPos.x ) >= 7.f ){
		m_discovered = false; // Playerを見失った
		if (!countFlag){
			countFlag = true;
			m_curTime = timeGetTime();
		}
		m_endTime = timeGetTime();
		if( (m_endTime - m_curTime) / 1000 >= 10){ //　EnemyとPlayerの距離が一番遠い状態で10秒経過したら待機
			m_motionID = MOTION_WAIT2;
			m_curTime = timeGetTime();
		}
		else m_motionID = MOTION_WAIT;
	}
	else{
		m_discovered = true;	// プレイヤーを発見
	}
	// プレイヤーを発見している状態なら攻撃モーション
	if(m_discovered){
		if( fabsf(m_position.x - m_playerPos.x ) <= 6.f ){ // 敵との距離が中距離？の場合(噛み付き)
			m_motionID = MOTION_BITE;
		}
		if( fabsf(m_position.x - m_playerPos.x ) <= 4.f ){ // 敵との距離が近距離の場合(はたく攻撃 L or R)
			m_motionID = rand()%2+7;
		}


	}
	// モーションとモーションの間は待機
	if(interval){
		m_HitCount = 0;
		m_motionID = MOTION_WAIT;
		MotionEnd = timeGetTime();
		if( (MotionEnd - MotionStart) /1000 >= 4 ){ // モーションとモーションの間は4秒待つ
			interval = false;
		}
	}
	SetMotion(m_motionID);
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CMushroom::Draw()
{
	UpdateAnimTime();
	
	D3DXMATRIX rotation;							// 回転
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(-90), D3DXToRadian(-90), D3DXToRadian(0));
	m_model->Draw( m_position,rotation);

	// 判定に使用する矩形の数を決める
	SetRect();
	// ボディの矩形
	UpdateRect("Body",0);
	// 手の矩形
	 //右手のモーション時
	if( m_curMotionID == MOTION_R_WHISK ){
		m_hitting_box[0] = m_box[1];
		UpdateRect("L_Arm4",1);
	}//左手のモーション時
	else if( m_curMotionID == MOTION_L_WHISK ){ 
		m_hitting_box[0] = m_box[1];
		UpdateRect("R_Arm4",1);
	}
	// 噛み付きモーション
	else if( m_curMotionID == MOTION_BITE ){
		m_hitting_box[0] = m_box[2];
		//m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"HeadCenter" );

	}

	DrawBox(m_box);
	
}
/*--------------------------------------------------------------

	アニメーション変更
	@param	int キー情報
	@return なし

--------------------------------------------------------------*/
void CMushroom::SetMotion(int _motionID)
{
		// モーションを変更
	if(  m_model->ChangeMotion(_motionID) ){
		// 再生しているアニメーションを保存
		m_curMotionID = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID <= MOTION_WAIT2 )
		m_state = STATE_WAIT;
	if( m_curMotionID >= MOTION_BITE) 
		m_state = STATE_ATTACK;
	
	if( m_state == STATE_ATTACK && m_HitCount == 0 ){
		m_correctionValue = 20;
	}else{
		m_correctionValue = 0;
	}
}
/*--------------------------------------------------------------

	キャラの移動速度を返す
	@param	なし
	@return 移動速度
	
--------------------------------------------------------------*/
float CMushroom::GetCharaSpeed()
{
	return m_speed;
}

/*--------------------------------------------------------------

	BasBone
	Body
	Head
	HeadCenter

	L_Arm1~4
	R



---------------------------------------------------------------*/
