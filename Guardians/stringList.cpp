#include "stdafx.h"

std::vector<CTexString*>		 CStringList::equipStrList;		// 装備リスト
std::vector<CTexString*>		 CStringList::equipPrice;		// 装備の値段のリスト

std::vector<CTexString*>		 CStringList::itemStrList;		// アイテムリスト
std::vector<CTexString*>		 CStringList::itemPrice;		// アイテムの値段のリスト

std::vector<CStringList::List>	 CStringList::explainStrList;	// アイテム＆装備の説明リスト

std::vector<CTexString*>		 CStringList::saveStrList;		// セーブ画面時に使用する文字のリスト

std::vector<CTexString*>		 CStringList::MenuStrList;
std::vector<CTexString*>		 CStringList::numberStrList;	// 数字のリスト
std::vector<CTexString*>		 CStringList::smallNumberStrList;	// 数字のリスト
std::vector<CTexString*>		 CStringList::middleNumberStrList;	// 数字のリスト

std::vector<CTexString*>		 CStringList::MessageStrList;	// メッセージリスト

CTexString*						 CStringList::m_none;			// 「なし」という文字画像		10/30追記

std::vector<bool>				 CStringList::m_isSelLst;		

void CStringList::Create(LPDIRECT3DDEVICE9 _pDevice , CGameData* _pGameData)
{
	if( !saveStrList.empty() ) return;
	std::string wstr[] = {
		"プレイ時間",
		"所持金",
		"取得装備",
		"取得アイテム",
		"実績解除",
		"データ無し",
		"DATA01",
		"DATA02",
		"DATA03",
		"DATA04",
		"DATA05",
		"DATA06",
		"DATA07",
		"DATA08",
		"DATA09",
		"DATA10",
	};
	for( int i = 0; i < sizeof(wstr)/sizeof(std::string); i++ ) {
		saveStrList.push_back(new CTexString(_pDevice, wstr[i], 20, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	std::string wstr2[] = {
		"０",
		"１",
		"２",
		"３",
		"４",
		"５",
		"６",
		"７",
		"８",
		"９",
		"：",
		"×",
		"＋",
		"/",
		"％",
		"　",
		"金額",
		"所持数",
	};
	for( int i = 0; i < sizeof(wstr2)/sizeof(std::string); i++ ) {
		numberStrList.push_back(new CTexString(_pDevice, wstr2[i], FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	for( int i = 0; i < sizeof(wstr2)/sizeof(std::string); i++ ) {
		smallNumberStrList.push_back(new CTexString(_pDevice, wstr2[i], FONT_SIZE_W / 2, 20, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	for( int i = 0; i < sizeof(wstr2)/sizeof(std::string); i++ ) {
		middleNumberStrList.push_back(new CTexString(_pDevice, wstr2[i], 20, 20, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	std::string wstr3[] = {
		"戦闘を開始しますか？",
		"上書きしますか？",
		"はい",
		"いいえ",
		"ロードしますka？",
	};
	for( int i = 0; i < sizeof(wstr3)/sizeof(std::string); i++ ) {
		MessageStrList.push_back(new CTexString(_pDevice, wstr3[i], FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	std::string wstr5[] = {
		"メニュー切替",	// PIC_MENU,
		"戦闘準備",		// PIC_PREPARATION,
		"キャンセル",		// PIC_CANCEL,
		"ステージ選択",	// PIC_STAGE_SELECT,
		"順番設定",		// PIC_TURN_NO,
		"キャラ選択",		// PIC_CHARA_SELECT,
		"装備変更",		// PIC_CHANGE_EQUIP,
		"購入",			// PIC_BUY,
		"決定",			// PIC_ENTER,
		"項目選択",		// PIC_ITEM_SELECT,
	};

	for( int i = 0; i < sizeof(wstr5)/sizeof(std::string); i++ ) {
		MenuStrList.push_back(new CTexString(_pDevice, wstr5[i], 25, 60, L"ＭＳ　Ｓゴシック" ) );
		m_isSelLst.push_back(true);
	}
	char c[256];
	std::string wdst;
	for(unsigned i = 0; i < _pGameData->m_equipList.size();i++){
		// 装備の名前
		//CStringConvert::Widen(_pGameData->m_equipList[i].name,wdst);
		equipStrList.push_back(new CTexString(_pDevice,_pGameData->m_equipList[i].name, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		// 装備の値段
		sprintf_s(c, "%d",_pGameData->m_equipList[i].price);
		//CStringConvert::Widen(c,wdst);
		equipPrice.push_back(new CTexString(_pDevice,c, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY  ) );
		m_isSelLst.push_back(true);
	}

	for(unsigned i = 0; i < _pGameData->m_itemList.size();i++){
		//CStringConvert::Widen(_pGameData->m_itemList[i].name,wdst);
		itemStrList.push_back(new CTexString(_pDevice,_pGameData->m_itemList[i].name, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		// アイテムの値段
		sprintf_s(c, "%d",_pGameData->m_itemList[i].price);
		//CStringConvert::Widen(c,wdst);
		itemPrice.push_back(new CTexString(_pDevice,c, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY  ) );
		m_isSelLst.push_back(true);
	}

	// 装備とアイテムの説明をリストに追加
	List tmp;
	for(unsigned i = 0; i < _pGameData->m_itemList.size();i++){
		//CStringConvert::Widen(_pGameData->m_itemList[i].explainStr,wdst);
		tmp.m_strLst = (new CTexString(_pDevice, _pGameData->m_itemList[i].explainStr, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		tmp.No = _pGameData->m_itemList[i].no;
		explainStrList.push_back(tmp);
	}
	for(unsigned i = 0; i < _pGameData->m_equipList.size();i++){
		//CStringConvert::Widen(_pGameData->m_equipList[i].explainStr,wdst);
		tmp.m_strLst = (new CTexString(_pDevice, _pGameData->m_equipList[i].explainStr, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		tmp.No = _pGameData->m_equipList[i].no;
		explainStrList.push_back(tmp);
	}
	// なし　の文字画像
	m_none = new CTexString(_pDevice, "なし", FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY);

	
}
void CStringList::Release()
{
	for(unsigned int i = 0; i < MessageStrList.size();i++){
		SAFE_DELETE(MessageStrList[i]);
	}
	std::vector<CTexString*>().swap(MessageStrList);
	for(unsigned int i = 0; i < numberStrList.size();i++){
		SAFE_DELETE(numberStrList[i]);
		SAFE_DELETE(middleNumberStrList[i]);
		SAFE_DELETE(smallNumberStrList[i]);
	}
	std::vector<CTexString*>().swap(numberStrList);
	std::vector<CTexString*>().swap(middleNumberStrList);
	std::vector<CTexString*>().swap(smallNumberStrList);
	for(unsigned int i = 0; i < equipStrList.size();i++){
		SAFE_DELETE(equipStrList[i]);
		SAFE_DELETE( equipPrice[i] );
	}
	std::vector<CTexString*>().swap(equipStrList);
	std::vector<CTexString*>().swap(equipPrice);

	for(unsigned int i = 0; i < itemStrList.size();i++){
		SAFE_DELETE(itemStrList[i]);
		SAFE_DELETE(itemPrice[i]);
	}
	std::vector<CTexString*>().swap(itemStrList);
	std::vector<CTexString*>().swap(itemPrice);

	for(unsigned int i = 0; i < saveStrList.size();i++){
		SAFE_DELETE(saveStrList[i]);
	}	
	std::vector<CTexString*>().swap(saveStrList);
	for(unsigned int i = 0; i < explainStrList.size();i++){
		SAFE_DELETE( explainStrList[i].m_strLst );
	}
	std::vector<CStringList::List>().swap(explainStrList);
	for(unsigned i = 0; i < MenuStrList.size();i++){
		SAFE_DELETE(MenuStrList[i]);
	}
	std::vector<CTexString*>().swap(MenuStrList);
		std::vector<bool>().swap(m_isSelLst);
	// 「なし」の文字解放	10/30 追記
	SAFE_DELETE(m_none);
}
