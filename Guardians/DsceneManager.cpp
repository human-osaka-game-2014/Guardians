#include "stdafx.h"



// グローバル変数(スレッド起動時に使用)
typedef struct {
	CGameData* pGameData;
	LPDIRECT3DDEVICE9 device;
	CCharacterManager::MODELDATA model;
	CField::FIELD_DATA field;
	bool isEnd;
} PARAM, *lpPARAM;

PARAM param;

DWORD dwID;
/*---------------------------------------------------------------

	モデルをロードする
 	@param LPVOID 
	@return 

 ---------------------------------------------------------------*/
unsigned __stdcall ThreadFuncCreate(LPVOID vdParam) {
	lpPARAM lpParam = (lpPARAM)vdParam;
	lpParam->isEnd = false;
	
	reinterpret_cast<CSceneManager*>(vdParam)->Load(lpParam->device,lpParam->pGameData,&lpParam->model ,&lpParam->field );
	lpParam->isEnd = true;
	return 0;
}
/*---------------------------------------------------------------

 	モデルの再ロード
 	@param LPVOID 
	@return 

 ---------------------------------------------------------------*/
unsigned __stdcall ThreadFuncUpdate(LPVOID vdParam) {
	lpPARAM lpParam = (lpPARAM)vdParam;
	lpParam->isEnd = false;
	reinterpret_cast<CSceneManager*>(vdParam)->Update(lpParam->device,lpParam->pGameData,&lpParam->model,&lpParam->field );

	lpParam->isEnd = true;
	return 0;
}
/*---------------------------------------------------------------

 	コンストラクタ
 	(各メンバ変数の初期化を行う)

 ---------------------------------------------------------------*/
CSceneManager::CSceneManager(HWND hWnd,CGraphicsDevice _gaphics) : 
	m_pScene( nullptr ), m_step( STEP_CREATE ), m_nextSceneID( CScene::SCENE_GAME ),
m_hWnd(hWnd),m_graphics(_gaphics) ,m_time(0)
{
	m_pGameData = new CGameData();	// コンストラクタでデータがロードされる	
	m_pGameData->Load(0);
	m_Input = new CInput();
	m_Input->Create(hWnd);

	//===========================================
	//　スレッド処理
	//===========================================
	// ThreadFuncに渡す構造体にデータを渡す
	param.pGameData = m_pGameData;
	param.device = m_graphics.GetDevice();
	param.isEnd = true;

	//param.field = NULL;
	// スレッドを起動
	HANDLE thread =	(HANDLE)_beginthreadex(NULL,0,ThreadFuncCreate,&param,0,(unsigned int*)&dwID);
	// スレッドを終了する
	CloseHandle( thread );
}

/**
 *	デストラクタ
 *	(解放処理を行う)
 */
CSceneManager::~CSceneManager()
{
	// シーンオブジェクトを解放
	if( m_pScene != nullptr ) {
		delete m_pScene;
		m_pScene = nullptr;
	}
	SAFE_DELETE(m_pGameData);

	CStringList::Release();

	SAFE_DELETE(m_Input);

	for(int i = 0;i < 3; i++ ){
		SAFE_DELETE(param.model.player[i]);
	}
	for(int i = 0;i < 4; i++ ){
		SAFE_DELETE(param.model.enemy[i]);
	}
	SAFE_DELETE(param.field.m_field);
}

/**
 *	シーンごとの処理(操作)を行う
 *	@param	なし
 *	@return	なし
 */
void CSceneManager::Control()
{
	CScene::SceneID nowSceneID;
	if( m_pScene != NULL ) {
		nowSceneID = m_pScene->GetSceneID();
	} else {
		nowSceneID = m_nextSceneID;
	}
	// バトルシーン突入時にモデルのロードが終わっていなければバトルシーンの生成はしない
	if ( nowSceneID == CScene::SCENE_BATTLE && param.isEnd == false ){
		return;
	}
	switch( m_step ) { // ステップ分け
	case STEP_CREATE:
		// シーンIDを参照して
		// 生成するシーンを変える
		switch( nowSceneID ) {
		case CScene::SCENE_LOGO:
			m_pScene = new CLogoScene(m_graphics.GetDevice(),m_Input);
			//CStringList::Create(m_graphics.GetDevice(),m_pGameData);
			break;
		case CScene::SCENE_OPENING:
			m_pScene = new COpeningScene(m_hWnd,m_graphics.GetDevice(),m_Input);
			//m_pScene = new CTitleScene(m_graphics.GetDevice());
			break;
		case CScene::SCENE_TITLE:
			m_pScene = new CTitleScene(m_graphics.GetDevice(),m_hWnd,m_Input);
			//m_pGameData->Load(0);
			break;
		case CScene::SCENE_GAME:
			m_pScene = new CPrepareMission(m_graphics.GetDevice(),m_pGameData,m_Input);
			CStringList::Create(m_graphics.GetDevice(),m_pGameData);
			if(m_time == 0){
				m_time = timeGetTime();
			}
			break;
		case CScene::SCENE_BATTLE:
			CStringList::Create(m_graphics.GetDevice(),m_pGameData);
			m_pScene = new CBattleScene(m_graphics.GetDevice(),m_pGameData,m_Input,&param.model,param.field.m_field);
			break;
		case CScene::SCENE_RESULT:
		{
			// リザルトに戻ってきたときはスレッドを起動してモデルをロード開始する
			HANDLE thread =	(HANDLE)_beginthreadex(NULL,0,ThreadFuncUpdate,&param,0,(unsigned int*)&dwID);
			// スレッドを終了する
			CloseHandle( thread );
			// とりあえず仮

			m_pScene = new CResultScene(m_graphics.GetDevice(), m_pGameData,m_Input);
			break;
		}
		case CScene::SCENE_ENDING:
			//m_pScene = new CEndingScene(m_graphics.GetDevice());
			break;
		}
		// 次のステップへ
		m_step = STEP_PROC;
		break;
	case STEP_PROC:
		// newしたシーンのControl関数が
		// 呼び出される
//		m_pScene->Control();
		if( nowSceneID >= CScene::SCENE_GAME && nowSceneID <= CScene::SCENE_ENDING ){ 	//ゲームシーンならプレイ時間を取得
			DWORD endTime = timeGetTime();
			m_pGameData->m_playTime = (endTime-m_time)/1000;
		}
		// 今現在のシーンＩＤと違うなら別のシーンに移動する
		if( (m_nextSceneID = m_pScene->Control()) != nowSceneID )
		{
//			m_sceneID = static_cast<SceneID>( m_pScene->GetSceneID());
			// 次のステップへ
			m_step = STEP_RELEASE;
		}
		break;
	case STEP_RELEASE:
		if( m_pScene != nullptr ) {
			delete m_pScene;
			m_pScene = nullptr;
		}
		// 次のステップへ
		m_step = STEP_CREATE;
		break;
	}
}
/**
 *	シーンごとの描画を行う
 *	@param	なし
 *	@return	なし
 */
void CSceneManager::Render()
{
	// ステップの状態を調べる
	if( m_step != STEP_PROC ) return ;


	m_pScene->Draw();
}

/**
 *	シーン内の管理を行う
 *	@param	なし
 *	@return	なし
 */
void CSceneManager::Run()
{
	m_Input->InputUpdate();
	// 処理
	Control();

	CScene::SceneID nowSceneID;
	if( m_pScene != NULL ) {
		nowSceneID = m_pScene->GetSceneID();
	} else {
		nowSceneID = m_nextSceneID;
	}
	// もしバトルシーン突入時にモデルのロードが終わっていなければ描画しない
	if ( nowSceneID == CScene::SCENE_BATTLE && param.isEnd == false ){
		return;
	}

	// 描画開始
	if(nowSceneID != CScene::SCENE_OPENING){
		m_graphics.BeginScene(0,0,0);
	}

	// 描画
	Render();

	// 描画終了
	if(nowSceneID != CScene::SCENE_OPENING){
		m_graphics.EndScene();
	}

}
bool CSceneManager::Load(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CCharacterManager::MODELDATA* _model,CField::FIELD_DATA* _field)
{
	// プレイヤークラスオブジェクトの生成
	// 出撃順で生成するキャラクターを分岐(現在仮の為全てネルを生成)
	
	
	for(int i = 0; i < PLAYER_MAX;i++){
		if( _pGameData->m_turnNo[i] == ALDO )
			_model->player[i] = new CAldfauth(_pDevice);
		else if ( _pGameData->m_turnNo[i] == MINE )
			_model->player[i] = new CMinertza(_pDevice);
		else
			_model->player[i] = new CNeru(_pDevice);
	}
	
	// 敵を生成(　ステージ数によって敵が変わる予定)
	//switch( _pGameData->m_nowClearStageNum){
	//case 0:
		_model->enemy[0] = new CMushroom(_pDevice);
		_model->enemy[3] = new CFenrir(_pDevice);
		//_model->enemy[1] = new CAuger(_pDevice);
		//_model->enemy[2] = new CAuger(_pDevice);
		//_model->enemy[3] = new CAuger(_pDevice);
	//}

	// マップのロード
	_field->m_field = new CField(_pDevice,(_pGameData->m_nowClearStageNum + 1 )/ 4);
	

	return true;
}
bool CSceneManager::Update(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CCharacterManager::MODELDATA* _model,CField::FIELD_DATA* _field)
{
	//// もしステージボスを倒していたら敵を生成し直す
	//if( ( (_pGameData->m_nowClearStageNum +1) / 4 ) != ( ( _pGameData->m_oldClearStageNum + 1 ) / 4 )){
	//	// 敵を生成
	//	for(int i = m_pGameData->m_oldClearStageNum; i < _pGameData->m_nowClearStageNum + 1;i++){ // 現在のステージNo+次のステージのモデルを
	//		switch( _pGameData->m_oldClearStageNum ){	
	//		case 0:
	//			_model->enemy[0] = new CMushroom(_pDevice);
	//			break;
	//		case 3:
	//			_model->enemy[1] = new CFenrir(_pDevice);
	//			break;
	//			//_model->enemy[1] = new CAuger(_pDevice);
	//			//_model->enemy[2] = new CAuger(_pDevice);
	//			//_model->enemy[3] = new CAuger(_pDevice);
	//		}
	//	}
	//	// フィールドを生成し直す
	//	//_field->m_field = new CField(_pDevice,(_pGameData->m_nowClearStageNum + 1 )/ 4);
	//	_pGameData->m_oldClearStageNum = _pGameData->m_nowClearStageNum;
	//}
	return true;
}
