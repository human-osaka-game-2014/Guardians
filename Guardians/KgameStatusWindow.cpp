#include "stdafx.h"
/*--------------------------------------------------------------

	�������e:�L����,�ő�HP,MP,�U��,�h��,���x,�u���̕\��
	�쐬��:��
	�쐬��:10/07
	�X�V��:11/08
	�X�V���e
	  �A�C�R���̒ǉ�
	  �t�H���g�����̏C��
	  ���ʒǉ��\��
	�֐��@
		draw�̍쐬
	�ϐ��@
	int	m_hp	HP�̒ǉ�
	int	m_mp	MP�̒ǉ�
	int	m_atk	�U���͂̒ǉ�
	int	m_def	����͂̒ǉ�
	int	m_spd	���x�͂̒ǉ�
	int	m_ins	�u���͂̒ǉ�
--------------------------------------------------------------*/


CGameStatusWindow::CGameStatusWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData) :
	CGameWindow( _pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT)),m_pGameData( _pGameData ),m_charaID(0)
{

	m_texChara = CTexMgr.Get(TEX_CHARA_ICON );

}
CGameStatusWindow::~CGameStatusWindow()
{

}

void CGameStatusWindow::Control() //����
{
	CGameWindow::Control();
}	
void CGameStatusWindow::Draw()    //�`��
{
	CGameWindow::Draw();

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280, m_position.y-170,0,272,280,274);			//�d�؂�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-170,520,272,800,274);			//�d�؂�̕\��


	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y-140,-2,492,126,524);		//�ő�HP�\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-120, m_position.y-140,128,588,162,620);		//:�̕\��

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y-80,126,492,254,524);		//�ő�MP�\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-120, m_position.y-80,128,588,162,620);		//:�̕\��

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280, m_position.y-10,0,272,280,274);			//�d�؂�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-10,520,272,800,274);			//�d�؂�̕\��

	switch(m_charaID){			  //�L������ID�I��
		
		case 0:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y-220,0,300,255,332);		//�A���h�t�@�E�g�̕\��
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,0,0,320,520);		//�A���h�t�@�E�g
			break;
		case 1:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y+-220,0,332,255,364);	//�l���̕\��
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,320,0,640,520);		//�l�����}��
			break;
		case 2:
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-205, m_position.y+-220,0,364,256,396);	//�~�l���c�@�̕\��
			m_vertex.DrawTextureLT(m_pDevice, m_texChara, m_position.x-30, m_position.y-250,640,0,960,520);		//�~�l���c�@
			break;
		default:
			break;
	}


	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+15,0,524,128,556);			//�U���̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+65,126,524,254,556);		//�h��̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+115,0,556,128,588);			//���x�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-235, m_position.y+165,128,556,256,588);		//�u���̕\��

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+15,128,588,162,620);		//:�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+65,128,588,162,620);		//:�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+115,128,588,162,620);		//:�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-180, m_position.y+165,128,588,162,620);		//:�̕\��

	m_hp=m_pGameData->m_chara[m_charaID].hp;				//�L������HP	
	m_mp=m_pGameData->m_chara[m_charaID].mp;				//�L������MP	
	m_atk=m_pGameData->m_chara[m_charaID].atk;				//�L�����̍U���@
	m_def=m_pGameData->m_chara[m_charaID].def;				//�L�����̖h��  
	m_spd=m_pGameData->m_chara[m_charaID].spd;				//�L�����̑��x	
	m_ins=m_pGameData->m_chara[m_charaID].ins;				//�L�����̏u��  
	//�L�����̃X�e�[�^�X�̕\��
	for(int i = 0;i < 2; i++){
		switch( m_pGameData->m_chara[m_charaID].equip[i].stType ){
		case 0:
			m_hp -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 1:
			m_mp -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 2:
			m_atk -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 3:
			m_def -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 4:
			m_spd -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		case 5:
			m_ins -= m_pGameData->m_chara[m_charaID].equip[i].power;
			break;
		};
	};

	/*���[�J���ϐ��錾*/
	int l_hpdiv[3];												//HP�𕪊�
	int l_mpdiv[3];												//MP�𕪊�
	int l_atkdiv[2];											//�U���𕪊�
	int l_defdiv[2];											//�h��𕪊�
	int l_spddiv[2];											//���x�𕪊�
	int l_insdiv[2];											//�u���𕪊�
	
	for(int i=2;i>=0;i--){										//HP,MP�̃X�e�[�^�X��1�����i�[
		l_hpdiv[i]=m_hp%10;
		l_mpdiv[i]=m_mp%10;
		m_hp/=10;
		m_mp/=10;
	}
	for(int i=1;i>=0;i--){										//�U��,�h��,���x,�u���̃X�e�[�^�X��1�����i�[
		l_atkdiv[i]=m_atk%10;
		l_defdiv[i]=m_def%10;
		l_spddiv[i]=m_spd%10;
		l_insdiv[i]=m_ins%10;
		m_atk /= 10;
		m_def /= 10;
		m_spd /= 10;
		m_ins /= 10;
	}
	
	for( int i = 0; i < 3; i++ ) {                      //HP,MP�����̕\��������
		int alpha = CStringList::numberStrList[i] ? 255 : 128;
		CStringList::numberStrList[l_hpdiv[i]]->Draw(m_position.x - 80 + 20 * i, m_position.y - 126, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_mpdiv[i]]->Draw(m_position.x-80+20 * i, m_position.y-67,		D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
	}
	for( int i = 0; i < 2; i++ ) {                      //�U��,�h��,���x,�u�������̕\��������
		int alpha = CStringList::numberStrList[i] ? 255 : 128;
		CStringList::numberStrList[l_atkdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+30, D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_defdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+80, D3DCOLOR_ARGB(alpha,255,255,255),  CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_spddiv[i]]->Draw(m_position.x-150+20*i, m_position.y+130, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
		CStringList::numberStrList[l_insdiv[i]]->Draw(m_position.x-150+20*i, m_position.y+180, D3DCOLOR_ARGB(alpha,255,255,255), CStringList::numberStrList[i]->getLength());
	}
	// �ω��\�͒l�i�[�p�ϐ�
	std::vector<int> variation;
	std::vector<int>::iterator it;
	int type;
	int power;
	// �ω�����p�����[�^�[�ɂ����for�����񂷉񐔂�ς���
	if(m_pGameData->m_chara[m_charaID].equip[0].stType ==  m_pGameData->m_chara[m_charaID].equip[1].stType) type = 1;
	else type = 2;

	for(int i = 0; i < type;i++){
		// type��1�̏ꍇ������2�̕ω��l�𑫂��Ă���
		type == 1 ? power = m_pGameData->m_chara[m_charaID].equip[0].power + m_pGameData->m_chara[m_charaID].equip[1].power : power = m_pGameData->m_chara[m_charaID].equip[i].power;
		// �\�͕ω��̒l�𕪉�
		for(int j = 2; j >= 0;j--){
			if( power == 0 ) break;
			it = variation.begin();
			variation.insert(it,power % 10);
			power = power / 10;
		}
		// �`�悷��ʒu
		int drawPos = m_pGameData->m_chara[m_charaID].equip[i].stType;
		// �`��ʒu(HP�EMP�̏ꍇ)
		if(drawPos < 2){
			for(unsigned i = 0; i < variation.size() ;i++){
				CStringList::numberStrList[ variation[i] ]->Draw( m_position.x -10+(20 * i)  , m_position.y - 126 + ( drawPos * 59 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ variation[i] ]->getLength());
			}
			// +�̕`��
			CStringList::numberStrList[ 12 ]->Draw( m_position.x - 40  , m_position.y - 126 + ( drawPos * 59 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 12 ]->getLength());
			// vector�z����N���A
			variation.clear();
		}else{
			for(unsigned i = 0; i < variation.size() ;i++){
				CStringList::numberStrList[ variation[i] ]->Draw( m_position.x-60 + 20 * i  , m_position.y - 70 + ( drawPos * 50 ), D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ variation[i] ]->getLength());
			}
			// +�̕`��
			CStringList::numberStrList[ 12 ]->Draw( m_position.x-90  , m_position.y - 70 + ( drawPos * 50 ), D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 12 ]->getLength());
			// vector�z����N���A
			variation.clear();

		}
	}
		//if( i < 2 ) m_strLst[ 10 ]->Draw( m_position.x-10  , m_position.y - 126 + ( i * 59 ), D3DCOLOR_ARGB(alpha,255,255,255), m_strLst[ 10 ]->getLength());
}		
void CGameStatusWindow::SetSelectEquipID(int _selectEquipID)// �I������Ă��鑕����ID���Z�b�g
{
	m_selectEquipID =_selectEquipID;
};											
void CGameStatusWindow::SetCharaID(int _charaID)
{
	m_charaID = _charaID;								// �I������Ă���L������ID���Z�b�g
};