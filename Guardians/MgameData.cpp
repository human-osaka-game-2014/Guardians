/**
 @file MgameData.cpp
 @date 作成日：2014/10/18
 @author 三浦
 */

#include "stdafx.h"
#include <time.h>
/**
 *
 *	取得した文字列を分割する
 *　@param s		文字列
 *	@param delim	分割する文字
 *
 */
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
/**
 *
 *	コンストラクタ
 *
 */
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
		if( count < MAX_EQUIP + MAX_ITEM ){
			tmp.no = std::stoi( splitStr[0]);
			strcpy_s(tmp.name,splitStr[1].c_str());
			tmp.price = std::stoi( splitStr[2]);;
			strcpy_s(tmp.explainStr,splitStr[3].c_str());
			tmp.nums = 1;
		}
		// 分解したものを、m_itemListに登録
		if( count < MAX_EQUIP ){
			tmp.stType = std::stoi( splitStr[4] );
			tmp.power = std::stoi( splitStr[5] );
			tmp.unlockNo = std::stoi( splitStr[6] );
			m_equipList.push_back(tmp);
		}else if (count < MAX_EQUIP + MAX_ITEM){
			tmp.unlockNo = std::stoi( splitStr[4] );
			m_itemList.push_back(tmp);
		}else{
			struct EMBLEM tmp;
			strcpy_s(tmp.name,str.c_str());
			m_emblemList.push_back(tmp);
		}
		count++;
	}
	m_emblemFlag.resize(m_emblemList.size() + 1);

	m_hasTools.resize(0);
	m_hasEquip.resize(0);
	
}
/**
 *
 *	装備を検索する
 *　@param _itemNum (アイテムナンバー)
 *	@param _type 種類(アイテムor装備)
 *
 */
int CGameData::Search(int _itemNum,ItemType _type)
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
/**
 *
 *	データをロードする
 *　@param _dataID ロード画面で選択したデータの番号
 *
 */
void CGameData::Load(int _dataID)
{
	// 文字列生成
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ifstream ifs(ss.str());

	std::string str;
	int         count =  0;
	int			itemCount = 0;
	int			equipCount = 0;
	int			m_emblemCount = 0;
	while( std::getline( ifs, str )){
		switch( count ){
		case 0: // セーブ日付
			sscanf_s(str.c_str(),"セーブ日時:%d/%d/%d %d:%d", &m_time.year, &m_time.month, &m_time.date, &m_time.hour, &m_time.minute);
			break;
		case 1: // プレイタイム
			int hour, minute, second; 
			sscanf_s(str.c_str(),"プレイ時間:%d:%d:%d", &hour, &minute, &second);
			m_playTime = hour * 3600 + minute * 60 + second;
			break;
		case 2: // 所持金
			sscanf_s(str.c_str(),"所持金:%d", &m_money);
			break;
		case 3: // 取得装備
			sscanf_s(str.c_str(),"取得装備:%d％", &m_equipPer);
			break;
		case 4: //ステージクリア数
			sscanf_s(str.c_str(),"ステージクリア数:%d", &m_nowClearStageNum);
			m_oldClearStageNum = m_nowClearStageNum;
			m_selectStageNum = m_nowClearStageNum % 4;
			break;
		case 5:
			sscanf_s(str.c_str(),"SelectStageNo:%d",&m_selectStageNum);
			break;
			// 装備品
		case 6:    // 力の腕輪
		case 7:    // 破壊の腕輪
		case 8:    // 白虎の腕輪
		case 9:    // 守りのローブ
		case 10:    // 破邪のローブ
		case 11:   // 玄武のローブ
		case 12:   // 燕の靴
		case 13:   // 隼の靴
		case 14:   // 朱雀の靴
		case 15:   // 修験者の帯
		case 16:   // 青龍の帯
		case 17:   // 導師の魔力器
		case 18:   // 麒麟の魔力器
		case 19:   // 吸魔の指輪
		case 20:   // 毒蛇のピアス
		case 21:   // 身代わりのお守り
			{			// ← caseの中で変数の宣言を行う場合はこの｛とbreakの前の }が必要。他にも制御の転送が～というエラーがでたらこれで対処してください
				str.c_str();
				std::stringstream ss2;
				ss2 << m_equipList[equipCount].name;
				ss2 << ":%d";

				int num;
				sscanf_s(str.c_str(),ss2.str().c_str(), &num);
				// 装備を所持していた場合
				if( num ){
					Equip eq = m_equipList[equipCount];
					eq.nums = num;	// 個数セット
					m_hasEquip.push_back( eq );
					equipCount++;
				}
			}
			break;
			// 消費アイテム
		case 22:   // 治癒の宝珠
		case 23:   // 快癒の宝珠
		case 24:   // 魔力の宝珠
		case 25:   // 天魔の宝珠
		case 26:   // 解毒の宝珠
		case 27:   // 全快の宝珠
		case 28:   // 神癒の宝珠
		case 29:   // 強撃の護符
		case 30:   // 守護の護符
		case 31:   // 俊足の護符
		case 32:   // 天来の護符
		case 33:   // 炎舞の魔術書
		case 34:   // 吸魔の魔術書
		case 35:   // 鈍足の魔術書
			{			// ← caseの中で変数の宣言を行う場合はこの｛とbreakの前の }が必要。他にも制御の転送が～というエラーがでたらこれで対処してください
				std::stringstream ss2;
				ss2 << m_itemList[itemCount].name;
				ss2 << ":%d個";

				int num;
				sscanf_s(str.c_str(),ss2.str().c_str(), &num);
				if( num ){
					HaveTool tool;
					tool = m_hasTools[itemCount];
					tool.nums = num;	// 個数セット
					m_hasTools.push_back( tool );
				}
			}
			break;
			// 実績(SAVEファイルで1ならば取得済み、0ならばまだ取得していない)
		case 36:  // 並ぶものなし
		case 37:  // 猪突猛進
		case 38:  // 怖いもの知らず
		case 39:  // 騎士長の誇り
		case 40:  // 止まらぬ進撃
		case 41:  // 身一つの勝利
		case 42:  // 道具要らず
		case 43:  // 不断の前進
		case 44:  // お宝発掘
		case 45:  // 力の証明
		case 46:  // 必殺の心得
			{
				// ヘッダーの方に std::vector<bool> m_emblemFlag のような変数をbool型で宣言
				// またstd::vector<char*> m_emblemList という称号のリストと m_emblemCount という称号のカウントを作成
				std::stringstream ss2;
				ss2 << m_emblemList[m_emblemCount].name;
				ss2 << ":%d";
				int flag;
				sscanf_s(str.c_str(), ss2.str().c_str(), &flag);	// ここでflagに0か1が入る
				
				m_emblemFlag.push_back( flag == 1 ? true : false );
				
				// ここまでが一つ分なので装備や道具のようにcaseを増やす。また、m_emblemCountを増やすなどをする
			}
			break;
		case 47:
			sscanf_s(str.c_str(),"取得アイテム:%d",&m_itemPer);
			break;
		case 48:
			sscanf_s(str.c_str(),"取得称号:%d",&m_emblemPer);
			break;
		}
		count++;
	}
}
/**
 *
 *	NEWGAME!!! の読み込み
 *
 */
void CGameData::newGame()
{
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
			m_chara[count].equip[0] = m_equipList[Search( std::stoi(splitStr[7]),TYPE_EQUIP )];
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
}
/**
 *
 *	データをセーブする
 *　@param _dataID セーブ画面で選択したデータの番号
 *
 */
void CGameData::Save(int _dataID)
{
	using namespace std;
	// 文字列生成
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ofstream ofs(ss.str());
	
	time_t timer = time(NULL);
	struct tm date;
	localtime_s(&date,&timer); // 現在の日付を取得

	int tmp = m_playTime;
	int time[6];	// 時間を3個の配列に分割
	int count = 0;	
	memset(&time,0,sizeof(time));	// 配列の中身を0にしておく
	// プレイ時間を分解
	while( tmp > 0 ){
		time[count] = tmp % 10;
		tmp /= 10;
		count++;
	}
	ofs << "セーブ日時:" << date.tm_year << "/" << date.tm_mon << "/" << date.tm_mday << " " << date.tm_hour << ":" << date.tm_min << endl;
	ofs << "プレイ時間:" << time[5] << time[4] << ":" << time[3] << time[2] << ":" << time[1] << time[0] << endl;
	
	m_equipPer = static_cast<int>(static_cast<float>(m_hasEquip.size() + 1) / MAX_EQUIP * 100);

	ofs << "所持金:" << m_money << endl;
	ofs << "取得装備:" << m_equipPer << endl;
	ofs << "ステージクリア数:"<< m_nowClearStageNum << endl;
	ofs << "SelectStageNo:"<< m_selectStageNum << endl;
	// 装備やアイテムを書き込む
	for(unsigned i = 0; i < m_equipList.size(); i++){
		ofs << m_equipList[i].name << ":0"  << endl;
	}
	for(unsigned i = 0; i < m_itemList.size(); i++){
		ofs << m_itemList[i].name << ":0" << endl;
	}

	for(unsigned i = 0; i < m_emblemList.size(); i++){
		int tmp = (int)m_emblemFlag[i];
		ofs << m_emblemList[i].name << ":" << tmp << endl;
	}
	// 装備の所持率を取得
	m_emblemPer = static_cast<int>(static_cast<float>( m_emblemList.size() + 1) / 11 * 100);
	m_itemPer = static_cast<int>(static_cast<float>( m_hasTools.size() + 1) / MAX_ITEM * 100);

	ofs << "取得アイテム:" << m_itemPer << endl;
	ofs << "取得称号:" << m_emblemPer << endl;
}