//12/18 行動の関数分け

#include "stdafx.h"

// 静的なメンバー変数の実体宣言
const float CPlayer::INIT_VELOCITY = 0.40f;	// ジャンプ初速度

const float CPlayer::INIT_HEIGHT_POSITION = -0.5f;

D3DXVECTOR3 CPlayer::m_position = INIT_PLAYER_POSITION;

float CPlayer::m_angle = RIGHT_ANGLE;
//float CPlayer::m_alpha = 1.0f; // モデルのアルファ値

/**
 *
 * コンストラクタ
 * @param _pDevice 
 *
 */
CPlayer::CPlayer(LPDIRECT3DDEVICE9 _pDevice) : CCharacter(_pDevice,RIGHT_ANGLE) , m_jumpMove(0.f, -1.f),m_jumpFlag(false),m_isPlay(false)
{
	CScene::m_keyStateOn = 0;
	m_motionID = MOTION_WAIT;
}
/**
 *
 * デストラクタ
 *
 */
CPlayer::~CPlayer()
{
	
}
/**
 *
 * 制御
 *
 */
void CPlayer::Control()
{
	// 戦闘開始演出中は移動移動しない
	if( m_step != STEP_MOVE ) return;
	// 待機モーション再生中は状態を待機に
	if( m_curMotionID == MOTION_WAIT ) m_motionState = MSTATE_WAIT;
	// モーションが終わっていたら待機モーションに戻す
	if( m_animList[m_curMotionID].endTime <= m_time ) m_motionID = MOTION_WAIT;


	// モーションの状態
	switch( m_motionState ){
	case MSTATE_WAIT:
		Run();	  // 走る
		avoid();  // 回避
		Squat();  // しゃがみ
		Jump();   // ジャンプ
		Attack(); // 攻撃
		break;
	case MSTATE_JUMP:
		Jump();
		Run();
		break;
	case MSTATE_SQUAT:
		Squat();
		Attack();
		break;
	case MSTATE_AVOID:
		avoid();
		break;
	case MSTATE_IN_MOTION:
		Attack();
		Flinch();
		break;
	case MSTATE_AERIAL:
		Aerial();
		Jump();
		break;
	}

	// 死亡モーションが終わっていたらモーションを進めない
	if( (m_curMotionID == MOTION_DEAD &&  m_animList[MOTION_DEAD].endTime <= m_time) || (m_curMotionID == MOTION_APPEAL2 &&  m_animList[MOTION_APPEAL2].endTime <= m_time) ){
		m_motionStop = true;
	}
	// モーションを変更
	if( !m_motionStop ) SetMotion( m_motionID );
	// プレイヤーの座標を変更
	m_position.x += m_move.x;
	// 右壁
	if( m_position.x >= CCharacter::RIGHT_WALL ){
		m_position.x = CCharacter::RIGHT_WALL;
		m_move.x = 0.f;
	}
	// 左壁
	if( m_position.x <= CCharacter::LEFT_WALL ){ 
		m_position.x = CCharacter::LEFT_WALL;
		m_move.x = 0.f;
	}

	if( m_curMotionID == MOTION_WAIT ) m_HitCount = 0;
	
	CScene::m_keyStateOn = 0;
}
/**
 *
 * 怯み
 *
 */
void CPlayer::Flinch()
{
	// 無敵
	m_invincible = true;
	// 怯み状態も回避モーションの値を使用する
	float MOVE_DISTANCE = 5.f; // 回避モーションで移動する距離
	int TOTAL_FRAME = (int)(m_animList[MOTION_FLINCH].endTime - m_animList[MOTION_FLINCH].startTime); // 回避モーションのフレーム数
	// 1fの移動量
	float add = -0.1f;

	// モーション中ならモデルを点滅させる
	if( m_time > m_animList[MOTION_FLINCH].startTime && m_time < m_animList[MOTION_FLINCH].endTime){
		if( m_alpha > 1.0f) 
			add = add * -1;
		else if( m_alpha < 0.5f) 
			add = add * -1;
		m_alpha += add;
	// モーションが終了していたらα値を戻す
	}else{
		m_alpha = 1.0f;
		// 無敵解除
		m_invincible = false;
	}
}
/**
 *
 * ジャンプ
 *
 */
void CPlayer::Jump()
{
	// モーションを変更するまでのフレーム
	int DELAY_FRAME = 10;
	// ジャンプ速度
	float INIT_JUMP_SPEED = 0.006f;
	static bool keyPush = false;
	static int TOTAL_FRAME = 0; // 経過時間

	// ジャンプ中はジャンプできない状態
	if( m_motionState == MSTATE_WAIT && !m_jumpFlag && (CScene::m_keyStateOn & UP) != 0){	
		TOTAL_FRAME++;
		// ボタンを押している時間が一定以上(上＋攻撃キーを優先させる)
		if(TOTAL_FRAME == DELAY_FRAME){
			m_motionID = MOTION_JUMP;
			TOTAL_FRAME = 0;
		}
	}

	if( m_curMotionID == MOTION_JUMP )
		TOTAL_FRAME++;

	if( m_curMotionID == MOTION_JUMP && !m_jumpFlag && TOTAL_FRAME >= m_jumpStartFrame){
		m_jumpFlag = true;
		m_jumpSpeed = INIT_VELOCITY;
	}

	if( m_jumpFlag ){

		if( m_curMotionID == MOTION_JUMP && m_animList[MOTION_JUMP].endTime >= m_time ){
			m_position.y += m_jumpSpeed;
			m_jumpSpeed -= INIT_JUMP_SPEED;
		}else{
			m_motionID = MOTION_JUMP_FALL;
		}

		if( m_curMotionID == MOTION_JUMP_FALL && m_animList[MOTION_JUMP_FALL].endTime >= m_time ){
			Fall(30);
			if(m_position.y <= INIT_PLAYER_POSITION.y){
				m_jumpFlag = false;
				TOTAL_FRAME = 0;
			}
		}
	}
}
/**
 *
 * 落下
 *
 */
void CPlayer::Fall(int _frame)
{
	static float Height = m_position.y;
	// a = 重力 * 時間
	float acceleration = Height / ((_frame * _frame) / 2);
	// v
	static float velocity = 0;
	
	m_position.y -= velocity;

	velocity += acceleration;
	
	// ジャンプ中下キーが押されていたら落下速度を加算
	if( ((CScene::m_keyStateOn & DOWN) != 0) && (m_jumpSpeed < 0)) 
		m_position.y += velocity;
	
	// 着地
	if(m_position.y <= INIT_PLAYER_POSITION.y){
		velocity = 0;
		m_position.y = INIT_PLAYER_POSITION.y;
		ResetMotion(MOTION_WAIT);
		m_motionID = MOTION_WAIT;
	}
}
/**
 *
 * しゃがみ
 *
 */
void CPlayer::Squat()
{	
	// しゃがみ状態フラグ
	static bool isSquat = false;

	// しゃがみ状態からキーを話すとしゃがみ解除
	if(  isSquat && (CScene::m_keyStateOn & DOWN) == 0 ){
		isSquat = false;
		m_motionID = MOTION_STAND_UP;
		m_motionStop = false;
	}

	if( (CScene::m_keyStateOn & DOWN) == 0) return;

	m_motionID = MOTION_SQUAT_START;
	//しゃがみ始めモーションが終わってもキーが押されていたら
	if( m_animList[MOTION_SQUAT_START].endTime <= m_time ) 
		isSquat = true;
	// しゃがみモーションでストップ
	if( isSquat ){
		m_motionID = MOTION_SQUAT;
		m_motionStop = true;
		m_move.x = 0; // 移動と同時押し警戒で移動値を0に
	}
}
/**
 *
 * 走る
 *
 */
void CPlayer::Run()
{
	// 止まるモーションへ以降するフレーム数(走り出しモーション　＋　走りモーション)
	int STOP_FRAME = (int)((m_animList[MOTION_START_RUN].endTime - m_animList[MOTION_START_RUN].startTime) + (m_animList[MOTION_RUN].endTime - m_animList[MOTION_RUN].startTime));
	// モーションを変更するまでのフレーム
	int DELAY_FRAME = 5;
	static int TOTAL_FRAME = 0;
	m_move.x = 0; // 移動量は0に
	// 左キーが押されたとき
	if( (CScene::m_keyStateOn & LEFT) != 0){
		TOTAL_FRAME++;
		// 5フレーム押されていたら走り出しモーションへ
		if( m_curMotionID != MOTION_RUN && TOTAL_FRAME >= DELAY_FRAME ) m_motionID = MOTION_START_RUN;

		if( m_curMotionID == MOTION_RUN || m_curMotionID == MOTION_START_RUN){
			Move();		// 移動
			m_angle = LEFT_ANGLE;		// 走りモーション中のアングル
		}
	}

	//// 右キーが押されたとき
	if( (CScene::m_keyStateOn & RIGHT) != 0){
		TOTAL_FRAME++;
		// 5フレーム押されていたら走り出しモーションへ
		if( m_curMotionID != MOTION_RUN && TOTAL_FRAME >= DELAY_FRAME ) m_motionID = MOTION_START_RUN;
		// 走りモーション中のアングル
		if( m_curMotionID == MOTION_RUN || m_curMotionID == MOTION_START_RUN){
			Move();
			m_angle = RIGHT_ANGLE;
		}
	}

	// 走りだしモーションが終わっていたら走りモーションに移行
	if( TOTAL_FRAME && m_animList[MOTION_START_RUN].endTime <= m_time ) m_motionID = MOTION_RUN;
	
	static float tmpAngle = 0; // 止まるモーション時の一次保存用アングル
	// キーが離されたら
	if( (CScene::m_keyStateOn & LEFT || CScene::m_keyStateOn & RIGHT ) == 0 ){
		if( m_curMotionID == MOTION_START_RUN ){
			ResetMotion(MOTION_WAIT);
			m_motionID = MOTION_WAIT;
		}
		// 走りモーション中なら止まるモーションへ移行
		if( m_curMotionID == MOTION_RUN ){
			if( TOTAL_FRAME >= STOP_FRAME ){
				// ストップモーション
				m_motionID = MOTION_STOP_RUN;
				tmpAngle = m_angle;
			}else{
				ResetMotion(MOTION_WAIT);
				m_motionID = MOTION_WAIT;
			}
		}
		TOTAL_FRAME = 0; // 押されていたフレーム数を0に
	}

	// 止まるモーション時
	if( m_curMotionID == MOTION_STOP_RUN ){
		Move();
		m_angle = tmpAngle; // 方向を変えない
	}
}
/**
 *
 * 空中
 *
 */
void CPlayer::Aerial()
{
	// Ｓ＋下キー
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & DOWN) ){
		m_motionID = MOTION_AIR;
		ResetMotion(MOTION_AIR);
	}

}
/**
 *
 * 攻撃
 *
 */
void CPlayer::Attack()
{
	int oldMotion = m_motionID;
	if( m_motionState == MSTATE_IN_MOTION )
		m_move.x = 0;
	// Ｄキー
	if( (CScene::m_keyStateOn & KEY_D ) != 0 ){
		m_motionID = MOTION_SKILL;
	}
	// Ｄ＋下キー
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & LEFT) != 0 ){
		if( m_angle == LEFT_ANGLE )
			m_motionID = MOTION_SKILL2;
	}
	// Ｄ＋下キー
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & RIGHT) != 0 ){
		if( m_angle == RIGHT_ANGLE )
			m_motionID = MOTION_SKILL2;
	}
	// Ｄ＋下キー
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & DOWN) != 0 ){
		m_motionID = MOTION_SKILL4;
	}
	// Ｄ＋上キー
	if( (CScene::m_keyStateOn & KEY_D ) != 0 && (CScene::m_keyStateOn & UP) != 0 ){
		m_motionID = MOTION_SKILL3;
	}


	// Ｓキー単体
	if( ( CScene::m_keyStateOn & KEY_S) != 0 ){
		m_motionID = MOTION_ATTACK;
	}

	// Ｓ＋下キー
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & DOWN) != 0 ){
		m_motionID = MOTION_LOWER;
	}
	// Ｓ＋上キー
	if( (CScene::m_keyStateOn & KEY_S ) != 0 && (CScene::m_keyStateOn & UP) ){
		//m_motionID = MOTION_UPPER;
	}

	// モーション停止したいモーション以外はフラグを解除
	if( m_motionStop && m_motionID != oldMotion)
		m_motionStop = false;

}
/**
 *
 * 回避
 *
 */
void CPlayer::avoid()
{
	float MOVE_DISTANCE = 5.f; // 回避モーションで移動する距離
	int TOTAL_FRAME = (int)(m_animList[MOTION_AVOID].endTime - m_animList[MOTION_AVOID].startTime); // 回避モーションのフレーム数
	int MOVE_FRAME = TOTAL_FRAME - 12; // 移動するフレーム( モーション中の移動モーションはTOTAL - 12)
	float add = 0; // 1fの移動量
	// 無敵フレーム
	float INVICIBLE_FRAME = 25.f;

	if( CScene::m_keyStateOn & RIGHT && CScene::m_keyStateOn & KEY_S &&  m_angle != RIGHT_ANGLE ){
		m_motionID = MOTION_AVOID;
	}

	if( CScene::m_keyStateOn & LEFT && CScene::m_keyStateOn & KEY_S && m_angle != LEFT_ANGLE ){
		m_motionID = MOTION_AVOID;
	}

	if( m_motionID == MOTION_AVOID) add = MOVE_DISTANCE / TOTAL_FRAME;
	
	SetMotion(m_motionID);

	// 25フレーム目までは無敵
	if( m_curMotionID == MOTION_AVOID && m_time - m_animList[MOTION_AVOID].startTime <= INVICIBLE_FRAME )
		 m_invincible = true;
	 else
		 m_invincible = false;

	// 回避モーション中の移動
	if( m_curMotionID == MOTION_AVOID && m_time - m_animList[MOTION_AVOID].startTime <= MOVE_FRAME){
		m_move.x = 0;
		if( m_angle == LEFT_ANGLE ) m_move.x += add;
		else m_move.x -= add;
	}
}
/**
 *
 * 移動
 *
 */
void CPlayer::Move()
{
	// 移動時徐々に加速していくように

	static float velocity = 0;
	velocity += 0.01f;

	// キャラクターの最大スピードを超えないように
	if( m_speed.x <= velocity )
		velocity = m_speed.x;

	// 左キーが押されたとき
	if( (CScene::m_keyStateOn & LEFT) != 0){
		m_move.x -= velocity;		// 移動量
		m_angle = LEFT_ANGLE;		// 走りモーション中のアングル
	}
	// 右キーが押されたとき
	if( (CScene::m_keyStateOn & RIGHT) != 0){
		m_move.x += velocity;
		m_angle = RIGHT_ANGLE;
	}

	// 加速度 = モーションの時間÷キャラクターの最大速度
	//float acceleration = m_speed.x / ( m_animList[MOTION_STOP_RUN].endTime - m_animList[MOTION_STOP_RUN].startTime );
	// 滑りすぎるので0.02f
	float acceleration = 0.02f;
	// とまるモーション中は減速
	if( m_curMotionID == MOTION_STOP_RUN ){
		velocity -= acceleration;
		if( velocity <= 0.f )
			velocity = 0.f;

		if( m_angle == LEFT_ANGLE )
			m_move.x -= velocity;
		else
			m_move.x += velocity;
	}
}
/**
 *
 * positionをセットする
 * @param _position
 *
 */
void CPlayer::SetPosition(D3DXVECTOR3 _position)
{
	m_position = _position;
}
/**
 *
 * 位置を取得する
 * @return position
 *
 */
D3DXVECTOR3 CPlayer::GetPosition()
{
	return m_position;
}
/**
 *
 * 防御貫通フラグを取得する
 * @return int ダメージ計算に使用するのでintで返す
 *
 */
int CPlayer::Getflag()
{
	return !(int)true;	
}
/**
 *
 * アルファ値を加算する
 * @param	_value
 *
 */
void CPlayer::addAlpha(float _value)
{
	m_alpha += _value;
	if( m_alpha >= 1.0f ) m_alpha = 1.0f;
	if( m_alpha <= 0.f ) m_alpha = 0.f;
}