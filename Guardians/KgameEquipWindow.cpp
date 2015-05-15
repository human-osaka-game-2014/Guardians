#include "stdafx.h"
/* 定数 */



/*--------------------------------------------------------------

	処理内容:装備や道具,仕切りの描画
	作成者:岸
	作成日:10/05
	更新日:11/08
	更新内容
	フォントの位置の修正
	アイコンの追加
	関数　
		drawの作成
	変数　
		追加なし

--------------------------------------------------------------*/

/*--------------------------------------------------------------

	コンストラクタ(デバイス、座標、ゲームデータ、メニューIDをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス
	@param D3DXVECTOR2			描画する位置(x,y)
	@param CGameData			ゲームデータの参照
	@param int　menu			使用するメニューID

--------------------------------------------------------------*/
CGameEquipWindow::CGameEquipWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID) :
	CGameWindow(_pDevice, _position, _menuID == 1 ?static_cast<float>(MAX_WIDTH_CHARA) :static_cast<float>(MAX_WIDTH_STATUS), _menuID == 1 ? static_cast<float>(MAX_HEIGHT_CHARA) :static_cast<float>(MAX_HEIGHT_STATUS))
	,m_pGameData( _pGameData ),m_charaID(0)
{

	m_textureicon[0]=CTexMgr.Get(TEX_EQUIP_ICON );
	m_textureicon[1]=CTexMgr.Get(TEX_ITEM_ICON );

}
CGameEquipWindow::~CGameEquipWindow()
{

}



void CGameEquipWindow::Control()
{
	CGameWindow::Control();
}

void CGameEquipWindow::Draw()
{

	CGameWindow::Draw();
	
	CGameWindow::SetGameData(m_pGameData);
		
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-233, m_position.y-193,0,460,127,492);										//装備の表示
	
	for (int i=1;i<=2;i++){
		CStringList::numberStrList[i]->Draw(m_position.x-135, m_position.y-182+70*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[i]->getLength());		//数字の表示
		CStringList::numberStrList[10]->Draw(m_position.x-110, m_position.y-182+68*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[10]->getLength());	//:の表示
	}	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280,	 m_position.y-55,0,272,280,274);										//仕切りの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x,		 m_position.y-55,520,272,800,274);										//仕切りの表示
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-230,	 m_position.y-15,128,460,256,492);									//道具の表示
	for (int i=1;i<=4;i++){
		CStringList::numberStrList[i]->Draw(m_position.x-130, m_position.y+54*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[i]->getLength());			//数字の表示
		CStringList::numberStrList[10]->Draw(m_position.x-105, m_position.y+54*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[10]->getLength());		//:の表示
	}
	/*装備の表示*/
	// 1番目の装備の表示
	// Sarch関数で配列番号を取得
	for( int i = 0, no; i < 2; i++ ) {
		no =  Search(m_pGameData->m_chara[m_charaID].equip[i].no,TYPE_EQUIP);

		// 描画座標に格納
		float drawPosX = m_position.x-40, drawPosY = m_position.y-180 + i*66;

		// 検索にひっかからなかったら「なし」そうでなければ「装備名」を表示
		if( no == -1 ) {
			CStringList::m_none->Draw(drawPosX, drawPosY, CStringList::m_none->getLength());
		} else {
			CStringList::equipStrList[ no ]->Draw(drawPosX, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::equipStrList[ no ]->getLength());
			//腕輪系アイコンの表示
			if(no<3)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
			//ロープ系のアイコンの表示
			else if(2<no&&no<6)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-3),0,200+40*static_cast<float>(no-3),40);
			//靴系アイコンの表示
			else if(5<no&&no<9)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no-6),40,40+40*static_cast<float>(no-6),80);
			//帯系のアイコンの表示
			else if(8<no&&no<11)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-9),40,200+40*static_cast<float>(no-9),80);
			//魔力器系アイコンの表示
			else if(10<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no-11),80,40+40*static_cast<float>(no-11),120);
			//特殊系のアイコンの表示
			else if(13<no&&no<16)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-14),80,200+40*static_cast<float>(no-14),120);
		}
	}
	/*道具の表示*/
	for(int i = 0, no; i < 4; i++){
		no = Search(m_pGameData->m_tools[i].no,TYPE_ITEM);

		// 描画座標に格納
		float drawPosX = m_position.x-30, drawPosY = m_position.y+(55*i);
		// 検索にひっかからなかったら「なし」そうでなければ「アイテム名」を表示
		if( no == -1 ) {
			CStringList::m_none->Draw(drawPosX, drawPosY, CStringList::m_none->getLength());
		} else {
			CStringList::itemStrList[ no ]->Draw(drawPosX, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::itemStrList[ no ]->getLength());	
			//宝珠系アイコン
			if(no<7)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], drawPosX-60,drawPosY-18,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
			//護符,魔術書系アイコン
			else if(6<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], drawPosX-60,drawPosY-18,0+40*static_cast<float>(no-7),40,40+40*static_cast<float>(no-7),80);
			// 「×」と「何個」の表示のため座標移動
			drawPosX = m_position.x+157;

			CStringList::numberStrList[11]->Draw(drawPosX, drawPosY, CStringList::numberStrList[11]->getLength());
			CStringList::numberStrList[ m_pGameData->m_tools[i].nums ]->Draw(drawPosX+22, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ m_pGameData->m_tools[i].nums ]->getLength());
		}
	}

}
void CGameEquipWindow::SetSelectEquipID(int _selectEquipID)// 選択されている装備のIDをセット
{
	m_selectEquipID =_selectEquipID;
};											
void CGameEquipWindow::SetCharaID(int _charaID)
{
	m_charaID = _charaID;								// 選択されているキャラのIDをセット
};