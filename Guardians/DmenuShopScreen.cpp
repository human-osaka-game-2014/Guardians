/*--------------------------------------------------------------

	処理内容: ショップ画面
	作成者:檀上
	作成日:9/24
	更新日:10/19
	更新内容:
	関数　
		
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"
/*--------------------------------------------------------------

	コンストラクタ

--------------------------------------------------------------*/
CMenuShopScreen::CMenuShopScreen(LPDIRECT3DDEVICE9 _pDevice,CGameData* _gameData) :
	CMenuScreen( _pDevice ) , m_drawID(0) ,m_oldID(0) , m_state(STATE_SELECT_SHOPMENU)
{
	m_equipID = 0;

	m_pGameData = _gameData;

	m_gameWindow = new CGameWindow*[WINDOW_TYPE_NUM];	// 種類分生成

	m_gameWindow[WND_SHOPMENU] = new CGameShopMenuWindow(m_pDevice,INIT_SHOPMENU_WINDOW_POSITION);
	m_gameWindow[WND_SHOPLIST] = NULL;

	m_gameCursor = new CGameCursor*[CURSOR_TYPE_NUM];	// 種類分生成

	m_gameCursor[CUR_MENU] = new CGameSelectCursor(m_pDevice, INIT_SHOP_CURSOR_POSITION,CGameSelectCursor::CUR_SHOP);		// ショップカテゴリ選択カーソル
	m_gameCursor[CUR_SHOP] = NULL;

	m_gameTelop = new CGameTelop*[TELOP_TYPE_NUM];
	m_gameTelop[TELOP_EXPLAIN] = NULL;
}
/*--------------------------------------------------------------

	デストラクタ

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

	制御

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
	// ショップメニュー(アイテムor装備)選択画面時
	case STATE_SELECT_SHOPMENU:
		switch(_keyState){
		case UP:
			m_equipID = (m_equipID + 2-1 ) % 2;
			m_gameCursor[CUR_MENU]->SetNextPosition(D3DXVECTOR2(INIT_SHOP_CURSOR_POSITION.x, INIT_SHOP_CURSOR_POSITION.y + m_equipID * (68.f)));
			//アイテム変更用カーソルの位置は初期位置に戻しておく
			m_drawID = 0;
			break;
		case DOWN:
			m_equipID = (m_equipID + 1) % 2;
			m_gameCursor[CUR_MENU]->SetNextPosition(D3DXVECTOR2(INIT_SHOP_CURSOR_POSITION.x, INIT_SHOP_CURSOR_POSITION.y + m_equipID * (68.f)));
			//アイテム変更用カーソルの位置は初期位置に戻しておく
			m_drawID = 0;
			break;
		case KEY_S:
			OpenWindow();	// アイテム選択ウインドウ生成
			dynamic_cast<CGameShopListWindow*>(m_gameWindow[WND_SHOPLIST])->SetSelectID( m_equipID );	// カーソルの位置をセット
			m_itemNum = (m_equipID == EQUIP ? m_pGameData->m_equipList.size() : m_pGameData->m_itemList.size());	//アイテムの個数を格納しておく
			m_oldID = m_equipID; 
			m_equipID = 0;
			m_state = STATE_WINDOW_SHOPLIST;	// 購入画面へ移行
		}
		break;
	// 購入画面時
	case STATE_WINDOW_SHOPLIST:
		switch( _keyState ){	
		case UP:
			// カーソルの移動処理
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
			// カーソルの移動処理
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
				//購入できる場合は所持金を減らして所持道具を増やす
				Search(m_oldID,m_equipID);
				//アイテム変更用カーソルの位置は初期位置に戻しておく
				m_drawID = 0;
				m_equipID = m_oldID;
				m_state = STATE_SELECT_SHOPMENU;
				DeleteWindow();
			}else{
				//お金が足りていない場合
			}
			break;
		case KEY_A:
			// 購入画面のウインドウを削除
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

	描画

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

	購入したいアイテムを所持しているか調べる
	@param int	選択した項目(アイテムor装備)
	@param int  調べたいアイテムのナンバー
	@return		なし

---------------------------------------------------*/
void CMenuShopScreen::Search(int _oldID,int _No)
{
	bool isFound = false;

	if( _oldID == TOOLS ){
		// 道具リストから検索
		for(unsigned int i = 0; i < m_pGameData->m_hasTools.size() ;i++){
			if(m_pGameData->m_hasTools[i].no == m_pGameData->m_itemList[_No].no){
				// 最大所持数未満なら所持数を増やす
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
		// 装備リストからサーチ
		for(unsigned int i = 0; i < m_pGameData->m_hasEquip.size() ;i++){
			if(m_pGameData->m_hasEquip[i].no == m_pGameData->m_equipList[_No].no){
				// 最大所持数未満なら所持数を増やす
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
	// 所持金を減らす
	m_pGameData->m_money -= (m_oldID == TOOLS ? m_pGameData->m_itemList[m_equipID].price :  m_pGameData->m_equipList[m_equipID].price);

}
/* --------------------------------------------------

	購入画面ウインドウの生成
	@param		なし
	@return		なし

---------------------------------------------------*/
void CMenuShopScreen::OpenWindow()
{
	m_gameCursor[CUR_SHOP] = new CGameItemCursor(m_pDevice,INIT_SHOPLIST_CURSOR_POSITION,CGameItemCursor::CUR_SHOP );
	m_gameWindow[WND_SHOPLIST] = new CGameShopListWindow(m_pDevice,D3DXVECTOR2(410.f+370.f,65.f+292.5f),m_pGameData,CGameWindow::EQUIP);
	m_gameTelop[TELOP_EXPLAIN] = new CGameExplainTelop(m_pDevice,INIT_EXPLAIN_TELOP_POSITION,m_pGameData);
}
/* --------------------------------------------------

	購入画面ウインドウの削除
	@param	なし
	@return なし

---------------------------------------------------*/
void CMenuShopScreen::DeleteWindow()
{
	SAFE_DELETE(m_gameCursor[CUR_SHOP]);
	SAFE_DELETE(m_gameWindow[WND_SHOPLIST]);
	SAFE_DELETE(m_gameTelop[TELOP_EXPLAIN]);
}