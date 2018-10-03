/*--------------------------------------------------------------

	�������e: �I����(�͂��A������)�p�E�C���h�E�̕`��
	�쐬��: �h��
	�쐬��:10/19
	�֐��@
		�R���X�g���N�^
		�f�X�g���N�^
		Draw
		�ǉ�
	�ϐ��@
		

--------------------------------------------------------------*/
#include "stdafx.h"

const float CGameSelectWindow::MAX_WIDTH	= 384.f+160.f;
const float CGameSelectWindow::MAX_HEIGHT	= 320;
/*--------------------------------------------------------------

	�R���X�g���N�^
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`��ʒu
	@param int					�`�悷�郁�b�Z�[�W��ID

--------------------------------------------------------------*/
CGameSelectWindow::CGameSelectWindow(LPDIRECT3DDEVICE9 _pDevice,D3DXVECTOR2 _position,int _id) : CGameWindow(_pDevice,_position,MAX_WIDTH,MAX_HEIGHT) , m_id(_id)
{

}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CGameSelectWindow::~CGameSelectWindow()
{

}
/*--------------------------------------------------------------

	����
	@param		�Ȃ�
	@return		�Ȃ�

--------------------------------------------------------------*/
void CGameSelectWindow::Control()
{
	CGameWindow::Control();
}
/*--------------------------------------------------------------

	�`��
	@param		�Ȃ�
	@return		�Ȃ�

--------------------------------------------------------------*/
void CGameSelectWindow::Draw()
{
	CGameWindow::Draw();

	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-(MAX_WIDTH/2), m_position.y-(MAX_HEIGHT/2)+90,0,272,MAX_WIDTH/2,274);			//�d�؂�̕`��
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x, m_position.y-(MAX_HEIGHT/2)+90,800 - MAX_WIDTH/2,272,800,274);				//�d�؂�̕`��	
	
	// ���b�Z�[�W�̕`��
	CStringList::MessageStrList[m_id]->Draw( m_position.x-(MAX_WIDTH/2)+160, m_position.y-(MAX_HEIGHT/2)+55, D3DCOLOR_ARGB(255,255,255,255), CStringList::MessageStrList[m_id]->getLength());
	
	// �͂��A�������̕`��
	for(int i = 2; i < 4;i++){
		CStringList::MessageStrList[i]->Draw( m_position.x-(MAX_WIDTH/2)+260 + ((i-2) * -12), m_position.y-(MAX_HEIGHT/2)+80 * i-2, D3DCOLOR_ARGB(255,255,255,255), CStringList::MessageStrList[i]->getLength());
	}
}