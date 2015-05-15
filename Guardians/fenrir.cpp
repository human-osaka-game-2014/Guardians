#include "stdafx.h"

/*--------------------------------------------------------------

コンストラクタ
@param	LPDIRECT3DDEVICE9 描画デバイス
@return なし

--------------------------------------------------------------*/
CFenrir::CFenrir(LPDIRECT3DDEVICE9 _pDevice) : CEnemy(_pDevice), m_speed(0.00f)
{
	//ステータス設定
	m_status.hp = m_status.maxHP = 1000;
	//DEF = 25;
	//actionGauge = 100;
	//actionGaugeRecover = 25;

	TimeCount = 0;

	m_model = new XFileAnimationMesh(_T("image\\xfile\\Enemy\\StageBoss2.X"), m_pDevice, D3DXVECTOR3(0.025f, 0.075f, 0.025f));

	// ボックスの生成
	CreateBox();

	// モーションの開始時間と終了時間
	double Animation[MOTION_MAX_NUM][2] = {
		{ 0, 100 },  // 00) 待機
		{ 100, 200 }, // 01) ひるみ
		{ 200, 295 }, // 02) 死亡
		{ 300, 345 }, // 03) ジャンプ溜め→跳び
		{ 345, 345 }, // 04) ジャンプ滞空（ここで一端固定
		{ 345, 400 }, // 05) ジャンプ着地
		{ 400, 460 }, // 06) 向き反転 (415-445で跳び上がりつつ180°回転　しっぽにダメージ判定)
		{ 465, 520 }, // 07) ジャンプ着地噛みつき
		{ 520, 580 }, // 08) 噛みつき (540-555で口に当たり判定)
		{ 580, 650 }, // 09) 火炎弾 (625で発射)
		{ 650, 690 }, // 10) しっぽ攻撃（675でエフェクト）
		{ 690, 730 }, // 11) 火炎放射前
		{ 730, 730 }, // 12) 火炎放射中
		{ 730, 770 }, // 13) 火炎放射後
		{ 770, 800 }, // 14) 遠吠え前
		{ 800, 800 }, // 15) 遠吠え中
		{ 800, 860 }, // 16) 遠吠え後
		{ 0, 100 }, // 16) 遠吠え後待機
		{ 860, 930 }, // 17) 体当たり前
		{ 930, 930 }, // 18) 体当たり中
		{ 930, 960 }, // 19) 体当たり後
	};

	m_animList.resize(MOTION_MAX_NUM);
	// 配列にモーション時間を格納
	for (int i = 0; i < MOTION_MAX_NUM; i++){
		m_animList[i].startTime = Animation[i][0];
		m_animList[i].endTime = Animation[i][1];
		m_animList[i].chancel = false;
		
	}
	m_animList[MOTION_WAIT].chancel = true;
	
	// アニメーションをセット
	m_model->SetAnimList(&m_animList);
	m_model->ChangeMotion(0);

	SetMotion(MOTION_WAIT);


	m_sidePos[0] = -11.f;
	m_sidePos[1] = 9.f;
}
/*--------------------------------------------------------------

デストラクタ



--------------------------------------------------------------*/
CFenrir::~CFenrir()
{
	SAFE_DELETE(m_model);
	//	SAFE_DELETE(m_sphere[0].pShereMaterials);
	for (unsigned i = 0; i < m_box.size(); i++)
		SAFE_DELETE(m_box[i].pMaterials)

}
/*--------------------------------------------------------------

制御
@param	なし
@return なし

--------------------------------------------------------------*/
void CFenrir::Control()
{
	static bool countFlag = false;
	static bool	interval = false;		//休憩時間
	static unsigned	actionFlag = 0;		//行動分岐用
	static DWORD MotionStart, MotionEnd;
	static int LoadCount;				//一時変数系
	srand((unsigned int)time(NULL));

	TimeCount++;

	// 死亡モーションが終わっていたらモーションを進めない
	if( m_curMotionID == MOTION_DEATH &&  m_animList[MOTION_DEATH].endTime <= m_time )
		m_motionStop = true;

	 // 特定のモーション終了時に休憩中でなければ
	if(!interval){
		if( CheckInterval() ){
			MotionStart = timeGetTime(); // インターバル中の時間を計測開始
			interval = true;
		}
	}

	// 敵のAI

	// 一定距離でPlayerを発見する
	if( fabsf(m_position.x - m_playerPos.x ) >= 25.f ){
		m_discovered = false; // Playerを見失った
		m_motionID = MOTION_WAIT; // 待機モーションに
	}
	else{
		m_discovered = true;	// プレイヤーを発見
	}

	// プレイヤーを発見して自分が待機モーション中なら行動分岐
	if ( m_discovered && m_curMotionID == MOTION_WAIT ){

		if ((m_position.x - m_playerPos.x) * m_angle > 0)			//プレイヤーが背後にいたら
			if (fabsf(m_position.x - m_playerPos.x) < 10.f){		//　近距離
				if (actionFlag == 2){							//　反転→尻尾→反転の時
					m_motionID = MOTION_TAIL;
					actionFlag = 1;
				}
				else if (!actionFlag && rand() % 10 < 4){		//　　尻尾使ってなかったら40％で使う
					m_motionID = MOTION_TAIL;
					actionFlag = 1;
				}
				else {											//　　それ以外は反転
					m_motionID = MOTION_TURN;
					actionFlag = 0;
				}
			}
			else m_motionID = MOTION_TURN;
		else {	//プレイヤーが前にいる時
			if ( rand() % 20 < 3){			//　行動値がそれなりにあったら15％で遠吠え
				m_motionID = MOTION_HOWL1;
			}
			// 近距離の時
			else if (fabsf(m_position.x - m_playerPos.x) < 10.f){
				if (rand() % 10 < 2){							//　　20％で反転→尻尾→反転を使用
					m_motionID = MOTION_TURN;
					actionFlag = 2;
				}
			//　中距離の時
			} else if (fabsf(m_position.x - m_playerPos.x) < 15.f){
				if (rand() % 10 < 4)							//　　　40％でファイアブレス　残りでちょっと待機
					m_motionID = MOTION_FIRE1;
				else if (rand() % 10 < 5)						//　　　50％で体当たり　残りでちょっと待機
					m_motionID = MOTION_ATTACK1;
			//　遠距離の時
			} else {								
				if ( rand() % 10 < 2)		//　　行動値がそれなりにあったら20％でタックル
					m_motionID = MOTION_ATTACK1;
				else
					m_motionID = MOTION_JUMP1;					//　　80％でジャンプ(更に50%で中距離)　残りで噛みつきジャンプ
			}
		}
	}
		
	switch(m_curMotionID){
	case MOTION_JUMP1:
	case MOTION_JUMP2:
	case MOTION_JUMP_BITE:
	case MOTION_JUMP3:
		Jump();
		break;
	case MOTION_TURN:
		Turn();
		break;
	case MOTION_ATTACK1:
	case MOTION_ATTACK2:
	case MOTION_ATTACK3:
		Attack();
	case MOTION_HOWL1:
	case MOTION_HOWL2:
	case MOTION_HOWL3:
		Howl();
		break;
	case MOTION_FIRE1:
	case MOTION_FIRE2:
	case MOTION_FIRE3:
		Fire();
		break;
	}
	

	// モーションとモーションの間は待機
	if(interval){
		m_HitCount = 0;
		m_motionID = MOTION_WAIT;
		MotionEnd = timeGetTime();
		if( (MotionEnd - MotionStart) /1000 >= 2 ){ // モーションとモーションの間は4秒待つ
			interval = false;
		}
	}

	SetMotion(m_motionID);

	// 右壁
	if( m_position.x >= CCharacter::RIGHT_WALL )
		m_position.x = CCharacter::RIGHT_WALL;
	// 左壁
	if( m_position.x <= CCharacter::LEFT_WALL ) 
		m_position.x = CCharacter::LEFT_WALL;
}
bool CFenrir::CheckInterval()
{
	// 特定のモーション後は待機時間を設ける
	switch(m_curMotionID){
	case MOTION_JUMP3:
	case MOTION_TURN:
	case MOTION_BITE:
	case MOTION_JUMP_BITE:
	case MOTION_FIRE3:
	case MOTION_HOWL3:
	case MOTION_FIREBALL:
	case MOTION_TAIL:
		if( m_time >= m_animList[m_curMotionID].endTime )
			return true;
		break;
	};
	return false;

}
/*--------------------------------------------------------------

描画
@param	なし
@return なし

--------------------------------------------------------------*/
void CFenrir::Draw()
{
	if (!m_motionStop) // モーションストップフラグが立っていない場合はモーション時間を進める
		m_time = m_model->AdvanceTime(1.0f / 60.f);

	D3DXMATRIX rotation;							// 回転
	D3DXMatrixRotationYawPitchRoll(&rotation, D3DXToRadian(m_angle), D3DXToRadian(-90), D3DXToRadian(0));

	m_model->Draw(m_position, rotation);

	SetRect();
	// ボディの矩形
	UpdateRect("BaseBone",0);

	//for(int i = 0; i < m_box.size(); i++){
	//	DrawBox(m_box[i]);
	//}
}
/*--------------------------------------------------------------

アニメーション変更
@param	int キー情報
@return なし

--------------------------------------------------------------*/
void CFenrir::SetMotion(int _motionID)
{
		// モーションを変更
	if(  m_model->ChangeMotion(_motionID) ){
		// 再生しているアニメーションを保存
		m_curMotionID = _motionID;
		// モーション時間をリセット
		m_time = m_animList[m_curMotionID].startTime;
	}

	if( m_curMotionID <= MOTION_DEATH )
		m_state = STATE_WAIT;
	else
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
float CFenrir::GetCharaSpeed()
{
	return m_speed;
}

int CFenrir::GetDamage()
{
	return 30;
}


void CFenrir::TailHammer(){
	m_curEffect = MOTION_TAIL;
	MYFRAME* m_frame;
	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "Tail_3");
	SetBonePos(&effectPos[0], m_frame);
}
void CFenrir::Attack()
{
	float m_move;
	if( m_curMotionID ==  MOTION_ATTACK1 ){
		m_move = 0.1f;
		if ( m_angle == LEFT_ANGLE )
			m_move = m_move * -1.f;

		m_position.x += m_move;

		if (m_time >= m_animList[MOTION_ATTACK1].endTime)
			m_motionID = MOTION_ATTACK3;
	}
	if( m_curMotionID == MOTION_ATTACK3 ){
		m_move = 1.2f;
		if ( m_angle == RIGHT_ANGLE )
			m_move = m_move * -1;

		m_position.x += m_move;

		if (m_time >= m_animList[MOTION_ATTACK3].endTime)
			m_motionID = MOTION_TURN;
		
	}
	m_hitting_box[0] = m_box[BODY];
	//if (!m_isPlay){
	//	m_curEffect = MOTION_ATTACK2;
	//	if (m_angle < 0) e_position = -0.7f; else e_position = 0.7f;
	//	MYFRAME* m_frame;
	//	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "TopJaw");
	//	SetBonePos(&effectPos[0], m_frame);
	//	effectPos[0].x += e_position * 4;
	//	m_isPlay = true;
	//}
	//else if (m_curMotionID == MOTION_ATTACK2){
	//	m_effectList[m_curEffect].move.x = 0.7f;
	//	MYFRAME* m_frame;
	//	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "TopJaw");
	//	SetBonePos(&effectPos[0], m_frame);
	//}
	//else {
	//	if (e_position > 0)	e_position -= 0.05f;
	//	else if (e_position < 0)	e_position += 0.05f;
	//}
	//m_position.x += e_position;
	//return;
}

/*--------------------------------------------------------------

ボックスを生成
@param なし
@return なし

--------------------------------------------------------------*/
void CFenrir::CreateBox()
{
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// スフィアの生成
	// 現在未使用
	//sphere.center = D3DXVECTOR3(0.f,0.f,0.f);
	//sphere.radius = 10.f;
	//m_sphere.push_back(sphere);
	//m_model->CreateSphere(&m_sphere[0]);
	//体
	box.max = D3DXVECTOR3(160.0f, 100.0f, 100.0f);
	box.min = D3DXVECTOR3(0.f, 0.f, 0.f);
	box.center = D3DXVECTOR3(0.f, 0.f, 0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//頭
	box.max = D3DXVECTOR3(75.0f, 65.0f, 80.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//尾
	box.max = D3DXVECTOR3(80.0f, 70.0f, 80.0f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	//エフェクト用
	box.max = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	box.length = box.max - box.min;
	for (int i = 0; i < EFFECT_MAX_NUM; i++)
		m_box.push_back(box);
	for (unsigned i = 0; i < m_box.size(); i++)
		m_model->CreateBox(&m_box[i]);

}

void CFenrir::BoxControl()
{
	//BOXの管理
	MYFRAME* m_frame;
	D3DXVECTOR3 position;
	// 体の矩形
	m_frame = (MYFRAME*)D3DXFrameFind(m_model->GetFrameRoot(), "Back");
	SetBonePos(&position, m_frame);
	position.y -= 2.f;
	UpdateRect(position, BODY);

}

void CFenrir::Jump()
{
	static float INIT_VELOCITY = 0.5f; // 初速

	static float VELOCITY = INIT_VELOCITY;
	// 加速度
	float ACCELERATE = 0.002f;
	
	// ジャンプ開始フレーム
	const int JUMP_START_FRAME = 335;

	switch(m_curMotionID){
	case MOTION_JUMP1:
		if( m_time >= JUMP_START_FRAME ){ // ジャンプ開始フレームになっていたら
			if (m_angle != RIGHT_ANGLE) m_position.x += 0.4f;
			else  m_position.x -= 0.4f;
			VELOCITY -= ACCELERATE; // jump速度を一定量－
			m_position.y += VELOCITY;  
		}
		if (m_time >= m_animList[m_curMotionID].endTime){ // ジャンプモーションが終わっていたら
			m_motionID = MOTION_JUMP2; // モーションを滞空へ
		}
		break;
	case MOTION_JUMP2:
		// ジャンプの最高点の時は加速度を0に
		VELOCITY = 0;
		if ( rand() % 10 < 5 ) {
			m_motionID = MOTION_JUMP_BITE;
		}
		else m_motionID = MOTION_JUMP3;
		break;
	case MOTION_JUMP3:
	case MOTION_JUMP_BITE:
		// 空中にいる時
		if (m_position.y > INIT_ENEMY_POSITION.y){
			VELOCITY -= ACCELERATE * 10; // 一定量マイナス
			m_position.y += VELOCITY;
			if (m_angle != RIGHT_ANGLE ) m_position.x += 0.3f;
			else  m_position.x -= 0.3f;
		}// 地面についていたら
		else
			m_position.y = INIT_ENEMY_POSITION.y;

		// モーションが終了していたら
		if (m_time >= m_animList[m_curMotionID].endTime){
			// 待機モーションに戻し、速度、positionを初期値へ
			m_motionID = MOTION_WAIT;
			VELOCITY = INIT_VELOCITY;
			m_position.y = INIT_ENEMY_POSITION.y;
		}
		break;
	}
	// 頭の矩形を更新
	UpdateRect("Head", HEAD);
	m_hitting_box[0] = m_box[HEAD];
}
void CFenrir::Turn()
{
	int TOTAL_FRAME = (int)(m_time - m_animList[MOTION_TURN].startTime);
	if (TOTAL_FRAME < 15){
		e_position = 0.45f;
	}
	else if (TOTAL_FRAME < 45){	//ジャンプ＆反転
		m_angle -= 6;
		m_position.y += e_position;
		e_position -= 0.03f;
	}
	else if (m_time >= m_animList[MOTION_TURN].endTime){
		//actionGauge -= 10;
		m_motionID = MOTION_WAIT;
		if (m_angle == -270) m_angle = 90;
		m_position.y = INIT_ENEMY_POSITION.y;
		//STR = 0;
	}
	//m_curMotionID == MOTION_ATTACK1;
}
void CFenrir::Tail()
{
	int LoadCount = (int)(m_time - m_animList[MOTION_TAIL].startTime);
	//STR = 40;
	//addState = 0;
	if (LoadCount == 25) {
		//actionGauge -= 15;
		TailHammer();
		//STR = 60;
		//addState = 1;
	}
	if (m_time >= m_animList[MOTION_TAIL].endTime){
		m_curMotionID = MOTION_WAIT;
		//STR = 0;
		//addState = 0;
	}
	UpdateRect("Tail_3",TAIL);
	m_hitting_box[0] = m_box[TAIL];

}
void CFenrir::Howl()
{
	if( m_curMotionID == MOTION_HOWL1 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_HOWL2;

	if( m_curMotionID == MOTION_HOWL2 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_HOWL3;

	if( m_curMotionID == MOTION_HOWL3 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_WAIT;

}
void CFenrir::Fire()
{
	if( m_curMotionID == MOTION_FIRE1 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_FIRE2;

	if( m_curMotionID == MOTION_FIRE2 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_FIRE3;

	if( m_curMotionID == MOTION_FIRE3 && m_time >= m_animList[m_curMotionID].endTime )
		m_motionID = MOTION_WAIT;

}
/*--------------------------------------------------------------

BaseBone
Breast
Back
Head
Tail_1~3

---------------------------------------------------------------*/
