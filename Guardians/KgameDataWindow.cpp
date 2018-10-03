#include "stdafx.h"
/*--------------------------------------------------------------

	�������e:TIME��MONEY�A�����̕\��
	�쐬��:��
	�X�V��:11/08
	�֐��@
		TIME�̌v�Z�̏C��
	�ϐ��@
		�ǉ��Ȃ�
		�����̏C��

--------------------------------------------------------------*/
const D3DXVECTOR2 CGameDataWindow::WINDOW_POSITION = D3DXVECTOR2(71.f, 768.f);	// �u�E�B���h�E�v�ړ�����W
const D3DXVECTOR2 CGameDataWindow::TIME_POSITION = D3DXVECTOR2(10.f, 660.f);	// �u�v���C���ԁv�`����W
const D3DXVECTOR2 CGameDataWindow::MONEY_POSITION = D3DXVECTOR2(10.f, 665.f);	// �u�������v�`����W


/*------------------------------------------
   
    �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^���Z�b�g, ���̑������o�ϐ��̏��������s��)�@
	@param	LPDIRECT3DDEVICE9	�f�o�C�X
	@param	D3DXVECTOR2			���S���W
	@param	float				�L����ő啝
	@param	float				�L����ő卂���@

------------------------------------------*/
CGameDataWindow::CGameDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData) : 
CGameWindow(_pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT), WINDOW_POSITION), m_pGameData( _pGameData )
{
	// ���̃E�B���h�E�ł͍L�����Ԃ̓J�b�g���Ĉړ���Ԃ���X�^�[�g
	m_state = STATE_MOVE;
	m_width = MAX_WIDTH - NOMOVE_PARTS_SIZE.x*2;
	m_height = MAX_HEIGHT;

}
CGameDataWindow::~CGameDataWindow()
{

}

/*------------------------------------------
   
    ����
	@param	�Ȃ�
	@return	�Ȃ��@

------------------------------------------*/
void CGameDataWindow::Control()
{
	CGameWindow::Control();
}

/*------------------------------------------
   
    �`��
	@param	�Ȃ�
	@return	�Ȃ��@

------------------------------------------*/
void CGameDataWindow::Draw()
{
	CGameWindow::Draw();

   
	int l_time=m_pGameData->m_playTime;		//TIME�̎擾	
	int l_timeSeconds=l_time%60;					//�b�݂̂̌v�Z
	int l_timeMinutes=l_time/60%100%60;				//���݂̂̌v�Z
	int l_timeHours=l_time/3600;					//���Ԃ݂̂̌v�Z
	int l_money = m_pGameData->m_money ;	
	int l_timediv[6];								//TIME�𕪊�
	int l_moneydiv[6];
	for(int i = 0; i < 6;i++){
		l_moneydiv[i] = -1;
	}//MONEY�𕪊�
	for(int i=5;i>=4;i--){							//TIME(�b)�̃X�e�[�^�X��1�����i�[
		l_timediv[i]=l_timeSeconds%10;	
		l_timeSeconds/=10;
	}
	for(int i=3;i>=2;i--){							//TIME(��)�̃X�e�[�^�X��1�����i�[
		l_timediv[i]=l_timeMinutes%10;	
		l_timeMinutes/=10;
	}
	for(int i=1;i>=0;i--){							//TIME(����)�̃X�e�[�^�X��1�����i�[
		l_timediv[i]=l_timeHours%10;	
		l_timeHours/=10;
	}
	m_digits = 6;
	int digits = 0;
	while( l_money != 0 ){
		//MONEY�̃X�e�[�^�X��1�����i�[
		l_moneydiv[digits] = l_money % 10;
		l_money /= 10;
		digits++;
	}

	/*TIME�̕\��*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x, TIME_POSITION.y,254,412,382,428);						//TIME�̕\��

	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x + 130, TIME_POSITION.y,340,412,352,428);				//�R�����̕\��	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x + 168, TIME_POSITION.y,340,412,352,428);				//�R�����̕\��
	for( int i = 0; i < 2; i++ ) {																										    //TIME(����)�̕\��������
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+100+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	for( int i = 2; i < 4; i++ ) {																											//TIME(��)�̕\��������
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+108+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	for( int i = 4; i < 6; i++ ) {																										    //TIME(�b)�̕\��������
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+116+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x-10, TIME_POSITION.y+20,600,272,800,274);										//�d�؂�̕\��
	/*MONEY�̕\��*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture,  MONEY_POSITION.x,MONEY_POSITION.y+25,384,412,512,428);										//MONEY�̕\��
	
	for( int i = 0; i < 6; i++ ) { 	//�������̕\��
		if( i == 5 && l_moneydiv[m_digits-1-5] == -1 ){	
			m_vertex.DrawTextureLT(m_pDevice, m_texture,  MONEY_POSITION.x,MONEY_POSITION.y+25,384,412,512,428);										//MONEY�̕\��
			CStringList::smallNumberStrList[0]->Draw( MONEY_POSITION.x+100+16*5,  MONEY_POSITION.y+32, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[0]->getLength());
		}
		if(	l_moneydiv[m_digits-1-i] == -1 ) continue;
		CStringList::smallNumberStrList[l_moneydiv[m_digits-1-i]]->Draw( MONEY_POSITION.x+100+16*i,  MONEY_POSITION.y+32, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
}
