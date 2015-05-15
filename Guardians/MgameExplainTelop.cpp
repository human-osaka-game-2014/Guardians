/*--------------------------------------------------------------

	処理内容:装備などの情報をテロップ上に描画
	作成者:三浦
	作成日:9/27
	更新日:9/27
	更新内容:
	   9/27     Draw追加
	関数　
		コンストラクタの追加
		Control
		Draw
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

CGameExplainTelop::CGameExplainTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CGameData* _pGameData) :
	CGameTelop(_pDevice, _position, 1280.f), m_toolID( 0 ),m_pGameData(_pGameData)
{

}
CGameExplainTelop::~CGameExplainTelop()
{

}
void CGameExplainTelop::Control()
{
	CGameTelop::Control();
}

void CGameExplainTelop::Draw( int _no )
{
	CGameTelop::Draw();

	if( _no != -1 ) {
		int no = Search( _no );
		float size = CStringList::explainStrList[no].m_strLst->getWidth();
		CStringList::explainStrList[no].m_strLst->Draw(1250 - size, 680,D3DCOLOR_ARGB(255,255,255,255), CStringList::explainStrList[no].m_strLst->getLength()); 
	}
}
int CGameExplainTelop::Search(int _No)
{
	for(unsigned int i = 0; i < CStringList::explainStrList.size();i++){
		if( _No == CStringList::explainStrList[i].No){
			return i;
		}
	}
	return -1;
}
