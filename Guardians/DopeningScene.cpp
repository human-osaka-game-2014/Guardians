#include "stdafx.h"


COpeningScene::COpeningScene(HWND _hWnd,LPDIRECT3DDEVICE9 _pDevice,CInput* _input) : CScene(_pDevice,_input)
{
	m_sceneID = SCENE_OPENING;
	m_directShow = new CDirectShow(_hWnd);
	m_directShow->Volume(0);

}
COpeningScene::~COpeningScene()
{
	SAFE_DELETE(m_directShow);
}
COpeningScene::SceneID COpeningScene:: Control()
{
	return SCENE_TITLE;
	//CScene::Control();

	//if( CScene::m_keyStatePush == KEY_Z){
	//	m_directShow->isEnd();

	//	return SCENE_TITLE;
	//}
	//if(m_directShow->CheckEnd()){
	//	return SCENE_TITLE;
	//}

	//return SCENE_OPENING;
}
void COpeningScene::Draw()
{
	m_directShow->Run();
}