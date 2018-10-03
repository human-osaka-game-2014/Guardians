/**
 * @file DbattleScene.cpp
 */

#include "stdafx.h"

bool CBattleScene::m_pause = false;
// �R���{��
int  CBattleScene::comboCount = 0;
// ���E�̕�
const float CBattleScene::RIGHT_WALL = 20.f;
const float CBattleScene::LEFT_WALL = 4.8f;


CBattleScene::CBattleScene(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CInput* _input,CCharacterManager::MODELDATA* _chara,CField* _field) :
	CScene(_pDevice,_input),m_pGameData(_pGameData) , m_cameraPos(-5.f,0.f) , m_move(0.f,0.f), m_alpha(m_pGameData->m_nowClearStageNum % 4 == 0 ? 255 : 0)
	,m_charaChange(STATE_BATTLE)
{
	m_sceneID = SCENE_BATTLE;

	CTexMgr.Load(m_sceneID, m_pDevice);

	CScene::m_keyStateOn = 0;
	CScene::m_keyStatePush = 0;

	m_field = _field;
	// ���U���g�o�R�p�Ƀt�B�[���h���W�����Z�b�g����
	m_field->SetPosition( D3DXVECTOR2(0.f,0.f) );
	
	// �~�σ_���[�W�����Z�b�g
	m_pGameData->m_pDamage.damage = 0;
	m_pGameData->m_pDamage.damageTaken = 0;
	comboCount = 0;

	m_camera = new CCamera(m_pDevice);

	m_character = new CCharacterManager(m_pDevice,_pGameData,_chara);

	m_ui = new CBattleUI(m_pDevice,_pGameData);

	m_feed = CTexMgr.Get( 16 );

}

CBattleScene::~CBattleScene()
{
	//SAFE_DELETE(m_field);
	SAFE_DELETE(m_ui);

	SAFE_DELETE(m_camera);

	SAFE_DELETE(m_character);

	CTexMgr.Release();
}
CBattleScene::SceneID CBattleScene::Control()
{
	
	CScene::Control();

	// �|�[�Y����
	if( ( m_keyStateOn & KEY_SPACE) && !m_pause) 
		m_pause = true;
	else if( ( m_keyStateOn & KEY_SPACE) && m_pause)
		m_pause = false;

	if( m_pause ){
		m_keyStateOn = 0;	// �L�[���͂𖳌���
		return SCENE_BATTLE;	// �|�[�Y���͂����ŏ������~�߂�
	}

	// �L�������
	switch( m_charaChange ){
	case STATE_BATTLE:
		if( (CScene::m_keyStatePush & KEY_A) != 0 ){
			m_charaChange = STATE_CHARA_CHANGE;
			m_changeTime = 0;
		}
		break;
	case STATE_CHARA_CHANGE:
		int add = CC_MAX_ALPHA / CC_ADDALPHA_FRAME;	// 1F�̃A���t�@������
		// �L�����ύX���͉�ʂ��Â�
		if( m_changeTime <= CC_ADDALPHA_FRAME ){
			m_alpha += add;
			if( m_alpha >= CC_MAX_ALPHA ) m_alpha = CC_MAX_ALPHA;
		}else if( m_changeTime >= CHANGE_LIMIT - CC_ADDALPHA_FRAME ){
			// �L�����ύX���̌o�ߎ��Ԃ��^�C�����~�b�g10�t���[���O�Ȃ�
			m_alpha -= add;
			if( m_alpha <= 0 ) m_alpha = 0;
		}

		if( (CScene::m_keyStatePush & KEY_A) != 0){

			m_changeTime = 0;	// �o�ߎ��Ԃ�0��

			m_ui->SetNextPosition();

		}
		m_character->CharacterChange();
		m_changeTime++;
		// �������Ԃ��߂��Ă�����
		if( m_changeTime >= CHANGE_LIMIT ){
			m_charaChange = STATE_BATTLE;	// �퓬��Ԃɖ߂�
			m_character->SetAlpha();
		}
		break;
	}

	m_character->Control();
	// UI
	m_ui->SetBossHP(m_character->GetHP());
	m_ui->Control();
	// �t�B�[���h�̈ړ��ʂ����߂�
	m_move = m_character->GetCharaSpeed();
	// �v���C���[�̈ʒu���擾
	m_playerPos = m_character->GetPlayer()->GetPosition();

	// �J�����ړ��͈�
	if( m_playerPos.x >= RIGHT_WALL ){
		m_playerPos.x = RIGHT_WALL;
		m_move.x = 0.f;
	}
	if( m_playerPos.x <= LEFT_WALL ){
		m_playerPos.x = LEFT_WALL;
		m_move.x = 0.f;
	}

	// �퓬�J�n���̃t�F�[�h�C������
	if( m_playerPos.y <= 0.f ) {
		m_alpha--;
		if( m_alpha <= 0 ) m_alpha = 0; 
	}

	m_field->SetCharaSpeed( m_move );
	m_field->Control();

	// �s�k��
	if( m_pGameData->m_death){
		if ( m_character->GetMotionEnd(CPlayer::MOTION_DEAD) )
			return SCENE_RESULT;
	}
	// ������
	if( m_pGameData->m_win ){
		if ( m_character->GetMotionEnd(CPlayer::MOTION_APPEAL2) ){
			return SCENE_RESULT;
		}
	}
	
	m_keyStateOn = 0;

	return SCENE_BATTLE;
}

void CBattleScene::Draw()
{

	D3DXVECTOR3 eye = D3DXVECTOR3(m_playerPos.x, m_playerPos.y  + 18.f, -50.f);
	// �����_
	m_camera->Look(eye, D3DXVECTOR3(m_playerPos.x, m_playerPos.y  + 18.f, 0.f));


	m_field->Draw();

	m_character->Draw();

	m_ui->Draw();

	// �t�F�[�h�C���p�摜�̕`��
	DrawBlackPic(m_alpha);
}

/**
 * FadeIn Out �p�摜�̐���
 * @param[in] _alpha �A���t�@�l
 */
void CBattleScene::DrawBlackPic(int _alpha)
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	CVertex vertex;
	vertex.DrawTextureLT(m_pDevice, m_feed, 0.f, 0.f, D3DCOLOR_ARGB(m_alpha,255,255,255));
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
