#include "stdafx.h"

// �萔
// �e�N�X�`�����W(�̍�)�̐擪�ʒu
const D3DXVECTOR2 CResultScene::UV_EMB_POSITION(0.f, 0.f);
// �̍������̕��A����
const D3DXVECTOR2 CResultScene::TEX_EMB_SIZE(180.f, 30.f);
// �̍��\�����W
const D3DXVECTOR2 CResultScene::POS_EMB_CHECK(170.f, 280.f);
// �̍�(�I�t�Z�b�g�l)
const D3DXVECTOR2 CResultScene::POS_EMB_OFFSET(80.f, 50.f);
// �̍��\�����W(�X�e�[�W�N���A����̍�)
const D3DXVECTOR2 CResultScene::POS_EMB_CLEAR[] = {
	D3DXVECTOR2(680.f		, 280.f + 5 * 50.f),		// �s�f�̑O�i
	D3DXVECTOR2(680.f+55.f	, 280.f + 6 * 50.f),		// ���󔭌@
	D3DXVECTOR2(915.f		, 280.f + 5 * 50.f),		// �͂̏ؖ�
	D3DXVECTOR2(915.f+55.f	, 280.f + 6 * 50.f),		// �K�E�̐S��
};
// �̍��\�����W(�`�F�b�N�|�C���g��)
const D3DXVECTOR2 CResultScene::POS_CHECKPOINT(750.f, 296.f);

// �e�N�X�`�����W(�̍����)�̈ʒu
const D3DXVECTOR2 CResultScene::UV_EMBBAR_POSITION[] = {D3DXVECTOR2(0.f, 360.f), D3DXVECTOR2(0.f, 385.f)};
// �̍�����̕��A����
const D3DXVECTOR2 CResultScene::TEX_EMBBAR_SIZE[] = {D3DXVECTOR2(400.f, 25.f),D3DXVECTOR2(215.f, 25.f)};
// �̍����(�I�t�Z�b�g�l)
const D3DXVECTOR2 CResultScene::POS_EMBBAR_OFFSET(10.f, 14.f);

// �̍��ʃA�j���[�V��������
const int CResultScene::ANIMNO_LIST[] = {0,4,5,6,7,3,2,1,2,3,2,1};
// �̍��ʂ̐�(����͑S�X�e�[�W32����)
const int CResultScene::EMBBALL_NUMS[] = {32,32,32,32,32,32};
// �̍�������̍��ʂ܂ł̃I�t�Z�b�g�l
const float CResultScene::EMBTOBALL_OFFSET = 160.f;

// �l�������\���ʒu
const D3DXVECTOR2 CResultScene::POS_GET_MONEY[] = {
	D3DXVECTOR2(595.f, 165.f+CStringList::FONT_SIZE_H/8),
	D3DXVECTOR2(915.f, 165.+CStringList::FONT_SIZE_H/4),
	D3DXVECTOR2(595.f, 165.+CStringList::FONT_SIZE_H/4),
};							
// �{�[�i�X�\���ʒu
const D3DXVECTOR2 CResultScene::POS_GET_BONUS[] = {
	D3DXVECTOR2(845.f, 165.f +CStringList::FONT_SIZE_H/8),
	D3DXVECTOR2(1175.f, 165.f+CStringList::FONT_SIZE_H/4),
	D3DXVECTOR2(845.f, 165.f +CStringList::FONT_SIZE_H/4),
};
// �l�������ő包��
const int CResultScene::MONEY_MAX_DIGIT = 6;
// �{�[�i�X�̔{��(�e�̍�)
const float CResultScene::BONUS[] = {1.5f, 1.4f, 1.4f, 1.4f, 1.3f, 1.2f, 1.2f, 1.2f, 1.2f, 1.1f, 1.1f};

// �A�C�e���\���ʒu
const D3DXVECTOR2 CResultScene::POS_ITEM[] = {
	D3DXVECTOR2(500.f, 240.f),
	D3DXVECTOR2(820.f, 240.f),
};

// �X�e�[�W���Ƃ̃`�F�b�N�|�C���g��(���Z�^)
const int CResultScene::STAGE_NUMS[] = {
	4, 8, 12, 16, 20, 24,
};
// �f�t�H���g�J���[
const DWORD CResultScene::DEFAULT_COLOR = D3DCOLOR_XRGB(255,255,255);

/*------------------------------------------------------
	
	�R���X�g���N�^
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param CGameData*			�Q�[���f�[�^

------------------------------------------------------*/
CResultScene::CResultScene(LPDIRECT3DDEVICE9 _pDevice, CGameData* _pGameData,CInput* _input) :
CScene( _pDevice , _input ), m_cntMoney( 0 ), m_pGameData( _pGameData )
{
	CScene::m_keyStatePush = 0;

	m_stageID = m_pGameData->m_nowClearStageNum/4;
	// ��(�f�o�b�O�p)
//	m_pGameData->m_death = true;
//	m_pGameData->m_nowClearStageNum = 2;
	m_pGameData->m_resultMoney = 5000;
	// �f�o�b�O�����܂�

	// �X�e�[�WID
	
	// �V�[���h�c�����U���g��
	m_sceneID = SCENE_RESULT;

	// ��Ԃ��l�������\����
	m_state = STATE_MONEY;
	// �l������
//	m_pGameData->m_resultMoney = 5000;
	// �{�[�i�X���v�Z
	CulcBonus( m_pGameData->m_nowClearStageNum );

	// �e�N�X�`���Z�b�g�̓ǂݍ���
	CTexMgr.Load(SCENE_RESULT, m_pDevice);


	// �w�i�p�̃e�N�X�`���̓Q�[���f�[�^�̃X�e�[�W�ԍ��Ō��߂�
	// �s�k���ŗD�����
	if( m_pGameData->m_death ) {
		m_texBG = CTexMgr.Get( m_bgID = BG_LOSE );
	} else if( m_pGameData->m_nowClearStageNum < STAGE_NUMS[ m_stageID ]-1 ) {
		// ���݂̃X�e�[�W�ő吔�ȉ��Ȃ�`�F�b�N�|�C���g�ʉߎ�
		m_texBG = CTexMgr.Get( m_bgID = BG_CHECK );
	} else {
		// �{�X�X�e�[�W
		m_texBG = CTexMgr.Get( m_bgID = BG_CLEAR );
	}
	// �\�����p�e�N�X�`��
	m_texUI = CTexMgr.Get( TEX_UI_NO );
	// �A�C�e���e�N�X�`��
	m_texIcon = CTexMgr.Get( TEX_ICON );

	// �̍��ʐ���

	// �N���A���Ă�X�e�[�W�����X�e�[�W���̃`�F�b�N�|�C���g�����������
	m_embBallNum = m_pGameData->m_nowClearStageNum < STAGE_NUMS[ m_stageID ]-1 ? NUM_CHECK_EMB : EMBBALL_NUMS[ m_stageID ];
	// ���S�t���O�������Ă�����s�k��ʗp�H
	bool isLose = m_pGameData->m_death;
	if( isLose ) { m_embBallNum = NUM_CHECK_EMB*3; }
	m_embBall = new EmblemBall*[ m_embBallNum ];

	// �`�F�b�N�|�C���g/�N���A���ʏ̍�
	int min = m_embBallNum == NUM_CHECK_EMB ? (m_pGameData->m_nowClearStageNum % 4) * NUM_CHECK_EMB : 0;
	int max = m_embBallNum == NUM_CHECK_EMB ? min + NUM_CHECK_EMB : NUM_CHECK_EMB*4;

	// �s�k���Ă����ꍇ�͐i�݋�Ɋ֌W�Ȃ��A�R�̃`�F�b�N�|�C���g�����ׂĕ\��
	if( isLose ) {
		min = 0;
		max = NUM_CHECK_EMB*3;
	}
	for( int i = min; i < max; i++ ) {
		int lineNum = isLose ? i /  3 : m_embBallNum == NUM_CHECK_EMB ? 0 : i / 4;
		int rawNum = isLose ? i % 3 : m_embBallNum == NUM_CHECK_EMB ? min/NUM_CHECK_EMB : i % 4;

		int type = rawNum == 3 ? EmblemBall::TYPE_GOLD : EmblemBall::TYPE_SILVER;
		int getType = m_pGameData->m_stageEmbFlag[m_stageID][rawNum][m_embBallNum == NUM_CHECK_EMB ? i - min : lineNum];

		D3DXVECTOR2 p;

		if( m_embBallNum != NUM_CHECK_EMB && !isLose ) {
			p = D3DXVECTOR2((rawNum == 3 ? POS_EMB_CHECK.x + TEX_EMBBAR_SIZE[0].x + (lineNum%2  ? POS_EMB_OFFSET.x/2 : 0.f): POS_EMB_CHECK.x+EMBTOBALL_OFFSET+(lineNum%2  ? POS_EMB_OFFSET.x : 0.f) + rawNum * 50.f),
				POS_EMB_CHECK.y + lineNum * POS_EMB_OFFSET.y);
		} else {
			if( isLose ) {
				p = D3DXVECTOR2(POS_CHECKPOINT.x + rawNum * 50.f,
					POS_CHECKPOINT.y + lineNum * POS_EMB_OFFSET.y);
			} else {
				p = D3DXVECTOR2(POS_CHECKPOINT.x, POS_CHECKPOINT.y + (i-min) * POS_EMB_OFFSET.y);
			}
		}
		m_embBall[i-min] = new EmblemBall( type, getType, p );
	}
	// �N���A���̂�
	if( m_embBallNum != NUM_CHECK_EMB && !isLose ) {
		for( int i = 0; i < 4; i++ ) {
			int type = EmblemBall::TYPE_GOLD;
			int getType = m_pGameData->m_stageEmbFlag[m_stageID][3][i+NUM_CHECK_EMB];

			D3DXVECTOR2 p(POS_EMB_CLEAR[i].x+EMBTOBALL_OFFSET,
				POS_EMB_CLEAR[i].y);

			m_embBall[i+NUM_CHECK_EMB*4] = new EmblemBall( type, getType, p );
		}
	}

	m_addMoney = 1;
}

/*------------------------------------------------------
	
	�f�X�g���N�^

------------------------------------------------------*/
CResultScene::~CResultScene()
{
	// �e�N�X�`���Z�b�g�̉��
	CTexMgr.Release();

	// �̍��ʂ̉��
	for( int i = 0; i < m_embBallNum; i++ ) {
		SAFE_DELETE( m_embBall[i] );
	}
	SAFE_DELETE_ARRAY( m_embBall );
}

/*------------------------------------------------------
	
	����
	@param	�Ȃ�
	@return �V�[���ԍ�

------------------------------------------------------*/
CResultScene::SceneID CResultScene::Control()
{
	 CScene::m_keyStatePush  = 0;
	CScene::Control();

	// S�{�^���������ꂽ���̏���
	if( CScene::m_keyStatePush == KEY_S )
	{
		if( m_state <= STATE_BONUS ) m_state = STATE_NEXTSCENE;
		else if( m_state == STATE_NEXTSCENE ) {
			// ���S���͐퓬�����֖߂�
			if( m_pGameData->m_death ){
				return SCENE_GAME;
			}
			// �I��ł���X�e�[�W���{�X�X�e�[�W�Ȃ�Q�[���V�[���ցH
			if( (m_pGameData->m_selectStageNum + 1) % 4 == 0 ){
				return SCENE_GAME;
			}else if( m_pGameData->m_selectStageNum >= m_pGameData->m_nowClearStageNum ){
				// �I�������X�e�[�W�����N���A��ԂȂ�
				m_pGameData->m_selectStageNum++;
				m_pGameData->m_nowClearStageNum++;
			}else
				// �N���A�ς݂ł���ΑI�����Ă���X�e�[�WID�݂̂����߂�H
				m_pGameData->m_selectStageNum++;

			// �����܂ŗ����珬�{�X�X�e�[�W�Ȃ̂�win�t���O�͉���
			m_pGameData->m_win = false;
			return SCENE_BATTLE;
			/*if( m_pGameData->m_selectStageNum < 
				m_embBallNum == EMBBALL_NUMS[ m_stageID ] )	return SCENE_GAME;
			else{			
				m_pGameData->m_nowClearStageNum++;
				return SCENE_BATTLE;
			*/
		}
	}

	// �̍��ʃA�j���[�V����
	for( int i = 0; i < m_embBallNum; i++ ) {
		m_embBall[i]->Control();
	}

	int result = -1;
	// ��ԂŃV�[���𕪊�
	switch( m_state ) {
	case STATE_MONEY:
		result = m_pGameData->m_resultMoney;
		break;
	case STATE_BONUS:
		result = m_bonus;
		break;
	}

	if( m_state < STATE_NEXTSCENE ) {
		if( m_cntMoney < result ) {
			m_cntMoney += m_addMoney;

			// ����1�i�KUP�����瑝�₷�ʂ𑝂₷
			if( m_addMoney * 10 <= m_cntMoney ) m_addMoney *= 10 + 1;
		} else {
			m_cntMoney = -1;
			// �����̃J�E���g���ő�Ȃ玟�̏�Ԃ�
			m_state = static_cast<State>(m_state + 1);
		}
	}

	return m_sceneID;
}

/*------------------------------------------------------
	
	�`��
	@param	�Ȃ�
	@return �Ȃ�

------------------------------------------------------*/
void CResultScene::Draw()
{
	CVertex v;
	v.DrawTextureCC( m_pDevice, m_texBG, CLIENT_WIDTH/2, CLIENT_HEIGHT/2, DEFAULT_COLOR);

	// �w�iID�ŏ����𕪊�
	switch( m_bgID ) {
	case BG_CHECK:	// �`�F�b�N�|�C���g�ʉߎ�
		break;
	case BG_CLEAR:	// �X�e�[�W�N���A��
		{
			for( int i = 0; i < NUM_MAX_EMB; i++ ) {
				int type = i >= NUM_CHECK_EMB;

				// ���
				FRECT srcBar(UV_EMBBAR_POSITION[type].x, UV_EMBBAR_POSITION[type].y, 
					UV_EMBBAR_POSITION[type].x+TEX_EMBBAR_SIZE[type].x, UV_EMBBAR_POSITION[type].y+TEX_EMBBAR_SIZE[type].y);

				// �`����W
				D3DXVECTOR2 drawPos = type == 0 ? 
					D3DXVECTOR2( POS_EMB_CHECK.x + (i%2 ? POS_EMB_OFFSET.x : 0.f), POS_EMB_CHECK.y + POS_EMB_OFFSET.y*i) : 
					POS_EMB_CLEAR[ i - NUM_CHECK_EMB ];

				v.DrawTextureLT( m_pDevice, m_texUI, drawPos.x + POS_EMBBAR_OFFSET.x, drawPos.y + POS_EMBBAR_OFFSET.y, srcBar, DEFAULT_COLOR );

				// �̍�
				FRECT srcEmb(UV_EMB_POSITION.x, UV_EMB_POSITION.y+i*TEX_EMB_SIZE.y, 
					UV_EMB_POSITION.x+TEX_EMB_SIZE.x, UV_EMB_POSITION.y+(i+1)*TEX_EMB_SIZE.y);
				
				v.DrawTextureLT( m_pDevice, m_texUI, drawPos.x, drawPos.y, srcEmb, DEFAULT_COLOR );

			}
		}
		break;
	case BG_LOSE:	// �s�k��
		break;
	}

	// �̍��ʂ̕\��
	for( int i = 0; i < m_embBallNum; i++ ) {
		m_embBall[i]->Draw(m_pDevice, m_texUI);
	}

	// �����̌����擾
	int money = m_state == STATE_MONEY ? m_cntMoney : m_pGameData->m_resultMoney;
	DrawMoney( money, POS_GET_MONEY[m_bgID] );

	if( m_state >= STATE_BONUS ) {
		money = m_state == STATE_BONUS ? m_cntMoney : m_bonus;
		DrawMoney( money, POS_GET_BONUS[m_bgID] );
	}

	int itemNum = m_pGameData->m_nowClearStageNum < STAGE_NUMS[ m_stageID ]-1 ? STAGE_BOSS : STAGE_CHECK;
	for( unsigned i = 0; i < m_pGameData->m_getItem.size(); i++ ) {
		v.DrawTextureLT( m_pDevice, m_texIcon, POS_ITEM[ itemNum ].x + 10.f * i , POS_ITEM[ itemNum ].y, 
			GetItemRect(m_pGameData->m_getItem[i].no) );
	}
}

// �e�N�X�`�����W
const FRECT CResultScene::EmblemBall::EMBBALL_RECT[] = {
	FRECT(0, 408, 60, 459),
	FRECT(0, 459, 60, 510),
};

/*------------------------------------------------------
	
	�R���X�g���N�^
	@param int			�����₩
	@param int			�擾�����^�C�~���O
	@param D3DXVECTOR2	�\���ʒu

------------------------------------------------------*/
CResultScene::EmblemBall::EmblemBall(int _type, int _getType, D3DXVECTOR2 _pos) :
m_type( _type ), m_getType( _getType ), m_pos( _pos ), m_animNo( 0 ), m_animSpd( 10 ),
m_animCnt( 0 ), m_rect( EMBBALL_RECT[_type] )
{

}

/*------------------------------------------------------
	
	����(�A�j���[�V����)
	@param	�Ȃ�
	@return �Ȃ�

------------------------------------------------------*/
void CResultScene::EmblemBall::Control()
{
	// �擾�^�C�v�ŕ���
	switch( m_getType )
	{
	case TYPE_YET:	// �擾�܂�
		// �A�j���[�V�����͂Ȃ�
		break;
	default:		// �擾�ς�/����擾
		if( m_animCnt++ > m_animSpd ) {
			m_animNo = (1+m_animNo) % (sizeof(ANIMNO_LIST) / sizeof(int));
			if( m_animNo == 0 ) {	// ���[�v������5����J�n
				m_animNo = 5;
			}
			m_animCnt = 0;
		}
		// ��`�X�V
		m_rect.left = EMBBALL_RECT[ m_type ].left + ANIMNO_LIST[m_animNo] * 60;
		m_rect.right = m_rect.left + 60;
		break;
	}
}

/*------------------------------------------------------
	
	�`��
	@param	�Ȃ�
	@return �Ȃ�

------------------------------------------------------*/
void CResultScene::EmblemBall::Draw(LPDIRECT3DDEVICE9 _pDevice, CTexture _tex)
{
	CVertex v;

	D3DCOLOR drawColor = m_getType == TYPE_NOW ? DEFAULT_COLOR : D3DCOLOR_XRGB(128,128,128);

	v.DrawTextureLT(_pDevice, _tex, m_pos.x, m_pos.y, m_rect, drawColor);
}

//=====================�����֐�===================================

/*------------------------------------------------------
	
	�{�[�i�X�v�Z
	@param	int		�X�e�[�W�ԍ�
	@return �Ȃ�

------------------------------------------------------*/
void CResultScene::CulcBonus(int _stageID)
{
	float bonus = static_cast<float>(m_pGameData->m_resultMoney);

	// �X�e�[�W�N���A��̂ݒǉ��{������	
	for( int i = 0; i < (_stageID != 0 && _stageID % 3 == STAGE_BOSS ? NUM_MAX_EMB : NUM_CHECK_EMB) ; i++ ) {
		// ���ł��擾�����Ȃ�{���v�Z�Ɋ܂߂�
		if( m_pGameData->m_stageEmbFlag[_stageID / 4][_stageID % 4][i] )
			bonus *= BONUS[i];
	}
	m_bonus = static_cast<int>(bonus) - m_pGameData->m_resultMoney;
}

/*------------------------------------------------------
	
	�l������/�{�[�i�X�\��
	@param	int				�\�����邨��
	@param	D3DXVECTOR2		�\������ʒu
	@return �Ȃ�

------------------------------------------------------*/
void CResultScene::DrawMoney(int _money, D3DXVECTOR2 _pos)
{
	int digit = static_cast<int>(log10(static_cast<float>(_money))+1);
	// ������0�̂Ƃ��͋����Ō���1���ɂ���
	if( _money == 0 ) digit = 1;
	for( int i = 0, n = _money; i < digit; i++, n /= 10) {
		// 1���擾
		CStringList::numberStrList[n%10]->Draw( _pos.x - i*CStringList::FONT_SIZE_W,
			_pos.y, DEFAULT_COLOR, 1 );
	}
}

/*------------------------------------------------------

	�A�C�e����`�v�Z
	@param	int				�A�C�e���ԍ�
	@return �A�C�e����`

------------------------------------------------------*/
FRECT CResultScene::GetItemRect(int _no)
{
	int w = _no % 7;
	int h = _no / 7;

	return FRECT(w * 40.f, h * 40.f, (w+1)*40.f, (h+1)*40.f);
}
