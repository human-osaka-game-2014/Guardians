#include "stdafx.h"

// �G�Q�[�W�̊O�g
const FRECT CBattleUI::SIDE_FRAME_VERTEX	= FRECT(0,45,35,70);
const FRECT CBattleUI::FRAME_VERTEX		= FRECT(100,0,300,45);
						
const D3DXVECTOR2  CBattleUI::SIDE_FRAME_POS = D3DXVECTOR2(240,660);
const D3DXVECTOR2  CBattleUI::FRAME_POS		= D3DXVECTOR2(280,660);

const D3DXVECTOR2  CBattleUI::RIGHT_FRAME_POS = D3DXVECTOR2(880,660);
const FRECT  CBattleUI::RIGHT_FRAME_VERTEX = FRECT(40,0,100,45);

const D3DXVECTOR2  CBattleUI::LEFT_FRAME_POS = D3DXVECTOR2(240,660);
const FRECT  CBattleUI::LEFT_FRAME_VERTEX = FRECT(0,0,40,45);

const D3DXVECTOR2  CBattleUI::INIT_SIDE_GAUGE_POS = D3DXVECTOR2(240,680);
const D3DXVECTOR2  CBattleUI::INIT_GAUGE_POS = D3DXVECTOR2(260,680);
const D3DXVECTOR2  CBattleUI::INIT_RIGHT_GAUGE_POS = D3DXVECTOR2(860,680);

// �L�����N�^�[UI�̕`��ʒu
const D3DXVECTOR2 CBattleUI::INIT_CHARA_POS[PLAYER_MAX] = {
	D3DXVECTOR2(45.f,10.f),
	D3DXVECTOR2(200.f,30.f),
	D3DXVECTOR2(320.f,30.f),
};

// �Q�[�W�������̒��_���W
const FRECT CBattleUI::GAUGE_VERTEX[CBattleUI::GAUGE_TYPE_NUM] = {
	FRECT(100,45,300,67),
	FRECT(100,95,300,117),
	FRECT(100,70,300,92),
};
// �Q�[�W�E�[���̒��_���W
const FRECT CBattleUI::SIDE_GAUGE_VERTEX[CBattleUI::GAUGE_TYPE_NUM] = {
	FRECT(22,45,55,67),
	FRECT(22,90,55,120),
	FRECT(22,70,55,95),
};
// �G�Q�[�W��
const FRECT CBattleUI::SIDE_RED_GAUGE_VERTEX	= FRECT(0,70,22,95);

// �O�g�̈ʒu
static const D3DXVECTOR2 INIT_FRAME_POS[PLAYER_MAX] ={
	D3DXVECTOR2(45,10),
	D3DXVECTOR2((float)CBattleUI::FRAME_SIZE,30),
	D3DXVECTOR2((float)CBattleUI::FRAME_SIZE + (float)CBattleUI::FRAME_SIZE * 0.6f,30),
};

//�E�o�[			����100x0	�E��300x45
//�E���̌��������	����0x45	�E��55x70
//�E�Ԃ̌�������Ƌ�	����0x70	�E��55x95
//�E���̌��������	����0x90	�E��55x120
//�E���Q�[�W		����100x45	�E��300x67
//�E�ԃQ�[�W		����100x70	�E��300x92
//�E���Q�[�W		����100x95	�E��300x117	

CBattleUI::CBattleUI(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData) :
	m_pDevice(_pDevice),m_pGameData(_pGameData),m_state(STATE_BATTLE) , m_comboNum(0)
{
	CTexMgr.Load(4, m_pDevice); //UI�摜�ǂݍ���
	
	UI = CTexMgr.Get(TEX_BATTLE_UI );
	blackPic   = CTexMgr.Get(TEX_BATTLE_BLACK );
	enemyGauge = CTexMgr.Get(TEX_BATTLE_ENEMY_HP);

	m_combo = new CCombo(m_pDevice);

	m_charaID[ALDO]=ALDO;				//���L����
	m_charaID[NERU_MARU]=NERU_MARU;		//���L����
	m_charaID[MINE]=MINE;				//���L����

	for(int i = 0; i < PLAYER_MAX; i++){
		m_chara[i].mp = m_chara[i].MAXmp = m_pGameData->m_chara[i].mp;
		m_chara[i].hp = m_chara[i].MAXhp = m_pGameData->m_chara[i].hp;
	}

	for(int i = 0; i < PLAYER_MAX;i++){
		
		m_chara[i].positionID = m_pGameData->m_turnNo[i];

		switch( i ){
		case ALDO:
			m_chara[i].position = INIT_FRAME_POS[m_pGameData->m_turnNo[i]];
			break;
		case NERU_MARU:
			m_chara[i].position = INIT_FRAME_POS[m_pGameData->m_turnNo[i]];
			break;
		case MINE:
			m_chara[i].position = INIT_FRAME_POS[m_pGameData->m_turnNo[i]];
			break;
		}
		// �擪�̃L�����N�^�[�Ȃ�
		if( m_pGameData->m_turnNo[i] == 0 ){
			m_chara[i].scale = 1.0f;
			m_activeCharaNo = i;	// �o�����̐擪�L�����̈ʒu��ۑ�
		}else{
			m_chara[i].scale = 0.8f;
		}
	}

}
CBattleUI::~CBattleUI()
{
	SAFE_DELETE(m_combo);
}
void CBattleUI::Control()
{
	D3DXVECTOR2 Move = D3DXVECTOR2(10.0f,1.0f);
	//if((CScene::m_keyStatePush & KEY_S) != 0){
	//	m_comboNum++; //��
	//}
	switch( m_state ){
	case STATE_BATTLE:

		m_combo->Control(CBattleScene::comboCount);	// �R���{���̐���

		if( (CScene::m_keyStatePush & KEY_A) != 0 ){
			m_state = STATE_CHARA_CHANGE;
		}
		break;
		// �L�����ύX��
	case STATE_CHARA_CHANGE:
		for(int i = 0; i < PLAYER_MAX; i++){
			// �L�����ύX���ɉ摜���ړ�����
			if( m_chara[i].position != INIT_CHARA_POS[m_chara[i].positionID] )
				m_chara[i].position += Move;
			if( m_chara[i].position.x >= INIT_CHARA_POS[m_chara[i].positionID].x )
				m_chara[i].position.x = INIT_CHARA_POS[m_chara[i].positionID].x;
			if( m_chara[i].position.x >= INIT_CHARA_POS[m_chara[i].positionID].y )
				m_chara[i].position.y = INIT_CHARA_POS[m_chara[i].positionID].y;

			if( m_chara[i].positionID == 0 && m_chara[i].scale >= 1.0f) {
				m_chara[i].scale = 1.0f;
			}else if( m_chara[i].positionID != 0 && m_chara[i].scale >= 0.8f )
				m_chara[i].scale = 0.8f;
			else
				m_chara[i].scale += 0.01f;
		}
		break;
	}

	int MPuse=0;  //�l�o�����

	static int add = 2.f; // 1f�Ɍ��炷�Q�[�W��
	// HP�����炷
	if( m_pGameData->m_pDamage.damageTaken > 0 ){
		m_chara[m_activeCharaNo].hp -= add;
		m_pGameData->m_pDamage.damageTaken -= add;
	}
	if( m_chara[m_activeCharaNo].hp <= 0){
		m_chara[m_activeCharaNo].hp  = 0;
		m_pGameData->m_death = true;
	}
	// MP�����炷
	if( MPuse > 0 ){
		m_pGameData->m_chara[m_activeCharaNo].mp -= add;
		MPuse -= add;
	}
	if( m_chara[m_activeCharaNo].mp < 0) m_chara[m_activeCharaNo].mp  = 0;

	CScene::m_keyStatePush = 0;
}
void CBattleUI::SetBossHP(CGameData::ENEMY_STATUS _status)
{
	m_enemyMAXHP = _status.maxHP;
	m_enemyHP = _status.hp;
}
void CBattleUI::SetNextPosition()
{
	for(int i = 0; i < PLAYER_MAX; i++){
		m_chara[i].positionID = (m_chara[i].positionID + 1) % PLAYER_MAX;
		m_pGameData->m_turnNo[i] = (m_pGameData->m_turnNo[i] + 1) % PLAYER_MAX;
	}
}


// �Q�[�W�̍ő�X�P�[��(3�{)
static float MAX_GAUGE_SCALE = 3;

void CBattleUI::Draw()
{
	switch( m_state ){
	case STATE_BATTLE:
		m_combo->Draw();
		break;
	case STATE_CHARA_CHANGE:
		break;
	};

	float red,black,white;
	red = black = white = MAX_GAUGE_SCALE;

	// ���Q�[�W
	//m_vertex.SetSizeX(1.f); // �e�N�X�`���T�C�Y�𓙔{�ɖ߂�
	//m_vertex.DrawTextureLT(m_pDevice,enemyGauge,INIT_SIDE_GAUGE_POS,SIDE_RED_GAUGE_VERTEX);	// ���[
	//m_vertex.SetSizeX(MAX_GAUGE_SCALE);	
	//m_vertex.DrawTextureLT(m_pDevice,enemyGauge,INIT_GAUGE_POS,RED_GAUGE_VERTEX);	// ����
	
	// �ԃQ�[�W
	float sideRed = INIT_SCALE;
	
	m_enemyHP = m_enemyHP - m_pGameData->m_pDamage.damage;

	if( ( m_enemyHP / m_enemyMAXHP) <= 0.9f){
		red = MAX_GAUGE_SCALE * ( m_enemyHP / m_enemyMAXHP);
		sideRed = 0;
		if( red <= 0 ){
			red = 0;
			m_pGameData->m_win = true;
		}
	}else{
		float maxHP = m_enemyMAXHP * 0.1f;
		float hp = maxHP - (m_enemyMAXHP - m_enemyHP);
		sideRed = INIT_SCALE * ( hp / maxHP );
	}

	// �e�Q�[�W�̃X�P�[��
	float gaugeScale[GAUGE_TYPE_NUM][2] = {
		{black,INIT_SCALE},
		{white,INIT_SCALE},
		{red,sideRed},
	};
	// �Q�[�W�̒��g��`��
	for(int i = 0; i < GAUGE_TYPE_NUM; i++){

		if(i == WHITE) continue;// ���󔒃Q�[�W�͕`�悵�Ȃ�

		m_vertex.SetSizeX(gaugeScale[i][0]);	// �ԃQ�[�W
		m_vertex.DrawTextureLT(m_pDevice,enemyGauge,INIT_GAUGE_POS,GAUGE_VERTEX[i]);	// ����
		m_vertex.SetSizeX(gaugeScale[i][1]);	// �E�[�ԃQ�[�W
		m_vertex.DrawTextureLT(m_pDevice,enemyGauge,INIT_RIGHT_GAUGE_POS,SIDE_GAUGE_VERTEX[i]);	// ����

	}



	m_vertex.SetSizeX(INIT_SCALE); // �e�N�X�`���T�C�Y�𓙔{�ɖ߂�
	m_vertex.DrawTextureLT(m_pDevice,enemyGauge,INIT_SIDE_GAUGE_POS,SIDE_RED_GAUGE_VERTEX);	// �Q�[�W�̍��[
	m_vertex.DrawTextureLT(m_pDevice,enemyGauge,LEFT_FRAME_POS,LEFT_FRAME_VERTEX);	// �t���[�����[
	m_vertex.DrawTextureLT(m_pDevice,enemyGauge,RIGHT_FRAME_POS,RIGHT_FRAME_VERTEX);// �t���[���E�[
	// �t���[��������
	for(int i = 0;i * FRAME_SIZE < FRAME_MAX_SIZE; i++)
		m_vertex.DrawTextureLT(m_pDevice,enemyGauge,FRAME_POS.x + (i * FRAME_SIZE),FRAME_POS.y,FRAME_VERTEX);


	//UI�\��

	float HPper[3];             //HP%�p�[�Z���e�[�W
	float MPper[3];				//MP%�p�[�Z���e�[�W
	for(int i=0;i<3;i++){		//HP%�p�[�Z���e�[�W MP%�p�[�Z���e�[�W����
		HPper[i]=105*(1.0f-(static_cast<float>(m_chara[m_charaID[i]].hp)/m_chara[m_charaID[i]].MAXhp));
		MPper[i]=105*(1.0f-(static_cast<float>(m_chara[m_charaID[i]].mp)/m_chara[m_charaID[i]].MAXmp));
	}
	static const D3DXVECTOR2 INIT_CHARA_POS[PLAYER_MAX] = {
		D3DXVECTOR2(101,10),
		D3DXVECTOR2(231,50),
		D3DXVECTOR2(326,50),
	};


	// ���Q�[�W
	static const FRECT CHARA_GAUGE_VERTEX = FRECT(120,465,207,570);

	static const float HP_GAUGE_POS = 58;
	static const float MP_GAUGE_POS = 84;
	// y 105;
	// x 87;
	D3DXVECTOR2 FRAME_SIZE = D3DXVECTOR2(105,87);
	//D3DXVECTOR2 shiftPos;

	for(int i = 0; i < PLAYER_MAX; i++){
		if( m_pGameData->m_turnNo[i] == 0 ) {
			//shiftPos = D3DXVECTOR2(0,0);
		}

		m_vertex.SetSizeX(m_chara[i].scale);
		m_vertex.SetSizeY(m_chara[i].scale);
		m_vertex.SetAngle(-90);
		m_vertex.DrawTextureLT(m_pDevice,UI,m_chara[i].position.x + (HP_GAUGE_POS * m_chara[i].scale),m_chara[i].position.y,CHARA_GAUGE_VERTEX);	//�I��ł���L�����̍��Q�[�W�\��
		m_vertex.DrawTextureLT(m_pDevice,UI,m_chara[i].position.x + (HP_GAUGE_POS * m_chara[i].scale),m_chara[i].position.y + HPper[i],0,465+HPper[i],60,570);	//�I��ł���L������HP�\��
		m_vertex.DrawTextureLT(m_pDevice,UI,m_chara[i].position.x + (MP_GAUGE_POS * m_chara[i].scale),m_chara[i].position.y + MPper[i],60,465+MPper[i],120,570);	//�I��ł���L������MP�\��
		m_vertex.DrawTextureLT(m_pDevice,UI,m_chara[i].position.x,m_chara[i].position.y,0+((float)i*145),360,145+((float)i*145),465);	//�I��ł���L�����̕\��
	}
	m_vertex.SetSizeX(1.f);
	m_vertex.SetSizeY(1.f);
	// 62
	// 86
}

const CCombo::vector2 CCombo::NUMBER_POS = CCombo::vector2(100,160); // �����̈ʒu
const float	 CCombo::NUM_SIZE = 64;									 // �����̃T�C�Y
const FRECT CCombo::TELOP_VERTEX = FRECT(296,770,616,870);			 // �e���b�v�̒��_���W
const FRECT CCombo::NUMBER_VERTEX = FRECT(296,680,360,770);			 // �����̒��_���W
CCombo::CCombo(LPDIRECT3DDEVICE9 _pDevice) : m_comboNum(0),m_alpha(255),m_oldComboNum(0), m_pDevice(_pDevice) , m_state(STATE_BATTLE)
{
	m_texture = CTexMgr.Get(TEX_BATTLE_UI );
}
void CCombo::Control(int _comboNum)
{
	// �R���{�����X�V
	m_comboNum  = _comboNum;
	// �R���{�����O�t���[���ƈႤ�ꍇtime�����Z�b�g
	if( m_comboNum == 0 || m_comboNum != m_oldComboNum ){
		m_comboTime = 0;
		m_alpha = 255;
	}

	switch( m_state ){
	case STATE_BATTLE:
		// �R���{����0�ȊO�̏ꍇ�R���{��Ԃ�
		if( _comboNum != 0 ) m_state = STATE_COMBO;
		
		break;
	case STATE_COMBO:
		combodiv.clear();
		// �R���{���𕪊�
		while( m_oldComboNum > 0 ){
			std::vector<int>::iterator it = combodiv.begin();
			it = combodiv.insert(it,m_oldComboNum % 10);
			m_oldComboNum /= 10;
		}

		// �R���{�`��̃��l�����炷
		if( m_comboTime < COMBO_TIME_LIMIT)	
			m_alpha -= 0.6f;
		else if( m_alpha >= COMBO_TIME_LIMIT)
			m_alpha -= 3;
		// �R���{�\������������o�g���֖߂�
		if( m_alpha <= 0 ){
			m_state = STATE_BATTLE;
			m_alpha = 0;
			CBattleScene::comboCount = 0;
		}
	};
	// �R���{����ۑ�
	m_oldComboNum = m_comboNum;
}
void CCombo::Draw()
{

	
	switch( m_state ){
	case STATE_BATTLE:
		// �R���{��Ԃ��������ꂽ��vector�̗v�f���폜
		combodiv.clear();
		break;
	case STATE_COMBO:
		// combo(����)�̕`�� 
		m_vertex.DrawTextureLT(m_pDevice,m_texture,NUMBER_POS,TELOP_VERTEX,D3DCOLOR_ARGB(static_cast<int>(m_alpha),255,255,255));

		// �����̕`��
		for(unsigned i = 0; i < combodiv.size(); i++){
			m_vertex.DrawTextureLT(m_pDevice,m_texture,NUMBER_POS.x + (i * NUM_SIZE),NUMBER_POS.y,
				NUMBER_VERTEX.left+(NUM_SIZE * combodiv[i]),NUMBER_VERTEX.top,NUMBER_VERTEX.right +(NUM_SIZE * combodiv[i]),NUMBER_VERTEX.bottom,
				D3DCOLOR_ARGB(static_cast<int>(m_alpha),255,255,255));
		}
	};
}
