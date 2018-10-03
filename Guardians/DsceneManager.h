/*=======================================

	�V�[���̑J�ځA�Ǘ����s���N���X
	�쐬��  :2014/10/16
	�쐬��  : �h��
	�X�V��  :
	�X�V��  :
	�X�V���e:

=======================================*/
class CSceneManager
{
public:


protected:
	// �����X�e�b�v
	enum Step {
		STEP_CREATE,	// ����
		STEP_PROC,		// ������
		STEP_RELEASE,	// ���
	};

	DWORD		m_time; // �v���C���Ԋi�[�p


	/** �V�[���N���X�I�u�W�F�N�g */
	CScene*		m_pScene;
	CScene::SceneID m_nextSceneID;
	/** �X�e�b�v�ϐ� */
	Step		m_step;
	/** �O���t�B�b�N�X�N���X�I�u�W�F�N�g */
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