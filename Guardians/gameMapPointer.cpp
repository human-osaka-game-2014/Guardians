#include "stdafx.h"

// 静的なメンバ変数の実体化
const FRECT CGameMapPointer::pointAnimRect[] = {
	FRECT(0.f, 0.f, 160.f, 180.f),
	FRECT(160.f, 0.f, 320.f, 180.f),
	FRECT(320.f, 0.f, 480.f, 180.f),
	FRECT(480.f, 0.f, 640.f, 180.f),
};

const int CGameMapPointer::POINT_ANIM_NO[] = {
	0, 1, 2, 3, 2, 1,
};
const D3DXVECTOR2 CGameMapPointer::m_checkPointPos[CHECK_POINT_NUM] = {
	D3DXVECTOR2(520, 2540),	// チェックポイントスタート
	D3DXVECTOR2(570, 2482),		// チェックポイント1
	D3DXVECTOR2(656, 2406),		// チェックポイント2
	D3DXVECTOR2(715, 2300),		// チェックポイント3
	D3DXVECTOR2(772, 2120),		// チェックポイント4
	D3DXVECTOR2(794, 2027),		// チェックポイント5
	D3DXVECTOR2(771, 1951),		// チェックポイント6
	D3DXVECTOR2(856, 1735),		// チェックポイント7
	D3DXVECTOR2(700, 1663),		// チェックポイント8
	D3DXVECTOR2(627, 1518),		// チェックポイント9
	D3DXVECTOR2(604, 1281),		// チェックポイント10
	D3DXVECTOR2(706, 1151),		// チェックポイント11
	D3DXVECTOR2(794, 981),		// チェックポイント12
	D3DXVECTOR2(1028, 877),		// チェックポイント13
	D3DXVECTOR2(894, 767),	// チェックポイント14
	D3DXVECTOR2(780, 677),		// チェックポイント3
	D3DXVECTOR2(910, 505),	// チェックポイント1
	D3DXVECTOR2(882, 365),		// チェックポイント2
	D3DXVECTOR2(864, 223),		// チェックポイント3
};
const D3DXVECTOR2 CGameMapPointer::POINTER_SIZE = D3DXVECTOR2(60.f,130.f);

CGameMapPointer::CGameMapPointer(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int _clearStageNum,CGameData* _pGameData):
	CChip( _pDevice, _position, CChip::START, true ),	m_pCount(0),m_pTime(POINT_ANIME_TIME),m_state(STATE_WAIT),m_shake(0.0f),
	m_shakeSpeed(0.1f),m_shakeCount(0),m_clearCount(_clearStageNum),m_move(1.0f,1.0f)
	,m_nextPosition(595.f,2280.f),m_checkPointNum(0),m_nextCheckPointNum(1),m_backCount(1),m_pMoveTime(0),m_pGameData(_pGameData)
{
	m_position = D3DXVECTOR2(m_checkPointPos[_clearStageNum].x - 60,m_checkPointPos[_clearStageNum].y - 130);
	m_pointTexture = CTexMgr.Get( TEX_MAP_CHIP );

	//m_position.push_back(D3DXVECTOR2(510.f, 2360.f));
	//m_position.push_back(D3DXVECTOR2(595.f, 2280.f));
	//m_position.push_back(D3DXVECTOR2(655.f, 2170.f));

	//m_staticPosition.push_back(D3DXVECTOR2(510.f, 2360.f));
	//m_staticPosition.push_back(D3DXVECTOR2(595.f, 2280.f));
	//m_staticPosition.push_back(D3DXVECTOR2(655.f, 2170.f));
}

void CGameMapPointer::Control()
{
	//ポインタ点滅アニメーション
	m_pTime--;
	if(m_pTime == 0){
		m_pCount = (m_pCount+1)%( sizeof(POINT_ANIM_NO) / sizeof(int) );
		m_pTime = ANIME_TIME;
	}
	//ポインタ上下移動
	m_shakeCount++;
	m_shake -= m_shakeSpeed;
	if(m_shakeCount == MOVE_TIME/2){
		m_shakeSpeed *= -1.0f;
		m_shakeCount = 0;
	}
	switch( m_state ){
	// ポインタを移動
	case STATE_MOVE:
		m_position += m_move;
		m_pMoveTime++;
		if( m_pMoveTime >= POINTER_MOVE_FRAME )
			m_position = m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE;
		break;
	case STATE_MOVE_RIGHT:
		// ポインタの移動量を決める
		m_move = ((m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE) - m_position) / POINTER_MOVE_FRAME;

		// 状態を移動状態に
		m_state = STATE_MOVE;
		break;
	case STATE_MOVE_LEFT:
		// ポインタの移動量を決める
		m_move = ( (m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE) - m_position) / POINTER_MOVE_FRAME;

		// 状態を移動状態に
		m_state = STATE_MOVE;

		break;
	};
	// ポインターの位置がチェックポイントの位置と同じなら待機状態に戻す
	if( m_position == (m_checkPointPos[m_pGameData->m_selectStageNum] - POINTER_SIZE)){
		m_state = STATE_WAIT;
		m_pMoveTime = 0;
	}

}

void CGameMapPointer::Draw()
{
	// 移動状態以外ならポインタをアニメーションさせる
	if(m_state != STATE_MOVE){
		m_vertex.DrawTextureLT(m_pDevice, m_pointTexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y + m_shake,
		pointAnimRect[POINT_ANIM_NO[m_pCount]]);
	}else{
		m_vertex.DrawTextureLT(m_pDevice, m_pointTexture, m_position.x+m_cameraPosition.x, m_position.y+m_cameraPosition.y, 
		pointAnimRect[0]);
	}
}

void CGameMapPointer:: SetClearCount(int _clearCount)
{
	m_clearCount = _clearCount;
}

void CGameMapPointer::SetMoveDirection(State _state)
{
	// ポインタが待機状態なら移動状態に
	if( m_state == STATE_WAIT ) m_state = _state;
	
	if( m_state == STATE_MOVE_LEFT ){
		// 選択しているステージ番号を減らす
		m_pGameData->m_selectStageNum--;
		if( m_pGameData->m_selectStageNum < 0 )
			m_pGameData->m_selectStageNum = 0;
	}else if( m_state == STATE_MOVE_RIGHT ){
		// 選択しているステージ番号を減らす
		m_pGameData->m_selectStageNum++;
		if( m_pGameData->m_selectStageNum > m_pGameData->m_nowClearStageNum )
			m_pGameData->m_selectStageNum = m_pGameData->m_nowClearStageNum;
	}
}

CGameMapPointer::State CGameMapPointer::GetState()
{
	return  m_state;
}