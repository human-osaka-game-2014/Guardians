/**
 @file DsceneManager.cpp
 @date �쐬���F2014/10/16
 @author �h��
 */

#include "stdafx.h"


// �O���[�o���ϐ�(�X���b�h�N�����Ɏg�p)
typedef struct {
	CGameData* pGameData;
	LPDIRECT3DDEVICE9 device;
	CCharacterManager::MODELDATA model;
	CField::FIELD_DATA field;
	bool isEnd;
} PARAM, *lpPARAM;

PARAM param;

DWORD dwID;

/**
 * ���f�������[�h����
 * @param vdParam �X���b�h�N���p�p�����[�^
 * @return ���0
 */
unsigned __stdcall ThreadFuncCreate(LPVOID vdParam) {
	lpPARAM lpParam = (lpPARAM)vdParam;
	lpParam->isEnd = false;
	
	reinterpret_cast<CSceneManager*>(vdParam)->Load(lpParam->device,lpParam->pGameData,&lpParam->model ,&lpParam->field );
	lpParam->isEnd = true;
	return 0;
}

/**
 * ���f���̍ă��[�h
 * @param vdParam �X���b�h�N���p�p�����[�^
 * @return ���0
 */
unsigned __stdcall ThreadFuncUpdate(LPVOID vdParam) {
	lpPARAM lpParam = (lpPARAM)vdParam;
	lpParam->isEnd = false;
	//reinterpret_cast<CSceneManager*>(vdParam)->Update(lpParam->device,lpParam->pGameData,&lpParam->model,&lpParam->field );

	lpParam->isEnd = true;
	return 0;
}

/**
 * �R���X�g���N�^
 * �e�����o�ϐ��̏��������s��
 * @param hWnd �E�B���h�E�n���h��
 * @param _graphics �O���t�B�b�N�f�o�C�X
 */
CSceneManager::CSceneManager(HWND hWnd,CGraphicsDevice _graphics) : 
	m_pScene( nullptr ), m_step( STEP_CREATE ), m_nextSceneID( CScene::SCENE_GAME ),
m_hWnd(hWnd),m_graphics(_graphics) ,m_time(0)
{
	m_pGameData = new CGameData();	// �R���X�g���N�^�Ńf�[�^�����[�h�����	
	m_pGameData->newGame();
	m_Input = new CInput();
	m_Input->Create(hWnd);

	//===========================================
	//�@�X���b�h����
	//===========================================
	// ThreadFunc�ɓn���\���̂Ƀf�[�^��n��
	param.pGameData = m_pGameData;
	param.device = m_graphics.GetDevice();
	param.isEnd = true;

	//param.field = NULL;
	// �X���b�h���N��
	HANDLE thread =	(HANDLE)_beginthreadex(NULL,0,ThreadFuncCreate,&param,0,(unsigned int*)&dwID);
	// �X���b�h���I������
	CloseHandle( thread );
}

/**
 *	�f�X�g���N�^
 *	(����������s��)
 */
CSceneManager::~CSceneManager()
{
	// �V�[���I�u�W�F�N�g�����
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
 *	�V�[�����Ƃ̏���(����)���s��
 */
void CSceneManager::Control()
{
	CScene::SceneID nowSceneID;
	if( m_pScene != NULL ) {
		nowSceneID = m_pScene->GetSceneID();
	} else {
		nowSceneID = m_nextSceneID;
	}
	// �o�g���V�[���˓����Ƀ��f���̃��[�h���I����Ă��Ȃ���΃o�g���V�[���̐����͂��Ȃ�
	if ( nowSceneID == CScene::SCENE_BATTLE && param.isEnd == false ){
		return;
	}
	switch( m_step ) { // �X�e�b�v����
	case STEP_CREATE:
		// �V�[��ID���Q�Ƃ���
		// ��������V�[����ς���
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
			m_pScene = new CBattleScene(m_graphics.GetDevice(),m_pGameData,m_Input,&param.model,param.field.m_field);
			break;
		case CScene::SCENE_RESULT:
			m_pScene = new CResultScene(m_graphics.GetDevice(), m_pGameData,m_Input);
			break;
		case CScene::SCENE_ENDING:
			//m_pScene = new CEndingScene(m_graphics.GetDevice());
			break;
		}
		// ���̃X�e�b�v��
		m_step = STEP_PROC;
		break;
	case STEP_PROC:
		// new�����V�[����Control�֐���
		// �Ăяo�����
//		m_pScene->Control();
		if( nowSceneID >= CScene::SCENE_GAME && nowSceneID <= CScene::SCENE_ENDING ){ 	//�Q�[���V�[���Ȃ�v���C���Ԃ��擾
			DWORD endTime = timeGetTime();
			m_pGameData->m_playTime = (endTime-m_time)/1000;
		}
		// �����݂̃V�[���h�c�ƈႤ�Ȃ�ʂ̃V�[���Ɉړ�����
		if( (m_nextSceneID = m_pScene->Control()) != nowSceneID )
		{
//			m_sceneID = static_cast<SceneID>( m_pScene->GetSceneID());
			// ���̃X�e�b�v��
			m_step = STEP_RELEASE;
		}
		break;
	case STEP_RELEASE:
		
		if( m_pScene != nullptr ) {
			delete m_pScene;
			m_pScene = nullptr;
		}
		// ���̃X�e�b�v��
		m_step = STEP_CREATE;
		break;
	}
}
/**
 *	�V�[�����Ƃ̕`����s��
 */
void CSceneManager::Render()
{
	// �X�e�b�v�̏�Ԃ𒲂ׂ�
	if( m_step != STEP_PROC ) return ;


	m_pScene->Draw();
}

/**
 *	�V�[�����̊Ǘ����s��
 */
void CSceneManager::Run()
{
	m_Input->InputUpdate();
	// ����
	Control();

	CScene::SceneID nowSceneID;
	if( m_pScene != NULL ) {
		nowSceneID = m_pScene->GetSceneID();
	} else {
		nowSceneID = m_nextSceneID;
	}
	// �����o�g���V�[���˓����Ƀ��f���̃��[�h���I����Ă��Ȃ���Ε`�悵�Ȃ�
	if ( nowSceneID == CScene::SCENE_BATTLE && param.isEnd == false ){
		return;
	}

	// �`��J�n
	if(nowSceneID != CScene::SCENE_OPENING){
		m_graphics.BeginScene(0,0,0);
	}

	// �`��
	Render();

	// �`��I��
	if(nowSceneID != CScene::SCENE_OPENING){
		m_graphics.EndScene();
	}

}

bool CSceneManager::Load(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CCharacterManager::MODELDATA* _model,CField::FIELD_DATA* _field)
{
	// �v���C���[�N���X�I�u�W�F�N�g�̐���
	// �o�����Ő�������L�����N�^�[�𕪊�(���݉��̈בS�ăl���𐶐�)
	
	
	for(int i = 0; i < PLAYER_MAX;i++){
		if( i == ALDO )
			_model->player[i] = new CAldfauth(_pDevice);
		else if ( i == NERU_MARU )
			_model->player[i] = new CNeru(_pDevice);
		else
			_model->player[i] = new CMinertza(_pDevice);

	}
	
	// �G�𐶐�(�@�X�e�[�W���ɂ���ēG���ς��\��)
	//switch( _pGameData->m_nowClearStageNum){
	//case 0:
		_model->enemy[0] = new CMushroom(_pDevice);
		_model->enemy[3] = new CFenrir(_pDevice);
		//_model->enemy[1] = new CAuger(_pDevice);
		//_model->enemy[2] = new CAuger(_pDevice);
		//_model->enemy[3] = new CAuger(_pDevice);
	//}

	// �}�b�v�̃��[�h
	_field->m_field = new CField(_pDevice,(_pGameData->m_nowClearStageNum + 1 )/ 4);
	

	return true;
}
