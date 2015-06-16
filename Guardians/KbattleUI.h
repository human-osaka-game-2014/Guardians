class CCombo;
class CGauge;

class CBattleUI
{
public:
	static const int GAUGE_TYPE_NUM = 3;
	// ゲージの種類
	enum GAUGE_TYPE{
		BLACK,
		WHITE,
		RED,
	};
	// ゲージ右端部の頂点座標
	static const FRECT SIDE_GAUGE_VERTEX[GAUGE_TYPE_NUM];
	// ゲージ中央部の頂点座標
	static const FRECT GAUGE_VERTEX[GAUGE_TYPE_NUM];

	static const FRECT SIDE_FRAME_VERTEX;
	static const FRECT FRAME_VERTEX;

	static const FRECT SIDE_BLACK_GAUGE_VERTEX;
	static const FRECT BLACK_GAUGE_VERTEX;
	static const FRECT RIGHT_BLACK_GAUGE_VERTEX;

	static const FRECT SIDE_RED_GAUGE_VERTEX;
	static const FRECT RED_GAUGE_VERTEX;

	static const FRECT SIDE_WHITE_GAUGE_VERTEX;
	static const FRECT WHITE_GAUGE_VERTEX;

	static const D3DXVECTOR2 SIDE_FRAME_POS;
	static const D3DXVECTOR2 FRAME_POS;		
	 
	static const D3DXVECTOR2 RIGHT_FRAME_POS;
	static const FRECT RIGHT_FRAME_VERTEX;

	static const D3DXVECTOR2 LEFT_FRAME_POS;
	static const FRECT LEFT_FRAME_VERTEX;

	static const D3DXVECTOR2 INIT_SIDE_GAUGE_POS;
	static const D3DXVECTOR2 INIT_GAUGE_POS;
	static const D3DXVECTOR2 INIT_RIGHT_GAUGE_POS;

	static const int FRAME_MAX_SIZE = 600;
	static const int FRAME_SIZE = 200;

	static const FRECT rect;

	enum STATE{
		STATE_BATTLE,
		STATE_CHARA_CHANGE,
	};
private:
	LPDIRECT3DDEVICE9	m_pDevice;

	CTexture    UI;
	CTexture	blackPic;				    //黒画面表示
	CTexture	enemyGauge;						//敵HPバー表示
	CVertex		m_vertex;

	CCombo*		m_combo;
	CGauge*		m_gauge[3];
	CGameData*  m_pGameData;    // ゲームデータ
	
	STATE		m_state;			// 戦闘状態
	
	// キャラUI
	int			m_time;					// キャラ交代中のフレーム
	// コンボ数

	bool        m_charachange;			//キャラ交代判定           
    int         m_changecount;			//キャラ交代時間数　
	float		m_enemyMAXHP;           //敵のHP
	float		m_enemyHP;

public:
    CBattleUI(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGamedata);
	~CBattleUI();
	void Control(); 
	void Draw();

	void SetBossHP(CGameData::ENEMY_STATUS _status);

	void DrawCombo();
	void ControlCombo();

	void SetNextPosition();
};
class CGauge
{
public:
	static const int	MOVE_TIME = 30;

	static const FRECT CHARA_GAUGE_VERTEX;
	static const FRECT HP_VERTEX;
	static const FRECT MP_VERTEX;
	static const D3DXVECTOR2 CHARA_POSITION[PLAYER_MAX];
	// キャラクター画像描画パラメーター
	struct STATUS{
   		int hp;	
		int mp;
		int MAXhp;	
		int MAXmp;
	};

private:
	CVertex		m_vertex;
	CTexture	m_tex;

	LPDIRECT3DDEVICE9 m_pDevice;


	D3DXVECTOR2 m_position;
	D3DXVECTOR2 m_nextPosition;
	float		m_scale;
	float		m_HPper;
	float		m_MPper;
	float		m_move;
	float		m_addScale;
	float		m_maxScale;
	int			m_charaID;	// キャラクターのID(0:アルドファウト 1:ネルマル 2:ミネルツァ)
	int			m_time;


	CGameData*  m_pGameData;
	STATUS		m_status;
public:
	CGauge(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pGameData,int _charaID);
	~CGauge(){};

	void Control(); 
	void Draw();

	void SetNextPosition();
private:

};
class CCombo
{
public:
	typedef D3DXVECTOR2 vector2;

	static const int COMBO_TIME_LIMIT = 120; // コンボの継続時間(120フレーム)

	enum STATE{
		STATE_BATTLE,
		STATE_COMBO,
	};

	static const vector2 NUMBER_POS;
	static const float	 NUM_SIZE;
	static const FRECT	 TELOP_VERTEX;
	static const FRECT	 NUMBER_VERTEX;
private:
	CTexture	m_texture;
	CVertex		m_vertex;
	LPDIRECT3DDEVICE9 m_pDevice;

	STATE m_state;
	float	  m_alpha;
	std::vector<int> combodiv;	//コンボ分割

	int         m_comboNum;				//コンボ数
	int			m_oldComboNum;			// 1f前のコンボ数
	int			m_comboTime;			// コンボ中の時間
public:
	CCombo(LPDIRECT3DDEVICE9 _pDevice);
	~CCombo(){};

	void Control(int _comboNum);
	void Draw();
};