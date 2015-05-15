#ifndef _GAME_SAVEDATA_WINDOW_H_
#define _GAME_SAVEDATA_WINDOW_H_



class CGameSaveDataWindow : public CGameWindow
{
private:
	struct Data{
		bool data;			//データの有無
		int hour;			//時間
		int minute;			//分
		int second;			//秒
		int year;			//年
		int month;			//月
		int date;			//日
		int realhour;		//リアルタイム(時間)
		int realminutes;	//リアルタイム(分)
		int playtime;		//プレイ時間
		int money;			//お金
		int stageclear;		//ステージクリア数
		int equipper;		//装備所持率
		int itemper;		//アイテム所持率
		int achieve;		//実績率
	};
	int m_drawID;
	int	m_cursorPos;
	int m_cursolpoint;
	int m_drawFirst;
	int m_head;
	int m_tail;
	static const int MAX_ITEM=14;			//最大アイテム商品数
	static const int MAX_EQUIP=16;			//最大装備商品数
	static const int MAX_WIDTH	= 1150;		// ウィンドウ最大幅
	static const int MAX_HEIGHT = 520;		// ウィンドウ最大高さ
	static const int MAX_ITEMNUMBER=14;		//アイテム最大所持数
	static const int MAX_STAGENUMBER=6;		//ステージ最大数
	static const int MAX_EMBLEM=11;			//最大称号数

	Data    m_Data[10];                     //データ10個分
	CGameData*  m_pGameData;                //ゲームデータの参照
	CTexture	m_textureChip;				//マップチップアイコン
public:
	CGameSaveDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int m_state);	// コンストラクタ(デバイス、座標、ゲームデータ,状態をセット)
	~CGameSaveDataWindow();
	void Load(int _ID);																	//セーブデータをファイルから読み込む
	void Control();		// 制御
	void Draw();		// 描画
	void SetCursorID(int _cursorID);

};
#endif


