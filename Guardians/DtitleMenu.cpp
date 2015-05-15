/*-------------------------------------------------------------

	タイトルメニューの制御

	作成日  :2014/10/30
	作成者  : 檀上

	更新日  :
	更新者  :
	更新内容:	
---------------------------------------------------------------*/
#include "stdafx.h"

/*--------------------------------------------------------------

	コンストラクタ(デバイスをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス

--------------------------------------------------------------*/
CTitleMenu::CTitleMenu(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_alpha(0),m_addalpha(255/60),m_drawID(0),m_flg(false) ,m_size(1.0f),m_position(D3DXVECTOR2(550.f,400.f))
{
	m_texture = CTexMgr.Get(1);
}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CTitleMenu::~CTitleMenu()
{

}
/*--------------------------------------------------------------

	描画の制御
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CTitleMenu::Control()
{
	if( m_drawID == DRAW_PRESS ){
			//点灯している状態ならalpha値を減らす
			m_alpha += m_addalpha;
			if(m_alpha < 0)	{
				m_alpha = 0;
				m_addalpha = -(m_addalpha);
			}
			if(m_alpha > 255){
				m_alpha = 255;
				m_addalpha = -(m_addalpha);
			}
	}else{
		if(m_alpha < 255){
			m_alpha += m_addalpha;
			if(m_alpha >= 255){
				m_alpha = 255;
				m_drawID++;
				m_alpha = 0;
			}
		}
	}
}
/*--------------------------------------------------------------

	描画
	@param int	なし
	@param int	なし
	@return		なし

--------------------------------------------------------------*/
void CTitleMenu::Draw( int _selectID,int _skipFlag )
{
		switch( m_drawID ){
		case DRAW_START:
			m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,0,0,200,50,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
			break;
		//case DRAW_LOAD:
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,0,0,200,50,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+50,0,50,200,100,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
		//	break;
		//case DRAW_CONFIG:
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,0,0,200,50,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+50,0,50,200,100,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+100,0,100,200,150,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
		//	break;
		//case DRAW_EXIT:
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,0,0,200,50,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+50,0,50,200,100,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+100,0,100,200,150,D3DCOLOR_ARGB(255,255,255,255) );
		//	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+150,0,150,200,200,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
		//	break;
		case DRAW_PRESS:
			if( m_alpha == 255 ){
				m_flg = true;
			}
			if( m_flg ){
				if( m_size < 1.3f )	m_size += 0.01f;
				for(int i = 0; i < 1;i++){
					if( i == _selectID ) {
						m_vertex.SetSizeY(1.0f);
						m_vertex.SetSizeX(1.0f);
					}else { 
						m_vertex.SetSizeY(1.0f);
						m_vertex.SetSizeX(1.0f);
					}
					m_vertex.DrawTextureCC( m_pDevice,m_texture,m_position.x+100.f,m_position.y+25.f + 50.f*i,0.f,50.f*i,200.f,50.f*i+50.f,D3DCOLOR_ARGB(255,255,255,255) );
				}
			}
		m_vertex.SetSizeY(1.0f);
		m_vertex.SetSizeX(1.0f);
		m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y+200,0,200,200,250,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
		break;
	}
}
/*--------------------------------------------------------------

	描画IDをセット
	@param int	描画ID
	@return		なし

--------------------------------------------------------------*/
void CTitleMenu::SetDrawID(int _drawID)
{
	m_drawID = _drawID;
	m_alpha = 255;
}