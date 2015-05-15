#include "stdafx.h"
/*--------------------------------------------------------------

	処理内容:コンストラクタの宣言,アクセサリー、装備また装備の価格や個数の描画
	作成者:岸
	作成日:10/15
	更新日:10/22
	関数
		スクロールバーの修正　
		drawの作成
	変数　
		追加なし

--------------------------------------------------------------*/

CGameShopListWindow::CGameShopListWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type):
	CGameWindow(_pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT)),m_drawID(0)// コンストラクタ(デバイス、座標、ゲームデータ、選択されたタイプをセット
{
	m_pGameData=_pGameData;
	m_type=_type;
}
CGameShopListWindow::~CGameShopListWindow()
{

}
void CGameShopListWindow::Control()
{
	CGameWindow::Control();
}													
	
void CGameShopListWindow::Draw()
{
	CGameWindow::Draw();
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-370, m_position.y-240,0,272,370,274);						//仕切りの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-240,430,272,800,274);						//仕切りの表示
    CStringList::numberStrList[ 16 ]->Draw(m_position.x+20, m_position.y-260, D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 16 ]->getLength());	//金額表示
	CStringList::numberStrList[17]->Draw(m_position.x+155, m_position.y-260, D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[17]->getLength());  //所持数表示
	////アイテムリストを表示
	if(m_type == 0){     
		float size =  24.5f - (m_pGameData->m_itemList.size() - 9.f);	// バーの中身のサイズを決める(max - itemsize - 一度に表示する項目)
		float move = ((m_pGameData->m_itemList.size() - 9.f) * 16.f)  / (m_pGameData->m_itemList.size() - 9.f) ;	// 移動量を決める
		m_vertex.SetSizeY( size );
		if( 9 < m_pGameData->m_itemList.size() )	// 表示項目よりリストのアイテム数が多ければ描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+310, m_position.y-180 + (m_drawID * move),272,218,286,234); 
		m_vertex.SetSizeY(1.0f);
		// アイテムの描画位置を設定する
		if( CScene::m_keyStatePush == UP ){
			if( m_cursorPos > m_pGameData->m_itemList.size() -1 - 8 ) {
				if( m_drawID + 8 < m_cursorPos )
					m_drawID = m_pGameData->m_itemList.size() -1 - 8;
			}else{
				if( m_drawID > m_cursorPos )	m_drawID = m_cursorPos;
			}
		}else if( CScene::m_keyStatePush == DOWN){
			if( m_cursorPos < 9 ) {
				if( m_drawID + 8 < m_cursorPos || m_cursorPos == 0) m_drawID = 0;
			}else{
				if( m_drawID+9 <= m_cursorPos )	m_drawID = m_cursorPos - 8;
			}
		}
		//道具の描画
		for(int i=0;i<MAX_ITEM_NUMBER;i++){										//道具名表示
			CStringList::itemStrList[ i + m_drawID ]->Draw(m_position.x-290, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::itemStrList[ i + m_drawID ]->getLength()); 
			// 所持数の表示
			CStringList::numberStrList[ Sarch(0,i+m_drawID) ]->Draw(m_position.x+200, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ Sarch(0,i+m_drawID) ]->getLength());  						
			// 値段の表紙
			CStringList::itemPrice[ i + m_drawID ]->Draw(m_position.x, m_position.y-190+54*i,D3DCOLOR_ARGB(255,255,255,255), CStringList::itemPrice[ i + m_drawID ]->getLength()); 
		}

	}
//装備リストを表示
	 else {      
		 float size =  24.5f - (m_pGameData->m_equipList.size() - 9.f);	// バーの中身のサイズを決める(max - itemsize - 一度に表示する項目)
		float move = ((m_pGameData->m_equipList.size() - 9.f) * 16.f)  / (m_pGameData->m_equipList.size() - 9.f) ;	// 移動量を決める
	
		m_vertex.SetSizeY( size );
		if( 9 < m_pGameData->m_equipList.size() )	// 表示項目よりリストのアイテム数が多ければ描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+310, m_position.y-180 + (m_drawID * move),272,218,286,234); 
		m_vertex.SetSizeY(1.0f);

		if( CScene::m_keyStatePush == UP ){
			if( m_cursorPos > m_pGameData->m_equipList.size() -1 - 8 ) {
				if( m_drawID + 8 < m_cursorPos )
					m_drawID = m_pGameData->m_equipList.size() -1 - 8;
			}else{
				if( m_drawID > m_cursorPos ){
					m_drawID = m_cursorPos;
				}
			}
		}else if( CScene::m_keyStatePush == DOWN){
			if( m_cursorPos < 9 ) {
				if( m_drawID + 8 < m_cursorPos || m_cursorPos == 0)
					m_drawID = 0;
			}else{
				if( m_drawID+9 <= m_cursorPos ){
					 m_drawID = m_cursorPos - 8;
				}
			}
		}
		for(int i=0;i<MAX_ITEM_NUMBER;i++){										//装備名表示
			CStringList::equipStrList[ i+m_drawID ]->Draw(m_position.x-290, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::equipStrList[ i+m_drawID ]->getLength());  
			//装備の持っている数表示
			CStringList::numberStrList[ Sarch(1,i+m_drawID) ]->Draw(m_position.x+200, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ Sarch(1,i+m_drawID) ]->getLength());  						
			//装備の価格表示
			CStringList::equipPrice[ i+m_drawID ]->Draw(m_position.x, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::equipPrice[ i+m_drawID ]->getLength()); 
		}
	}
	float size =  (m_position.y + 189.5f) - (m_position.y - 230.5f);
	m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+290.f,m_position.y-232.5f,272,48,322,128);					//スクロールバーの表示(上)　　　
	for(int i=0;i<40;i++){
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+290.f,m_position.y-152.5f + ( 10*i ),272,128,322,138);		//スクロールバーの表示
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+290.f,m_position.y+189.f,272,138,322,218);					//スクロールバーの表示(下)
}						
void CGameShopListWindow::SetCursorPosition(int _pos)// 選択されている装備のIDをセット
{
	m_cursorPos =_pos;
}										
void CGameShopListWindow::SetSelectID(int _select)
{
	m_type = _select;								// 選択されているキャラのIDをセット
}
/* --------------------------------------------------
	描画したいアイテムを所持しているか調べる

---------------------------------------------------*/
int CGameShopListWindow::Sarch(int _oldID,int _No)
{
	if( _oldID == 0 ){
		for(unsigned int i = 0; i < m_pGameData->m_hasTools.size() ;i++){
			if(m_pGameData->m_hasTools[i].no == m_pGameData->m_itemList[_No].no){
				return m_pGameData->m_hasTools[i].nums;
			}
		}
	}else{
		for(unsigned int i = 0; i < m_pGameData->m_hasEquip.size() ;i++){
			if(m_pGameData->m_hasEquip[i].no == m_pGameData->m_equipList[ _No ].no){
				return m_pGameData->m_hasEquip[i].nums;
			}
		}
	}
	return 0;
}