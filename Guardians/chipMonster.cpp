#include "stdafx.h"

// Ã“I‚Èƒƒ“ƒo•Ï”‚ÌŽÀ‘Ì‰»
const FRECT CChipMonster::monAnimRect[] = {
	FRECT(0.f, 72.f, 256.f, 256.f),
	FRECT(256.f, 72.f, 512.f, 256.f),
	FRECT(512.f, 72.f, 768.f, 256.f),
};

CChipMonster::CChipMonster(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, ChipType _type, bool _isAnim):
	CChip( _pDevice, _position, _type, _isAnim ),m_alpha(0),m_alphaSpeed(255/20),
	m_state( STATE_FEEDIN )
{
	m_texture = CTexMgr.Get( TEX_MONSTER_CHIP );
	
	m_animRect.left =  monAnimRect[0].left;
	m_animRect.right =  monAnimRect[0].right;
	m_animRect.top = monAnimRect[0].top + (_type-CChip::MONSCHIP_STAGE1BOSS)*256.f;
	m_animRect.bottom = m_animRect.top + (256.f-72.f);
}

void  CChipMonster::Control()
{
	if( m_animFlag ) {
		switch( m_state ) {
		case STATE_FEEDIN:
			if( (m_alpha += m_alphaSpeed) >= 255 ) {
				m_alpha = 255;
				m_state = STATE_ANIMATION;
			}
			break;
		case STATE_ANIMATION:
			MoveAnimation();

			m_animRect.left =  monAnimRect[ANIM_NO_LIST[m_animeCount]].left;
			m_animRect.right =  monAnimRect[ANIM_NO_LIST[m_animeCount]].right;
			break;
		}
	}
}

void CChipMonster::Draw(){
	if( m_animFlag )
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, m_animRect,D3DCOLOR_ARGB(m_alpha,255,255,255));	

}