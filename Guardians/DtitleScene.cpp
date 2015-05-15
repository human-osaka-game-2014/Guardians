#include "stdafx.h"

CTitleScene::CTitleScene(LPDIRECT3DDEVICE9 _pDevice,HWND _hWnd,CInput* _input) : CScene( _pDevice,_input ),m_pDevice( _pDevice ) ,m_selectID(0)
{
	m_sceneID = SCENE_TITLE;
	CTexMgr.Load(SCENE_TITLE,m_pDevice);

	m_title		 = new CTitle(m_pDevice);
	
	m_titleMenu = new CTitleMenu(m_pDevice);

	SetSkipFlag(true);
	CScene::m_keyStatePush = 0;
	//m_directShow = new CDirectShow(_hWnd);
}

CTitleScene::~CTitleScene()
{
	SAFE_DELETE(m_title);
	SAFE_DELETE(m_titleMenu);
	CTexMgr.Release();

	//SAFE_DELETE(m_directShow);


}
CTitleScene::SceneID CTitleScene::Control()
{
	CScene::m_keyStatePush = 0;

	CScene::Control();

	//if( CScene::m_keyStatePush == KEY_Z){
	//	m_sceneID = CSceneManager::SCENE_TITLE;
	//	m_skipFlag = true;
	//}
	//if(m_directShow->CheckEnd()){
	//	m_sceneID = CSceneManager::SCENE_TITLE;
	//}


	m_title->Control(m_skipFlag);
	// タイトルロゴが描画し終わったら文字画像の描画
	if( m_title->GetState() == CTitle::STATE_MOVE_END){
		m_titleMenu->Control();
	}
	// Zキーが押されたらゲームシーンへ
	if(  CScene::m_keyStatePush == KEY_S || CScene::m_keyStatePush == KEY_Z ) {
		return SCENE_GAME;
	}

	if( CScene::m_keyStatePush == UP ){
		m_selectID = (m_selectID+1) % 1;
	}
	if( CScene::m_keyStatePush == DOWN ){
		m_selectID = (m_selectID+1) % 1;
	}
	
	if( m_title->GetState() == CTitle::STATE_TRANSITION ){
		return SCENE_GAME;
	}

	return SCENE_TITLE;
}
void CTitleScene::Draw()
{
	m_titleMenu->Draw(m_selectID,m_skipFlag);
	m_title->Draw( );
}

void CTitleScene::SetSkipFlag(bool _skipFlag)
{
	m_skipFlag = _skipFlag;
	m_titleMenu->SetDrawID(CTitleMenu::DRAW_PRESS);
	m_title->SetState(CTitle::STATE_MOVE_END);
	
}