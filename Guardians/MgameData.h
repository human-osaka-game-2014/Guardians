#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

class CGameData
{
public:
	static const int MAX_EMBLEM=11;			//最大称号数
	static const int MAX_ITEM = 14;			//最大アイテム商品数
	static const int MAX_EQUIP = 16;			//最大装備商品数

	CGameData();

	enum stType{
		HP,
		MP,
		ATK,
		DEF,
		SPD,
		INS,
		TYPE_MAX,
	};

	struct Time
	{
		int year;
		int month;
		int date;
		int hour;
		int minute;
	};

	struct Thing
	{
		int no;			// 番号　10/24追加　檀上
		int type;			// 種類
		int nums;			// 個数
		char explainStr[256];		// 説明
	};

	struct HaveTool		// 所持道具
	{
		int no;			// 番号　10/24追加　檀上
		int type;			// 種類
		int nums;			// 個数
		char explainStr[256];		// 説明
	};
	struct Equip		// 装備
	{
		int no;			// 番号
		char name[256];    // 名前     
		int type;			// 種類
		int nums;			// 個数
		int price;          // 価格
		int stType;			// 変化するステータスの種類
		int power;			// 変化量
		int unlockNo;
		char explainStr[256];		// 説明
	};
	struct Character		// キャラクター
	{
		char	name[256];	// 名前
		int		hp;				
		int		mp;				
		int		atk;
		int		def;
		int		spd;
		int		ins;		// 瞬発力
		Equip	equip[2];	// 装備
	};
	struct Damage
	{
		// 与えたダメージ
		int damage;
		// 受けたダメージ
		int damageTaken;
	};
	//ステータス
	struct ENEMY_STATUS 
	{
		int ATK;
		int	DEF;			//防御力
		int	STR;			//使用技攻撃力
		int	addState;		//使用技状態異常付与ID
		int	actionGauge;	//行動値
		int	actionGaugeRecover;	//行動値回復量
		float hp;
		float maxHP;
	};
	struct EMBLEM
	{
		char name[256];
	};

	enum { HAVE_TOOL_MAX = 4 };		// 持ち込める道具の最大数
	enum { UNLOCK_TOOL_MAX = 10 };	// アンロックできる道具最大数(仮)
	enum { UNLOCK_EQUIP_MAX = 10 };	// アンロックできる装備最大数(仮)

	std::vector<Equip>		m_itemList;						// ゲームで使用するアイテム一覧
	std::vector<Equip>		m_equipList;
	std::vector<HaveTool>	m_hasTools;						// 所持道具
	std::vector<Equip>		m_hasEquip;						// 所持装備品
	std::vector<bool>		m_emblemFlag;					// 実績（称号）フラグ
	std::vector<EMBLEM>		m_emblemList;					// 実績リスト
	HaveTool				m_tools[HAVE_TOOL_MAX];			// 持ち込み道具(4個)
	Character				m_initchara[PLAYER_MAX];
	Character				m_chara[PLAYER_MAX];			// 3人分

	Damage					m_pDamage;						// playerダメージ計算用
	//Damage					m_eDamage;						// enemyダメージ計算用
	int						m_nowClearStageNum;				// 現在のステージクリア数
	int						m_selectStageNum;
	int						m_oldClearStageNum;				// バトル出撃前のステージクリア数(モデルのリロードが必要か判断)
	int						m_turnNo[PLAYER_MAX];			// 出撃順番
	int						m_playerCharaNo;				// 先頭のキャラの番号(出撃順を決めるときに保存)
	int						m_unlockTools[UNLOCK_TOOL_MAX];	// 商品アンロックリスト(道具)
	int						m_unlockEquip[UNLOCK_EQUIP_MAX];// 商品アンロックリスト(装備)
	Time                    m_time;                         // セーブ日付
	int						m_playTime;						// プレイ時間
	int						m_money;						// 所持金
	int                     m_toolsPer;                     // 取得装備率
	bool					m_death;						// 死んだかどうか(追加)
	int						m_resultMoney;					// 獲得資金
	int						m_stageEmbFlag[6][4][11];		// ステージごとのエンブレム情報
	std::vector<HaveTool>	m_getItem;						// ステージでゲットしたアイテム


	bool					m_win;

	int m_equipPer;
	int m_itemPer;
	int m_emblemPer;
public:
	int Search(int _itemNum,ItemType _type);		//アイテムナンバーから配列番号を探す
	void Load(int _dataID);	// セーブファイルから読み込み
	void Save(int _dataID);    // ファイルをセーブ  10/18追加
	void newGame();			// ニューゲームのデータをロードする
};

#endif