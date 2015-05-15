/*--------------------------------------------------------------

	処理内容:ゲームデータ管理
	作成者:三浦
	作成日:10/18
	更新日:
	更新内容:
	関数　
		コンストラクタ
		Load
		Save
	変数　

--------------------------------------------------------------*/
#include "stdafx.h"

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
    if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

CGameData::CGameData()
{
	// ここでファイル読み込み
	// ifstreamでファイルを指定して読み込み
	std::ifstream ifs("List\\itemList.txt");

	HaveTool have;
	have.no = 0;
	m_getItem.push_back(have);
	
	// while文でgetlineで1行ずつ取得する
	int count = 0;
	std::string str;
	while( getline( ifs, str )){
		std::vector<std::string> splitStr = split(str,',');		//sscanf_s(str.c_str(),"%d,%s,%d,%s", &num, itemName, &price, explainStr);

		Equip   tmp;
		tmp.no = std::stoi( splitStr[0]);
		strcpy_s(tmp.name,splitStr[1].c_str());
		tmp.price = std::stoi( splitStr[2]);;
		strcpy_s(tmp.explainStr,splitStr[3].c_str());
		tmp.nums = 1;
		// 分解したものを、m_itemListに登録
		if( count > 15 ){
			tmp.unlockNo = std::stoi( splitStr[4] );
			m_itemList.push_back(tmp);
		}else{
			tmp.stType = std::stoi( splitStr[4] );
			tmp.power = std::stoi( splitStr[5] );
			tmp.unlockNo = std::stoi( splitStr[6] );
			m_equipList.push_back(tmp);
		}
		count++;
	}
	m_hasTools.resize(0);
	m_hasEquip.resize(0);
	
}
int CGameData::Sarch(int _itemNum,ItemType _type)
{
	if( _type == TYPE_EQUIP ){
		for(unsigned int i = 0; i < m_equipList.size();i++){
			if(m_equipList[i].no == _itemNum )
				return i;
		}
	}else{
		for(unsigned int i = 0; i < m_itemList.size();i++){
			if(m_itemList[i].no == _itemNum )
				return i;
		}
	}
	return -1;
}
void CGameData::Load(int _dataID)
{
	//_dataID = 0;
	if( /*newGame*/_dataID == 0){
		for( int i = 0; i < 4; i++ ) {
			//仮　初期アイテムの初期化
			m_tools[i].no		= i == 0 ? m_itemList[i].no : -1;
			m_tools[i].nums		= 3;
			strcpy_s( m_tools[0].explainStr,m_itemList[0].explainStr);
		}
		m_death = false;
		m_win  = false;
		// 最初は所持装備がないので0番(なし)を入れておく
		m_hasEquip.push_back(m_equipList[0]);

		std::ifstream ifs("SaveData\\newgame.txt");
		int count = 0;
		std::string str;

		while( std::getline( ifs,str )){
			std::vector<std::string> splitStr = split(str,',');		//sscanf_s(str.c_str(),"%d,%s,%d,%s", &num, itemName, &price, explainStr);
			switch( count ){
			case 0:
			case 1:
			case 2:
				strcpy_s( m_chara[count].name,256,splitStr[0].c_str() );
				m_chara[count].hp	= std::stoi(splitStr[1]);
				m_chara[count].mp	= std::stoi(splitStr[2]);
				m_chara[count].atk	= std::stoi(splitStr[3]);
				m_chara[count].def	= std::stoi(splitStr[4]);
				m_chara[count].spd	= std::stoi(splitStr[5]);
				m_chara[count].ins	= std::stoi(splitStr[6]);
				m_chara[count].equip[0] = m_equipList[Sarch( std::stoi(splitStr[7]),TYPE_EQUIP )];
				m_chara[count].equip[0].nums = 1;
				m_chara[count].equip[1] = m_equipList[0];
				break;
			case 3:
				sscanf_s(str.c_str(),"出撃順,%d,%d,%d",&m_turnNo[0],&m_turnNo[1],&m_turnNo[2]);
				break;
			case 4:
				int hour, minute, second; 
				sscanf_s(str.c_str(),"プレイ時間,%d,%d,%d", &hour, &minute, &second);
				m_playTime = hour*3600 + minute*60 + second;
				break;
			case 5:
				sscanf_s(str.c_str(),"ステージクリア数,%d",&m_nowClearStageNum);
				m_oldClearStageNum = m_nowClearStageNum;
				m_selectStageNum = m_nowClearStageNum % 4;
				break;
			case 6:
				sscanf_s(str.c_str(),"SelectStageNo:%d",&m_selectStageNum);
				break;
			case 7:
				sscanf_s(str.c_str(),"money,%d",&m_money);
				break;
			}
			count++;
		}
	}else{
		// 文字列生成
		std::stringstream ss;
		ss << "SaveData\\SAVE";
		ss << _dataID;
		ss << ".txt";

		std::ifstream ifs(ss.str());

		std::string str;
		int         count =  0;
		int			itemCount = 0;
		int			m_emblemCount = 0;
		while( std::getline( ifs, str )){
			switch( count ){
			case 0: // セーブ日付
				sscanf_s(str.c_str(),"セーブ日時：%d/%d/%d %d:%d", &m_time.year, &m_time.month, &m_time.date, &m_time.hour, &m_time.minute);
				break;
			case 1: // プレイタイム
				int hour, minute, second; 
				sscanf_s(str.c_str(),"プレイ時間：%d：%d：%d", &hour, &minute, &second);
				m_playTime = hour*3600 + minute*60 + second;
				break;
			case 2: // 所持金
				sscanf_s(str.c_str(),"所持金：%d", &m_money);
				break;
			case 3: // 取得装備
				sscanf_s(str.c_str(),"取得装備：%d％", &m_toolsPer);
				break;
			case 4: //ステージクリア数
				sscanf_s(str.c_str(),"ステージクリア数：%d", m_nowClearStageNum);
				m_oldClearStageNum = m_nowClearStageNum;
				m_selectStageNum = m_nowClearStageNum % 4;
				break;
				// 装備品
			case 5:    // 力の腕輪
			case 6:    // 破壊の腕輪
			case 7:    // 白虎の腕輪
			case 8:    // 守りのローブ
			case 9:    // 破邪のローブ
			case 10:   // 玄武のローブ
			case 11:   // 燕の靴
			case 12:   // 隼の靴
			case 13:   // 朱雀の靴
			case 14:   // 修験者の帯
			case 15:   // 青龍の帯
			case 16:   // 導師の魔力器
			case 17:   // 麒麟の魔力器
			case 18:   // 吸魔の指輪
			case 19:   // 毒蛇のピアス
			case 20:   // 身代わりのお守り
				// 消費アイテム
			case 21:   // 治癒の宝珠
			case 22:   // 快癒の宝珠
			case 23:   // 魔力の宝珠
			case 24:   // 天魔の宝珠
			case 25:   // 解毒の宝珠
			case 26:   // 全快の宝珠
			case 27:   // 神癒の宝珠
			case 28:   // 強撃の護符
			case 29:   // 守護の護符
			case 30:   // 俊足の護符
			case 31:   // 天来の護符
			case 32:   // 炎舞の魔術書
			case 33:   // 吸魔の魔術書
			case 34:   // 鈍足の魔術書
				{			// ← caseの中で変数の宣言を行う場合はこの｛とbreakの前の }が必要。他にも制御の転送が～というエラーがでたらこれで対処してください
					std::stringstream ss2;
					ss2 << m_itemList[itemCount].name;
					ss2 << "　%d個";

					int num;
					sscanf_s(str.c_str(),ss2.str().c_str(), &num);
					Equip eq;
					eq.nums = num;	// 個数セット
					eq.type = m_itemList[itemCount].type;
					m_hasEquip.push_back( eq );
				}
				break;
				// 実績(SAVEファイルで1ならば取得済み、0ならばまだ取得していない)
			case 35:  // 並ぶものなし
			case 36:  // 猪突猛進
			case 37:  // 怖いもの知らず
			case 38:  // 騎士長の誇り
			case 39:  // 止まらぬ進撃
			case 40:  // 身一つの勝利
			case 41:  // 道具要らず
			case 42:  // 不断の前進
			case 43:  // お宝発掘
			case 44:  // 力の証明
			case 45:  // 必殺の心得
				{
					// ヘッダーの方に std::vector<bool> m_emblemFlag のような変数をbool型で宣言
					// またstd::vector<char*> m_emblemList という称号のリストと m_emblemCount という称号のカウントを作成
					std::stringstream ss2;
					ss2 << m_emblemList[m_emblemCount];
					ss2 << ":%d";
					int flag;
					sscanf_s(str.c_str(), ss2.str().c_str(), &flag);	// ここでflagに0か1が入る
				
					m_emblemFlag.push_back( flag == 1 ? true : false );
				
					// ここまでが一つ分なので装備や道具のようにcaseを増やす。また、m_emblemCountを増やすなどをする
				}
				break;
			}
			count++;
		}
	}
}

void CGameData::Save(int _dataID)
{
	// 文字列生成
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ifstream ifs(ss.str());

}