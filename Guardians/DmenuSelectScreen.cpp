/**
 * @file DmenuSelectScreen.cpp
 */

#include "stdafx.h"

const D3DXVECTOR2 CMenuSelectScreen::INIT_CHARA_CURSOR_POSITION = D3DXVECTOR2(105.f,35.f);
const D3DXVECTOR2 CMenuSelectScreen::INIT_CHARA_READY_POSITION = D3DXVECTOR2(110.f,45.f);        // �X�e�[�W�I�����̃L�������W
const D3DXVECTOR2 CMenuSelectScreen::BOSS_POSITION = D3DXVECTOR2(950.f,40.f);
const D3DXVECTOR2 CMenuSelectScreen::INIT_SELECT_CURSOR_POSITION = D3DXVECTOR2(330.f,295.f);

CMenuSelectScreen::CMenuSelectScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData) :
	CMenuScreen( _pDevice ) ,m_charaID( 0 ),m_selectCount(0) , m_selectID(0)
{
	m_battleFlag = false;
	m_pGameData = _gameData;
	// Cursor
	m_gameCursor = new CGameCursor*[CURSOR_TYPE_NUM];	// ��ޕ�����

	m_gameCursor[CUR_CHARA] = new CGameCharaCursor( m_pDevice,INIT_CHARA_CURSOR_POSITION );
	m_gameCursor[CUR_SELECT] = NULL;
	// Telop
	m_gameTelop = new CGameTelop*[TELOP_TYPE_NUM];	// ��ޕ�����
	
	m_gameTelop[TELOP_CHARA] = new CGameCharaTelop(m_pDevice,INIT_CHARA_READY_POSITION,m_pGameData,1);       // �X�e�[�W�I�����̃L����
	m_gameTelop[TELOP_STAGE] = new CGameExplainTelop(m_pDevice,INIT_EXPLAIN_TELOP_POSITION,m_pGameData);     //
	m_gameTelop[STAGE_NAME]  = new CGameStageTelop(_pDevice, D3DXVECTOR2(64.f, 615.f), 0);         // �X�e�[�W���̕`��

	m_gameTelop[TELOP_BOSS]  = new CGameBossTelop(m_pDevice, BOSS_POSITION,0);				       // �X�e�[�W�I�����̃{�X�e���b�v

	// Window
	m_gameWindow = new CGameWindow*[WINDOW_TYPE_NUM];	// ��ޕ�����

	m_gameWindow[WND_EQUIP] = new CGameEquipWindow(m_pDevice,D3DXVECTOR2(350.f, 410.f),m_pGameData,1);
	m_gameWindow[WND_SELECT] = NULL;

	for(int i = 0;i < 3; i++){
		m_turnNo[i] = m_pGameData->m_turnNo[i];
		m_pGameData->m_turnNo[i] = -1;
	}
}

CMenuSelectScreen::~CMenuSelectScreen()
{
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameWindow[i]);
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameCursor[i]);
	}
	for( int i = 0; i < TELOP_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameTelop[i]);
	}
	SAFE_DELETE_ARRAY(m_gameCursor);
	
	SAFE_DELETE_ARRAY(m_gameTelop);
	
	SAFE_DELETE_ARRAY(m_gameWindow);
}

void CMenuSelectScreen::Control(int _keyState)
{
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		if( m_gameWindow[i] == NULL ) continue;
		m_gameWindow[i]->Control();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue;
		m_gameCursor[i]->Control();
	}


	if ( (CScene::m_keyStatePush & RIGHT) != 0){
		if( m_selectCount < 3 ){
			do{
				m_charaID = (m_charaID+1)%3;
				m_gameCursor[CUR_CHARA]->SetNextPosition(D3DXVECTOR2(INIT_CHARA_CURSOR_POSITION.x + m_charaID * (128.f + 42.f), INIT_CHARA_CURSOR_POSITION.y));
			}while(m_pGameData->m_turnNo[m_charaID] != -1);
		}
	}

	if ( (CScene::m_keyStatePush & LEFT) != 0){
		if( m_selectCount < 3 ){
			do{
				m_charaID = (m_charaID+2)%3;
				m_gameCursor[CUR_CHARA]->SetNextPosition(D3DXVECTOR2(INIT_CHARA_CURSOR_POSITION.x + m_charaID * (128.f + 42.f), INIT_CHARA_CURSOR_POSITION.y));	
			}while(m_pGameData->m_turnNo[m_charaID] != -1);
		}
	}

	if ( (CScene::m_keyStatePush & UP) != 0){					// ����L�[�������ꂽ��
		if(m_gameCursor[CUR_SELECT] != NULL ){
			m_selectID = (m_selectID+1)%2;
			m_gameCursor[CUR_SELECT]->SetNextPosition(D3DXVECTOR2(INIT_SELECT_CURSOR_POSITION.x, INIT_SELECT_CURSOR_POSITION.y + m_selectID * (80.f)));	
		}
	}

	if ( (CScene::m_keyStatePush & DOWN) != 0){	// �����L�[�������ꂽ��
		if(m_gameCursor[CUR_SELECT] != NULL ){
			m_selectID = (m_selectID+1)%2;
			m_gameCursor[CUR_SELECT]->SetNextPosition(D3DXVECTOR2(INIT_SELECT_CURSOR_POSITION.x, INIT_SELECT_CURSOR_POSITION.y + m_selectID * (80.f)));	
		}
	}

	if ( (CScene::m_keyStatePush & KEY_S) != 0){
		if( m_gameWindow[WND_SELECT] != NULL && m_selectID == 0 ){			//�I�����u�͂��v�Ȃ�퓬�J�n
			m_battleFlag = true;
		}else if ( m_gameWindow[WND_SELECT] != NULL && m_selectID == 1){							// �u�������v�Ȃ�L�����Z��
			m_selectCount = 0;
			m_selectID = 0;
			SAFE_DELETE(m_gameWindow[WND_SELECT]);
			SAFE_DELETE(m_gameCursor[CUR_SELECT]);
			for(int i = 0;i < 3; i++){
				m_pGameData->m_turnNo[i] = -1;
			}
		}else if( m_pGameData->m_turnNo[m_charaID] == -1 ){
			m_pGameData->m_turnNo[m_charaID] = m_selectCount;	//�o������turnNo��
			// �擪�̃L���������߂����ɔԍ���ۑ����Ă���
			if( m_pGameData->m_turnNo[m_charaID] == 0 ) m_pGameData->m_playerCharaNo = m_charaID;
			m_oldID[m_selectCount] = m_charaID;
			m_selectCount++;
			if(m_selectCount < 3){	
				do{
					m_charaID = (m_charaID+1)%3;
					m_gameCursor[CUR_CHARA]->SetNextPosition(D3DXVECTOR2(INIT_CHARA_CURSOR_POSITION.x + m_charaID * (128.f + 42.f), INIT_CHARA_CURSOR_POSITION.y));
				}while( m_pGameData->m_turnNo[m_charaID] != -1 );
			}else{
				m_gameWindow[WND_SELECT] = new CGameSelectWindow(m_pDevice,D3DXVECTOR2(500.f,330.f),0);
				m_gameCursor[CUR_SELECT] = new CGameSelectCursor(m_pDevice,INIT_SELECT_CURSOR_POSITION,CGameSelectCursor::CUR_SELECT);
			}
		}
	}
	if ( (CScene::m_keyStatePush & KEY_A) != 0){
		if(m_pGameData->m_turnNo[m_oldID[m_selectCount-1]] != -1){
			m_selectCount--;
			m_pGameData->m_turnNo[m_oldID[m_selectCount]] = -1;
			if(m_selectCount == 2 ){
				SAFE_DELETE(m_gameWindow[WND_SELECT]);
				SAFE_DELETE(m_gameCursor[CUR_SELECT]);
				m_selectID = 0;
			}

		}
	}
}

void CMenuSelectScreen::Draw()
{
	for( int i = 0; i < TELOP_TYPE_NUM-1; i++ ) {
		m_gameTelop[i]->Draw();
	}

	dynamic_cast<CGameEquipWindow*>(m_gameWindow[WND_EQUIP])->SetCharaID(m_charaID);
	for(int i = 0;i < WINDOW_TYPE_NUM;i++){
		if( m_gameWindow[i] == NULL ) continue;	
		m_gameWindow[i]->Draw();
	}
	//if(�Ȃ�Ƃ��t���O�������Ă���){boss�̕`��
	//	m_gameTelop[TELOP_BOSS]->Draw();
	//}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue;
		m_gameCursor[i]->Draw();
	}
}
/**
 * �o�g���V�[���ɑJ�ڂ��邩�ǂ����̃t���O��Ԃ�
 * @retval true  �o������I�����I�����
 * @retval false �I�����I����Ă��Ȃ�
 */
bool CMenuSelectScreen::GetBattleFlag()
{
	return m_battleFlag;
}
