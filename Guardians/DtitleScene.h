class CTitleScene : public CScene
{
public:
	enum SelectID
	{
		SELECT_START,
		SELECT_LOAD,
		SELECT_CONFIG,
		SELECT_EXIT,
		SELECT_PRESS,
	};
private:
	static const int SELECT_TYPE_MAX = 5;

	LPDIRECT3DDEVICE9			m_pDevice;	//描画デバイス

	CGameCursor*				m_gameCursor;
	CTitle*						m_title;
	CTitleMenu*					m_titleMenu;
	CDirectShow*				m_directShow;
	C3DModel*					m_model;
	CCamera*					m_camera;

	int							m_selectID;
	bool						m_skipFlag;

public:
	CTitleScene(LPDIRECT3DDEVICE9 _pDevice,HWND hWnd,CInput* _input);
	~CTitleScene();

	SceneID Control();
	void Draw();

	void SetSkipFlag(bool _skipFlag);

};