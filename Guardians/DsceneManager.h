/*=======================================

	シーンの遷移、管理を行うクラス
	作成日  :2014/10/16
	作成者  : 檀上
	更新日  :
	更新者  :
	更新内容:

=======================================*/
class CSceneManager
{
public:


protected:
	// 処理ステップ
	enum Step {
		STEP_CREATE,	// 生成
		STEP_PROC,		// 処理中
		STEP_RELEASE,	// 解放
	};

	DWORD		m_time; // プレイ時間格納用


	/** シーンクラスオブジェクト */
	CScene*		m_pScene;
	CScene::SceneID m_nextSceneID;
	/** ステップ変数 */
	Step		m_step;
	/** グラフィックスクラスオブジェクト */
	CGraphicsDevice	m_graphics;
	DWORD time;

	CInput*			m_Input;
	CGameData*		m_pGameData;
	HWND			m_hWnd;

	//CAru* m_model;
	CCharacterManager::MODELDATA modelData;
public:
	CSceneManager(HWND hWnd,CGraphicsDevice _graphics);

	~CSceneManager();

	void Control();
	void Render();
	void Run();

	bool Load(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CCharacterManager::MODELDATA* _model,CField::FIELD_DATA* _field);
	bool Update(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,CCharacterManager::MODELDATA* _model,CField::FIELD_DATA* _field);

	void SetGraphics(CGraphicsDevice _graphics) {
		m_graphics = _graphics;
		m_pScene->SetDevice( m_graphics.GetDevice() );
	}

	//void __cdecl //ThreadFunc(LPVOID vdParam);
};