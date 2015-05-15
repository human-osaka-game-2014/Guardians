/*--------------------------------------------------------------

	処理内容:テロップの描画
	作成者:三浦
	作成日:9/27
	更新日:9/27
	更新内容:
		9/27     Draw追加
		10/11　　ヘッダーのControl,Drawをvirtualで宣言
	関数　
		コンストラクタの追加
		Control
		Draw
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

CGameTelop::CGameTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth) : 
	m_pDevice( _pDevice ), m_position( _position ), m_maxWidth( _maxWidth )
{
	m_tex = CTexMgr.Get( TEX_TELOP );
}
void CGameTelop::Draw()
{
	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x, m_position.y, 0, 0, 604, 100 );
		m_vertex.SetSizeX(1.1f);
	m_vertex.DrawTextureLT( m_pDevice, m_tex, m_position.x+604.f, m_position.y, 0, 101, 604, 200 );
		m_vertex.SetSizeX(1.0f);
}