/**
 * @file DgameCursor.cpp
 */

#include "stdafx.h"
/* 定数 */
// 広がる際に変動しない部分のサイズ(隅１個分(24×24) 
const D3DXVECTOR2 CGameCursor::NOMOVE_PARTS_SIZE = D3DXVECTOR2(24.f, 24.f);

CGameCursor::CGameCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : m_pDevice(_pDevice),m_position(_position.x,_position.y),
	m_alpha(255),m_fadeType(FADE_OUT), m_flickFlag(true),m_addAlpha((m_alpha/2)/FLICKER_TIME)
{

}

CGameCursor::~CGameCursor()
{

}
/**
 * カーソルを点滅させる
 */
void CGameCursor::ControlFlicker()
{

	//点灯している状態ならalpha値を減らす
	if(m_fadeType == FADE_OUT){
		m_alpha -= m_addAlpha;
		if(m_alpha <= 128)	m_fadeType = FADE_IN;
	}

	if(m_fadeType == FADE_IN){
		m_alpha += m_addAlpha;
		if(m_alpha >= 255)	m_fadeType = FADE_OUT;
	}
}
void CGameCursor::Control()	// 制御
{
	//点滅アニメーションの制御
	if(m_flickFlag) ControlFlicker();

	switch( m_state ) {
	case STATE_MOVE:
		switch( m_direction ) {
		case DIR_HORIZONTAL:
			m_position.x += m_moveX;
			if( fabs(m_position.x - m_nextPosition.x) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.x = ROUND_OFF(m_position.x);
			}
			break;
		case DIR_VIRTICAL:
			m_position.y += m_moveY;
			if( fabs(m_position.y - m_nextPosition.y) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.y = ROUND_OFF(m_position.y);
			}
			break;
		case DIR_DIAGONAL:
			m_position.y += m_moveY;
			m_position.x += m_moveX;
			if( fabs(m_position.y - m_nextPosition.y) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.x = ROUND_OFF(m_position.x);
				m_position.y = ROUND_OFF(m_position.y);
			}
			break;
		}
		break;
	}
}
void CGameCursor::Draw()	// 描画
{
	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
}
/*--------------------------------------------------------------

	移動先の座標をセット
	@param	D3DXVECTOR2 
	@return なし

--------------------------------------------------------------*/	
void CGameCursor::SetNextPosition(D3DXVECTOR2 _nextPosition)
{
	m_nextPosition.x = _nextPosition.x;
	m_nextPosition.y = _nextPosition.y;
	// X軸が同じの場合縦に移動
	if( m_nextPosition.x == m_position.x ) {
		m_direction = DIR_VIRTICAL;
		m_state = STATE_MOVE;
		// 一回の移動量
		m_moveY = (m_nextPosition.y - m_position.y) / MOVE_TIME;
	}
	// Y軸が同じの場合横に移動
	else if( m_nextPosition.y == m_position.y ) {
		m_direction = DIR_HORIZONTAL;
		m_state = STATE_MOVE;
		// 一回の移動量
		m_moveX = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
	else{	//どちらも違う場合は斜めに移動
		m_direction = DIR_DIAGONAL;
		m_state = STATE_MOVE;
		//一回の移動量
		m_moveY = (m_nextPosition.y - m_position.y) / MOVE_TIME;
		m_moveX = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
}
/**
 * 選択されている項目番号を取得
 * @param 選んでいるID
 */
int CGameCursor::GetSelectID()														
{
	return m_selectID;
}
/**
 * カーソルの状態(移動中など)を取得する
 * @return カーソルの状態
 */
int CGameCursor::GetState()
{
	return m_state;
}