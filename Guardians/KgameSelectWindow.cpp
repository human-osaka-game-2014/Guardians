/*--------------------------------------------------------------

	処理内容: 選択肢(はい、いいえ)用ウインドウの描画
	作成者: 檀上
	作成日:10/19
	関数　
		コンストラクタ
		デストラクタ
		Draw
		追加
	変数　
		

--------------------------------------------------------------*/
#include "stdafx.h"

const float CGameSelectWindow::MAX_WIDTH	= 384.f+160.f;
const float CGameSelectWindow::MAX_HEIGHT	= 320;
/*--------------------------------------------------------------

	コンストラクタ
	@param LPDIRECT3DDEVICE9	描画デバイス
	@param D3DXVECTOR2			描画位置
	@param int					描画するメッセージのID

--------------------------------------------------------------*/
CGameSelectWindow::CGameSelectWindow(LPDIRECT3DDEVICE9 _pDevice,D3DXVECTOR2 _position,int _id) : CGameWindow(_pDevice,_position,MAX_WIDTH,MAX_HEIGHT) , m_id(_id)
{

}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CGameSelectWindow::~CGameSelectWindow()
{

}
/*--------------------------------------------------------------

	制御
	@param		なし
	@return		なし

--------------------------------------------------------------*/
void CGameSelectWindow::Control()
{
	CGameWindow::Control();
}
/*--------------------------------------------------------------

	描画
	@param		なし
	@return		なし

--------------------------------------------------------------*/
void CGameSelectWindow::Draw()
{
	CGameWindow::Draw();

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-(MAX_WIDTH/2), m_position.y-(MAX_HEIGHT/2)+90,0,272,MAX_WIDTH/2,274);			//仕切りの描画
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-(MAX_HEIGHT/2)+90,800 - MAX_WIDTH/2,272,800,274);				//仕切りの描画	
	
	// メッセージの描画
	CStringList::MessageStrList[m_id]->Draw( m_position.x-(MAX_WIDTH/2)+160, m_position.y-(MAX_HEIGHT/2)+55, D3DCOLOR_ARGB(255,255,255,255), CStringList::MessageStrList[m_id]->getLength());
	
	// はい、いいえの描画
	for(int i = 2; i < 4;i++){
		CStringList::MessageStrList[i]->Draw( m_position.x-(MAX_WIDTH/2)+260 + ((i-2) * -12), m_position.y-(MAX_HEIGHT/2)+80 * i-2, D3DCOLOR_ARGB(255,255,255,255), CStringList::MessageStrList[i]->getLength());
	}
}