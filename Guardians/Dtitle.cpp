#include "stdafx.h"

CTitle::CTitle(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_alpha(255),m_addAlpha(255 / 240),m_nextPosition(100),m_state(STATE_WAIT),m_timeCount(0),m_sceneChange(false)
{
	m_texture = CTexMgr.Get(0);
	m_position = D3DXVECTOR2(400.f,200.f);

	SetMovement();
}
CTitle::~CTitle()
{

}
void CTitle::Control(int _skipFlag)
{
	if ( m_state != STATE_TRANSITION && _skipFlag ){
		m_position.y = m_nextPosition;
		m_state = STATE_MOVE_END;
	}
	switch(m_state){
	case STATE_MOVE:
		m_position.y += m_move;
		if( fabs(m_position.y - m_nextPosition) <= 0.1f ) {
			m_position.y = ROUND_OFF(m_position.y);
			m_state = STATE_MOVE_END;
		}
		break;
	case STATE_WAIT:
		m_timeCount++;
		if( m_timeCount == 120 ) m_state = STATE_MOVE;
		break;
	case STATE_MOVE_END:
		break;
	}
}
void CTitle::SetMovement()
{
	// ˆê‰ñ‚ÌˆÚ“®—Ê
	m_move = (m_nextPosition - m_position.y) / MOVE_TIME;
}
void CTitle::Draw( )
{
	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
	if( CScene::m_keyStatePush == KEY_Z ){
		m_sceneChange = true;
		m_state = STATE_TRANSITION;
	}
	//if( m_sceneChange ) {
	//	m_vertex.DrawTexture( m_pDevice,m_position.x,m_position.y,D3DCOLOR_ARGB(0,0,0,0) );
	//	m_alpha -= 2;
	//	if( m_alpha <= 0 ) {
	//		m_alpha = 0;
	//		m_state = STATE_TRANSITION;
	//	}
	//}
}
CTitle::State CTitle::GetState()
{
	return m_state;
}

void CTitle::SetState(State _state)
{
	m_state = _state;
	if( m_state == STATE_MOVE_END ) {
		m_position.y = m_nextPosition;
	}
}