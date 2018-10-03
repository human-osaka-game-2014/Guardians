class CCombo;

class CBattleUI
{
public:
	static const int GAUGE_TYPE_NUM = 3;
	// �Q�[�W�̎��
	enum GAUGE_TYPE{
		BLACK,
		WHITE,
		RED,
	};
	// �Q�[�W�E�[���̒��_���W
	static const FRECT SIDE_GAUGE_VERTEX[GAUGE_TYPE_NUM];
	// �Q�[�W�������̒��_���W
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

	static const D3DXVECTOR2 INIT_CHARA_POS[PLAYER_MAX];

	static const int FRAME_MAX_SIZE = 600;
	static const int FRAME_SIZE = 200;

	//static const D3DXVECTOR2
	//static const D3DXVECTOR2
	//static const D3DXVECTOR2
	//static const D3DXVECTOR2
	static const FRECT rect;

	enum STATE{
		STATE_BATTLE,
		STATE_CHARA_CHANGE,
	};

	// �L�����N�^�[�摜�`��p�����[�^�[
	struct chara{
   		int hp;	
		int mp;
		int MAXhp;	
		int MAXmp;
		int positionID;
		float scale;
		D3DXVECTOR2 position;
	};



private:
	LPDIRECT3DDEVICE9	m_pDevice;

	CTexture    UI;
	CTexture	blackPic;				    //����ʕ\��
	CTexture	enemyGauge;						//�GHP�o�[�\��
	CVertex		m_vertex;

	CCombo*		m_combo;
	CGameData*  m_pGameData;    // �Q�[���f�[�^
	
	STATE		m_state;			// �퓬���
	
	int         m_charaID[3];			//�I�����Ă���L����
	chara       m_chara[3];             //�L����
	int			m_activeCharaNo;
	// �L����UI
	int			m_time;					// �L������㒆�̃t���[��
	// �R���{��
	int			m_comboNum;

	bool        m_charachange;			//�L������㔻��           
    int         m_changecount;			//�L������㎞�Ԑ��@
	bool        m_startchange;          //�L�����������
	bool        m_initializestatus;     //�L���������ʒu
	float		m_enemyMAXHP;           //�G��HP
	float		m_enemyHP;
	bool        m_ishit;                //�����蔻��                 

	D3DCOLOR            m_color;
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
class CCombo
{
public:
	typedef D3DXVECTOR2 vector2;

	static const int COMBO_TIME_LIMIT = 120; // �R���{�̌p������(120�t���[��)

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
	std::vector<int> combodiv;	//�R���{����

	int         m_comboNum;				//�R���{��
	int			m_oldComboNum;			// 1f�O�̃R���{��
	int			m_comboTime;			// �R���{���̎���
public:
	CCombo(LPDIRECT3DDEVICE9 _pDevice);
	~CCombo(){};

	void Control(int _comboNum);
	void Draw();
};