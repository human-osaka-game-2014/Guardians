/**
 * @file DmenuStatusScreen.cpp
 */
#include "stdafx.h"

CMenuStatusScreen::CMenuStatusScreen(LPDIRECT3DDEVICE9 _pDevice, CGameData* _gameData) :
	CMenuScreen( _pDevice ), m_charaID( 0 ), m_changeID( 0 ),m_equipPos( INIT_EQUIP_CURSOR_POSITION.y ),
	m_state( STATE_SELECT), m_drawID( 0 )
{
	m_pGameData = _gameData;

	m_gameWindow = new CGameWindow*[WINDOW_TYPE_NUM];	// ��ޕ�����

	m_gameWindow[WND_STATUS] = new CGameStatusWindow(m_pDevice, INIT_STATUS_WINDOW_POSITION, m_pGameData);		// �X�e�[�^�X�E�B���h�E
	m_gameWindow[WND_EQUIP] = new CGameEquipWindow(m_pDevice, INIT_EQUIP_WINDOW_POSITION, m_pGameData, 2);	// �����E�B���h�E
	m_gameWindow[WND_THING] = NULL;	
	// �������̃E�B���h�E�͍ŏ��͑��݂��Ȃ�

	m_gameCursor = new CGameCursor*[CURSOR_TYPE_NUM];	// ��ޕ�����

	m_gameCursor[CUR_CHARA] = new CGameCharaCursor(m_pDevice, INIT_CHARA_CURSOR_POSITION);					// �L�����I���J�[�\��
	m_gameCursor[CUR_EQUIP] = new CGameItemCursor(m_pDevice, INIT_EQUIP_CURSOR_POSITION,CGameItemCursor::CUR_EQUIP);		// ����/����I���J�[�\��
	m_gameCursor[CUR_CHANGE] = NULL;				// �������I���J�[�\���͍ŏ��͑��݂��Ȃ�

	m_gameTelop = new CGameTelop*[TELOP_TYPE_NUM];			// �e���b�v

	m_gameTelop[TELOP_CHARA] = new CGameCharaTelop(m_pDevice, INIT_CHARA_TELOP_POSITION,m_pGameData,0);	// �L�����摜
	m_gameTelop[TELOP_EXPLAIN] = new CGameExplainTelop(m_pDevice,INIT_EXPLAIN_TELOP_POSITION,m_pGameData);
}
CMenuStatusScreen::~CMenuStatusScreen()
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

void CMenuStatusScreen::Control(int _keyState)
{	
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		if( m_gameWindow[i] == NULL ) continue ;
		m_gameWindow[i]->Control();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue ;
		m_gameCursor[i]->Control();
	}

	if( m_gameWindow[WND_EQUIP]->Get() != CGameWindow::STATE_WAIT ) return ;

	if( m_gameWindow[WND_THING] != NULL )
		dynamic_cast<CGameThingsWindow*>(m_gameWindow[WND_THING])->SetCursorPosition( m_changeID );

	static const float EQUIP_CURSOR_SIZE = 68.f;
	static const float ITEM_CURSOR_SIZE = 54.f;
	switch( m_state ){
	// �L����/�����I�����
	case STATE_SELECT:
		switch(_keyState){
		case UP:
			// �J�[�\���̈ړ�
			m_equipID = (m_equipID + EQUIP_SELECT_NUM-1) % EQUIP_SELECT_NUM;
			if( m_equipID < 2 ){
				m_gameCursor[CUR_EQUIP]->SetNextPosition(D3DXVECTOR2(INIT_EQUIP_CURSOR_POSITION.x, INIT_EQUIP_CURSOR_POSITION.y + m_equipID * (EQUIP_CURSOR_SIZE)));
				m_equipPos = INIT_EQUIP_CURSOR_POSITION.y + m_equipID * (EQUIP_CURSOR_SIZE);			
			}else{
				m_gameCursor[CUR_EQUIP]->SetNextPosition(D3DXVECTOR2(INIT_ITEM_CURSOR_POSITION.x, INIT_ITEM_CURSOR_POSITION.y + (m_equipID-2) * (ITEM_CURSOR_SIZE)));
				m_equipPos = INIT_ITEM_CURSOR_POSITION.y + (m_equipID-2) * (ITEM_CURSOR_SIZE);
			}
			break;
		case DOWN:
			// �J�[�\���̈ړ�
			m_equipID = (m_equipID + +1) % EQUIP_SELECT_NUM;
			if( m_equipID < 2 ){	
				m_gameCursor[CUR_EQUIP]->SetNextPosition(D3DXVECTOR2(INIT_EQUIP_CURSOR_POSITION.x, INIT_EQUIP_CURSOR_POSITION.y + m_equipID * (EQUIP_CURSOR_SIZE)));
				m_equipPos = INIT_EQUIP_CURSOR_POSITION.y + m_equipID * (EQUIP_CURSOR_SIZE);
			}else{
				m_gameCursor[CUR_EQUIP]->SetNextPosition(D3DXVECTOR2(INIT_ITEM_CURSOR_POSITION.x, INIT_ITEM_CURSOR_POSITION.y + (m_equipID-2) * (ITEM_CURSOR_SIZE)));
				m_equipPos = INIT_ITEM_CURSOR_POSITION.y + (m_equipID-2) * (ITEM_CURSOR_SIZE);
			}
			break;
		case LEFT:
			// �J�[�\���̈ړ�
			m_charaID = (m_charaID+2) % PLAYER_MAX;
			m_gameCursor[CUR_CHARA]->SetNextPosition(D3DXVECTOR2(INIT_CHARA_CURSOR_POSITION.x + m_charaID * (128.f + 42.f), INIT_CHARA_CURSOR_POSITION.y));

			break;
		case RIGHT:
			// �J�[�\���̈ړ�
			m_charaID = (m_charaID+1) % PLAYER_MAX;
			m_gameCursor[CUR_CHARA]->SetNextPosition(D3DXVECTOR2(INIT_CHARA_CURSOR_POSITION.x + m_charaID * (128.f + 42.f), INIT_CHARA_CURSOR_POSITION.y));
			break;
		case KEY_S:
			m_gameWindow[WND_EQUIP]->SetNextPosition( D3DXVECTOR2( 640.f, 173+240+5.f ) );
			m_gameCursor[CUR_EQUIP]->SetNextPosition( D3DXVECTOR2( 400.f+115.f,m_equipPos) );
			m_gameWindow[WND_THING] = new CGameThingsWindow( m_pDevice, D3DXVECTOR2( 800.f+465.f/2, 160.f+500.f/2 ), m_pGameData,CGameWindow::EQUIP );
			m_gameCursor[CUR_CHANGE] = new CGameItemCursor( m_pDevice, INIT_CHANGE_CURSOR_POSITION,CGameItemCursor::CUR_ITEM);	
			dynamic_cast<CGameThingsWindow*>(m_gameWindow[WND_THING])->SetSelectID( m_equipID );
			m_itemNum = (m_equipID < 2 ? m_pGameData->m_hasEquip.size() : m_pGameData->m_hasTools.size());	//�A�C�e���̌����i�[���Ă���
			// �����ύX��Ԃ�
			m_state = STATE_CHANGE;
			break;
		}
		break;
	// �����ύX���
	case STATE_CHANGE:
		switch(_keyState){
		case UP:
			// �J�[�\���̈ړ�
			if( m_itemNum == 0 ) return;
			m_changeID = (m_changeID + m_itemNum-1 ) % m_itemNum;
			m_drawID--;

			if( m_itemNum > 8 ) {
				if( m_drawID <= 0 && m_changeID != m_itemNum-1 ) {
					m_drawID = 0;
				}
				else if( m_drawID < 0 ) {
					m_drawID = m_itemNum >= 9 ? 8 : m_itemNum-1;
				}
			} else {
				m_drawID = m_changeID;
			}

			m_gameCursor[CUR_CHANGE]->SetNextPosition(D3DXVECTOR2(INIT_CHANGE_CURSOR_POSITION.x,INIT_CHANGE_CURSOR_POSITION.y + m_drawID * (54.f)));

			break;
		case DOWN:
			// �J�[�\���̈ړ�
			if( m_itemNum == 0 ) return;
			m_changeID = (m_changeID+1) % m_itemNum;
			m_drawID++;
			if( m_itemNum > 7 ) {
				if( m_drawID >= 7 && m_changeID != 0 ) { m_drawID = 7; }
				else if( m_drawID > 7 ){
					m_drawID = m_itemNum <= m_changeID ? 7 : 0;
				}
			} else {
				m_drawID = m_changeID;
			}
			m_gameCursor[CUR_CHANGE]->SetNextPosition(D3DXVECTOR2(INIT_CHANGE_CURSOR_POSITION.x,INIT_CHANGE_CURSOR_POSITION.y + m_drawID * (54.f)));

			break;
		case KEY_A:
			SAFE_DELETE(m_gameCursor[CUR_CHANGE]);
			SAFE_DELETE(m_gameWindow[WND_THING]);
			//�E�C���h�E�͌��̈ʒu��
			m_gameWindow[WND_EQUIP]->SetNextPosition( INIT_EQUIP_WINDOW_POSITION );
			m_gameCursor[CUR_EQUIP]->SetNextPosition( D3DXVECTOR2( INIT_EQUIP_CURSOR_POSITION.x,m_equipPos) );
			//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂�
			m_drawID = 0;
			m_changeID = 0;
			m_state = STATE_SELECT;
			break;
		case KEY_S:
						// �A�C�e���ύX��ʂ̎��͑I������Ă���A�C�e����ύX���ăE�C���h�E�����ɖ߂�
			// �����ύX��Ԃ̃J�[�\�������������w���Ă��鎞�͑�����ύX
			if( m_equipID < 2 )	{
				// ���������Ȃ��̏ꍇ
				if( m_pGameData->m_hasEquip.empty() ) {
					if( m_pGameData->m_chara[m_charaID].equip[m_equipID].no != -1 ) { // �u�Ȃ��v�̏ꍇ�͏���
						m_pGameData->m_hasEquip.push_back( m_pGameData->m_chara[m_charaID].equip[m_equipID]);
						m_pGameData->m_chara[m_charaID].equip[m_equipID].no = -1;
					}
				}
				// 1�ȏ㑕��������ꍇ
				else {
					if( m_pGameData->m_chara[m_charaID].equip[m_equipID].no == -1 ) { // �u�Ȃ��v�̏ꍇ
						m_pGameData->m_chara[m_charaID].equip[m_equipID] = m_pGameData->m_hasEquip[m_changeID];	// �܂������������
						ChangeStatus(m_equipID,add);
						if( m_pGameData->m_hasEquip[m_changeID].nums == 1 ) { // �c��1�������珜�O
							std::vector<CGameData::Equip>::iterator it = m_pGameData->m_hasEquip.begin();
							for( unsigned i = 0; i < m_pGameData->m_hasEquip.size(); i++, it++ ) {
								if( i == m_changeID ) {
									m_pGameData->m_hasEquip.erase(it);
									break;
								}
							}
						} else m_pGameData->m_hasEquip[m_changeID].nums--;
					} else { // �������Z�b�g����Ă���ꍇ
						ChangeStatus(m_equipID,subtract);
						CGameData::Equip tmp = m_pGameData->m_chara[m_charaID].equip[m_equipID];

						// �܂����������������������X�g�ɂ��邩����
						unsigned i = 0;
						for( i = 0; i < m_pGameData->m_hasEquip.size(); i++ ) {
							if( m_pGameData->m_hasEquip[i].no == m_pGameData->m_chara[m_charaID].equip[m_equipID].no ) break;
						}
						if( i == m_pGameData->m_hasEquip.size() ) { // ������������Ȃ�����
							if( m_pGameData->m_hasEquip[m_changeID].nums == 1 ) { // 1�Ȃ����
								m_pGameData->m_chara[m_charaID].equip[m_equipID] = m_pGameData->m_hasEquip[m_changeID];
								m_pGameData->m_hasEquip[m_changeID] = tmp;
							} else {
								m_pGameData->m_hasEquip[m_changeID].nums--;	// �܂�1���炷
								m_pGameData->m_hasEquip.push_back(m_pGameData->m_chara[m_charaID].equip[m_equipID]); // �������Ă����������������X�g�Ɉڍs
								m_pGameData->m_chara[m_charaID].equip[m_equipID] = m_pGameData->m_hasEquip[m_changeID];
							}
						}
						else { // ��������������
							// ������������Ȃ����
							if( m_pGameData->m_hasEquip[m_changeID].no != m_pGameData->m_chara[m_charaID].equip[m_equipID].no )
							{
								m_pGameData->m_hasEquip[i].nums++;
								m_pGameData->m_chara[m_charaID].equip[m_equipID] = m_pGameData->m_hasEquip[m_changeID];
								if( m_pGameData->m_hasEquip[m_changeID].nums == 1 ) { // �c��1�������珜�O
									std::vector<CGameData::Equip>::iterator it = m_pGameData->m_hasEquip.begin();
									for( unsigned i = 0; i < m_pGameData->m_hasEquip.size(); i++, it++ ) {
										if( i == m_changeID ) {
											m_pGameData->m_hasEquip.erase(it);
											break;
										}
									}
								} else m_pGameData->m_hasEquip[m_changeID].nums--;
							}
						}
						ChangeStatus(m_equipID,add);
					}
				}
			}else{			// �A�C�e���ύX���Ȃ瑕���A�C�e����ύX
				// �A�C�e�������Ȃ��̏ꍇ
				if( m_pGameData->m_hasTools.empty() ) {
					if( m_pGameData->m_tools[m_equipID-2].no != -1 ) { // �u�Ȃ��v�̏ꍇ�͏���
						m_pGameData->m_hasTools.push_back( m_pGameData->m_tools[m_equipID-2] );
						m_pGameData->m_tools[m_equipID-2].no = -1;
					}
				}
				// 1�ȏ�A�C�e��������ꍇ
				else {
					if( m_pGameData->m_tools[m_equipID-2].no == -1 ) { // �u�Ȃ��v�̏ꍇ
						m_pGameData->m_tools[m_equipID-2] = m_pGameData->m_hasTools[m_changeID];
						// ���ꂽ���������O
						std::vector<CGameData::HaveTool>::iterator it = m_pGameData->m_hasTools.begin();
						for( unsigned i = 0; i < m_pGameData->m_hasTools.size(); i++, it++ ) {
							if( i == m_changeID ) {
								m_pGameData->m_hasTools.erase(it);
								break;
							}
						}
					} else { // �A�C�e�����Z�b�g����Ă���ꍇ
						CGameData::HaveTool tmp = m_pGameData->m_tools[ m_equipID - 2 ];
						m_pGameData->m_tools[ m_equipID - 2 ] = m_pGameData->m_hasTools[m_changeID];
						m_pGameData->m_hasTools[m_changeID] = tmp;
					}
				}
			}
			SAFE_DELETE(m_gameCursor[CUR_CHANGE]);
			SAFE_DELETE(m_gameWindow[WND_THING]);
			//�E�C���h�E�͌��̈ʒu��
			m_gameWindow[WND_EQUIP]->SetNextPosition( INIT_EQUIP_WINDOW_POSITION );
			m_gameCursor[CUR_EQUIP]->SetNextPosition( D3DXVECTOR2( INIT_EQUIP_CURSOR_POSITION.x,m_equipPos) );
			//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂��Ă���
			m_drawID = 0;
			m_changeID = 0;
			m_state = STATE_SELECT;
			break;
		}
	}
				//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂��Ă���
		//	m_drawID = 0;
	if( m_gameWindow[WND_THING] != NULL)
		dynamic_cast<CGameThingsWindow*>(m_gameWindow[WND_THING])->SetDrawID(m_drawID);
}
void CMenuStatusScreen::Draw()
{

	for( int i = 0; i < TELOP_TYPE_NUM-1; i++){
		m_gameTelop[i]->Draw();
	}
	if( m_equipID < 2 ){
		m_pGameData->m_chara[m_charaID].equip[m_equipID];	
	}
	int viewNo = -1;
	if( m_gameCursor[CUR_CHANGE] == NULL ) {
		if( m_equipID < 2 ) {
			viewNo = m_pGameData->m_chara[m_charaID].equip[m_equipID].no;
		} else {
			viewNo = m_pGameData->m_tools[m_equipID-2].no;
		}
	} else {
		if( m_equipID < 2 ) {
			viewNo = m_pGameData->m_hasEquip.size() == 0 ? -1 : m_pGameData->m_hasEquip[m_changeID].no;
		} else {
			viewNo = m_pGameData->m_hasTools.size() == 0 ? -1 : m_pGameData->m_hasTools[m_changeID].no;
		}
	}
	dynamic_cast<CGameExplainTelop*>(m_gameTelop[TELOP_EXPLAIN])->Draw( viewNo );

	dynamic_cast<CGameStatusWindow*>(m_gameWindow[WND_STATUS])->SetCharaID(m_charaID);
	dynamic_cast<CGameEquipWindow*>(m_gameWindow[WND_EQUIP])->SetCharaID(m_charaID);
	for( int i = 0; i < WINDOW_TYPE_NUM-1; i++ ) {
		m_gameWindow[i]->Draw();
	}

	m_gameCursor[CUR_CHARA]->Draw();

	dynamic_cast<CGameItemCursor*>( m_gameCursor[CUR_EQUIP])->Draw(m_equipID);
	// �����I���E�B���h�E�͑��̃E�B���h�E/�J�[�\�����O
	if( m_gameWindow[WND_THING] != NULL ) m_gameWindow[WND_THING]->Draw();
	// �����ύX�I���J�[�\���͑����I���E�B���h�E���O
	if( m_gameCursor[CUR_CHANGE] != NULL ) m_gameCursor[CUR_CHANGE]->Draw(); 

}
int CMenuStatusScreen::GetSelectID()
{
	return m_changeID;
}
void CMenuStatusScreen::ChangeStatus(int _equipID,ChangeType _type)
{
	int power;

	if( _type == add ) power = m_pGameData->m_chara[m_charaID].equip[_equipID].power;
	else power = - m_pGameData->m_chara[m_charaID].equip[_equipID].power;

	switch( m_pGameData->m_chara[m_charaID].equip[_equipID].stType ){
	case 0:
		m_pGameData->m_chara[m_charaID].hp += power;
		break;
	case 1:
		m_pGameData->m_chara[m_charaID].mp += power;
		break;
	case 2:
		m_pGameData->m_chara[m_charaID].atk += power;
		break;
	case 3:
		m_pGameData->m_chara[m_charaID].def += power;
		break;
	case 4:
		m_pGameData->m_chara[m_charaID].spd += power;
		break;
	case 5:
		m_pGameData->m_chara[m_charaID].ins += power;
		break;
	};
}