/*--------------------------------------------------------------

	処理内容:ボステロップの描画
	作成者:三浦
	作成日:9/27
	更新日:9/27
	更新内容:
	    9/27  Draw追加
		10/11 テクスチャ座標の調整
	関数　
		コンストラクタ
		Control
		Draw
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

CGameBossTelop::CGameBossTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID) :
	CGameTelop(_pDevice, _position, 640.f), m_stageID( _stageID )
{
	m_bossTex = CTexMgr.Get( TEX_BOSS );
}
CGameBossTelop::~CGameBossTelop()
{

}
void CGameBossTelop::Control()
{
	CGameTelop::Control();
}

void CGameBossTelop::Draw()
{
	CGameTelop::Draw();

//	m_vertex.SetSizeY(50.f);
//	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y, 0, 0, 300, 680 );  // テクスチャの切り取り座標追加

	switch( m_stageID ){
	case 0:
		m_vertex.SetSizeY(1.0f);
		m_vertex.SetSizeX(1.0f);
		m_vertex.DrawTextureLT( m_pDevice,  m_bossTex, m_position.x, m_position.y, 0 ,0, 300, 680 );
		m_vertex.SetSizeY(0.5f);
     	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x-310.f, m_position.y+510.f, 0, 0, 604, 100 );  // ボス名テロップ
		m_vertex.SetSizeY(1.0f);
		m_vertex.DrawTextureLT( m_pDevice, m_bossTex, m_position.x+15.f, m_position.y+520.f, 0, 680, 128, 712 );
		m_vertex.DrawTextureLT( m_pDevice, m_bossTex, m_position.x+145.f, m_position.y+520.f, 0, 713, 128, 746 );
		break;

	default:
		break;
	}
	//switch( m_stageID ){
	//case 0:
	//	m_vertex.SetSizeY(50.f);
	//	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x-310.f, m_position.y+510.f, 0, 0, 604, 100 );  // テクスチャの切り取り座標追加
	//	break;

	//default:
	//	break;
	//}
}
