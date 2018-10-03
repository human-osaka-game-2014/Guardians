/*--------------------------------------------------------------

	�������e: �V���b�v���
	�쐬��:�h��
	�쐬��:9/24
	�X�V��:10/19
	�X�V���e:
	�֐��@
		
	�ϐ��@

--------------------------------------------------------------*/

#include "stdafx.h"
/*--------------------------------------------------------------

	�R���X�g���N�^

--------------------------------------------------------------*/
CMenuShopScreen::CMenuShopScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData) :
	CMenuScreen( _pDevice ) , m_drawID(0) ,m_oldID(0) , m_state(STATE_SELECT_SHOPMENU)
{
	m_equipID = 0;

	m_pGameData = _gameData;

	m_gameWindow = new CGameWindow*[WINDOW_TYPE_NUM];	// ��ޕ�����

	m_gameWindow[WND_SHOPMENU] = new CGameShopMenuWindow(m_pDevice,INIT_SHOPMENU_WINDOW_POSITION);
	m_gameWindow[WND_SHOPLIST] = NULL;

	m_gameCursor = new CGameCursor*[CURSOR_TYPE_NUM];	// ��ޕ�����

	m_gameCursor[CUR_MENU] = new CGameSelectCursor(m_pDevice, INIT_SHOP_CURSOR_POSITION,CGameSelectCursor::CUR_SHOP);		// �V���b�v�J�e�S���I���J�[�\��
	m_gameCursor[CUR_SHOP] = NULL;

	m_gameTelop = new CGameTelop*[TELOP_TYPE_NUM];
	m_gameTelop[TELOP_EXPLAIN] = NULL;
}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CMenuShopScreen::~CMenuShopScreen()
{

	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameWindow[i]);
	}
	SAFE_DELETE_ARRAY(m_gameWindow);
	
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		SAFE_DELETE(m_gameCursor[i]);
	}
	SAFE_DELETE_ARRAY(m_gameCursor);

	SAFE_DELETE(m_gameTelop[0]);
	
	SAFE_DELETE_ARRAY(m_gameTelop);
}
/*--------------------------------------------------------------

	����

--------------------------------------------------------------*/
void CMenuShopScreen::Control(int _keyState)
{
	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		if( m_gameWindow[i] == NULL ) continue ;
		m_gameWindow[i]->Control();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue ;
		m_gameCursor[i]->Control();
	}
	switch( m_state ){
	// �V���b�v���j���[(�A�C�e��or����)�I����ʎ�
	case STATE_SELECT_SHOPMENU:
		switch(_keyState){
		case UP:
			m_equipID = (m_equipID + 2-1 ) % 2;
			m_gameCursor[CUR_MENU]->SetNextPosition(D3DXVECTOR2(INIT_SHOP_CURSOR_POSITION.x, INIT_SHOP_CURSOR_POSITION.y + m_equipID * (68.f)));
			//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂��Ă���
			m_drawID = 0;
			break;
		case DOWN:
			m_equipID = (m_equipID + 1) % 2;
			m_gameCursor[CUR_MENU]->SetNextPosition(D3DXVECTOR2(INIT_SHOP_CURSOR_POSITION.x, INIT_SHOP_CURSOR_POSITION.y + m_equipID * (68.f)));
			//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂��Ă���
			m_drawID = 0;
			break;
		case KEY_S:
			OpenWindow();	// �A�C�e���I���E�C���h�E����
			dynamic_cast<CGameShopListWindow*>(m_gameWindow[WND_SHOPLIST])->SetSelectID( m_equipID );	// �J�[�\���̈ʒu���Z�b�g
			m_itemNum = (m_equipID == EQUIP ? m_pGameData->m_equipList.size() : m_pGameData->m_itemList.size());	//�A�C�e���̌����i�[���Ă���
			m_oldID = m_equipID; 
			m_equipID = 0;
			m_state = STATE_WINDOW_SHOPLIST;	// �w����ʂֈڍs
		}
		break;
	// �w����ʎ�
	case STATE_WINDOW_SHOPLIST:
		switch( _keyState ){	
		case UP:
			// �J�[�\���̈ړ�����
			if( m_itemNum == 0 ) return;
			m_equipID = (m_equipID + m_itemNum-1 ) % m_itemNum;
			m_drawID--;

			if( m_itemNum > 8 ) {
				if( m_drawID <= 0 && m_equipID != m_itemNum-1 ) m_drawID = 0;
				else if( m_drawID < 0 ) m_drawID = m_itemNum >= 9 ? 8 : m_itemNum-1;
			} 
			else m_drawID = m_equipID;
			
			m_gameCursor[CUR_SHOP]->SetNextPosition(D3DXVECTOR2(INIT_SHOPLIST_CURSOR_POSITION.x,INIT_SHOPLIST_CURSOR_POSITION.y + m_drawID * (54.f)));
			break;
		case DOWN:
			// �J�[�\���̈ړ�����
			m_equipID = (m_equipID + m_itemNum+1 ) % m_itemNum;
			m_drawID++;
			if( m_itemNum > 8 ) {
				if( m_drawID >= 8 && m_equipID != 0 )  m_drawID = 8;
				else if( m_drawID > 8 ) m_drawID = m_itemNum <= m_equipID ? 8 : 0;
			} 
			else m_drawID = m_equipID;
			m_gameCursor[CUR_SHOP]->SetNextPosition(D3DXVECTOR2(INIT_SHOPLIST_CURSOR_POSITION.x,INIT_SHOPLIST_CURSOR_POSITION.y + m_drawID * (54.f)));
			break;
		case KEY_S:
			if( m_pGameData->m_money >= (m_oldID == 0 ? m_pGameData->m_itemList[m_equipID].price :  m_pGameData->m_equipList[m_equipID].price) ){
				//�w���ł���ꍇ�͏����������炵�ď�������𑝂₷
				Search(m_oldID,m_equipID);
				//�A�C�e���ύX�p�J�[�\���̈ʒu�͏����ʒu�ɖ߂��Ă���
				m_drawID = 0;
				m_equipID = m_oldID;
				m_state = STATE_SELECT_SHOPMENU;
				DeleteWindow();
			}else{
				//����������Ă��Ȃ��ꍇ
			}
			break;
		case KEY_A:
			// �w����ʂ̃E�C���h�E���폜
			DeleteWindow();
			m_drawID = 0;
			m_equipID = m_oldID;
			m_state = STATE_SELECT_SHOPMENU;
			break;
		}
	}
	if( m_gameWindow[WND_SHOPLIST] != NULL )
		dynamic_cast<CGameShopListWindow*>(m_gameWindow[WND_SHOPLIST])->SetCursorPosition( m_equipID );
}
/*--------------------------------------------------------------

	�`��

--------------------------------------------------------------*/
void CMenuShopScreen::Draw()
{
	if( m_gameTelop[TELOP_EXPLAIN] != NULL )
		dynamic_cast<CGameExplainTelop*>(m_gameTelop[TELOP_EXPLAIN])->Draw( m_oldID == 1 ? m_pGameData->m_equipList[m_equipID].no : m_pGameData->m_itemList[m_equipID].no);

	for( int i = 0; i < WINDOW_TYPE_NUM; i++ ) {
		if( m_gameWindow[i] == NULL ) continue ;
		m_gameWindow[i]->Draw();
	}
	for( int i = 0; i < CURSOR_TYPE_NUM; i++ ) {
		if( m_gameCursor[i] == NULL ) continue ;
		m_gameCursor[i]->Draw();
	}
}
/* --------------------------------------------------

	�w���������A�C�e�����������Ă��邩���ׂ�
	@param int	�I����������(�A�C�e��or����)
	@param int  ���ׂ����A�C�e���̃i���o�[
	@return		�Ȃ�

---------------------------------------------------*/
void CMenuShopScreen::Search(int _oldID,int _No)
{
	bool isFound = false;

	if( _oldID == TOOLS ){
		// ����X�g���猟��
		for(unsigned int i = 0; i < m_pGameData->m_hasTools.size() ;i++){
			if(m_pGameData->m_hasTools[i].no == m_pGameData->m_itemList[_No].no){
				// �ő及���������Ȃ珊�����𑝂₷
				if( m_pGameData->m_hasTools[i].nums < MAX_POSSESSION ){ 
					m_pGameData->m_hasTools[i].nums++;
					isFound = true;
					break;
				}else
					return;
			}
		}
		if( !isFound ){
			CGameData::HaveTool tmp;
			tmp.nums = 1;
			tmp.no = m_pGameData->m_itemList[_No].no;
			strcpy_s(tmp.explainStr,m_pGameData->m_itemList[_No].explainStr);
			m_pGameData->m_hasTools.push_back(tmp);
		}
	}else if( _oldID == EQUIP ){
		// �������X�g����T�[�`
		for(unsigned int i = 0; i < m_pGameData->m_hasEquip.size() ;i++){
			if(m_pGameData->m_hasEquip[i].no == m_pGameData->m_equipList[_No].no){
				// �ő及���������Ȃ珊�����𑝂₷
				if( m_pGameData->m_hasEquip[i].nums < MAX_POSSESSION ){
					m_pGameData->m_hasEquip[i].nums++;
					isFound = true;
					break;
				}
				else 
					return;
			}
		}
		if( !isFound )
			m_pGameData->m_hasEquip.push_back(m_pGameData->m_equipList[_No]);
	}
	// �����������炷
	m_pGameData->m_money -= (m_oldID == TOOLS ? m_pGameData->m_itemList[m_equipID].price :  m_pGameData->m_equipList[m_equipID].price);

}
/* --------------------------------------------------

	�w����ʃE�C���h�E�̐���
	@param		�Ȃ�
	@return		�Ȃ�

---------------------------------------------------*/
void CMenuShopScreen::OpenWindow()
{
	m_gameCursor[CUR_SHOP] = new CGameItemCursor(m_pDevice,INIT_SHOPLIST_CURSOR_POSITION,CGameItemCursor::CUR_SHOP );
	m_gameWindow[WND_SHOPLIST] = new CGameShopListWindow(m_pDevice,D3DXVECTOR2(410.f+370.f,65.f+292.5f),m_pGameData,CGameWindow::EQUIP);
	m_gameTelop[TELOP_EXPLAIN] = new CGameExplainTelop(m_pDevice,INIT_EXPLAIN_TELOP_POSITION,m_pGameData);
}
/* --------------------------------------------------

	�w����ʃE�C���h�E�̍폜
	@param	�Ȃ�
	@return �Ȃ�

---------------------------------------------------*/
void CMenuShopScreen::DeleteWindow()
{
	SAFE_DELETE(m_gameCursor[CUR_SHOP]);
	SAFE_DELETE(m_gameWindow[WND_SHOPLIST]);
	SAFE_DELETE(m_gameTelop[TELOP_EXPLAIN]);
}