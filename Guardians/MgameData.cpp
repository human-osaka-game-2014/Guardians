/**
 @file MgameData.cpp
 @date �쐬���F2014/10/18
 @author �O�Y
 */

#include "stdafx.h"
#include <time.h>
/**
 *
 *	�擾����������𕪊�����
 *�@@param s		������
 *	@param delim	�������镶��
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
 *	�R���X�g���N�^
 *
 */
CGameData::CGameData()
{
	// �����Ńt�@�C���ǂݍ���
	// ifstream�Ńt�@�C�����w�肵�ēǂݍ���
	std::ifstream ifs("List\\itemList.txt");

	HaveTool have;
	have.no = 0;
	m_getItem.push_back(have);
	
	// while����getline��1�s���擾����
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
		// �����������̂��Am_itemList�ɓo�^
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
 *	��������������
 *�@@param _itemNum (�A�C�e���i���o�[)
 *	@param _type ���(�A�C�e��or����)
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
 *	�f�[�^�����[�h����
 *�@@param _dataID ���[�h��ʂőI�������f�[�^�̔ԍ�
 *
 */
void CGameData::Load(int _dataID)
{
	// �����񐶐�
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
		case 0: // �Z�[�u���t
			sscanf_s(str.c_str(),"�Z�[�u����:%d/%d/%d %d:%d", &m_time.year, &m_time.month, &m_time.date, &m_time.hour, &m_time.minute);
			break;
		case 1: // �v���C�^�C��
			int hour, minute, second; 
			sscanf_s(str.c_str(),"�v���C����:%d:%d:%d", &hour, &minute, &second);
			m_playTime = hour * 3600 + minute * 60 + second;
			break;
		case 2: // ������
			sscanf_s(str.c_str(),"������:%d", &m_money);
			break;
		case 3: // �擾����
			sscanf_s(str.c_str(),"�擾����:%d��", &m_equipPer);
			break;
		case 4: //�X�e�[�W�N���A��
			sscanf_s(str.c_str(),"�X�e�[�W�N���A��:%d", &m_nowClearStageNum);
			m_oldClearStageNum = m_nowClearStageNum;
			m_selectStageNum = m_nowClearStageNum % 4;
			break;
		case 5:
			sscanf_s(str.c_str(),"SelectStageNo:%d",&m_selectStageNum);
			break;
			// �����i
		case 6:    // �̘͂r��
		case 7:    // �j��̘r��
		case 8:    // ���Ղ̘r��
		case 9:    // ���̃��[�u
		case 10:    // �j�ׂ̃��[�u
		case 11:   // �����̃��[�u
		case 12:   // ���̌C
		case 13:   // ���̌C
		case 14:   // �鐝�̌C
		case 15:   // �C���҂̑�
		case 16:   // ���̑�
		case 17:   // ���t�̖��͊�
		case 18:   // �i�ق̖��͊�
		case 19:   // �z���̎w��
		case 20:   // �Ŏւ̃s�A�X
		case 21:   // �g����̂����
			{			// �� case�̒��ŕϐ��̐錾���s���ꍇ�͂��́o��break�̑O�� }���K�v�B���ɂ�����̓]�����`�Ƃ����G���[���ł��炱��őΏ����Ă�������
				str.c_str();
				std::stringstream ss2;
				ss2 << m_equipList[equipCount].name;
				ss2 << ":%d";

				int num;
				sscanf_s(str.c_str(),ss2.str().c_str(), &num);
				// �������������Ă����ꍇ
				if( num ){
					Equip eq = m_equipList[equipCount];
					eq.nums = num;	// ���Z�b�g
					m_hasEquip.push_back( eq );
					equipCount++;
				}
			}
			break;
			// ����A�C�e��
		case 22:   // �����̕��
		case 23:   // �����̕��
		case 24:   // ���͂̕��
		case 25:   // �V���̕��
		case 26:   // ��ł̕��
		case 27:   // �S���̕��
		case 28:   // �_���̕��
		case 29:   // �����̌아
		case 30:   // ���̌아
		case 31:   // �r���̌아
		case 32:   // �V���̌아
		case 33:   // �����̖��p��
		case 34:   // �z���̖��p��
		case 35:   // �ݑ��̖��p��
			{			// �� case�̒��ŕϐ��̐錾���s���ꍇ�͂��́o��break�̑O�� }���K�v�B���ɂ�����̓]�����`�Ƃ����G���[���ł��炱��őΏ����Ă�������
				std::stringstream ss2;
				ss2 << m_itemList[itemCount].name;
				ss2 << ":%d��";

				int num;
				sscanf_s(str.c_str(),ss2.str().c_str(), &num);
				if( num ){
					HaveTool tool;
					tool = m_hasTools[itemCount];
					tool.nums = num;	// ���Z�b�g
					m_hasTools.push_back( tool );
				}
			}
			break;
			// ����(SAVE�t�@�C����1�Ȃ�Ύ擾�ς݁A0�Ȃ�΂܂��擾���Ă��Ȃ�)
		case 36:  // ���Ԃ��̂Ȃ�
		case 37:  // ���˖Ґi
		case 38:  // �|�����̒m�炸
		case 39:  // �R�m���̌ւ�
		case 40:  // �~�܂�ʐi��
		case 41:  // �g��̏���
		case 42:  // ����v�炸
		case 43:  // �s�f�̑O�i
		case 44:  // ���󔭌@
		case 45:  // �͂̏ؖ�
		case 46:  // �K�E�̐S��
			{
				// �w�b�_�[�̕��� std::vector<bool> m_emblemFlag �̂悤�ȕϐ���bool�^�Ő錾
				// �܂�std::vector<char*> m_emblemList �Ƃ����̍��̃��X�g�� m_emblemCount �Ƃ����̍��̃J�E���g���쐬
				std::stringstream ss2;
				ss2 << m_emblemList[m_emblemCount].name;
				ss2 << ":%d";
				int flag;
				sscanf_s(str.c_str(), ss2.str().c_str(), &flag);	// ������flag��0��1������
				
				m_emblemFlag.push_back( flag == 1 ? true : false );
				
				// �����܂ł�����Ȃ̂ő����⓹��̂悤��case�𑝂₷�B�܂��Am_emblemCount�𑝂₷�Ȃǂ�����
			}
			break;
		case 47:
			sscanf_s(str.c_str(),"�擾�A�C�e��:%d",&m_itemPer);
			break;
		case 48:
			sscanf_s(str.c_str(),"�擾�̍�:%d",&m_emblemPer);
			break;
		}
		count++;
	}
}
/**
 *
 *	NEWGAME!!! �̓ǂݍ���
 *
 */
void CGameData::newGame()
{
	for( int i = 0; i < 4; i++ ) {
		//���@�����A�C�e���̏�����
		m_tools[i].no		= i == 0 ? m_itemList[i].no : -1;
		m_tools[i].nums		= 3;
		strcpy_s( m_tools[0].explainStr,m_itemList[0].explainStr);
	}
	m_death = false;
	m_win  = false;
	// �ŏ��͏����������Ȃ��̂�0��(�Ȃ�)�����Ă���
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
			sscanf_s(str.c_str(),"�o����,%d,%d,%d",&m_turnNo[0],&m_turnNo[1],&m_turnNo[2]);
			break;
		case 4:
			int hour, minute, second; 
			sscanf_s(str.c_str(),"�v���C����,%d,%d,%d", &hour, &minute, &second);
			m_playTime = hour*3600 + minute*60 + second;
			break;
		case 5:
			sscanf_s(str.c_str(),"�X�e�[�W�N���A��,%d",&m_nowClearStageNum);
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
 *	�f�[�^���Z�[�u����
 *�@@param _dataID �Z�[�u��ʂőI�������f�[�^�̔ԍ�
 *
 */
void CGameData::Save(int _dataID)
{
	using namespace std;
	// �����񐶐�
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ofstream ofs(ss.str());
	
	time_t timer = time(NULL);
	struct tm date;
	localtime_s(&date,&timer); // ���݂̓��t���擾

	int tmp = m_playTime;
	int time[6];	// ���Ԃ�3�̔z��ɕ���
	int count = 0;	
	memset(&time,0,sizeof(time));	// �z��̒��g��0�ɂ��Ă���
	// �v���C���Ԃ𕪉�
	while( tmp > 0 ){
		time[count] = tmp % 10;
		tmp /= 10;
		count++;
	}
	ofs << "�Z�[�u����:" << date.tm_year << "/" << date.tm_mon << "/" << date.tm_mday << " " << date.tm_hour << ":" << date.tm_min << endl;
	ofs << "�v���C����:" << time[5] << time[4] << ":" << time[3] << time[2] << ":" << time[1] << time[0] << endl;
	
	m_equipPer = static_cast<int>(static_cast<float>(m_hasEquip.size() + 1) / MAX_EQUIP * 100);

	ofs << "������:" << m_money << endl;
	ofs << "�擾����:" << m_equipPer << endl;
	ofs << "�X�e�[�W�N���A��:"<< m_nowClearStageNum << endl;
	ofs << "SelectStageNo:"<< m_selectStageNum << endl;
	// ������A�C�e������������
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
	// �����̏��������擾
	m_emblemPer = static_cast<int>(static_cast<float>( m_emblemList.size() + 1) / 11 * 100);
	m_itemPer = static_cast<int>(static_cast<float>( m_hasTools.size() + 1) / MAX_ITEM * 100);

	ofs << "�擾�A�C�e��:" << m_itemPer << endl;
	ofs << "�擾�̍�:" << m_emblemPer << endl;
}