/**
 * @file  Dscene.h
 * @brief シーンの共通処理(描画など)をまとめたクラス
 * @author danjo
 * @date 2014/10/16 新規作成
 * @date 2014/10/17\n
		コンストラクタ追加\n
		引数に描画デバイスを受け取る		
 */


/**
 * シーンの共通処理(描画など)をまとめたクラス
 */
class CScene
{
protected:
	static bool m_skipFlag;
public:
	static int					m_keyStatePush;			    // キー入力状態
	static int					m_keyStateOn;				// キー入力状態(ON)
	static float* keyPushTime;
	// シーン番号
	enum SceneID {
		SCENE_LOGO,
		SCENE_OPENING,
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_BATTLE,
		SCENE_RESULT,	// 追加
		SCENE_ENDING,
	};
protected:
	/** デバッグ用テキスト */
//	std::vector<CTexString*>	m_pDebugText;
	/** 描画用デバイス */
	LPDIRECT3DDEVICE9			m_pDevice;		
	CInput*						m_Input;
	SceneID						m_sceneID;
	State				m_state;					// 画面の状態
	int					m_menuID;					// メニュー番号（キャラ出撃選択/ステータス/ショップ/セーブ)
	int					m_stageID;					// ステージ番号
public:
	/**
	 *	コンストラクタ
	 *	@param _pDevice デバイス
	 *	@param _input 入力
	 *	@return	なし
	 */
	CScene(LPDIRECT3DDEVICE9 _pDevice , CInput* _input) : 
		m_pDevice( _pDevice ) , m_Input(_input){}

	/**
	 *	デストラクタ
	 */
	virtual ~CScene(){};

	/**
	 *	シーン内の処理(操作)を行う
	 *	@return	シーンID
	 */
	virtual SceneID Control();

	/**
	 *	シーン内の描画を行う
	 *	※純粋仮想関数の為、処理内容は派生先に記述
	 */
	virtual void Draw() = 0;

	void SetDevice(LPDIRECT3DDEVICE9 _pDevice) { m_pDevice = _pDevice; }
	SceneID GetSceneID() { return m_sceneID; }
};
