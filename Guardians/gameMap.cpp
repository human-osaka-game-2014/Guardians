#include "stdafx.h"

const CGameMap::ChipData CGameMap::CHIP_DATA[] = {
/*0*/	{ D3DXVECTOR2(400, 2500), CChip::START },					// スタート地点
/*1*/	{ D3DXVECTOR2(520, 2540), CChip::CHECKPOINT_CLEAR },		// チェックポイントスタート
/*2*/	{ D3DXVECTOR2(570, 2482), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*3*/	{ D3DXVECTOR2(656, 2406), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*4*/	{ D3DXVECTOR2(715, 2300), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*5*/	{ D3DXVECTOR2(665, 2145), CChip::STAGE1BOSS },				// ステージ1ボス
/*6*/	{ D3DXVECTOR2(615, 2115), CChip::MONSCHIP_STAGE1BOSS },	//ステージ１ボスモンスターアニメーション用
/*7*/	{ D3DXVECTOR2(772, 2120), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*8*/	{ D3DXVECTOR2(794, 2027), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*9*/	{ D3DXVECTOR2(771, 1951), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*10*/	{ D3DXVECTOR2(748, 1796), CChip::STAGE2BOSS },			// ステージ2ボス
/*11*/	{ D3DXVECTOR2(698, 1766), CChip::MONSCHIP_STAGE2BOSS },	//ステージ2ボスモンスターアニメーション用
/*12*/	{ D3DXVECTOR2(856, 1735), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*13*/	{ D3DXVECTOR2(700, 1663), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*14*/	{ D3DXVECTOR2(627, 1518), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*15*/	{ D3DXVECTOR2(574, 1363), CChip::STAGE3BOSS },			// ステージ3ボス
/*16*/	{ D3DXVECTOR2(524, 1333), CChip::MONSCHIP_STAGE3BOSS },	//ステージ3ボスモンスターアニメーション用
/*16*/	{ D3DXVECTOR2(604, 1281), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*17*/	{ D3DXVECTOR2(706, 1151), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*18*/	{ D3DXVECTOR2(794, 981),  CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*19*/	{ D3DXVECTOR2(824, 869),  CChip::STAGE4BOSS },			// ステージ4ボス
/*20*/	{ D3DXVECTOR2(774, 839),  CChip::MONSCHIP_STAGE4BOSS }, // ステージ4ボスモンスターアニメーション用
/*21*/	{ D3DXVECTOR2(1028, 877), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*22*/	{ D3DXVECTOR2(894, 767),  CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*23*/	{ D3DXVECTOR2(780, 677),  CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*24*/	{ D3DXVECTOR2(760, 533),  CChip::STAGE5BOSS },			// ステージ5ボス
/*25*/	{ D3DXVECTOR2(710, 503),  CChip::MONSCHIP_STAGE5BOSS }, // ステージ5ボスモンスターアニメーション用
/*26*/	{ D3DXVECTOR2(910, 505), CChip::CHECKPOINT_NOCLEAR },		// チェックポイント1
/*27*/	{ D3DXVECTOR2(882, 365),  CChip::CHECKPOINT_NOCLEAR },		// チェックポイント2
/*28*/	{ D3DXVECTOR2(864, 223),  CChip::CHECKPOINT_NOCLEAR },		// チェックポイント3
/*29*/	{ D3DXVECTOR2(806, 71),  CChip::STAGE6BOSS },			// ステージ6ボス
/*30*/	{ D3DXVECTOR2(756, 41),  CChip::MONSCHIP_STAGE6BOSS }, // ステージ6ボスモンスターアニメーション用
};

const int  CGameMap::STAGE1_LINE_NUMLIST[] = {	// ステージ1進行ライン個数リスト
	6, 14, 22, 23, -1,
};
const int CGameMap::STAGE2_LINE_NUMLIST[] = {	// ステージ2進行ライン個数リスト
	32, 38, 41, 42, -1,
};
const int CGameMap::STAGE3_LINE_NUMLIST[] = {	// ステージ3進行ライン個数リスト
	57, 65, 78, 79, -1,
};
const int CGameMap::STAGE4_LINE_NUMLIST[] = {	// ステージ4進行ライン個数リスト
	90, 100, 110, 111, -1,
};
const int CGameMap::STAGE5_LINE_NUMLIST[] = {	// ステージ5進行ライン個数リスト
	124, 135, 147, 148, -1,
};
const int CGameMap::STAGE6_LINE_NUMLIST[] = {	// ステージ6進行ライン個数リスト
	160, 170, 178, 179, -1,
};

const int* CGameMap::STAGE_LINE_NUMLIST[] = {	// 全ステージ進行ライン個数リスト
	STAGE1_LINE_NUMLIST,
	STAGE2_LINE_NUMLIST,
	STAGE3_LINE_NUMLIST,
	STAGE4_LINE_NUMLIST,
	STAGE5_LINE_NUMLIST,
	STAGE6_LINE_NUMLIST,
};

const POINT CGameMap::POINT_LIST[] = {		// ステージごとの進行ポイント表示数
	{0, 4},		// ステージ1
	{0, 23},	// ステージ2
	{23, 42},	// ステージ3
	{42, 79},	// ステージ4
	{79, 111},	// ステージ5
	{111, 148},	// ステージ6
};
const POINT CGameMap::CHIP_NUMLIST[] = {		// ステージごとのチップ表示数
	{0, 2},		// ステージ1
	{0, 6},		// ステージ2
	{6, 11},	// ステージ3
	{11, 16},	// ステージ4
	{16, 21},	// ステージ5
	{21, 26},	// ステージ6
};
const D3DXVECTOR2 CGameMap::INIT_CAMERA_POS(-75.f, -2000.f);

CGameMap::CGameMap(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,D3DXVECTOR2 _cameraPosition, int _stageID) :
	m_pDevice( _pDevice ), m_cameraPosition( _cameraPosition ),m_pointMin(0),m_pointMax(4),m_clearCount(0),
		m_state( STATE_CHECKMOVE ), m_pointNow( 0 ), m_pointMoveCnt( 0 ), m_chipMin( 0 ), m_chipMax( 2 ),
		m_stageID( _stageID ),m_pGameData(_pGameData)
{
	if( m_stageID > 0 ) {	// ステージ2以降
		m_state = STATE_MAPMOVE;
		m_pointMin = POINT_LIST[m_stageID].x;
		m_pointMax = POINT_LIST[m_stageID].y;
		m_pointNow = -1;
		m_chipMin = CHIP_NUMLIST[m_stageID].x;
		m_chipMax = CHIP_NUMLIST[m_stageID].y;

		m_cameraPosition.x = INIT_CAMERA_POS.x;
		m_cameraPosition.y = -(CHIP_DATA[(_stageID-1) * 5 + 1].position.y - 500.f);

		m_nextMapPosition.x = INIT_CAMERA_POS.x;
		m_nextMapPosition.y = -(CHIP_DATA[_stageID * 5].position.y - 500.f);

		m_threwBoss = true;
	} else {
		m_cameraPosition = INIT_CAMERA_POS;
		// ステージ1のマップ座標は動かないように設定
		m_nextMapPosition = m_cameraPosition;
		m_threwBoss = false;
	}

	std::ifstream ifs("image\\ROAD_LINE_POINT.txt");
	if(ifs.fail())
		return;

	std::string str;
	while(std::getline(ifs,str))
	{
		float x, y;
		sscanf_s(str.data(),"%f,%f",&x,&y);
	
		CChip chip(_pDevice, D3DXVECTOR2(x,y),CChip::ROAD_LINE);
		m_chipPoint.insert( m_chipPoint.begin(),  chip);
	}
	
	// 画像読み込み
	m_texture = CTexMgr.Get( TEX_MAP );
	for( int i = 0; i < CHIP_MAX; i++ ) {
		CChip::ChipType type;
		
		type = CHIP_DATA[i].type;
		//  　クリアしたステージ数 ＋ ステージID * ボス、ボスアニメのチップデータ(2個) ＋ スタート地点のチップ(1個)
		if( i <= m_pGameData->m_nowClearStageNum + ((m_stageID ) * 2 + 1) ) {
			if( type == CChip::CHECKPOINT_NOCLEAR )
				type = CChip::CHECKPOINT_CLEAR;
		}

		if(type >= CChip::MONSCHIP_STAGE1BOSS){
			bool isAnim = m_stageID+CChip::MONSCHIP_STAGE1BOSS <= type;
			m_pChip[i] = new CChipMonster(_pDevice, CHIP_DATA[i].position, type, isAnim);
		}else{
			bool isAnim = type <= CChip::STAGE6BOSS && m_stageID <= type;
			m_pChip[i] = new CChip(_pDevice, CHIP_DATA[i].position, type, isAnim);
		}
	}

	// マップポインタ
	int index = m_pGameData->m_nowClearStageNum == 0 ? 1 : m_pGameData->m_nowClearStageNum + m_stageID * 2;
	m_mapPointa = new CGameMapPointer(_pDevice,D3DXVECTOR2(CHIP_DATA[index].position.x - 60,CHIP_DATA[index].position.y - 130),m_pGameData->m_nowClearStageNum,m_pGameData);
//	m_mapPointa = new CGameMapPointer(_pDevice,D3DXVECTOR2(CHIP_DATA[_stageID * 3 + 1].position.x - 60,CHIP_DATA[_stageID * 3 + 1].position.y-130));
	m_clearCount = 0;

	// 全チップにカメラの位置を反映
	SetCameraPositionToAllChip(m_cameraPosition);
	
	
}
CGameMap::~CGameMap()
{
	SAFE_DELETE( m_mapPointa );

	for(int i = 0; i < CHIP_MAX;i++){
		SAFE_DELETE( m_pChip[i] );
	}
}
bool CGameMap::Control()
{
	if( m_pGameData->m_death ){
		for(int i = 0; i < 4; i++)
			STAGE_LINE_NUMLIST[m_stageID]--;
		m_pGameData->m_death = false;
	}
	// 状態分けする
	switch( m_state ) {
	case STATE_CHECKMOVE:
		if( m_pointNow < *STAGE_LINE_NUMLIST[m_stageID] ) {
			if( m_pointMoveCnt++ < POINT_MOVE_SPD ) break;
			m_pointNow++;
			m_pointMoveCnt = 0;
			if( m_pointNow == *STAGE_LINE_NUMLIST[m_stageID] ) {
				STAGE_LINE_NUMLIST[m_stageID]++;
				if( m_threwBoss && CHIP_DATA[m_chipMax].type >= CChip::MONSCHIP_STAGE1BOSS ) { m_threwBoss = false; m_chipMax++; }
				m_chipMax++;
 
				if( m_chipMax <  CHIP_MAX && CHIP_DATA[m_chipMax].type <= CChip::STAGE6BOSS ) m_chipMax++;

			}
			if( *STAGE_LINE_NUMLIST[m_stageID] == -1 ) m_state = STATE_POINTMOVE;
		}
		break;
	case STATE_MAPMOVE:
		if( m_nextMapPosition.y > m_cameraPosition.y ) {
			m_cameraPosition.y++;
		} else {
			// 超えたら同じ位置に
			m_cameraPosition.y = m_nextMapPosition.y;
			m_state = STATE_CHECKMOVE;
			m_pointNow = m_pointMax;
		}

		// 全チップにカメラの位置を反映
		SetCameraPositionToAllChip(m_cameraPosition);

		break;
	case STATE_POINTMOVE:
		// チップ
		for( int i = m_chipMin; i < m_chipMax; i++ ) {
			m_pChip[i]->Control();
		}
		//マップポインタアニメーション
		m_mapPointa->Control();
		break;
	case STATE_MP:
		// チップ
		for( int i = m_chipMin; i < m_chipMax; i++ ) {
			m_pChip[i]->Control();
		}
		//マップポインタアニメーション
		m_mapPointa->Control();

		if( m_dir == CGameMapPointer::STATE_MOVE_LEFT ){
			m_cameraPosition.y--;
		}else if( m_dir == CGameMapPointer::STATE_MOVE_RIGHT ){
			m_cameraPosition.y++;
		}
		
		if( m_dir == CGameMapPointer::STATE_MOVE_RIGHT && m_nextMapPosition.y < m_cameraPosition.y || 
			m_dir == CGameMapPointer::STATE_MOVE_LEFT && m_nextMapPosition.y > m_cameraPosition.y ){
			// 超えたら同じ位置に
			m_cameraPosition.y = m_nextMapPosition.y;
			m_state = STATE_POINTMOVE;
			m_pointNow = m_pointMax;
		}

		//if( m_nextMapPosition.y > m_cameraPosition.y ) {
		//	m_cameraPosition.y++;
		//} else {
		//	// 超えたら同じ位置に
		//	m_cameraPosition.y = m_nextMapPosition.y;
		//	m_state = STATE_POINTMOVE;
		//	m_pointNow = m_pointMax;
		//}
		// 全チップにカメラの位置を反映
		SetCameraPositionToAllChip(m_cameraPosition);
		break;
	}
	// ポインタ移動状態ならマップを描画し終わった
	if( m_state == STATE_POINTMOVE ) 
		return false;
	else						
		return true;
}

void CGameMap::Draw()
{
	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_cameraPosition.x, m_cameraPosition.y);

	// 進行ポイント
	int drawPointMax = (m_pointNow != -1) ? m_pointNow : m_pointMax;
	for(int i=m_pointMin;i < drawPointMax ;i++){
		m_chipPoint[i].Draw();
	}	

	// チップ
	for( int i = m_chipMin; i < m_chipMax; i++ ) {
		m_pChip[i]->Draw();
	}

	// マップポインタ
	if( m_state == STATE_POINTMOVE || m_state == STATE_MP) {
		m_mapPointa->Draw();
	}
}

void CGameMap::SetClearCount(int _clearCount)
{
	m_clearCount = _clearCount;

}

CGameMapPointer* CGameMap::GetMapPointer()
{
	return m_mapPointa;
}
void CGameMap::SetNextPosition(int _stageID,CGameMapPointer::State _state)
{
	if( m_stageID != (_stageID + 1) / 4 )
		m_state = STATE_MP;
	m_stageID = (_stageID + 1) / 4;

	if( _state == CGameMapPointer::STATE_MOVE_LEFT )
		m_dir = CGameMapPointer::STATE_MOVE_LEFT;
	else 
		m_dir = CGameMapPointer::STATE_MOVE_RIGHT;

	m_nextMapPosition.y = -(CHIP_DATA[((m_pGameData->m_selectStageNum + 1) / 4) * 5].position.y - 500.f);
	//m_cameraPosition.y = -(CHIP_DATA[((m_pGameData->m_selectStageNum / 4)-1) * 5 + 1].position.y - 500.f);

}

//====================================================内部関数=========================================================

// 全てのチップにカメラ座標セット
void CGameMap::SetCameraPositionToAllChip(D3DXVECTOR2 _cameraPosition)
{
	// 進行ライン
	for( unsigned i = 0; i < m_chipPoint.size(); i++ ) m_chipPoint[i].SetCameraPosition(_cameraPosition);
	// 各チップ(ステージ/チェックポイント)
	for( int i = 0; i < CHIP_MAX; i++ ) m_pChip[i]->SetCameraPosition(_cameraPosition);
	// マップポインタ
	m_mapPointa->SetCameraPosition(_cameraPosition);
}