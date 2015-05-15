class CLogoScene : public CScene
{
public:

private:
	CLogo* m_logo;
	LPDIRECT3DDEVICE9			m_pDevice;	//描画デバイス
public:
	CLogoScene(LPDIRECT3DDEVICE9 _pDevice,CInput* _input);
	~CLogoScene();

	SceneID Control();
	void Draw();
private:
};