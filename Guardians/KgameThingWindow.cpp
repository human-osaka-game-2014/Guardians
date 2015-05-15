#include "stdafx.h"

/*--------------------------------------------------------------

	処理内容:スクロールバーの表示
	作成者:岸
	作成日:10/11
	更新日:11/08
	更新内容
	アイコンの追加
　　なしの表示
	関数　
		drawの作成
	変数　
		追加なし

--------------------------------------------------------------*/
CGameThingsWindow::CGameThingsWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type, int _charaID) :
	CGameWindow(_pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT)),m_pGameData(_pGameData) , m_cursorPos( 0 )
{
	m_textureicon[0]=CTexMgr.Get(TEX_EQUIP_ICON );
	m_textureicon[1]=CTexMgr.Get(TEX_ITEM_ICON );
	CGameWindow::SetGameData(m_pGameData);
}
CGameThingsWindow::~CGameThingsWindow()
{

}
void CGameThingsWindow::Control()
{
	CGameWindow::Control();
}	
void CGameThingsWindow::Draw()
{
	CGameWindow::Draw();

	int no; // サーチ後の結果格納用
	//装備所持リストを表示
	if(m_type < 2 ){
		unsigned i=0;
		do{		//所持装備品の表示
			if( m_pGameData->m_hasEquip.empty()  )  CStringList::m_none->Draw(m_position.x-155, m_position.y-180 + 54 * i, D3DCOLOR_ARGB(255,255,255,255), CStringList::m_none->getLength() );	
			else{
				if( m_cursorPos > 8 ) no = Search( m_pGameData->m_hasEquip[ i + ( m_cursorPos - 8) ].no,TYPE_EQUIP);
				else no = Search( m_pGameData->m_hasEquip[i].no,TYPE_EQUIP);
				CStringList::equipStrList[ no ]->Draw(m_position.x-125, m_position.y-180 + 54 * i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::equipStrList[ no ]->getLength());	
				//腕輪系アイコンの表示
				if(no<3)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], m_position.x-185,m_position.y-198 + 54 * i,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
				//ロープ系のアイコンの表示
				else if(2<no&&no<6)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0],m_position.x-185,m_position.y-198 + 54 * i,160+40*static_cast<float>(no-3),0,200+40*static_cast<float>(no-3),40);
				//靴系アイコンの表示
				else if(5<no&&no<9)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], m_position.x-185,m_position.y-198 + 54 * i,0+40*static_cast<float>(no-6),40,40+40*static_cast<float>(no-6),80);
				//帯系のアイコンの表示
				else if(8<no&&no<11)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], m_position.x-185,m_position.y-198 + 54 * i,160+40*static_cast<float>(no-9),40,200+40*static_cast<float>(no-9),80);
				//魔力器系アイコンの表示
				else if(10<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0],m_position.x-185,m_position.y-198 + 54 * i,0+40*static_cast<float>(no-11),80,40+40*static_cast<float>(no-11),120);
				//特殊系のアイコンの表示
				else if(13<no&&no<16)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0],m_position.x-185,m_position.y-198 + 54 * i,160+40*static_cast<float>(no-14),80,200+40*static_cast<float>(no-14),120);
				if( m_pGameData->m_hasEquip[ i ].no != -1 ){
					// ×の表示
					CStringList::numberStrList[ 11 ]->Draw(m_position.x+100, m_position.y-180+54*i,  D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ 11 ]->getLength());				
					// 個数の表示
					CStringList::numberStrList[ m_pGameData->m_hasEquip[ i ].nums ]->Draw(m_position.x+125, m_position.y-180+54*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[m_pGameData->m_hasEquip[ i ].nums ]->getLength());
				}
				i++;
			}
		}while(i < MAX_ITEM_NUMBER && i < m_pGameData->m_hasEquip.size() );
		// バーの中身のサイズを決める(max - itemsize - 一度に表示する項目)
		float size =  16.5f - (m_pGameData->m_hasEquip.size() - 8.f);	
		float move = ((m_pGameData->m_hasEquip.size() - 8.f) * 16.f)  / (m_pGameData->m_hasEquip.size() - 8.f) ;	// 移動量を決める 
		if( 9 < m_pGameData->m_hasEquip.size() ){	// 表示項目よりリストのアイテム数が多ければ描画
			m_vertex.SetSizeY( size );
			m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x + 170.f, m_position.y - 130.f + ( m_drawID * move ),272,218,286,234); 
			m_vertex.SetSizeY(1.0f);
		}
	}
	//道具所持リストを表示
	else if( m_type > 1){
		
		//所持道具の表示
		unsigned i=0;
		do{
			if( m_pGameData->m_hasTools.empty() ) CStringList::m_none->Draw(m_position.x-155, m_position.y-180 + 54 * i, D3DCOLOR_ARGB(255,255,255,255), CStringList::m_none->getLength() );
			else {
				if( m_cursorPos > 8 ) no = Search( m_pGameData->m_hasTools[ i + ( m_cursorPos - 8) ].no,TYPE_ITEM);
				else no = Search( m_pGameData->m_hasTools[i].no,TYPE_ITEM);
				if( no == -1 ) {
				} else {
					CStringList::itemStrList[ no ]->Draw(m_position.x-120,m_position.y-180 + 54 * i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::itemStrList[ no ]->getLength());
					// ×の表示
					CStringList::numberStrList[ 11 ]->Draw(m_position.x+100, m_position.y-180 + 54 * i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 11 ]->getLength());	                          //×の表示
					// 個数の表示
					CStringList::numberStrList[m_pGameData->m_hasTools[ i ].nums]->Draw(m_position.x+125,m_position.y-180 + 54 * i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ m_pGameData->m_hasTools[ i ].nums ]->getLength());
					//宝珠系アイコン
					if(no<7)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], m_position.x-185,m_position.y-198 + 54 * i,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
					//護符,魔術書系アイコン
					else if(6<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], m_position.x-185,m_position.y-198 + 54 * i,0+40*static_cast<float>(no-7),40,40+40*static_cast<float>(no-7),80);
				}
				i++;
			}
		}while(i < MAX_ITEM_NUMBER && i < m_pGameData->m_hasTools.size() );

		//所持道具の表示
	}	
	m_vertex.DrawTextureLT(m_pDevice, m_texture,static_cast<float>(m_position.x+152.5),static_cast<float>(m_position.y-190),272,48,322,128);					//スクロールバーの表示(上)　　　
	for(int i=0;i<22;i++){
		m_vertex.DrawTextureLT(m_pDevice, m_texture,static_cast<float>(m_position.x+152.5), static_cast<float>(m_position.y-110+10*i),272,128,322,138);			//スクロールバーの表示
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture,static_cast<float>(m_position.x+152.5),static_cast<float>(m_position.y+110),272,138,322,218);					//スクロールバーの表示(下)
}
void CGameThingsWindow::SetCursorPosition(int _pos)// 選択されている装備のIDをセット
{
	m_cursorPos =_pos;
}											
void CGameThingsWindow::SetSelectID(int _select)
{
	m_type = _select;								// 選択されているキャラのIDをセット
}
void CGameThingsWindow::SetDrawID(int _drawID)
{
	m_drawID = _drawID;
}
CGameData* CGameThingsWindow::GetGameData()
{
	return m_pGameData;
}