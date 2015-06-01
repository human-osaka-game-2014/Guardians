/**
 * @file DMaru.cpp
 */

#include "stdafx.h"
/**
 * コンストラクタ
 * @param _pDevice 描画デバイス
 * @return なし
 */
CMaru::CMaru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice) , m_teleportState(TPSTATE_WAIT) , m_alpha(1.0f)
{
	m_motionStop = false;

	m_scale = D3DXVECTOR3(0.015f,0.03f,0.015f);

	m_model = new XFileAnimationMesh(_T("image\\xfile\\Player\\PC_2-2_Maru.X"),m_pDevice,m_scale);


	m_position = D3DXVECTOR3(-5.f,-0.5f,0.f);

	// 使用する矩形を作成
	CreateBox();

	m_time = 0;

	// モーションの開始時間と終了時間
	double Animation[MOTION_MAX_NUM][3] = {
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
		{575, 625,false },	// 16) 技1 氷壁　（605で発射）
		{625, 675,false },	// 17) 技2 火炎弾　(655で発射)
		{675, 720,false },	// 18) 技3 テレポ上(685-700でフェードアウト　700-715でフェードイン)							
		{725, 795,false },	// 19) 技4 岩攻撃 (755で発射)
		{800, 845,false },	// 20) 技4（空中） テレポ下 (810-825でフェードアウト　825-840でフェードイン)
		{845, 875,false },	// 21) ダメージ喰らい
		{875, 990,false },	// 22) 死亡
		{995, 1045,false },	// 23) スタン
		{1050, 1145,false },	// 24) 固有モーション1（戦闘開始時用）
		{1145, 1265,false },	// 25) 固有モーション2（勝利時）
	};

	m_animList.resize(MOTION_MAX_NUM);
	// 配列にモーション時間をセット
	for(int i = 0; i < MOTION_MAX_NUM;i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = Animation[i][2];
	}
	// アニメーション配列をセット
	m_model->SetAnimList(&m_animList);
	// 待機モーションをセット
	m_model->ChangeMotion( MOTION_WAIT );	
}
void CMaru::SetStopMotion(bool _flag)
{
	m_motionStop = _flag;
}

/**
 * ボックスを生成
 */
void CMaru::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// ボックスの生成
	box.max    = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.0f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);

	for(unsigned i = 0; i < m_box.size();i++)
		m_model->CreateBox(&m_box[i]);
	
}

/**
 * デストラクタ
 */
CMaru::~CMaru()
{
	SAFE_DELETE(m_model);
	//SAFE_DELETE(m_sphere[0].pShereMaterials);
	for( unsigned i = 0; i < m_box.size();i++){
		SAFE_DELETE(m_box[i].pMaterials);
	}
}

/**
 * 描画
 */
void CMaru::Draw()
{
	// 回転
	D3DXMATRIX rotation;							
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(RIGHT_ANGLE + m_angle), D3DXToRadian(RIGHT_ANGLE), D3DXToRadian(RIGHT_ANGLE));
	
	m_model->Draw(m_position,rotation);

	//SetRect();
	// ボディ(やられ判定)
	UpdateRect("pelvis",0);
	
	UpdateAnimTime();
}

void CMaru::Move( D3DXVECTOR3 _position , int _motionID ,int _angle)
{
	m_neruPos = _position;
	// モーションを変更
	SetMotion( _motionID );

	// ネルとの間隔
	static int SPACE = 1;
	static float moveSpeed = 0.06f;

	if( m_motionStop ) return;

	if( _angle == LEFT_ANGLE ){
		if( m_position.x  <= _position.x + SPACE )
			m_position.x += moveSpeed;
		else 
			m_position.x = _position.x + SPACE;
		m_angle = LEFT_ANGLE;
	}else{
		if( m_position.x  >= _position.x - SPACE )
			m_position.x -= moveSpeed;
		else 
			m_position.x = _position.x - SPACE;

		m_angle = RIGHT_ANGLE;
	}

	// プレイヤーの座標を変更
	//m_position.x += m_move.x;

	// 右壁
	if( m_position.x <= -10.f ) m_position.x = -10.f;
	// 左壁
	if( m_position.x >= 8.f ) m_position.x = 8.f;
	// 描画位置をセット
	SetPosition(D3DXVECTOR3(m_position.x,m_position.y,m_position.z));

}

/**
 * アニメーション変更
 * @param _motionID キー情報
 */
void CMaru::SetMotion(int _motionID)
{
	static double endTime = m_animList[MOTION_WAIT].endTime;

	// 再生しているアニメーションを保存
	//m_curMotionID = m_model->ChangeMotion(_motionID);
	if(  m_model->ChangeMotion(_motionID) ){
		m_curMotionID = _motionID;
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID == MOTION_WAIT ) m_state = STATE_WAIT;
	else if( m_curMotionID > MOTION_WAIT && m_curMotionID <= MOTION_STOP_RUN ) m_state = STATE_RUN;
	else if( m_curMotionID == MOTION_AVOID ) m_state = STATE_AVOID;
	else if( m_curMotionID == MOTION_JUMP ) m_state = STATE_JUMP;
	else if( m_curMotionID == MOTION_SQUAT_START ) m_state = STATE_SQUAT;
	else if( m_curMotionID == MOTION_SQUAT ) m_state = STATE_SQUAT2;
	else if( m_curMotionID >= MOTION_ATTACK ) m_state = STATE_ATTACK;

}

void CMaru::UpdateRect(LPCTSTR _name , int _ID )
{
	MYFRAME* m_frame;	// フレーム
	D3DXVECTOR3 position;	// ボーンの位置格納用
	m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),_name );
	SetBonePos(&position,m_frame);
	UpdateBox(position,&m_box[_ID]);
	DrawBox(m_box[_ID]);
}

void CMaru::UpdateRect(D3DXVECTOR3 _position , int _ID )
{
	UpdateBox(_position,&m_box[_ID]);
	DrawBox(m_box[_ID]);
}

void CMaru::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
