class CBattleScene : public CScene
{
public:
	static int			comboCount;		// コンボ数
	static bool			m_pause;		// ポーズフラグ
	static const float RIGHT_WALL;		// 右壁
	static const float LEFT_WALL;		// 左壁

	enum STATE{
		STATE_BATTLE,
		STATE_CHARA_CHANGE,
	};

	static const int	CHANGE_LIMIT = 120;	// キャラ交代の制限時間(120フレーム)
private:

	#define FIELD_TYPE_NUM 2

	enum FieldType{
		FIELD_1,
		FIELD_2,
	};

	CField*		m_field;		// フィールドクラスオブジェクト
	CCamera*    m_camera;		// カメラクラスオブジェクト
	CCharacterManager*	m_character;	// キャラクタークラスオブジェクト
	CGameData*			m_pGameData;	// ゲームデータ
	CBattleUI*			m_ui;			// UI

	D3DXVECTOR2			m_cameraPos;    // カメラの位置
	D3DXVECTOR2			m_move;			// カメラの移動量

	D3DXVECTOR2			charaSpeed;		// キャラクターのスピード
	D3DXVECTOR3			m_playerPos;

	//===============キャラ変更時の制御用変数===================//
	
	STATE				m_charaChange;	// キャラチェンジ状態
	int					m_changeTime;	// キャラチェンジ中の経過時間
	static const int	CC_MAX_ALPHA = 150;	// キャラ変更時のアルファ上限
	static const int	CC_ADDALPHA_FRAME = 20; // キャラ変更時のアルファ増加時間

	//===============フェードインorフェードアウト制御用変数===================//
	
	CTexture			m_feed;			// フェード用画像
	int					m_alpha;		// α値
	int					m_add;			// アルファ値増加量

public:

	CBattleScene(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGamedata,CInput* _input,CCharacterManager::MODELDATA* _chara,CField* _field);
	~CBattleScene();
	SceneID Control();
	void Draw();
	
private:
	void DrawBlackPic(int _alpha);
};