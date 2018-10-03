#include "stdafx.h"

const CGameMap::ChipData CGameMap::CHIP_DATA[] = {
/*0*/	{ D3DXVECTOR2(400, 2500), CChip::START },					// �X�^�[�g�n�_
/*1*/	{ D3DXVECTOR2(520, 2540), CChip::CHECKPOINT_CLEAR },		// �`�F�b�N�|�C���g�X�^�[�g
/*2*/	{ D3DXVECTOR2(570, 2482), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*3*/	{ D3DXVECTOR2(656, 2406), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*4*/	{ D3DXVECTOR2(715, 2300), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*5*/	{ D3DXVECTOR2(665, 2145), CChip::STAGE1BOSS },				// �X�e�[�W1�{�X
/*6*/	{ D3DXVECTOR2(615, 2115), CChip::MONSCHIP_STAGE1BOSS },	//�X�e�[�W�P�{�X�����X�^�[�A�j���[�V�����p
/*7*/	{ D3DXVECTOR2(772, 2120), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*8*/	{ D3DXVECTOR2(794, 2027), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*9*/	{ D3DXVECTOR2(771, 1951), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*10*/	{ D3DXVECTOR2(748, 1796), CChip::STAGE2BOSS },			// �X�e�[�W2�{�X
/*11*/	{ D3DXVECTOR2(698, 1766), CChip::MONSCHIP_STAGE2BOSS },	//�X�e�[�W2�{�X�����X�^�[�A�j���[�V�����p
/*12*/	{ D3DXVECTOR2(856, 1735), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*13*/	{ D3DXVECTOR2(700, 1663), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*14*/	{ D3DXVECTOR2(627, 1518), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*15*/	{ D3DXVECTOR2(574, 1363), CChip::STAGE3BOSS },			// �X�e�[�W3�{�X
/*16*/	{ D3DXVECTOR2(524, 1333), CChip::MONSCHIP_STAGE3BOSS },	//�X�e�[�W3�{�X�����X�^�[�A�j���[�V�����p
/*16*/	{ D3DXVECTOR2(604, 1281), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*17*/	{ D3DXVECTOR2(706, 1151), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*18*/	{ D3DXVECTOR2(794, 981),  CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*19*/	{ D3DXVECTOR2(824, 869),  CChip::STAGE4BOSS },			// �X�e�[�W4�{�X
/*20*/	{ D3DXVECTOR2(774, 839),  CChip::MONSCHIP_STAGE4BOSS }, // �X�e�[�W4�{�X�����X�^�[�A�j���[�V�����p
/*21*/	{ D3DXVECTOR2(1028, 877), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*22*/	{ D3DXVECTOR2(894, 767),  CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*23*/	{ D3DXVECTOR2(780, 677),  CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*24*/	{ D3DXVECTOR2(760, 533),  CChip::STAGE5BOSS },			// �X�e�[�W5�{�X
/*25*/	{ D3DXVECTOR2(710, 503),  CChip::MONSCHIP_STAGE5BOSS }, // �X�e�[�W5�{�X�����X�^�[�A�j���[�V�����p
/*26*/	{ D3DXVECTOR2(910, 505), CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g1
/*27*/	{ D3DXVECTOR2(882, 365),  CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g2
/*28*/	{ D3DXVECTOR2(864, 223),  CChip::CHECKPOINT_NOCLEAR },		// �`�F�b�N�|�C���g3
/*29*/	{ D3DXVECTOR2(806, 71),  CChip::STAGE6BOSS },			// �X�e�[�W6�{�X
/*30*/	{ D3DXVECTOR2(756, 41),  CChip::MONSCHIP_STAGE6BOSS }, // �X�e�[�W6�{�X�����X�^�[�A�j���[�V�����p
};

const int  CGameMap::STAGE1_LINE_NUMLIST[] = {	// �X�e�[�W1�i�s���C�������X�g
	6, 14, 22, 23, -1,
};
const int CGameMap::STAGE2_LINE_NUMLIST[] = {	// �X�e�[�W2�i�s���C�������X�g
	32, 38, 41, 42, -1,
};
const int CGameMap::STAGE3_LINE_NUMLIST[] = {	// �X�e�[�W3�i�s���C�������X�g
	57, 65, 78, 79, -1,
};
const int CGameMap::STAGE4_LINE_NUMLIST[] = {	// �X�e�[�W4�i�s���C�������X�g
	90, 100, 110, 111, -1,
};
const int CGameMap::STAGE5_LINE_NUMLIST[] = {	// �X�e�[�W5�i�s���C�������X�g
	124, 135, 147, 148, -1,
};
const int CGameMap::STAGE6_LINE_NUMLIST[] = {	// �X�e�[�W6�i�s���C�������X�g
	160, 170, 178, 179, -1,
};

const int* CGameMap::STAGE_LINE_NUMLIST[] = {	// �S�X�e�[�W�i�s���C�������X�g
	STAGE1_LINE_NUMLIST,
	STAGE2_LINE_NUMLIST,
	STAGE3_LINE_NUMLIST,
	STAGE4_LINE_NUMLIST,
	STAGE5_LINE_NUMLIST,
	STAGE6_LINE_NUMLIST,
};

const POINT CGameMap::POINT_LIST[] = {		// �X�e�[�W���Ƃ̐i�s�|�C���g�\����
	{0, 4},		// �X�e�[�W1
	{0, 23},	// �X�e�[�W2
	{23, 42},	// �X�e�[�W3
	{42, 79},	// �X�e�[�W4
	{79, 111},	// �X�e�[�W5
	{111, 148},	// �X�e�[�W6
};
const POINT CGameMap::CHIP_NUMLIST[] = {		// �X�e�[�W���Ƃ̃`�b�v�\����
	{0, 2},		// �X�e�[�W1
	{0, 6},		// �X�e�[�W2
	{6, 11},	// �X�e�[�W3
	{11, 16},	// �X�e�[�W4
	{16, 21},	// �X�e�[�W5
	{21, 26},	// �X�e�[�W6
};
const D3DXVECTOR2 CGameMap::INIT_CAMERA_POS(-75.f, -2000.f);

CGameMap::CGameMap(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,D3DXVECTOR2 _cameraPosition, int _stageID) :
	m_pDevice( _pDevice ), m_cameraPosition( _cameraPosition ),m_pointMin(0),m_pointMax(4),m_clearCount(0),
		m_state( STATE_CHECKMOVE ), m_pointNow( 0 ), m_pointMoveCnt( 0 ), m_chipMin( 0 ), m_chipMax( 2 ),
		m_stageID( _stageID ),m_pGameData(_pGameData)
{
	if( m_stageID > 0 ) {	// �X�e�[�W2�ȍ~
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
		// �X�e�[�W1�̃}�b�v���W�͓����Ȃ��悤�ɐݒ�
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
	
	// �摜�ǂݍ���
	m_texture = CTexMgr.Get( TEX_MAP );
	for( int i = 0; i < CHIP_MAX; i++ ) {
		CChip::ChipType type;
		
		type = CHIP_DATA[i].type;
		//  �@�N���A�����X�e�[�W�� �{ �X�e�[�WID * �{�X�A�{�X�A�j���̃`�b�v�f�[�^(2��) �{ �X�^�[�g�n�_�̃`�b�v(1��)
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

	// �}�b�v�|�C���^
	int index = m_pGameData->m_nowClearStageNum == 0 ? 1 : m_pGameData->m_nowClearStageNum + m_stageID * 2;
	m_mapPointa = new CGameMapPointer(_pDevice,D3DXVECTOR2(CHIP_DATA[index].position.x - 60,CHIP_DATA[index].position.y - 130),m_pGameData->m_nowClearStageNum,m_pGameData);
//	m_mapPointa = new CGameMapPointer(_pDevice,D3DXVECTOR2(CHIP_DATA[_stageID * 3 + 1].position.x - 60,CHIP_DATA[_stageID * 3 + 1].position.y-130));
	m_clearCount = 0;

	// �S�`�b�v�ɃJ�����̈ʒu�𔽉f
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
	// ��ԕ�������
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
			// �������瓯���ʒu��
			m_cameraPosition.y = m_nextMapPosition.y;
			m_state = STATE_CHECKMOVE;
			m_pointNow = m_pointMax;
		}

		// �S�`�b�v�ɃJ�����̈ʒu�𔽉f
		SetCameraPositionToAllChip(m_cameraPosition);

		break;
	case STATE_POINTMOVE:
		// �`�b�v
		for( int i = m_chipMin; i < m_chipMax; i++ ) {
			m_pChip[i]->Control();
		}
		//�}�b�v�|�C���^�A�j���[�V����
		m_mapPointa->Control();
		break;
	case STATE_MP:
		// �`�b�v
		for( int i = m_chipMin; i < m_chipMax; i++ ) {
			m_pChip[i]->Control();
		}
		//�}�b�v�|�C���^�A�j���[�V����
		m_mapPointa->Control();

		if( m_dir == CGameMapPointer::STATE_MOVE_LEFT ){
			m_cameraPosition.y--;
		}else if( m_dir == CGameMapPointer::STATE_MOVE_RIGHT ){
			m_cameraPosition.y++;
		}
		
		if( m_dir == CGameMapPointer::STATE_MOVE_RIGHT && m_nextMapPosition.y < m_cameraPosition.y || 
			m_dir == CGameMapPointer::STATE_MOVE_LEFT && m_nextMapPosition.y > m_cameraPosition.y ){
			// �������瓯���ʒu��
			m_cameraPosition.y = m_nextMapPosition.y;
			m_state = STATE_POINTMOVE;
			m_pointNow = m_pointMax;
		}

		//if( m_nextMapPosition.y > m_cameraPosition.y ) {
		//	m_cameraPosition.y++;
		//} else {
		//	// �������瓯���ʒu��
		//	m_cameraPosition.y = m_nextMapPosition.y;
		//	m_state = STATE_POINTMOVE;
		//	m_pointNow = m_pointMax;
		//}
		// �S�`�b�v�ɃJ�����̈ʒu�𔽉f
		SetCameraPositionToAllChip(m_cameraPosition);
		break;
	}
	// �|�C���^�ړ���ԂȂ�}�b�v��`�悵�I�����
	if( m_state == STATE_POINTMOVE ) 
		return false;
	else						
		return true;
}

void CGameMap::Draw()
{
	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_cameraPosition.x, m_cameraPosition.y);

	// �i�s�|�C���g
	int drawPointMax = (m_pointNow != -1) ? m_pointNow : m_pointMax;
	for(int i=m_pointMin;i < drawPointMax ;i++){
		m_chipPoint[i].Draw();
	}	

	// �`�b�v
	for( int i = m_chipMin; i < m_chipMax; i++ ) {
		m_pChip[i]->Draw();
	}

	// �}�b�v�|�C���^
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

//====================================================�����֐�=========================================================

// �S�Ẵ`�b�v�ɃJ�������W�Z�b�g
void CGameMap::SetCameraPositionToAllChip(D3DXVECTOR2 _cameraPosition)
{
	// �i�s���C��
	for( unsigned i = 0; i < m_chipPoint.size(); i++ ) m_chipPoint[i].SetCameraPosition(_cameraPosition);
	// �e�`�b�v(�X�e�[�W/�`�F�b�N�|�C���g)
	for( int i = 0; i < CHIP_MAX; i++ ) m_pChip[i]->SetCameraPosition(_cameraPosition);
	// �}�b�v�|�C���^
	m_mapPointa->SetCameraPosition(_cameraPosition);
}