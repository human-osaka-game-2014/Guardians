/*--------------------------------------------------------------

	処理内容:テロップ上にステージ名を描画
	作成者:三浦
	作成日:9/27
	更新日:9/27
	       10/11
	更新内容:
	   9/27  Drawの追加
	   10/11 テクスチャ座標の調整
	関数　
		コンストラクタの追加
		Control
		Draw
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

CGameStageTelop::CGameStageTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID) :
	CGameTelop( _pDevice, _position, 1280.f ) , m_stageID( _stageID)
{
	m_stageTex = CTexMgr.Get( TEX_FIELD_MENU );
}
CGameStageTelop::~CGameStageTelop()
{

}
void CGameStageTelop::Control()
{
	CGameTelop::Control();
}

void CGameStageTelop::Draw()
{
	CGameTelop::Draw();
//			m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y );
//			m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x+640.f, m_position.y ); // テクスチャの切り取り座標追加
	switch(m_stageID){ // ステージIDによってステージ名を変化させる
	case 0:
		m_vertex.DrawTextureLT( m_pDevice, m_stageTex, 730.f, 630.f, 500, 0, 954, 64 ); 
		break;

	default: // ステージ名追加されるとケースを増やしていく
		break;
	}
}