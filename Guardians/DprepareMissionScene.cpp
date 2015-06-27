/**
 * @file DprepareMissionScene.cpp
 */

#include "stdafx.h"

const CPrepareMission::CharaPictureData CPrepareMission::CH_PIC_DATA[] = {
	{ D3DXVECTOR2(85.f, 0.f),TEX_FIELD_MENU , CCharaPicture::TYPE_STAGE_SELECT },	// -ステージ選択-	
	{ D3DXVECTOR2(85.f, 0.f),TEX_FIELD_MENU , CCharaPicture::TYPE_STATUS },	
	{ D3DXVECTOR2(85.f, 0.f),TEX_FIELD_MENU , CCharaPicture::TYPE_SHOP },	
	{ D3DXVECTOR2(85.f, 0.f),TEX_FIELD_MENU , CCharaPicture::TYPE_SAVE },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
	{ D3DXVECTOR2(), 0 },	
};

CPrepareMission::CPrepareMission(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGamedata,CInput* _input) : CScene(_pDevice,_input) 
	,m_pDevice( _pDevice ), m_state( STATE_STAGE_SELECT ), m_menuID( 0 ), m_stageID( 0 ),
	m_oldState( m_state ), m_pScreen( NULL ), m_mapPosition(-75.f, -2000.f),m_pGameData(_pGamedata),m_clearCount(0)
{
	CScene::m_keyStatePush = 0;

	CTexMgr.Load(SCENE_GAME, m_pDevice);

	m_sceneID = SCENE_GAME;

	// ゲームデータ											
	m_pCursor = new CGameMenuCursor(_pDevice, D3DXVECTOR2(25.f, 40.f));					// メニューカーソル
	////Y軸は合わせておいてxの値を減らしてテロップを表示させる為にxは1280
	m_pTelop = new CGameTelop*[TELOP_TYPE_NUM];			// テロップ

	m_pTelop[TELOP_STAGE] = new CGameStageTelop(m_pDevice, INIT_EXPLAIN_TELOP_POSITION, 0);				// ステージテロップ
	m_pTelop[TELOP_BOSS]  = new CGameBossTelop(m_pDevice, INIT_BOSS_TELOP_POSITION,0);
	//				
	m_pWindow = new CGameDataWindow(_pDevice, D3DXVECTOR2(-199.f, 888.f), m_pGameData);	// ゲームデータ

	m_pMap = new CGameMap(_pDevice,m_pGameData,m_mapPosition, (m_pGameData->m_nowClearStageNum + 1)/4);		// マップ
	// デバッグ用
	//m_pMap = new CGameMap(_pDevice, m_mapPosition,m_pGameData->m_nowClearStageNum%4);		// マップ

	m_menuBar = new CMenuBar*[BAR_MAX];

	m_menuBar[BAR] = new CMenuBar(_pDevice);
	m_menuBar[BAR_ICON] = new CGameIcon(_pDevice,m_state);

	// 文字画像
	for( int i = 0; i < 4; i++ ) {
		m_pPicChara[i] = new CCharaPicture(_pDevice, CH_PIC_DATA[i].position,CH_PIC_DATA[i].textureID,CH_PIC_DATA[i].typeID);
	}
	// ステージクリアフラグ初期化
	for( int i = 0; i < STAGE_MAX; i++ ) {
		m_clearPoint[i] = false;
	}
}


CPrepareMission::~CPrepareMission()
{
	CTexMgr.Release();
	
	for( int i = 0; i < 4; i++ ){
		SAFE_DELETE(m_pPicChara[i]);
	}
	for( int i = 0; i < TELOP_TYPE_NUM; i++){
		SAFE_DELETE(m_pTelop[i]);
	}
	for( int i = 0; i < BAR_MAX; i++){	
		SAFE_DELETE(m_menuBar[i]);
	}	

	SAFE_DELETE(m_pWindow);
	SAFE_DELETE(m_pCursor);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pScreen);


	SAFE_DELETE_ARRAY(m_pTelop);
	SAFE_DELETE_ARRAY(m_menuBar);
}

CPrepareMission::SceneID CPrepareMission::Control()
{
	CScene::m_keyStatePush = 0;

	CScene::Control();


	m_oldState = m_state;

	// マップ移動状態が終わっていたらステージセレクトへ
	bool moving = m_pMap->Control();

	if( m_state != STATE_MENU_MOVE && !moving ) {
		// Eキーが押された時
		if ( (CScene::m_keyStatePush & KEY_E) != 0){
			// 今のメニュー項目から一つ進める
			m_menuID = (m_menuID+1)%MENU_MAX;
			// メニューカーソルを次の場所へ
			m_pCursor->SetNextPosition(D3DXVECTOR2(25.f, 40.f+145.f*m_menuID));
			// 状態をメニュー移動状態へ
			m_state = STATE_MENU_MOVE;
		}
		if ( (CScene::m_keyStatePush & KEY_Q) != 0){
			// 今のメニュー項目から一つ進める
			m_menuID = (m_menuID+MENU_MAX-1)%MENU_MAX;
			// メニューカーソルを次の場所へ
			m_pCursor->SetNextPosition(D3DXVECTOR2(25.f, 40.f+145.f*m_menuID));
			// 状態をメニュー移動状態へ
			m_state = STATE_MENU_MOVE;
		}
		// Sキーが押された時
		else if ( (CScene::m_keyStatePush & KEY_S) != 0){
			if( m_state == STATE_VIEW_STATUS ) m_state = STATE_CHANGE_ITEM;
			else if ( m_state == STATE_CHANGE_ITEM ) m_state = STATE_VIEW_STATUS;
		}
		// Sキーが押された時
		if ( (CScene::m_keyStatePush & KEY_S) != 0){
			if(m_state == STATE_STAGE_SELECT) {
				m_pScreen = new CMenuSelectScreen(m_pDevice,m_pGameData);
				CScene::m_keyStatePush = 0;
				m_state = STATE_CHARA_SELECT;
			}
		}
		// Aキーが押された時
		if ( (CScene::m_keyStatePush & KEY_A) != 0){
			if( m_state == STATE_CHANGE_ITEM ) m_state = STATE_VIEW_STATUS;
		}

	}
	switch( m_state ) {
	case STATE_STAGE_SELECT:		// ステージ選択
		// ウィンドウを動かす
		m_pWindow->Control();
		break;
	case STATE_VIEW_STATUS:
	case STATE_CHARA_SELECT:
	case STATE_SHOP:
	case STATE_CHANGE_ITEM:
	case STATE_SAVE:
		// 各画面のコントロールを呼ぶ
		m_pScreen->Control( CScene::m_keyStatePush );
		break;
	case STATE_MENU_MOVE:			// メニュー移動
		// カーソルを動かす
		m_pCursor->Control();

		// カーソルが止まったら次の状態へ
		if( m_pCursor->GetState() == CGameCursor::STATE_WAIT ) {
			m_state = static_cast<State>(STATE_STAGE_SELECT+m_menuID);

			// 状態がキャラ出撃選択からセーブの間なら
			if( m_state >= STATE_VIEW_STATUS && m_state <= STATE_SAVE ) {
				SAFE_DELETE(m_pScreen);	// 前の画面を消す

				// 状態に応じて、呼び出す画面を変える
				switch( m_state ) {
				case STATE_VIEW_STATUS:		m_pScreen = new CMenuStatusScreen(m_pDevice, m_pGameData); break;
				case STATE_SHOP:			m_pScreen = new CMenuShopScreen(m_pDevice,m_pGameData); break;
				case STATE_SAVE:			m_pScreen = new CMenuDataScreen(m_pDevice,m_pGameData); break;
				}
			}
		}
		break;
	}
	if(m_state == STATE_CHARA_SELECT )
		if(dynamic_cast<CMenuSelectScreen*>(m_pScreen)->GetBattleFlag())
			return SCENE_BATTLE;
	

	if(m_state == STATE_STAGE_SELECT){
		//チェックポイント
		if( CScene::m_keyStatePush == KEY_Z ) {
		if( m_clearCount < 3 ) m_clearCount++;		//チェックポイントが今は3個のため（後で変える）
			m_pMap->SetClearCount( m_clearCount);
		}

		//進行方向の管理
		//進む
		//待機状態で→が押されたら	
		if( CScene::m_keyStatePush ==  RIGHT && m_pMap->GetMapPointer()->GetState() == CGameMapPointer::STATE_WAIT){
			m_pMap->GetMapPointer()->SetMoveDirection(CGameMapPointer::STATE_MOVE_RIGHT);
			m_pMap->SetNextPosition(m_pGameData->m_selectStageNum,CGameMapPointer::STATE_MOVE_RIGHT);
		}
		//戻る
		//待機状態で←が押されたら
		if( CScene::m_keyStatePush ==  LEFT && m_pMap->GetMapPointer()->GetState() == CGameMapPointer::STATE_WAIT){
			m_pMap->GetMapPointer()->SetMoveDirection(CGameMapPointer::STATE_MOVE_LEFT);
			m_pMap->SetNextPosition(m_pGameData->m_selectStageNum,CGameMapPointer::STATE_MOVE_LEFT);
		}
	}

	return SCENE_GAME;
}
void CPrepareMission::Draw()
{
	// ステージ
	m_pMap->Draw();

	
	// メニュバー
	m_menuBar[BAR]->Draw(m_state);

	//// カーソル
	m_pCursor->Draw();
	// 文字画像(画面左上メニュー項目画像)
	m_pPicChara[m_menuID]->Draw();
	switch( m_state ) {
	case STATE_STAGE_SELECT:
		m_menuBar[BAR_ICON]->Draw(m_state);
		for(int i = 0; i < TELOP_TYPE_NUM-1; i++){
			m_pTelop[i]->Draw();		// 他の画面のテロップはメニュー画面クラスの方で描く
		}
		break;
	case STATE_VIEW_STATUS:
	case STATE_CHANGE_ITEM:
	case STATE_CHARA_SELECT:
	case STATE_SHOP:
	case STATE_SAVE:
		m_menuBar[BAR_ICON]->Draw(m_state);
		m_pScreen->Draw();		// 各画面の描画
		break;
	default:
		m_menuBar[BAR_ICON]->Draw(m_state);
		break;
	}
	// プレイ時間/所持金はテロップを描画した後に
	m_pWindow->Draw();

}