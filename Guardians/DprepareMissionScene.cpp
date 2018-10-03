/**
 * @file DprepareMissionScene.cpp
 */

#include "stdafx.h"

const CPrepareMission::CharaPictureData CPrepareMission::CH_PIC_DATA[] = {
	{ D3DXVECTOR2(85.f, 0.f),TEX_FIELD_MENU , CCharaPicture::TYPE_STAGE_SELECT },	// -�X�e�[�W�I��-	
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

	// �Q�[���f�[�^											
	m_pCursor = new CGameMenuCursor(_pDevice, D3DXVECTOR2(25.f, 40.f));					// ���j���[�J�[�\��
	////Y���͍��킹�Ă�����x�̒l�����炵�ăe���b�v��\��������ׂ�x��1280
	m_pTelop = new CGameTelop*[TELOP_TYPE_NUM];			// �e���b�v

	m_pTelop[TELOP_STAGE] = new CGameStageTelop(m_pDevice, INIT_EXPLAIN_TELOP_POSITION, 0);				// �X�e�[�W�e���b�v
	m_pTelop[TELOP_BOSS]  = new CGameBossTelop(m_pDevice, INIT_BOSS_TELOP_POSITION,0);
	//				
	m_pWindow = new CGameDataWindow(_pDevice, D3DXVECTOR2(-199.f, 888.f), m_pGameData);	// �Q�[���f�[�^

	m_pMap = new CGameMap(_pDevice,m_pGameData,m_mapPosition, (m_pGameData->m_nowClearStageNum + 1)/4);		// �}�b�v
	// �f�o�b�O�p
	//m_pMap = new CGameMap(_pDevice, m_mapPosition,m_pGameData->m_nowClearStageNum%4);		// �}�b�v

	m_menuBar = new CMenuBar*[BAR_MAX];

	m_menuBar[BAR] = new CMenuBar(_pDevice);
	m_menuBar[BAR_ICON] = new CGameIcon(_pDevice,m_state);

	// �����摜
	for( int i = 0; i < 4; i++ ) {
		m_pPicChara[i] = new CCharaPicture(_pDevice, CH_PIC_DATA[i].position,CH_PIC_DATA[i].textureID,CH_PIC_DATA[i].typeID);
	}
	// �X�e�[�W�N���A�t���O������
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

	// �}�b�v�ړ���Ԃ��I����Ă�����X�e�[�W�Z���N�g��
	bool moving = m_pMap->Control();

	if( m_state != STATE_MENU_MOVE && !moving ) {
		// E�L�[�������ꂽ��
		if ( (CScene::m_keyStatePush & KEY_E) != 0){
			// ���̃��j���[���ڂ����i�߂�
			m_menuID = (m_menuID+1)%MENU_MAX;
			// ���j���[�J�[�\�������̏ꏊ��
			m_pCursor->SetNextPosition(D3DXVECTOR2(25.f, 40.f+145.f*m_menuID));
			// ��Ԃ����j���[�ړ���Ԃ�
			m_state = STATE_MENU_MOVE;
		}
		if ( (CScene::m_keyStatePush & KEY_Q) != 0){
			// ���̃��j���[���ڂ����i�߂�
			m_menuID = (m_menuID+MENU_MAX-1)%MENU_MAX;
			// ���j���[�J�[�\�������̏ꏊ��
			m_pCursor->SetNextPosition(D3DXVECTOR2(25.f, 40.f+145.f*m_menuID));
			// ��Ԃ����j���[�ړ���Ԃ�
			m_state = STATE_MENU_MOVE;
		}
		// S�L�[�������ꂽ��
		else if ( (CScene::m_keyStatePush & KEY_S) != 0){
			if( m_state == STATE_VIEW_STATUS ) m_state = STATE_CHANGE_ITEM;
			else if ( m_state == STATE_CHANGE_ITEM ) m_state = STATE_VIEW_STATUS;
		}
		// S�L�[�������ꂽ��
		if ( (CScene::m_keyStatePush & KEY_S) != 0){
			if(m_state == STATE_STAGE_SELECT) {
				m_pScreen = new CMenuSelectScreen(m_pDevice,m_pGameData);
				CScene::m_keyStatePush = 0;
				m_state = STATE_CHARA_SELECT;
			}
		}
		// A�L�[�������ꂽ��
		if ( (CScene::m_keyStatePush & KEY_A) != 0){
			if( m_state == STATE_CHANGE_ITEM ) m_state = STATE_VIEW_STATUS;
		}

	}
	switch( m_state ) {
	case STATE_STAGE_SELECT:		// �X�e�[�W�I��
		// �E�B���h�E�𓮂���
		m_pWindow->Control();
		break;
	case STATE_VIEW_STATUS:
	case STATE_CHARA_SELECT:
	case STATE_SHOP:
	case STATE_CHANGE_ITEM:
	case STATE_SAVE:
		// �e��ʂ̃R���g���[�����Ă�
		m_pScreen->Control( CScene::m_keyStatePush );
		break;
	case STATE_MENU_MOVE:			// ���j���[�ړ�
		// �J�[�\���𓮂���
		m_pCursor->Control();

		// �J�[�\�����~�܂����玟�̏�Ԃ�
		if( m_pCursor->GetState() == CGameCursor::STATE_WAIT ) {
			m_state = static_cast<State>(STATE_STAGE_SELECT+m_menuID);

			// ��Ԃ��L�����o���I������Z�[�u�̊ԂȂ�
			if( m_state >= STATE_VIEW_STATUS && m_state <= STATE_SAVE ) {
				SAFE_DELETE(m_pScreen);	// �O�̉�ʂ�����

				// ��Ԃɉ����āA�Ăяo����ʂ�ς���
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
		//�`�F�b�N�|�C���g
		if( CScene::m_keyStatePush == KEY_Z ) {
		if( m_clearCount < 3 ) m_clearCount++;		//�`�F�b�N�|�C���g������3�̂��߁i��ŕς���j
			m_pMap->SetClearCount( m_clearCount);
		}

		//�i�s�����̊Ǘ�
		//�i��
		//�ҋ@��ԂŁ��������ꂽ��	
		if( CScene::m_keyStatePush ==  RIGHT && m_pMap->GetMapPointer()->GetState() == CGameMapPointer::STATE_WAIT){
			m_pMap->GetMapPointer()->SetMoveDirection(CGameMapPointer::STATE_MOVE_RIGHT);
			m_pMap->SetNextPosition(m_pGameData->m_selectStageNum,CGameMapPointer::STATE_MOVE_RIGHT);
		}
		//�߂�
		//�ҋ@��ԂŁ��������ꂽ��
		if( CScene::m_keyStatePush ==  LEFT && m_pMap->GetMapPointer()->GetState() == CGameMapPointer::STATE_WAIT){
			m_pMap->GetMapPointer()->SetMoveDirection(CGameMapPointer::STATE_MOVE_LEFT);
			m_pMap->SetNextPosition(m_pGameData->m_selectStageNum,CGameMapPointer::STATE_MOVE_LEFT);
		}
	}

	return SCENE_GAME;
}
void CPrepareMission::Draw()
{
	// �X�e�[�W
	m_pMap->Draw();

	
	// ���j���o�[
	m_menuBar[BAR]->Draw(m_state);

	//// �J�[�\��
	m_pCursor->Draw();
	// �����摜(��ʍ��チ�j���[���ډ摜)
	m_pPicChara[m_menuID]->Draw();
	switch( m_state ) {
	case STATE_STAGE_SELECT:
		m_menuBar[BAR_ICON]->Draw(m_state);
		for(int i = 0; i < TELOP_TYPE_NUM-1; i++){
			m_pTelop[i]->Draw();		// ���̉�ʂ̃e���b�v�̓��j���[��ʃN���X�̕��ŕ`��
		}
		break;
	case STATE_VIEW_STATUS:
	case STATE_CHANGE_ITEM:
	case STATE_CHARA_SELECT:
	case STATE_SHOP:
	case STATE_SAVE:
		m_menuBar[BAR_ICON]->Draw(m_state);
		m_pScreen->Draw();		// �e��ʂ̕`��
		break;
	default:
		m_menuBar[BAR_ICON]->Draw(m_state);
		break;
	}
	// �v���C����/�������̓e���b�v��`�悵�����
	m_pWindow->Draw();

}