/*--------------------------------------------------------------

	処理内容:データスクリーンのカーソル描画、ゲームデータの制御
	作成者:三浦
	作成日:10/18
	更新日:10/19
	更新内容:
		10/19  ウィンドウ、カーソルの初期位置座標セット
				セーブデータウィンドウの追加
	関数　
		コンストラクタ
		デストラクタ
		Control
		Draw
	変数　

--------------------------------------------------------------*/
#include "stdafx.h"

CMenuDataScreen::CMenuDataScreen(LPDIRECT3DDEVICE9 _pDevice, CGameData* _gameData) :
	CMenuScreen( _pDevice ), m_dataID(0) , m_dataPos(0,0), m_partID(0),m_page(0), m_state(STATE_PART),m_selectID(0)
{
	m_pGameData = _gameData;

	m_gameWindow = new CGameWindow*[WINDOW_TYPE_NUM];	// 種類分生成

	m_gameWindow[WND_SAVE] = new CGameSaveDataWindow(m_pDevice, INIT_SAVE_WINDOW_POSITION,m_state);		  //セーブデータウィンドウ
	//m_gameWindow[WND_DATA] = new CGameDataWindow(m_pDevice, INIT_STATUS_WINDOW_POSITION, m_pGameData);   //select
	m_gameWindow[WND_SELECT] = NULL;

	m_gameCursor = new CGameCursor*[CURSOR_TYPE_NUM];	// 種類分生成

	m_gameCursor[CUR_DATA] = new CGameSaveCursor(m_pDevice, INIT_DATA_CURSOR_POSITION);
	m_gameCursor[CUR_PART] = new CGameSelectCursor(m_pDevice, INIT_DATAPART_CURSOR_POSITION, CGameSelectCursor::CUR_DATA);
	m_gameCursor[CUR_SELECT] = NULL;

	m_gameTelop = new CGameTelop*[TELOP_TYPE_NUM];			// テロップ

	m_gameTelop[TELOP_NONE] = new CGameTelop(m_pDevice, INIT_EXPLAIN_TELOP_POSITION, 0);	

}

CMenuDataScreen::~CMenuDataScreen()
{
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
	SAFE_DELETE(m_gameWindow[i]);
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameCursor[i]);
	}
	for( int i = 0; i < TELOP_TYPE_NUM; i++) {
		SAFE_DELETE(m_gameTelop[i]);
	}

	SAFE_DELETE_ARRAY(m_gameWindow);

	SAFE_DELETE_ARRAY(m_gameCursor);

	SAFE_DELETE_ARRAY(m_gameTelop);

}

void CMenuDataScreen::Control(int _keyState)
{
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		if( m_gameWindow[i] == NULL ) continue ;
		m_gameWindow[i]->Control();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue ;
		m_gameCursor[i]->Control();
	}

	// Zキーが押された時
	if ( (CScene::m_keyStatePush & LEFT) != 0){
			if( m_state == STATE_PART ){
					m_partID = (m_partID+1)%2;
					// はいいいえ選択カーソルを指定未完
					m_gameCursor[CUR_PART]->SetNextPosition(D3DXVECTOR2(INIT_DATAPART_CURSOR_POSITION.x + m_partID * (150.f), INIT_DATAPART_CURSOR_POSITION.y)); // 座標は変更しなければならない
			}
					//m_partID = (m_partID+4)%5;
					//m_gameCursor[CUR_PART]->SetNextPosition(D3DXVECTOR2(INIT_DATAPART_CURSOR_POSITION.x + m_partID * (154.f), INIT_DATAPART_CURSOR_POSITION.y)); // 座標は変更しなければならない}
	}
	if ( (CScene::m_keyStatePush & RIGHT) != 0){
			if( m_state == STATE_PART ){
				//if( m_gameCursor[CUR_PART] == NULL ){
				//	m_partID = (m_partID+1)%5;
				//	m_gameCursor[CUR_PART]->SetNextPosition(D3DXVECTOR2(INIT_DATAPART_CURSOR_POSITION.x + m_partID * (154.f), INIT_DATAPART_CURSOR_POSITION.y)); // 座標は変更しなければならない
				//
				m_partID = (m_partID+1)%2;
				m_gameCursor[CUR_PART]->SetNextPosition(D3DXVECTOR2(INIT_DATAPART_CURSOR_POSITION.x + m_partID * (150.f), INIT_DATAPART_CURSOR_POSITION.y)); // 座標は変更しなければならない
			}
	}		
	if ( (CScene::m_keyStatePush & UP) != 0){
			if( m_state != STATE_DECIDE ){
				m_dataID = (m_dataID-1)%10;
				if( m_dataID <= -1 ){
					m_dataID = 9;
				}
				// カーソルが上まで来ると固定
				m_drawID--;
				if( m_dataID >= 7 ) m_drawID = m_dataID-7;
				else if( m_dataID < 7 && m_drawID <= 0 ) m_drawID = 0;
//				int m_drawID = m_dataID >= 7 ? m_dataID-7 : 0;
				m_gameCursor[CUR_DATA]->SetNextPosition(D3DXVECTOR2(INIT_DATA_CURSOR_POSITION.x + m_drawID * (20.f), INIT_DATA_CURSOR_POSITION.y + m_drawID * (130.f))); // 座標は変更しなければならない
			}else{
				// selectCursorのMove処理
				m_selectID = (m_selectID+1)%2;
				m_gameCursor[CUR_SELECT]->SetNextPosition(D3DXVECTOR2(INIT_SELECT_CURSOR_POSITION.x,INIT_SELECT_CURSOR_POSITION.y +  + m_selectID * (80.f) )); // 座標は変更しなければならない
			}
	}
	if ( (CScene::m_keyStatePush & DOWN) != 0){
			//if( m_state == STATE_SELECT ){
			if( m_state != STATE_DECIDE ){
					m_dataID = (m_dataID+1)%10;
					if( m_dataID >= 10 ){
						m_dataID = 0;
					}
					// カーソルが下まで来ると固定
					m_drawID++;

					if( m_dataID < 3 ) m_drawID = m_dataID;
					else if( m_dataID >= 3 && m_drawID >= 2 ) m_drawID = 2;
//					int m_drawID = m_dataID < 3 ? m_dataID : 2;
					m_gameCursor[CUR_DATA]->SetNextPosition(D3DXVECTOR2(INIT_DATA_CURSOR_POSITION.x + m_drawID * (20.f), INIT_DATA_CURSOR_POSITION.y + m_drawID * (130.f))); // 座標は変更しなければならない
			}else{
				// selectCursorのMove処理
				m_selectID = (m_selectID+1)%2;
				m_gameCursor[CUR_SELECT]->SetNextPosition(D3DXVECTOR2(INIT_SELECT_CURSOR_POSITION.x,INIT_SELECT_CURSOR_POSITION.y +  + m_selectID * (80.f) )); // 座標は変更しなければならない
			}
	}
	if ( (CScene::m_keyStatePush & KEY_S) != 0){
		if( m_state == STATE_PART ) m_state++;
		if( m_gameWindow[WND_SELECT] == NULL ){
			// はいいいえ選択画面表示
			m_gameWindow[WND_SELECT] = new CGameSelectWindow(m_pDevice,D3DXVECTOR2(700.f,300.f),1);
			m_gameCursor[CUR_SELECT] = new CGameSelectCursor(m_pDevice,INIT_SELECT_CURSOR_POSITION, CGameSelectCursor::CUR_SELECT);
			// 状態をDECIDEへ
		}else{
			// ウインドウが生成されている時は
			if( m_selectID == YES ){
				// はい　が押されたらpartIDでセーブ・ロードを判断
				if(m_partID == SAVE) m_pGameData->Save(m_dataID);
				else m_pGameData->Load(m_dataID);
				SAFE_DELETE(m_gameCursor[CUR_SELECT]);
				SAFE_DELETE(m_gameWindow[WND_SELECT]);
				m_state = STATE_PART;
				m_selectID = 0;
			}else if( m_selectID == NO){
				//いいえが押されたら
				SAFE_DELETE(m_gameCursor[CUR_SELECT]);
				SAFE_DELETE(m_gameWindow[WND_SELECT]);
				m_state = STATE_PART;
				m_selectID = 0;
			}
		}
	}
	dynamic_cast<CGameSaveDataWindow*> (m_gameWindow[WND_SAVE])->SetCursorID( m_dataID );

}

void CMenuDataScreen::Draw()
{
	for( int i = 0; i < TELOP_TYPE_NUM; i++){
		m_gameTelop[i]->Draw();
	}
	for( int i = 0; i < WINDOW_TYPE_NUM-1; i++ ) {
		m_gameWindow[i]->Draw();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM-1; i++ ){
		m_gameCursor[i]->Draw();
	}

	if( m_gameWindow[WND_SELECT] != NULL ) {
		m_gameWindow[WND_SELECT]->Draw();
		m_gameCursor[CUR_SELECT]->Draw();
	}
}