/**
 * @file  Dscene.h
 * @brief �V�[���̋��ʏ���(�`��Ȃ�)���܂Ƃ߂��N���X
 * @author danjo
 * @date 2014/10/16 �V�K�쐬
 * @date 2014/10/17\n
		�R���X�g���N�^�ǉ�\n
		�����ɕ`��f�o�C�X���󂯎��		
 */


/**
 * �V�[���̋��ʏ���(�`��Ȃ�)���܂Ƃ߂��N���X
 */
class CScene
{
protected:
	static bool m_skipFlag;
public:
	static int					m_keyStatePush;			    // �L�[���͏��
	static int					m_keyStateOn;				// �L�[���͏��(ON)
	static float* keyPushTime;
	// �V�[���ԍ�
	enum SceneID {
		SCENE_LOGO,
		SCENE_OPENING,
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_BATTLE,
		SCENE_RESULT,	// �ǉ�
		SCENE_ENDING,
	};
protected:
	/** �f�o�b�O�p�e�L�X�g */
//	std::vector<CTexString*>	m_pDebugText;
	/** �`��p�f�o�C�X */
	LPDIRECT3DDEVICE9			m_pDevice;		
	CInput*						m_Input;
	SceneID						m_sceneID;
	State				m_state;					// ��ʂ̏��
	int					m_menuID;					// ���j���[�ԍ��i�L�����o���I��/�X�e�[�^�X/�V���b�v/�Z�[�u)
	int					m_stageID;					// �X�e�[�W�ԍ�
public:
	/**
	 *	�R���X�g���N�^
	 *	@param _pDevice �f�o�C�X
	 *	@param _input ����
	 *	@return	�Ȃ�
	 */
	CScene(LPDIRECT3DDEVICE9 _pDevice , CInput* _input) : 
		m_pDevice( _pDevice ) , m_Input(_input){}

	/**
	 *	�f�X�g���N�^
	 */
	virtual ~CScene(){};

	/**
	 *	�V�[�����̏���(����)���s��
	 *	@return	�V�[��ID
	 */
	virtual SceneID Control();

	/**
	 *	�V�[�����̕`����s��
	 *	���������z�֐��ׁ̈A�������e�͔h����ɋL�q
	 */
	virtual void Draw() = 0;

	void SetDevice(LPDIRECT3DDEVICE9 _pDevice) { m_pDevice = _pDevice; }
	SceneID GetSceneID() { return m_sceneID; }
};
