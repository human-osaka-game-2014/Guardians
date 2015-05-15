/*--------------------------------------------------------------

	処理内容: チームロゴの制御
	作成者: 檀上
	作成日: 11/1
	更新日: 11/1
	更新内容:
		コンストラクタ
		フェードイン・フェードアウト
		描画処理
	変数　
		

--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	コンストラクタ(デバイスをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス

--------------------------------------------------------------*/
CLogo::CLogo(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_alpha( 0 ),m_fadeType(FADE_IN),m_addAlpha( 255 / 120),m_timeCount(0),m_transition(false)
{
	m_texture = CTexMgr.Get(0);
}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CLogo::~CLogo()
{

}	
/*--------------------------------------------------------------

	描画の制御　チームロゴのフェードイン・フェードアウト
	@param	なし
	@return なし 

--------------------------------------------------------------*/
void CLogo::Control()
{
	//点灯している状態ならalpha値を減らす
	if(m_fadeType == FADE_IN){
		m_alpha += m_addAlpha;
		if(m_alpha >= 255){
			m_alpha = 255;
			m_fadeType = FADE_STOP;
			m_timeCount = 0;
		}
	}

	if( m_fadeType == FADE_STOP ){
		m_timeCount++;
		if( m_timeCount == 120 )
			m_fadeType = FADE_OUT;
	}

	if(m_fadeType == FADE_OUT){
		m_alpha -= m_addAlpha;
		if(m_alpha <= 0){
			m_alpha = 0;
			m_fadeType = FADE_END;
			m_transition = true;

		}
	}
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし 

--------------------------------------------------------------*/
void CLogo::Draw()
{
	//m_vertex.DrawTexture( m_pDevice,100,0,D3DCOLOR_ARGB(m_alpha,255,255,255) );
	m_vertex.DrawTextureLT( m_pDevice,m_texture,200,-50,D3DCOLOR_ARGB(m_alpha,255,255,255) );
}
/*--------------------------------------------------------------

	シーンスキップフラグを返す
	@return シーン遷移フラグ 

--------------------------------------------------------------*/
bool CLogo::GetFlag()
{
	return m_transition;
}
