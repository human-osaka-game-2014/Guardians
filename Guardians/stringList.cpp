#include "stdafx.h"

std::vector<CTexString*>		 CStringList::equipStrList;		// �������X�g
std::vector<CTexString*>		 CStringList::equipPrice;		// �����̒l�i�̃��X�g

std::vector<CTexString*>		 CStringList::itemStrList;		// �A�C�e�����X�g
std::vector<CTexString*>		 CStringList::itemPrice;		// �A�C�e���̒l�i�̃��X�g

std::vector<CStringList::List>	 CStringList::explainStrList;	// �A�C�e���������̐������X�g

std::vector<CTexString*>		 CStringList::saveStrList;		// �Z�[�u��ʎ��Ɏg�p���镶���̃��X�g

std::vector<CTexString*>		 CStringList::MenuStrList;
std::vector<CTexString*>		 CStringList::numberStrList;	// �����̃��X�g
std::vector<CTexString*>		 CStringList::smallNumberStrList;	// �����̃��X�g
std::vector<CTexString*>		 CStringList::middleNumberStrList;	// �����̃��X�g

std::vector<CTexString*>		 CStringList::MessageStrList;	// ���b�Z�[�W���X�g

CTexString*						 CStringList::m_none;			// �u�Ȃ��v�Ƃ��������摜		10/30�ǋL

std::vector<bool>				 CStringList::m_isSelLst;		

void CStringList::Create(LPDIRECT3DDEVICE9 _pDevice , CGameData* _pGameData)
{
	if( !saveStrList.empty() ) return;
	std::string wstr[] = {
		"�v���C����",
		"������",
		"�擾����",
		"�擾�A�C�e��",
		"���щ���",
		"�f�[�^����",
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
		"�O",
		"�P",
		"�Q",
		"�R",
		"�S",
		"�T",
		"�U",
		"�V",
		"�W",
		"�X",
		"�F",
		"�~",
		"�{",
		"/",
		"��",
		"�@",
		"���z",
		"������",
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
		"�퓬���J�n���܂����H",
		"�㏑�����܂����H",
		"�͂�",
		"������",
		"���[�h���܂�ka�H",
	};
	for( int i = 0; i < sizeof(wstr3)/sizeof(std::string); i++ ) {
		MessageStrList.push_back(new CTexString(_pDevice, wstr3[i], FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
	}
	std::string wstr5[] = {
		"���j���[�ؑ�",	// PIC_MENU,
		"�퓬����",		// PIC_PREPARATION,
		"�L�����Z��",		// PIC_CANCEL,
		"�X�e�[�W�I��",	// PIC_STAGE_SELECT,
		"���Ԑݒ�",		// PIC_TURN_NO,
		"�L�����I��",		// PIC_CHARA_SELECT,
		"�����ύX",		// PIC_CHANGE_EQUIP,
		"�w��",			// PIC_BUY,
		"����",			// PIC_ENTER,
		"���ڑI��",		// PIC_ITEM_SELECT,
	};

	for( int i = 0; i < sizeof(wstr5)/sizeof(std::string); i++ ) {
		MenuStrList.push_back(new CTexString(_pDevice, wstr5[i], 25, 60, L"�l�r�@�r�S�V�b�N" ) );
		m_isSelLst.push_back(true);
	}
	char c[256];
	std::string wdst;
	for(unsigned i = 0; i < _pGameData->m_equipList.size();i++){
		// �����̖��O
		//CStringConvert::Widen(_pGameData->m_equipList[i].name,wdst);
		equipStrList.push_back(new CTexString(_pDevice,_pGameData->m_equipList[i].name, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		// �����̒l�i
		sprintf_s(c, "%d",_pGameData->m_equipList[i].price);
		//CStringConvert::Widen(c,wdst);
		equipPrice.push_back(new CTexString(_pDevice,c, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY  ) );
		m_isSelLst.push_back(true);
	}

	for(unsigned i = 0; i < _pGameData->m_itemList.size();i++){
		//CStringConvert::Widen(_pGameData->m_itemList[i].name,wdst);
		itemStrList.push_back(new CTexString(_pDevice,_pGameData->m_itemList[i].name, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY ) );
		m_isSelLst.push_back(true);
		// �A�C�e���̒l�i
		sprintf_s(c, "%d",_pGameData->m_itemList[i].price);
		//CStringConvert::Widen(c,wdst);
		itemPrice.push_back(new CTexString(_pDevice,c, FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY  ) );
		m_isSelLst.push_back(true);
	}

	// �����ƃA�C�e���̐��������X�g�ɒǉ�
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
	// �Ȃ��@�̕����摜
	m_none = new CTexString(_pDevice, "�Ȃ�", FONT_SIZE_W, FONT_SIZE_H, FONT_FAMILY);

	
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
	// �u�Ȃ��v�̕������	10/30 �ǋL
	SAFE_DELETE(m_none);
}
