#include "stdafx.h"
/*--------------------------------------------------------------

	�������e:�R���X�g���N�^�̐錾,�A�N�Z�T���[�A�����܂������̉��i����̕`��
	�쐬��:��
	�쐬��:10/15
	�X�V��:10/22
	�֐�
		�X�N���[���o�[�̏C���@
		draw�̍쐬
	�ϐ��@
		�ǉ��Ȃ�

--------------------------------------------------------------*/

CGameShopListWindow::CGameShopListWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, SelectType _type):
	CGameWindow(_pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT)),m_drawID(0)// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A�I�����ꂽ�^�C�v���Z�b�g
{
	m_pGameData=_pGameData;
	m_type=_type;
}
CGameShopListWindow::~CGameShopListWindow()
{

}
void CGameShopListWindow::Control()
{
	CGameWindow::Control();
}													
	
void CGameShopListWindow::Draw()
{
	CGameWindow::Draw();
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-370, m_position.y-240,0,272,370,274);						//�d�؂�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-240,430,272,800,274);						//�d�؂�̕\��
    CStringList::numberStrList[ 16 ]->Draw(m_position.x+20, m_position.y-260, D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ 16 ]->getLength());	//���z�\��
	CStringList::numberStrList[17]->Draw(m_position.x+155, m_position.y-260, D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[17]->getLength());  //�������\��
	////�A�C�e�����X�g��\��
	if(m_type == 0){     
		float size =  24.5f - (m_pGameData->m_itemList.size() - 9.f);	// �o�[�̒��g�̃T�C�Y�����߂�(max - itemsize - ��x�ɕ\�����鍀��)
		float move = ((m_pGameData->m_itemList.size() - 9.f) * 16.f)  / (m_pGameData->m_itemList.size() - 9.f) ;	// �ړ��ʂ����߂�
		m_vertex.SetSizeY( size );
		if( 9 < m_pGameData->m_itemList.size() )	// �\�����ڂ�胊�X�g�̃A�C�e������������Ε`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+310, m_position.y-180 + (m_drawID * move),272,218,286,234); 
		m_vertex.SetSizeY(1.0f);
		// �A�C�e���̕`��ʒu��ݒ肷��
		if( CScene::m_keyStatePush == UP ){
			if( m_cursorPos > m_pGameData->m_itemList.size() -1 - 8 ) {
				if( m_drawID + 8 < m_cursorPos )
					m_drawID = m_pGameData->m_itemList.size() -1 - 8;
			}else{
				if( m_drawID > m_cursorPos )	m_drawID = m_cursorPos;
			}
		}else if( CScene::m_keyStatePush == DOWN){
			if( m_cursorPos < 9 ) {
				if( m_drawID + 8 < m_cursorPos || m_cursorPos == 0) m_drawID = 0;
			}else{
				if( m_drawID+9 <= m_cursorPos )	m_drawID = m_cursorPos - 8;
			}
		}
		//����̕`��
		for(int i=0;i<MAX_ITEM_NUMBER;i++){										//����\��
			CStringList::itemStrList[ i + m_drawID ]->Draw(m_position.x-290, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::itemStrList[ i + m_drawID ]->getLength()); 
			// �������̕\��
			CStringList::numberStrList[ Sarch(0,i+m_drawID) ]->Draw(m_position.x+200, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ Sarch(0,i+m_drawID) ]->getLength());  						
			// �l�i�̕\��
			CStringList::itemPrice[ i + m_drawID ]->Draw(m_position.x, m_position.y-190+54*i,D3DCOLOR_ARGB(255,255,255,255), CStringList::itemPrice[ i + m_drawID ]->getLength()); 
		}

	}
//�������X�g��\��
	 else {      
		 float size =  24.5f - (m_pGameData->m_equipList.size() - 9.f);	// �o�[�̒��g�̃T�C�Y�����߂�(max - itemsize - ��x�ɕ\�����鍀��)
		float move = ((m_pGameData->m_equipList.size() - 9.f) * 16.f)  / (m_pGameData->m_equipList.size() - 9.f) ;	// �ړ��ʂ����߂�
	
		m_vertex.SetSizeY( size );
		if( 9 < m_pGameData->m_equipList.size() )	// �\�����ڂ�胊�X�g�̃A�C�e������������Ε`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+310, m_position.y-180 + (m_drawID * move),272,218,286,234); 
		m_vertex.SetSizeY(1.0f);

		if( CScene::m_keyStatePush == UP ){
			if( m_cursorPos > m_pGameData->m_equipList.size() -1 - 8 ) {
				if( m_drawID + 8 < m_cursorPos )
					m_drawID = m_pGameData->m_equipList.size() -1 - 8;
			}else{
				if( m_drawID > m_cursorPos ){
					m_drawID = m_cursorPos;
				}
			}
		}else if( CScene::m_keyStatePush == DOWN){
			if( m_cursorPos < 9 ) {
				if( m_drawID + 8 < m_cursorPos || m_cursorPos == 0)
					m_drawID = 0;
			}else{
				if( m_drawID+9 <= m_cursorPos ){
					 m_drawID = m_cursorPos - 8;
				}
			}
		}
		for(int i=0;i<MAX_ITEM_NUMBER;i++){										//�������\��
			CStringList::equipStrList[ i+m_drawID ]->Draw(m_position.x-290, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255), CStringList::equipStrList[ i+m_drawID ]->getLength());  
			//�����̎����Ă��鐔�\��
			CStringList::numberStrList[ Sarch(1,i+m_drawID) ]->Draw(m_position.x+200, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::numberStrList[ Sarch(1,i+m_drawID) ]->getLength());  						
			//�����̉��i�\��
			CStringList::equipPrice[ i+m_drawID ]->Draw(m_position.x, m_position.y-190+54*i, D3DCOLOR_ARGB(255,255,255,255),CStringList::equipPrice[ i+m_drawID ]->getLength()); 
		}
	}
	float size =  (m_position.y + 189.5f) - (m_position.y - 230.5f);
	m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+290.f,m_position.y-232.5f,272,48,322,128);					//�X�N���[���o�[�̕\��(��)�@�@�@
	for(int i=0;i<40;i++){
		m_vertex.DrawTextureLT(m_pDevice, m_texture,m_position.x+290.f,m_position.y-152.5f + ( 10*i ),272,128,322,138);		//�X�N���[���o�[�̕\��
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+290.f,m_position.y+189.f,272,138,322,218);					//�X�N���[���o�[�̕\��(��)
}						
void CGameShopListWindow::SetCursorPosition(int _pos)// �I������Ă��鑕����ID���Z�b�g
{
	m_cursorPos =_pos;
}										
void CGameShopListWindow::SetSelectID(int _select)
{
	m_type = _select;								// �I������Ă���L������ID���Z�b�g
}
/* --------------------------------------------------
	�`�悵�����A�C�e�����������Ă��邩���ׂ�

---------------------------------------------------*/
int CGameShopListWindow::Sarch(int _oldID,int _No)
{
	if( _oldID == 0 ){
		for(unsigned int i = 0; i < m_pGameData->m_hasTools.size() ;i++){
			if(m_pGameData->m_hasTools[i].no == m_pGameData->m_itemList[_No].no){
				return m_pGameData->m_hasTools[i].nums;
			}
		}
	}else{
		for(unsigned int i = 0; i < m_pGameData->m_hasEquip.size() ;i++){
			if(m_pGameData->m_hasEquip[i].no == m_pGameData->m_equipList[ _No ].no){
				return m_pGameData->m_hasEquip[i].nums;
			}
		}
	}
	return 0;
}