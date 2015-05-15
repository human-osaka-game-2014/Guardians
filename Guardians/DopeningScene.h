class COpeningScene : public CScene
{
private:
	CDirectShow*					m_directShow;
public:
	COpeningScene(HWND _hWnd,LPDIRECT3DDEVICE9 _pDevice,CInput* _input);
	~COpeningScene();

	SceneID Control();
	void Draw();
};