class CStringList
{
public:
	// 10/30追記　文字画像サイズ
	static const int FONT_SIZE_H = 60;
	static const int FONT_SIZE_W = 32;

	static  std::vector<CTexString*> MenuStrList;
	static  std::vector<CTexString*> numberStrList;		//文字画像表示
	static  std::vector<CTexString*> smallNumberStrList;	// 数字のリスト(ゲームデータウインドウ用)
	static  std::vector<CTexString*> middleNumberStrList;	// 数字のリスト(セーブデータスクリーン用)
	static  std::vector<CTexString*> saveStrList;		//文字画像表示
	static  std::vector<CTexString*> itemStrList;		//文字画像表示
	static  std::vector<CTexString*> equipStrList;		//文字画像表示
	static  std::vector<CTexString*> MessageStrList;
	static  std::vector<CTexString*> equipPrice;		// 装備の値段
	static  std::vector<CTexString*> itemPrice;			// アイテムの値段
	// 装備説明用
	struct List{
		CTexString* m_strLst;				//文字画像表示
		int No;
	};

	static  std::vector<List> explainStrList;		// アイテム説明用

	static 	CTexString*				 m_none;					// 「なし」という文字画像		10/30追記

private:

	static std::vector<bool> m_isSelLst;			//文字画像表示
public:
	static void Create(LPDIRECT3DDEVICE9 _pDevice , CGameData* _pGameData);
	static void Release();

private:
};