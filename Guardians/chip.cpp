#include "stdafx.h"

// 静的なメンバ変数の実体化
const FRECT CChip::animRect[] = {
	FRECT(0.f, 180.f, 160.f, 360.f),
	FRECT(160.f, 180.f, 320.f, 360.f),
	FRECT(320.f, 180.f, 480.f, 360.f),
};
const int CChip::ANIM_NO_LIST[] = {
	0, 1, 2, 1,
};


CChip::CChip(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, ChipType _type, bool _animFlag) :
	m_pDevice( _pDevice ), m_position( _position ), m_type( _type ), shadowRect(480.f, 180.f, 640.f, 360.f), m_animFlag(_animFlag), m_time(ANIME_TIME),m_animeCount(0)
{
	m_texture = CTexMgr.Get( TEX_MAP_CHIP );
	// 影のテクスチャ
	m_shadowtexture = CTexMgr.Get( TEX_MAP_CHIP );
	// 赤丸のテクスチャ
	m_animTexture = CTexMgr.Get( TEX_MAP_CHIP );


	// タイプによってテクスチャ座標を変える
	switch( m_type ) {
	case START:
		rect.left = 0.f;
		rect.right = rect.left+160.f;
		rect.top = 180.f*2;
		rect.bottom = rect.top+180.f;
		break;
	case STAGE1BOSS:
	case STAGE2BOSS:
	case STAGE3BOSS:
	case STAGE4BOSS:
	case STAGE5BOSS:
	case STAGE6BOSS:
		rect.left = (m_type <= STAGE3BOSS ? 160.f+(m_type-STAGE1BOSS)*160.f : (m_type-STAGE4BOSS)*160.f);
		rect.right = rect.left+160.f;
		rect.top = 360.f + (m_type <= STAGE3BOSS ? 0.f : 180.f);
		rect.bottom = rect.top+180.f;
		break;
	case ROAD_LINE:
		rect.left = 0.f;
		rect.right = rect.left+16.f;
		rect.top = 720.f;
		rect.bottom = rect.top+16.f;
		break;
	case CHECKPOINT_NOCLEAR:
		rect.left = 480.f;
		rect.right = rect.left+40.f;
		rect.top = 540.f;
		rect.bottom = rect.top+40.f;
		break;
	case CHECKPOINT_CLEAR:
		rect.left = 520;
		rect.right = rect.left+40;
		rect.top = 540;
		rect.bottom = rect.top+40;
		break;
	
	default:
		break;
	}

}

void CChip::Control()
{
	//明減アニメーション
	if( m_type <= STAGE6BOSS && m_animFlag ) {
		MoveAnimation();
	}
}

void CChip::SetAnimeFlag(bool _animFlag)
{
	//アニメフラグをセット
	m_animFlag = _animFlag;


}

void CChip::Draw()
{
	
	if( m_type <= STAGE6BOSS || m_type == START ) {
		m_vertex.DrawTextureLT(m_pDevice, m_shadowtexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, shadowRect);
		//アニメフラグtrueなら明減アニメーション
		if( m_animFlag ) m_vertex.DrawTextureLT(m_pDevice, m_animTexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, animRect[ANIM_NO_LIST[m_animeCount]]);
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, rect);
	}
	else
	{
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, rect);
	}
}

void CChip::SetCameraPosition(D3DXVECTOR2 _cameraPosition)
{
	// マップからカメラ座標をもらってセット
	m_cameraPosition = _cameraPosition;
}


void CChip::ChangeType(ChipType _type)
{
	m_type = _type;
}

//===========================内部関数=================================


void CChip::MoveAnimation()
{
	m_time--;
	if(m_time==0){
		m_animeCount = (m_animeCount+1)% (sizeof(ANIM_NO_LIST) / sizeof(int));
		m_time = ANIME_TIME;
	}
}