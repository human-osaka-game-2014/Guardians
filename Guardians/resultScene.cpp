#include "stdafx.h"

// 定数
// テクスチャ座標(称号)の先頭位置
const D3DXVECTOR2 CResultScene::UV_EMB_POSITION(0.f, 0.f);
// 称号文字の幅、高さ
const D3DXVECTOR2 CResultScene::TEX_EMB_SIZE(180.f, 30.f);
// 称号表示座標
const D3DXVECTOR2 CResultScene::POS_EMB_CHECK(170.f, 280.f);
// 称号(オフセット値)
const D3DXVECTOR2 CResultScene::POS_EMB_OFFSET(80.f, 50.f);
// 称号表示座標(ステージクリア限定称号)
const D3DXVECTOR2 CResultScene::POS_EMB_CLEAR[] = {
	D3DXVECTOR2(680.f		, 280.f + 5 * 50.f),		// 不断の前進
	D3DXVECTOR2(680.f+55.f	, 280.f + 6 * 50.f),		// お宝発掘
	D3DXVECTOR2(915.f		, 280.f + 5 * 50.f),		// 力の証明
	D3DXVECTOR2(915.f+55.f	, 280.f + 6 * 50.f),		// 必殺の心得
};
// 称号表示座標(チェックポイント時)
const D3DXVECTOR2 CResultScene::POS_CHECKPOINT(750.f, 296.f);

// テクスチャ座標(称号台座)の位置
const D3DXVECTOR2 CResultScene::UV_EMBBAR_POSITION[] = {D3DXVECTOR2(0.f, 360.f), D3DXVECTOR2(0.f, 385.f)};
// 称号台座の幅、高さ
const D3DXVECTOR2 CResultScene::TEX_EMBBAR_SIZE[] = {D3DXVECTOR2(400.f, 25.f),D3DXVECTOR2(215.f, 25.f)};
// 称号台座(オフセット値)
const D3DXVECTOR2 CResultScene::POS_EMBBAR_OFFSET(10.f, 14.f);

// 称号玉アニメーション順番
const int CResultScene::ANIMNO_LIST[] = {0,4,5,6,7,3,2,1,2,3,2,1};
// 称号玉の数(現状は全ステージ32個ずつ)
const int CResultScene::EMBBALL_NUMS[] = {32,32,32,32,32,32};
// 称号名から称号玉までのオフセット値
const float CResultScene::EMBTOBALL_OFFSET = 160.f;

// 獲得資金表示位置
const D3DXVECTOR2 CResultScene::POS_GET_MONEY[] = {
	D3DXVECTOR2(595.f, 165.f+CStringList::FONT_SIZE_H/8),
	D3DXVECTOR2(915.f, 165.+CStringList::FONT_SIZE_H/4),
	D3DXVECTOR2(595.f, 165.+CStringList::FONT_SIZE_H/4),
};							
// ボーナス表示位置
const D3DXVECTOR2 CResultScene::POS_GET_BONUS[] = {
	D3DXVECTOR2(845.f, 165.f +CStringList::FONT_SIZE_H/8),
	D3DXVECTOR2(1175.f, 165.f+CStringList::FONT_SIZE_H/4),
	D3DXVECTOR2(845.f, 165.f +CStringList::FONT_SIZE_H/4),
};
// 獲得資金最大桁数
const int CResultScene::MONEY_MAX_DIGIT = 6;
// ボーナスの倍率(各称号)
const float CResultScene::BONUS[] = {1.5f, 1.4f, 1.4f, 1.4f, 1.3f, 1.2f, 1.2f, 1.2f, 1.2f, 1.1f, 1.1f};

// アイテム表示位置
const D3DXVECTOR2 CResultScene::POS_ITEM[] = {
	D3DXVECTOR2(500.f, 240.f),
	D3DXVECTOR2(820.f, 240.f),
};

// ステージごとのチェックポイント数(加算型)
const int CResultScene::STAGE_NUMS[] = {
	4, 8, 12, 16, 20, 24,
};
// デフォルトカラー
const DWORD CResultScene::DEFAULT_COLOR = D3DCOLOR_XRGB(255,255,255);

/*------------------------------------------------------
	
	コンストラクタ
	@param LPDIRECT3DDEVICE9	描画デバイス
	@param CGameData*			ゲームデータ

------------------------------------------------------*/
CResultScene::CResultScene(LPDIRECT3DDEVICE9 _pDevice, CGameData* _pGameData,CInput* _input) :
CScene( _pDevice , _input ), m_cntMoney( 0 ), m_pGameData( _pGameData )
{
	CScene::m_keyStatePush = 0;

	m_stageID = m_pGameData->m_nowClearStageNum/4;
	// 仮(デバッグ用)
//	m_pGameData->m_death = true;
//	m_pGameData->m_nowClearStageNum = 2;
	m_pGameData->m_resultMoney = 5000;
	// デバッグここまで

	// ステージID
	
	// シーンＩＤをリザルトに
	m_sceneID = SCENE_RESULT;

	// 状態を獲得資金表示に
	m_state = STATE_MONEY;
	// 獲得資金
//	m_pGameData->m_resultMoney = 5000;
	// ボーナスを計算
	CulcBonus( m_pGameData->m_nowClearStageNum );

	// テクスチャセットの読み込み
	CTexMgr.Load(SCENE_RESULT, m_pDevice);


	// 背景用のテクスチャはゲームデータのステージ番号で決める
	// 敗北時最優先条件
	if( m_pGameData->m_death ) {
		m_texBG = CTexMgr.Get( m_bgID = BG_LOSE );
	} else if( m_pGameData->m_nowClearStageNum < STAGE_NUMS[ m_stageID ]-1 ) {
		// 現在のステージ最大数以下ならチェックポイント通過時
		m_texBG = CTexMgr.Get( m_bgID = BG_CHECK );
	} else {
		// ボスステージ
		m_texBG = CTexMgr.Get( m_bgID = BG_CLEAR );
	}
	// 表示物用テクスチャ
	m_texUI = CTexMgr.Get( TEX_UI_NO );
	// アイテムテクスチャ
	m_texIcon = CTexMgr.Get( TEX_ICON );

	// 称号玉生成

	// クリアしてるステージ数よりステージ毎のチェックポイント数が多ければ
	m_embBallNum = m_pGameData->m_nowClearStageNum < STAGE_NUMS[ m_stageID ]-1 ? NUM_CHECK_EMB : EMBBALL_NUMS[ m_stageID ];
	// 死亡フラグが立っていたら敗北画面用？
	bool isLose = m_pGameData->m_death;
	if( isLose ) { m_embBallNum = NUM_CHECK_EMB*3; }
	m_embBall = new EmblemBall*[ m_embBallNum ];

	// チェックポイント/クリア共通称号
	int min = m_embBallNum == NUM_CHECK_EMB ? (m_pGameData->m_nowClearStageNum % 4) * NUM_CHECK_EMB : 0;
	int max = m_embBallNum == NUM_CHECK_EMB ? min + NUM_CHECK_EMB : NUM_CHECK_EMB*4;

	// 敗北していた場合は進み具合に関係なく、３つのチェックポイント分すべて表示
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
	// クリア時のみ
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
	
	デストラクタ

------------------------------------------------------*/
CResultScene::~CResultScene()
{
	// テクスチャセットの解放
	CTexMgr.Release();

	// 称号玉の解放
	for( int i = 0; i < m_embBallNum; i++ ) {
		SAFE_DELETE( m_embBall[i] );
	}
	SAFE_DELETE_ARRAY( m_embBall );
}

/*------------------------------------------------------
	
	制御
	@param	なし
	@return シーン番号

------------------------------------------------------*/
CResultScene::SceneID CResultScene::Control()
{
	 CScene::m_keyStatePush  = 0;
	CScene::Control();

	// Sボタンが押された時の処理
	if( CScene::m_keyStatePush == KEY_S )
	{
		if( m_state <= STATE_BONUS ) m_state = STATE_NEXTSCENE;
		else if( m_state == STATE_NEXTSCENE ) {
			// 死亡時は戦闘準備へ戻る
			if( m_pGameData->m_death ){
				return SCENE_GAME;
			}
			// 選んでいるステージがボスステージならゲームシーンへ？
			if( (m_pGameData->m_selectStageNum + 1) % 4 == 0 ){
				return SCENE_GAME;
			}else if( m_pGameData->m_selectStageNum >= m_pGameData->m_nowClearStageNum ){
				// 選択したステージが未クリア状態なら
				m_pGameData->m_selectStageNum++;
				m_pGameData->m_nowClearStageNum++;
			}else
				// クリア済みであれば選択しているステージIDのみを勧める？
				m_pGameData->m_selectStageNum++;

			// ここまで来たら小ボスステージなのでwinフラグは解除
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

	// 称号玉アニメーション
	for( int i = 0; i < m_embBallNum; i++ ) {
		m_embBall[i]->Control();
	}

	int result = -1;
	// 状態でシーンを分岐
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

			// 桁が1段階UPしたら増やす量を増やす
			if( m_addMoney * 10 <= m_cntMoney ) m_addMoney *= 10 + 1;
		} else {
			m_cntMoney = -1;
			// お金のカウントが最大なら次の状態へ
			m_state = static_cast<State>(m_state + 1);
		}
	}

	return m_sceneID;
}

/*------------------------------------------------------
	
	描画
	@param	なし
	@return なし

------------------------------------------------------*/
void CResultScene::Draw()
{
	CVertex v;
	v.DrawTextureCC( m_pDevice, m_texBG, CLIENT_WIDTH/2, CLIENT_HEIGHT/2, DEFAULT_COLOR);

	// 背景IDで処理を分岐
	switch( m_bgID ) {
	case BG_CHECK:	// チェックポイント通過時
		break;
	case BG_CLEAR:	// ステージクリア時
		{
			for( int i = 0; i < NUM_MAX_EMB; i++ ) {
				int type = i >= NUM_CHECK_EMB;

				// 台座
				FRECT srcBar(UV_EMBBAR_POSITION[type].x, UV_EMBBAR_POSITION[type].y, 
					UV_EMBBAR_POSITION[type].x+TEX_EMBBAR_SIZE[type].x, UV_EMBBAR_POSITION[type].y+TEX_EMBBAR_SIZE[type].y);

				// 描画座標
				D3DXVECTOR2 drawPos = type == 0 ? 
					D3DXVECTOR2( POS_EMB_CHECK.x + (i%2 ? POS_EMB_OFFSET.x : 0.f), POS_EMB_CHECK.y + POS_EMB_OFFSET.y*i) : 
					POS_EMB_CLEAR[ i - NUM_CHECK_EMB ];

				v.DrawTextureLT( m_pDevice, m_texUI, drawPos.x + POS_EMBBAR_OFFSET.x, drawPos.y + POS_EMBBAR_OFFSET.y, srcBar, DEFAULT_COLOR );

				// 称号
				FRECT srcEmb(UV_EMB_POSITION.x, UV_EMB_POSITION.y+i*TEX_EMB_SIZE.y, 
					UV_EMB_POSITION.x+TEX_EMB_SIZE.x, UV_EMB_POSITION.y+(i+1)*TEX_EMB_SIZE.y);
				
				v.DrawTextureLT( m_pDevice, m_texUI, drawPos.x, drawPos.y, srcEmb, DEFAULT_COLOR );

			}
		}
		break;
	case BG_LOSE:	// 敗北時
		break;
	}

	// 称号玉の表示
	for( int i = 0; i < m_embBallNum; i++ ) {
		m_embBall[i]->Draw(m_pDevice, m_texUI);
	}

	// 数字の桁数取得
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

// テクスチャ座標
const FRECT CResultScene::EmblemBall::EMBBALL_RECT[] = {
	FRECT(0, 408, 60, 459),
	FRECT(0, 459, 60, 510),
};

/*------------------------------------------------------
	
	コンストラクタ
	@param int			金か銀か
	@param int			取得したタイミング
	@param D3DXVECTOR2	表示位置

------------------------------------------------------*/
CResultScene::EmblemBall::EmblemBall(int _type, int _getType, D3DXVECTOR2 _pos) :
m_type( _type ), m_getType( _getType ), m_pos( _pos ), m_animNo( 0 ), m_animSpd( 10 ),
m_animCnt( 0 ), m_rect( EMBBALL_RECT[_type] )
{

}

/*------------------------------------------------------
	
	操作(アニメーション)
	@param	なし
	@return なし

------------------------------------------------------*/
void CResultScene::EmblemBall::Control()
{
	// 取得タイプで分岐
	switch( m_getType )
	{
	case TYPE_YET:	// 取得まだ
		// アニメーションはなし
		break;
	default:		// 取得済み/今回取得
		if( m_animCnt++ > m_animSpd ) {
			m_animNo = (1+m_animNo) % (sizeof(ANIMNO_LIST) / sizeof(int));
			if( m_animNo == 0 ) {	// ループしたら5から開始
				m_animNo = 5;
			}
			m_animCnt = 0;
		}
		// 矩形更新
		m_rect.left = EMBBALL_RECT[ m_type ].left + ANIMNO_LIST[m_animNo] * 60;
		m_rect.right = m_rect.left + 60;
		break;
	}
}

/*------------------------------------------------------
	
	描画
	@param	なし
	@return なし

------------------------------------------------------*/
void CResultScene::EmblemBall::Draw(LPDIRECT3DDEVICE9 _pDevice, CTexture _tex)
{
	CVertex v;

	D3DCOLOR drawColor = m_getType == TYPE_NOW ? DEFAULT_COLOR : D3DCOLOR_XRGB(128,128,128);

	v.DrawTextureLT(_pDevice, _tex, m_pos.x, m_pos.y, m_rect, drawColor);
}

//=====================内部関数===================================

/*------------------------------------------------------
	
	ボーナス計算
	@param	int		ステージ番号
	@return なし

------------------------------------------------------*/
void CResultScene::CulcBonus(int _stageID)
{
	float bonus = static_cast<float>(m_pGameData->m_resultMoney);

	// ステージクリア後のみ追加倍率あり	
	for( int i = 0; i < (_stageID != 0 && _stageID % 3 == STAGE_BOSS ? NUM_MAX_EMB : NUM_CHECK_EMB) ; i++ ) {
		// 一回でも取得したなら倍率計算に含める
		if( m_pGameData->m_stageEmbFlag[_stageID / 4][_stageID % 4][i] )
			bonus *= BONUS[i];
	}
	m_bonus = static_cast<int>(bonus) - m_pGameData->m_resultMoney;
}

/*------------------------------------------------------
	
	獲得資金/ボーナス表示
	@param	int				表示するお金
	@param	D3DXVECTOR2		表示する位置
	@return なし

------------------------------------------------------*/
void CResultScene::DrawMoney(int _money, D3DXVECTOR2 _pos)
{
	int digit = static_cast<int>(log10(static_cast<float>(_money))+1);
	// お金が0のときは強制で桁を1桁にする
	if( _money == 0 ) digit = 1;
	for( int i = 0, n = _money; i < digit; i++, n /= 10) {
		// 1桁取得
		CStringList::numberStrList[n%10]->Draw( _pos.x - i*CStringList::FONT_SIZE_W,
			_pos.y, DEFAULT_COLOR, 1 );
	}
}

/*------------------------------------------------------

	アイテム矩形計算
	@param	int				アイテム番号
	@return アイテム矩形

------------------------------------------------------*/
FRECT CResultScene::GetItemRect(int _no)
{
	int w = _no % 7;
	int h = _no / 7;

	return FRECT(w * 40.f, h * 40.f, (w+1)*40.f, (h+1)*40.f);
}
