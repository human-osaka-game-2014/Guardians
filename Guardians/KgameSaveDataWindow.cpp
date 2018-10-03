#include "stdafx.h"


/*--------------------------------------------------------------

	�������e:�Z�[�u�f�[�^�̕\��
	�쐬��:��
	�쐬��:10/16
	�X�V��:11/08
	�X�V���e
	�R�[�h�̊ȗ���
	mapchip�A�C�R���̒ǉ�
--------------------------------------------------------------*/

CGameSaveDataWindow::CGameSaveDataWindow(LPDIRECT3DDEVICE9 _pDevice,D3DXVECTOR2 _position,int m_state):
CGameWindow(_pDevice,_position,static_cast<float>(MAX_WIDTH), static_cast<float>(MAX_HEIGHT))
{
	for(int i=0;i<10;i++){   //�f�[�^�P�O�����[�h
		Load(i);
	}
	m_textureChip= CTexMgr.Get(TEX_MAP_CHIP );
	m_head=0;  //�`�揉����
	m_tail=2;  //�`�揉����
	m_drawID=0;  //�`�揉����
}
CGameSaveDataWindow::~CGameSaveDataWindow()
{

}
/*--------------------------------------------------------------

	SAVEDATA.txt�̃��[�h
	@param int  ID    SAVEDATA.txt�̔ԍ�
	@return �Ȃ�

--------------------------------------------------------------*/

void CGameSaveDataWindow::Load(int _ID)
{							
	int itemcount=0;					//�A�C�e����
	int onlyitemcount[MAX_ITEM];		//�e�X�̃A�C�e��������
	int emblemcount=0;					//�̍���
	int onlyemblemcount[MAX_EMBLEM];	//�e�X�̏̍��l��
	
	std::stringstream ss;
	ss << "SaveData\\SAVE";
	ss << _ID;
	ss << ".txt"; 
	std::ifstream ifs(ss.str());

	if(ifs.fail()) {	//�f�[�^�ǂݍ��ݎ��s
		m_Data[_ID].data=FALSE;	//�f�[�^�̗L��
	}
	else{	//�f�[�^�ǂݍ��ݐ���
		std::string str;	//������^
		int count=0;
		//�t�@�C�����̃f�[�^�̏I���܂Ń��[�v
		while( std::getline(ifs,str) ){
			switch(count){
				case 0: // �Z�[�u���t
					sscanf_s(str.c_str(),"�Z�[�u����:%d/%d/%d %d:%d", &m_Data[_ID].year,&m_Data[_ID].month,&m_Data[_ID].date,&m_Data[_ID].realhour,&m_Data[_ID].realminutes);
					break;
				case 1: // �v���C�^�C��
					sscanf_s(str.c_str(),"�v���C����:%d:%d:%d", &m_Data[_ID].hour, &m_Data[_ID].minute, &m_Data[_ID].second);
					break;
				case 2: // ������
					sscanf_s(str.c_str(),"������:%d", &m_Data[_ID].money);
					break;

				case 3: // �擾����
					sscanf_s(str.c_str(),"�擾����:%d", &m_Data[_ID].equipper);
					break;
				case 4: //�X�e�[�W�N���A��
					sscanf_s(str.c_str(),"�X�e�[�W�N���A��:%d",&m_Data[_ID].stageclear);
					break;
				case 47:
					sscanf_s(str.c_str(),"�擾�A�C�e��:%d",&m_Data[_ID].itemper);
					break;
				case 48:
					sscanf_s(str.c_str(),"�擾�̍�:%d",&m_Data[_ID].achieve);
					break;
			}
			count++;
		}
	


		m_Data[_ID].data = TRUE;
	}
}
void CGameSaveDataWindow::Control() //����
{
	CGameWindow::Control();
}	

	


void CGameSaveDataWindow::Draw()    //�`��
{
	CGameWindow::Draw();
	//�J�[�\���̓����ɍ��킹�ĕ`��
	if(m_cursolpoint>m_tail){
		if(m_cursolpoint-m_tail>6){
		m_head=7;
		m_tail=9;
		m_drawID=7;
		}
		else{
		m_head++;
		m_tail++;
		m_drawID++;
		}
	}
	if(m_cursolpoint<m_head){
		if(m_head-m_cursolpoint>6){
		m_head=0;
		m_tail=2;
		m_drawID=0;
		}
		else{
		m_head--;
		m_tail--;
		m_drawID--;
		}
	}
	if(m_drawID<0){m_drawID=0;}
	if(m_drawID>7){m_drawID=7;}
	//�J�[�\�����ړ������Ƃ���DATA�\��������	
	/*�Z�[�u,���[�h,����,�R���t�B�O�̕\��(�ς��Ȃ��Ƃ���̕\��)*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-400, m_position.y-210,0,716,256,748);	//�Z�[�u
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-250, m_position.y-210,0,748,256,780);	//���[�h
    m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-90, m_position.y-210,0,780,256,812);	//����
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+50, m_position.y-210,0,812,256,844);	//�R���t�B�O
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+250, m_position.y-210,0,844,256,876);	//�Q�[���I��
	for(int i=0;i<4;i++){
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-525+20*i, m_position.y-150+130*i,0,272,400,274);		//�d�؂�̕\��
		m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-125+20*i, m_position.y-150+130*i,400,272,800,274);	//�d�؂�̕\��
	}
	for(int i=m_drawID;i<m_drawID+3;i++){
		CStringList::saveStrList[6+i]->Draw(m_position.x-525+20*(i-m_drawID), m_position.y-130+130*(i-m_drawID),  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[6]->getLength());	//DATA�̕\��
	}
	//�Z�[�u�f�[�^�̕\��
	int l_timeSeconds[3];		//�v���C����(�b)
	int l_timeMinutes[3];       //�v���C����(��)
	int l_timeHours[3];			//�v���C����(����)
	int l_money[3];				//������
	int l_timediv[3][6];		//TIME�𕪊�
	int l_moneydiv[3][6];		//MONEY�𕪊�
	int l_equipnum[3];			//������
	int l_equipdiv[3][2];		//�������𕪊�
	int l_itemnum[3];			//�A�C�e����
	int l_itemdiv[3][2];		//�A�C�e�����𕪊�
	int l_achievenum[3];		//���ѐ�
	int l_achievediv[3][2];		//���ѐ��𕪊�
	int l_yearnum[3];			//�N��
	int l_yeardiv[3][4];		//�N���𕪊�
	int l_monthnum[3];			//����
	int l_monthdiv[3][2];		//���𕪊�  
	int l_daynum[3];			//����
	int l_daydiv[3][2];			//���𕪊�
	int l_realtimeMinutes[3];	//���A���^�C��(��)
	int l_realtimeHours[3];		//���A���^�C��(����)
	int l_realtimediv[3][4];	//���A���^�C���𕪊�
	for(int i=0;i<3;i++){
		if (m_Data[m_drawID+i].data==FALSE){	//�f�[�^�����̕\��
			CStringList::saveStrList[5]->Draw(m_position.x-325+20*i, m_position.y-85+130*i,  D3DCOLOR_ARGB(255,255,255,255),CStringList::saveStrList[5]->getLength());
			continue;
		}
		// �ΐ��̕`��
		for(int j = 0; j < 2; j++){
			CStringList::middleNumberStrList[13]->Draw(m_position.x-250+20*i + (50 * j),  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[13]->getLength());
		}
		//:�̕\��
		for(int j = 0; j < 3; j++){
			CStringList::middleNumberStrList[10]->Draw( m_position.x-267+20*i + (43 * j), m_position.y-125+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	
		}
		CStringList::middleNumberStrList[10]->Draw(m_position.x-23+20*i, m_position.y-125+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:�̕\��
		CStringList::middleNumberStrList[10]->Draw(m_position.x-10+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:�̕\��			
		CStringList::middleNumberStrList[10]->Draw(m_position.x-245+20*i , m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:�̕\��
		CStringList::middleNumberStrList[10]->Draw(m_position.x+173+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:�̕\��
		CStringList::middleNumberStrList[10]->Draw(m_position.x-151+20*i, m_position.y-85+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[10]->getLength());	//:�̕\�� 

		CStringList::saveStrList[0]->Draw(m_position.x-400+20*i, m_position.y-130+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[0]->getLength());	//�v���C����
		CStringList::saveStrList[1]->Draw(m_position.x-100+20*i,m_position.y-130+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[1]->getLength());	//������
		CStringList::saveStrList[2]->Draw(m_position.x-350+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::saveStrList[2]->getLength());	//�擾����
		CStringList::saveStrList[3]->Draw(m_position.x-170+20*i, m_position.y-40+130*i,    D3DCOLOR_ARGB(255,255,255,255),CStringList::saveStrList[3]->getLength());	//�擾�A�C�e��
		CStringList::saveStrList[4]->Draw(m_position.x+70+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255),  CStringList::saveStrList[4]->getLength());	//���щ���
		//�X�e�[�W�N���A�̃A�C�R���\��
		m_vertex.SetSizeY(0.6f);
		m_vertex.SetSizeX(0.6f);
		if(m_Data[m_drawID+i].stageclear>7)m_Data[m_drawID+i].stageclear=7;
		if(m_Data[m_drawID+i].stageclear<=4)m_vertex.DrawTextureLT(m_pDevice, m_textureChip, m_position.x-535+20*static_cast<float>(i), m_position.y-125+130*static_cast<float>(i),0+160*static_cast<float>(m_Data[m_drawID+i].stageclear-1),360,160+160*static_cast<float>(m_Data[m_drawID+i].stageclear-1),540);	
		else if(m_Data[m_drawID+i].stageclear>4)m_vertex.DrawTextureLT(m_pDevice, m_textureChip, m_position.x-535+20*i, m_position.y-123+130*i,0+160*static_cast<float>(m_Data[m_drawID+i].stageclear-5),540,160+160*static_cast<float>(m_Data[m_drawID+i].stageclear-5),720);
		m_vertex.SetSizeY(1.0f);
		m_vertex.SetSizeX(1.0f);
		//���ԂƏ������̕\������
		l_timeSeconds[i]=m_Data[m_drawID+i].second;	//�b�̕���				
		l_timeMinutes[i]=m_Data[m_drawID+i].minute;	//���̕���
		l_timeHours[i]=m_Data[m_drawID+i].hour;		//���Ԃ̕���
		l_money[i]=m_Data[m_drawID+i].money;			//MONEY�̎擾	
		for(int j=5;j>=4;j--){	
		l_timediv[i][j]=l_timeSeconds[i]%10;	//TIME(�b)�̃X�e�[�^�X��1�����i�[	
		l_timeSeconds[i]/=10;
		l_timediv[i][j-2]=l_timeMinutes[i]%10;  //TIME(��)�̃X�e�[�^�X��1�����i�[	
		l_timeMinutes[i]/=10;
		l_timediv[i][j-4]=l_timeHours[i]%10;	//TIME(����)�̃X�e�[�^�X��1�����i�[
		l_timeHours[i]/=10;
		}
		for(int j=5;j>=0;j--){	//MONEY�̃X�e�[�^�X��1�����i�[
			l_moneydiv[i][j]=l_money[i]%10;
			l_money[i]/=10;
		}
		for( int j = 0; j < 2; j++ ) {  //TIME�̕\��				   
			CStringList::middleNumberStrList[l_timediv[i][j]]->Draw(m_position.x-250+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255),    CStringList::middleNumberStrList[i]->getLength());
			CStringList::middleNumberStrList[l_timediv[i][j+2]]->Draw( m_position.x-208+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		    CStringList::middleNumberStrList[l_timediv[i][j+4]]->Draw( m_position.x-166+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		for( int j = 0; j < 6; j++ ) {	//MONEY�̕\��					
			CStringList::middleNumberStrList[l_moneydiv[i][j]]->Draw( m_position.x-10+16*j+20*i,  m_position.y-130+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}	
		//�擾�����̕\��
		l_equipnum[i]=m_Data[m_drawID+i].equipper;	//�����̎擾
		if(l_equipnum[i]==100){	//100���̎���100����\��
			CStringList::middleNumberStrList[1]->Draw(m_position.x-236+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x-220+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x-204+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[ 14 ]->Draw(m_position.x-188+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());
		}
		else{
			for(int j=1;j>=0;j--){	//��������1�����i�[
				l_equipdiv[i][j]=l_equipnum[i]%10;	
				l_equipnum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//�������̕\��		
				CStringList::middleNumberStrList[l_equipdiv[i][j]]->Draw(m_position.x-235+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x-200+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%�̕\��
		}
		//�擾�A�C�e���̕\��
		l_itemnum[i]=m_Data[m_drawID+i].itemper;	//�A�C�e�����̎擾
		if(l_itemnum[i]==100){		//100���̎���100����\��
			CStringList::middleNumberStrList[1]->Draw(m_position.x+1+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),   CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+17+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+33+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[14]->Draw(m_position.x+49+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());
		 }
		 else{
			for(int j=1;j>=0;j--){	//�A�C�e������1�����i�[
				l_itemdiv[i][j]=l_itemnum[i]%10;	
				l_itemnum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//�A�C�e�����̕\��		
				CStringList::middleNumberStrList[l_itemdiv[i][j]]->Draw(m_position.x+2+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x+38+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%�̕\��
		 }
		//���щ����̕\��
		l_achievenum[i]=m_Data[m_drawID+i].achieve;	//���ѐ��̎擾
		if(l_achievenum[i]==100){	 //100���̎���100����\��
			CStringList::middleNumberStrList[1]->Draw(m_position.x+182+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[1]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+198+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[0]->Draw(m_position.x+216+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255),  CStringList::middleNumberStrList[0]->getLength());
			CStringList::middleNumberStrList[12]->Draw(m_position.x+232+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[12]->getLength());
		}
		else{
			for(int j=1;j>=0;j--){	//���ѐ���1�����i�[
				l_achievediv[i][j]=l_achievenum[i]%10;	
				l_achievenum[i]/=10;
			}
			for(int j = 0; j < 2; j++ ) {	//���ѐ��̕\��		
				CStringList::middleNumberStrList[l_achievediv[i][j]]->Draw(m_position.x+183+16*j+20*i,  m_position.y-40+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
			}
			CStringList::middleNumberStrList[14]->Draw(m_position.x+219+20*i, m_position.y-40+130*i,  D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[14]->getLength());	//%�̕\��
		}
		//�N�����̕\�� 
		l_yearnum[i]=m_Data[m_drawID+i].year;	//�N���̎擾
									//�N���𕪊�
		for(int j=3;j>=0;j--){						//�N����1�����i�[
			l_yeardiv[i][j]=l_yearnum[i]%10;	
			l_yearnum[i]/=10;
		}
		for(int j = 0; j < 4; j++ ) {	//�N���̕\��
			CStringList::middleNumberStrList[l_yeardiv[i][j]]->Draw(m_position.x-370+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_monthnum[i]=m_Data[m_drawID+i].month;  //���̎擾
		for(int j=1;j>=0;j--){	//������1�����i�[
		l_monthdiv[i][j]=l_monthnum[i]%10;	
		l_monthnum[i]/=10;
		}
		if(l_monthdiv[i][0]==0)l_monthdiv[i][0]=0;
		for(int j = 0; j < 2; j++ ) {	//�����̕\��		
		CStringList::middleNumberStrList[l_monthdiv[i][j]]->Draw(m_position.x-285+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_daynum[i]=m_Data[m_drawID+i].date; //���̎擾
		for(int j=1;j>=0;j--){	//������1�����i�[
		l_daydiv[i][j]=l_daynum[i]%10;	
		l_daynum[i]/=10;
		}
		if(l_daydiv[i][0]==0)l_daydiv[i][0]=29;
		for(int j = 0; j < 2; j++ ) {	//�����̕\��		
			CStringList::middleNumberStrList[l_daydiv[i][j]]->Draw(m_position.x-235+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}
		l_realtimeMinutes[i]=m_Data[m_drawID+i].realminutes;	//���݂̂̌v�Z
		l_realtimeHours[i]=m_Data[m_drawID+i].realhour;		//���Ԃ݂̂̌v�Z
		for(int j=3;j>=2;j--){	//����1�����i�[
			l_realtimediv[i][j]=l_realtimeMinutes[i]%10;	
			l_realtimeMinutes[i]/=10;
		}
		for(int j=1;j>=0;j--){	//���Ԃ�1�����i�[
			l_realtimediv[i][j]=l_realtimeHours[i]%10;	
			l_realtimeHours[i]/=10;
		}
		for(int j = 0; j < 2; j++ ) {	//���Ԃƕ��̕\��				   
			CStringList::middleNumberStrList[l_realtimediv[i][j]]->Draw(m_position.x-180+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		    CStringList::middleNumberStrList[l_realtimediv[i][j+2]]->Draw( m_position.x-138+16*j+20*i,  m_position.y-85+130*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::middleNumberStrList[i]->getLength());
		}  
	}
	//�X�N���[���o�[�̕\��
	int l_schrolladjust=m_cursolpoint;		//�X�N���[���o�[�̒��̒��������̂��߂Ɏ擾
	int l_scrollHeight=270*7/10;			//�X�N���[���o�[�̒��̍���
	float l_scrollmoving=27;				//�X�N���[���o�[�̒��̈ړ���	
	int   l_marginHeight;					//�X�N���[���o�[���̍����̒����p
	int   l_firstBurring;					//�X�N���[���o�[�̒����ŏ��ɖ��߂�ϐ�
	if(l_schrolladjust>5){l_schrolladjust=l_schrolladjust-5;}
	else{l_schrolladjust=0;}
	for(int i=0;i<l_scrollHeight/16;i++){	//�X�N���[���o�[�̒��̃o�[�\��
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+516, m_position.y-150+16*i+(l_schrolladjust*l_scrollmoving),272,218,286,234);
		l_marginHeight=l_scrollHeight-16*i;
		l_firstBurring=16*i;
	}
	for(int i=0;i<l_marginHeight;i++){		 //�c��̃X�N���[���o�[�̒���1px�Ŗ��߂�
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+516, m_position.y-150+l_firstBurring+(1*i)+l_scrollmoving*l_schrolladjust,272,218,286,219);
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+495, m_position.y-200,272,48,322,128);		//�X�N���[���o�[�̕\��(��)�@�@�@
	for(int i=0;i<27;i++){	//�X�N���[���o�[�̕\��(��)
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+495, m_position.y-150+10*i,272,128,322,138);	
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+495, m_position.y+120,272,138,322,218);	//�X�N���[���o�[�̕\��(��)
}
void CGameSaveDataWindow::SetCursorID(int _cursorID)
{
	m_cursolpoint = _cursorID;
};
