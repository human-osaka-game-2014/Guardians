#include "stdafx.h"

CLogoScene::CLogoScene(LPDIRECT3DDEVICE9 _pDevice , CInput* _input) : CScene(_pDevice,_input)
{
	m_sceneID = SCENE_LOGO;
	CTexMgr.Load(SCENE_LOGO, _pDevice);
	m_logo = new CLogo(_pDevice);
}
CLogoScene::~CLogoScene()
{
	CTexMgr.Release();

	SAFE_DELETE(m_logo);
}
CLogoScene::SceneID CLogoScene::Control()
{
	m_logo->Control();

	if(m_logo->GetFlag())
		return SCENE_TITLE;

	return SCENE_LOGO;
}
void CLogoScene::Draw()
{
	m_logo->Draw();
}