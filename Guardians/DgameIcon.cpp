#include "stdafx.h"

CGameIcon::CGameIcon(LPDIRECT3DDEVICE9 _pDevice,int _state) : CMenuBar(_pDevice)
{
	m_state = _state;

}
void CGameIcon::Draw(int _state)
{
	m_state = _state;
	m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_BAR],0,0,0,200,70,920);

	if( m_state < STATE_CHANGE_ITEM){
		m_state = m_oldState;
	}

	switch( m_state ){
	case STATE_STAGE_SELECT:
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],680,2,32,0,64,32);			// Bボタン
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,96,0,128,32);		// 十字
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,64,0,96,32);		// LT&RT
		CStringList::MenuStrList[PIC_TURN_NO]->Draw(730,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_TURN_NO]->getLength());
		CStringList::MenuStrList[PIC_STAGE_SELECT]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_STAGE_SELECT]->getLength());
		CStringList::MenuStrList[PIC_MENU]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_MENU]->getLength());
		m_oldState = m_state;
		break;
	case STATE_VIEW_STATUS:
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],680,2,32,0,64,32);			// Bボタン
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,96,0,128,32);		// 十字
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,64,0,96,32);		// LT&RT
		CStringList::MenuStrList[PIC_CHANGE_EQUIP]->Draw(730,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CHANGE_EQUIP]->getLength());
		CStringList::MenuStrList[PIC_CHARA_SELECT]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CHARA_SELECT]->getLength());				
		CStringList::MenuStrList[PIC_MENU]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_MENU]->getLength());
		m_oldState = m_state;
		break;
	case STATE_CHARA_SELECT:
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],680,2,32,0,64,32);
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,96,0,128,32);
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,0,0,32,32);			// Aボタン
		CStringList::MenuStrList[PIC_TURN_NO]->Draw(730,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_TURN_NO]->getLength());
		CStringList::MenuStrList[PIC_CHARA_SELECT]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CHARA_SELECT]->getLength());
		CStringList::MenuStrList[PIC_CANCEL]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CANCEL]->getLength());
		m_oldState = m_state;
		break;	
	case STATE_SHOP:
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,32,0,64,32);
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,64,0,96,32);
		CStringList::MenuStrList[PIC_BUY]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_BUY]->getLength());
		CStringList::MenuStrList[PIC_MENU]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_MENU]->getLength());
		m_oldState = m_state;
		break;
	case STATE_SAVE:
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],680,2,32,0,64,32);
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,96,0,128,32);
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,64,0,96,32);
		CStringList::MenuStrList[PIC_ENTER]->Draw(730,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_ENTER]->getLength());
		CStringList::MenuStrList[PIC_ITEM_SELECT]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_ITEM_SELECT]->getLength());
		CStringList::MenuStrList[PIC_MENU]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_MENU]->getLength());
		m_oldState = m_state;
		break;
	default:
		// アイテム変更画面
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],480,2,32,0,64,32);			// Bボタン
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],680,2,0,0,32,32);			// Aボタン
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],880,2,96,0,128,32);		// 十字
		m_vertex.DrawTextureLT(m_pDevice,m_texture[TEX_ICON],1080,2,64,0,96,32);		// LT&RT
		CStringList::MenuStrList[PIC_CHANGE_EQUIP]->Draw(530,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CHANGE_EQUIP]->getLength());
		CStringList::MenuStrList[PIC_CANCEL]->Draw(730,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CANCEL]->getLength());
		CStringList::MenuStrList[PIC_CHARA_SELECT]->Draw(930,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_CHARA_SELECT]->getLength());
		CStringList::MenuStrList[PIC_MENU]->Draw(1130,17,D3DCOLOR_ARGB(255,255,255,255),CStringList::MenuStrList[PIC_MENU]->getLength());
		m_oldState = m_state;
		break;
	}
}