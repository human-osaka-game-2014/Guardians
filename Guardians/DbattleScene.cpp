/**
 * @file DbattleScene.cpp
 */

#include "stdafx.h"

bool CBattleScene::m_pause = false;
// コンボ数
int  CBattleScene::comboCount = 0;
// 左右の壁
const float CBattleScene::RIGHT_WALL = 20.f;
const float CBattleScene::LEFT_WALL = 4.8f;


CBattleScene::CBattleScene(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CInput* _input,CCharacterManager::MODELDATA* _chara,CField* _field) :
	CScene(_pDevice,_input),m_pGameData(_pGameData) , m_cameraPos(-5.f,0.f) , m_move(0.f,0.f), m_alpha(m_pGameData->m_nowClearStageNum % 4 == 0 ? 255 : 0)
	,m_charaChange(STATE_BATTLE)
{
	m_sceneID = SCENE_BATTLE;

	CTexMgr.Load(m_sceneID, m_pDevice);

	CScene::m_keyStateOn = 0;
	CScene::m_keyStatePush = 0;

	m_field = _field;
	// リザルト経由用にフィールド座標をリセットする
	m_field->SetPosition( D3DXVECTOR2(0.f,0.f) );
	
	// 蓄積ダメージをリセット
	m_pGameData->m_pDamage.damage = 0;
	m_pGameData->m_pDamage.damageTaken = 0;
	comboCount = 0;

	m_camera = new CCamera(m_pDevice);

	m_character = new CCharacterManager(m_pDevice,_pGameData,_chara);

	m_ui = new CBattleUI(m_pDevice,_pGameData);

	m_feed = CTexMgr.Get( 16 );

}

CBattleScene::~CBattleScene()
{
	//SAFE_DELETE(m_field);
	SAFE_DELETE(m_ui);

	SAFE_DELETE(m_camera);

	SAFE_DELETE(m_character);

	CTexMgr.Release();
}
CBattleScene::SceneID CBattleScene::Control()
{
	
	CScene::Control();

	// ポーズ処理
	if( ( m_keyStateOn & KEY_SPACE) && !m_pause) 
		m_pause = true;
	else if( ( m_keyStateOn & KEY_SPACE) && m_pause)
		m_pause = false;

	if( m_pause ){
		m_keyStateOn = 0;	// キー入力を無効に
		return SCENE_BATTLE;	// ポーズ中はここで処理を止める
	}

	// キャラ交代
	switch( m_charaChange ){
	case STATE_BATTLE:
		if( (CScene::m_keyStatePush & KEY_A) != 0 ){
			m_charaChange = STATE_CHARA_CHANGE;
			m_changeTime = 0;
		}
		break;
	case STATE_CHARA_CHANGE:
		int add = CC_MAX_ALPHA / CC_ADDALPHA_FRAME;	// 1Fのアルファ増加量
		// キャラ変更時は画面を暗く
		if( m_changeTime <= CC_ADDALPHA_FRAME ){
			m_alpha += add;
			if( m_alpha >= CC_MAX_ALPHA ) m_alpha = CC_MAX_ALPHA;
		}else if( m_changeTime >= CHANGE_LIMIT - CC_ADDALPHA_FRAME ){
			// キャラ変更時の経過時間がタイムリミット10フレーム前なら
			m_alpha -= add;
			if( m_alpha <= 0 ) m_alpha = 0;
		}

		if( (CScene::m_keyStatePush & KEY_A) != 0){

			m_changeTime = 0;	// 経過時間を0に

			m_ui->SetNextPosition();

		}
		m_character->CharacterChange();
		m_changeTime++;
		// 制限時間を過ぎていたら
		if( m_changeTime >= CHANGE_LIMIT ){
			m_charaChange = STATE_BATTLE;	// 戦闘状態に戻す
			m_character->SetAlpha();
		}
		break;
	}

	m_character->Control();
	// UI
	m_ui->SetBossHP(m_character->GetHP());
	m_ui->Control();
	// フィールドの移動量を決める
	m_move = m_character->GetCharaSpeed();
	// プレイヤーの位置を取得
	m_playerPos = m_character->GetPlayer()->GetPosition();

	// カメラ移動範囲
	if( m_playerPos.x >= RIGHT_WALL ){
		m_playerPos.x = RIGHT_WALL;
		m_move.x = 0.f;
	}
	if( m_playerPos.x <= LEFT_WALL ){
		m_playerPos.x = LEFT_WALL;
		m_move.x = 0.f;
	}

	// 戦闘開始時のフェードイン処理
	if( m_playerPos.y <= 0.f ) {
		m_alpha--;
		if( m_alpha <= 0 ) m_alpha = 0; 
	}

	m_field->SetCharaSpeed( m_move );
	m_field->Control();

	// 敗北時
	if( m_pGameData->m_death){
		if ( m_character->GetMotionEnd(CPlayer::MOTION_DEAD) )
			return SCENE_RESULT;
	}
	// 勝利時
	if( m_pGameData->m_win ){
		if ( m_character->GetMotionEnd(CPlayer::MOTION_APPEAL2) ){
			return SCENE_RESULT;
		}
	}
	
	m_keyStateOn = 0;

	return SCENE_BATTLE;
}

void CBattleScene::Draw()
{

	D3DXVECTOR3 eye = D3DXVECTOR3(m_playerPos.x, m_playerPos.y  + 18.f, -50.f);
	// 注視点
	m_camera->Look(eye, D3DXVECTOR3(m_playerPos.x, m_playerPos.y  + 18.f, 0.f));


	m_field->Draw();

	m_character->Draw();

	m_ui->Draw();

	// フェードイン用画像の描画
	DrawBlackPic(m_alpha);
}

/**
 * FadeIn Out 用画像の制御
 * @param[in] _alpha アルファ値
 */
void CBattleScene::DrawBlackPic(int _alpha)
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	CVertex vertex;
	vertex.DrawTextureLT(m_pDevice, m_feed, 0.f, 0.f, D3DCOLOR_ARGB(m_alpha,255,255,255));
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
