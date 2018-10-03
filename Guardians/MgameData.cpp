/*--------------------------------------------------------------

	�������e:�Q�[���f�[�^�Ǘ�
	�쐬��:�O�Y
	�쐬��:10/18
	�X�V��:
	�X�V���e:
	�֐��@
		�R���X�g���N�^
		Load
		Save
	�ϐ��@

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
		tmp.no = std::stoi( splitStr[0]);
		strcpy_s(tmp.name,splitStr[1].c_str());
		tmp.price = std::stoi( splitStr[2]);;
		strcpy_s(tmp.explainStr,splitStr[3].c_str());
		tmp.nums = 1;
		// �����������̂��Am_itemList�ɓo�^
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
				m_chara[count].equip[0] = m_equipList[Sarch( std::stoi(splitStr[7]),TYPE_EQUIP )];
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
		// �����񐶐�
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
			case 0: // �Z�[�u���t
				sscanf_s(str.c_str(),"�Z�[�u�����F%d/%d/%d %d:%d", &m_time.year, &m_time.month, &m_time.date, &m_time.hour, &m_time.minute);
				break;
			case 1: // �v���C�^�C��
				int hour, minute, second; 
				sscanf_s(str.c_str(),"�v���C���ԁF%d�F%d�F%d", &hour, &minute, &second);
				m_playTime = hour*3600 + minute*60 + second;
				break;
			case 2: // ������
				sscanf_s(str.c_str(),"�������F%d", &m_money);
				break;
			case 3: // �擾����
				sscanf_s(str.c_str(),"�擾�����F%d��", &m_toolsPer);
				break;
			case 4: //�X�e�[�W�N���A��
				sscanf_s(str.c_str(),"�X�e�[�W�N���A���F%d", m_nowClearStageNum);
				m_oldClearStageNum = m_nowClearStageNum;
				m_selectStageNum = m_nowClearStageNum % 4;
				break;
				// �����i
			case 5:    // �̘͂r��
			case 6:    // �j��̘r��
			case 7:    // ���Ղ̘r��
			case 8:    // ���̃��[�u
			case 9:    // �j�ׂ̃��[�u
			case 10:   // �����̃��[�u
			case 11:   // ���̌C
			case 12:   // ���̌C
			case 13:   // �鐝�̌C
			case 14:   // �C���҂̑�
			case 15:   // ���̑�
			case 16:   // ���t�̖��͊�
			case 17:   // �i�ق̖��͊�
			case 18:   // �z���̎w��
			case 19:   // �Ŏւ̃s�A�X
			case 20:   // �g����̂����
				// ����A�C�e��
			case 21:   // �����̕��
			case 22:   // �����̕��
			case 23:   // ���͂̕��
			case 24:   // �V���̕��
			case 25:   // ��ł̕��
			case 26:   // �S���̕��
			case 27:   // �_���̕��
			case 28:   // �����̌아
			case 29:   // ���̌아
			case 30:   // �r���̌아
			case 31:   // �V���̌아
			case 32:   // �����̖��p��
			case 33:   // �z���̖��p��
			case 34:   // �ݑ��̖��p��
				{			// �� case�̒��ŕϐ��̐錾���s���ꍇ�͂��́o��break�̑O�� }���K�v�B���ɂ�����̓]�����`�Ƃ����G���[���ł��炱��őΏ����Ă�������
					std::stringstream ss2;
					ss2 << m_itemList[itemCount].name;
					ss2 << "�@%d��";

					int num;
					sscanf_s(str.c_str(),ss2.str().c_str(), &num);
					Equip eq;
					eq.nums = num;	// ���Z�b�g
					eq.type = m_itemList[itemCount].type;
					m_hasEquip.push_back( eq );
				}
				break;
				// ����(SAVE�t�@�C����1�Ȃ�Ύ擾�ς݁A0�Ȃ�΂܂��擾���Ă��Ȃ�)
			case 35:  // ���Ԃ��̂Ȃ�
			case 36:  // ���˖Ґi
			case 37:  // �|�����̒m�炸
			case 38:  // �R�m���̌ւ�
			case 39:  // �~�܂�ʐi��
			case 40:  // �g��̏���
			case 41:  // ����v�炸
			case 42:  // �s�f�̑O�i
			case 43:  // ���󔭌@
			case 44:  // �͂̏ؖ�
			case 45:  // �K�E�̐S��
				{
					// �w�b�_�[�̕��� std::vector<bool> m_emblemFlag �̂悤�ȕϐ���bool�^�Ő錾
					// �܂�std::vector<char*> m_emblemList �Ƃ����̍��̃��X�g�� m_emblemCount �Ƃ����̍��̃J�E���g���쐬
					std::stringstream ss2;
					ss2 << m_emblemList[m_emblemCount];
					ss2 << ":%d";
					int flag;
					sscanf_s(str.c_str(), ss2.str().c_str(), &flag);	// ������flag��0��1������
				
					m_emblemFlag.push_back( flag == 1 ? true : false );
				
					// �����܂ł�����Ȃ̂ő����⓹��̂悤��case�𑝂₷�B�܂��Am_emblemCount�𑝂₷�Ȃǂ�����
				}
				break;
			}
			count++;
		}
	}
}

void CGameData::Save(int _dataID)
{
	// �����񐶐�
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _dataID;
	ss << ".txt";

	std::ifstream ifs(ss.str());

}