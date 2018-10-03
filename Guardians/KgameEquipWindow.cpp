#include "stdafx.h"
/* �萔 */



/*--------------------------------------------------------------

	�������e:�����⓹��,�d�؂�̕`��
	�쐬��:��
	�쐬��:10/05
	�X�V��:11/08
	�X�V���e
	�t�H���g�̈ʒu�̏C��
	�A�C�R���̒ǉ�
	�֐��@
		draw�̍쐬
	�ϐ��@
		�ǉ��Ȃ�

--------------------------------------------------------------*/

/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A���j���[ID���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`�悷��ʒu(x,y)
	@param CGameData			�Q�[���f�[�^�̎Q��
	@param int�@menu			�g�p���郁�j���[ID

--------------------------------------------------------------*/
CGameEquipWindow::CGameEquipWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID) :
	CGameWindow(_pDevice, _position, _menuID == 1 ?static_cast<float>(MAX_WIDTH_CHARA) :static_cast<float>(MAX_WIDTH_STATUS), _menuID == 1 ? static_cast<float>(MAX_HEIGHT_CHARA) :static_cast<float>(MAX_HEIGHT_STATUS))
	,m_pGameData( _pGameData ),m_charaID(0)
{

	m_textureicon[0]=CTexMgr.Get(TEX_EQUIP_ICON );
	m_textureicon[1]=CTexMgr.Get(TEX_ITEM_ICON );

}
CGameEquipWindow::~CGameEquipWindow()
{

}



void CGameEquipWindow::Control()
{
	CGameWindow::Control();
}

void CGameEquipWindow::Draw()
{

	CGameWindow::Draw();
	
	CGameWindow::SetGameData(m_pGameData);
		
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-233, m_position.y-193,0,460,127,492);										//�����̕\��
	
	for (int i=1;i<=2;i++){
		CStringList::numberStrList[i]->Draw(m_position.x-135, m_position.y-182+70*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[i]->getLength());		//�����̕\��
		CStringList::numberStrList[10]->Draw(m_position.x-110, m_position.y-182+68*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[10]->getLength());	//:�̕\��
	}	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-280,	 m_position.y-55,0,272,280,274);										//�d�؂�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x,		 m_position.y-55,520,272,800,274);										//�d�؂�̕\��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-230,	 m_position.y-15,128,460,256,492);									//����̕\��
	for (int i=1;i<=4;i++){
		CStringList::numberStrList[i]->Draw(m_position.x-130, m_position.y+54*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[i]->getLength());			//�����̕\��
		CStringList::numberStrList[10]->Draw(m_position.x-105, m_position.y+54*(i-1),  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[10]->getLength());		//:�̕\��
	}
	/*�����̕\��*/
	// 1�Ԗڂ̑����̕\��
	// Sarch�֐��Ŕz��ԍ����擾
	for( int i = 0, no; i < 2; i++ ) {
		no =  Search(m_pGameData->m_chara[m_charaID].equip[i].no,TYPE_EQUIP);

		// �`����W�Ɋi�[
		float drawPosX = m_position.x-40, drawPosY = m_position.y-180 + i*66;

		// �����ɂЂ�������Ȃ�������u�Ȃ��v�����łȂ���΁u�������v��\��
		if( no == -1 ) {
			CStringList::m_none->Draw(drawPosX, drawPosY, CStringList::m_none->getLength());
		} else {
			CStringList::equipStrList[ no ]->Draw(drawPosX, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::equipStrList[ no ]->getLength());
			//�r�֌n�A�C�R���̕\��
			if(no<3)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
			//���[�v�n�̃A�C�R���̕\��
			else if(2<no&&no<6)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-3),0,200+40*static_cast<float>(no-3),40);
			//�C�n�A�C�R���̕\��
			else if(5<no&&no<9)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no-6),40,40+40*static_cast<float>(no-6),80);
			//�ьn�̃A�C�R���̕\��
			else if(8<no&&no<11)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-9),40,200+40*static_cast<float>(no-9),80);
			//���͊�n�A�C�R���̕\��
			else if(10<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,0+40*static_cast<float>(no-11),80,40+40*static_cast<float>(no-11),120);
			//����n�̃A�C�R���̕\��
			else if(13<no&&no<16)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[0], drawPosX-58,drawPosY-18,160+40*static_cast<float>(no-14),80,200+40*static_cast<float>(no-14),120);
		}
	}
	/*����̕\��*/
	for(int i = 0, no; i < 4; i++){
		no = Search(m_pGameData->m_tools[i].no,TYPE_ITEM);

		// �`����W�Ɋi�[
		float drawPosX = m_position.x-30, drawPosY = m_position.y+(55*i);
		// �����ɂЂ�������Ȃ�������u�Ȃ��v�����łȂ���΁u�A�C�e�����v��\��
		if( no == -1 ) {
			CStringList::m_none->Draw(drawPosX, drawPosY, CStringList::m_none->getLength());
		} else {
			CStringList::itemStrList[ no ]->Draw(drawPosX, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::itemStrList[ no ]->getLength());	
			//���n�A�C�R��
			if(no<7)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], drawPosX-60,drawPosY-18,0+40*static_cast<float>(no),0,40+40*static_cast<float>(no),40);
			//�아,���p���n�A�C�R��
			else if(6<no&&no<14)m_vertex.DrawTextureLT(m_pDevice, m_textureicon[1], drawPosX-60,drawPosY-18,0+40*static_cast<float>(no-7),40,40+40*static_cast<float>(no-7),80);
			// �u�~�v�Ɓu���v�̕\���̂��ߍ��W�ړ�
			drawPosX = m_position.x+157;

			CStringList::numberStrList[11]->Draw(drawPosX, drawPosY, CStringList::numberStrList[11]->getLength());
			CStringList::numberStrList[ m_pGameData->m_tools[i].nums ]->Draw(drawPosX+22, drawPosY,  D3DCOLOR_ARGB(255,255,255,255), CStringList::numberStrList[ m_pGameData->m_tools[i].nums ]->getLength());
		}
	}

}
void CGameEquipWindow::SetSelectEquipID(int _selectEquipID)// �I������Ă��鑕����ID���Z�b�g
{
	m_selectEquipID =_selectEquipID;
};											
void CGameEquipWindow::SetCharaID(int _charaID)
{
	m_charaID = _charaID;								// �I������Ă���L������ID���Z�b�g
};