#include "stdafx.h"

CTitleSelect::CTitleSelect(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_alpha(0),m_addalpha(255/60),m_drawID(0),m_flg(false) ,m_size(1.0f)
{
	m_texture = CTexMgr.Get(2);

	m_position.x = 550.f;
	m_position.y = 400.f;
}
CTitleSelect::~CTitleSelect()
{

}
void CTitleSelect::Control()
{
	if( m_drawID == DRAW_PRESS ){
			//ì_ìîÇµÇƒÇ¢ÇÈèÛë‘Ç»ÇÁalphaílÇå∏ÇÁÇ∑
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

				if( m_drawID == DRAW_PRESS ) {
					m_alpha = 255;
				}
			}
		}
	}
}
void CTitleSelect::Draw( int _selectID,int _skipFlag )
{
//	if( _skipFlag ) m_drawID = 4;
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
			break;
		case DRAW_PRESS:
			if( m_alpha == 255 ){
				m_flg = true;
			}
			if( m_flg ){
				if( m_size < 1.3f )	m_size += 0.01f;
				for(int i = 0; i < 4;i++){
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

void CTitleSelect::SetDrawID(int _drawID)
{
	m_drawID = _drawID;
	m_alpha = 255;
}