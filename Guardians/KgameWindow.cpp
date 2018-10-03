#include "stdafx.h"
/* �萔 */
// �L����ۂɕϓ����Ȃ������̃T�C�Y(���P��(128�~128) 
const D3DXVECTOR2 CGameWindow::NOMOVE_PARTS_SIZE = D3DXVECTOR2(128.f, 128.f);

/*------------------------------------------
   
    �R���X�g���N�^(�f�o�C�X�A���W�A�ő啝�A�����A�ړ���̈ʒu���Z�b�g, ���̑������o�ϐ��̏��������s��)�@
	@param	LPDIRECT3DDEVICE9	�f�o�C�X
	@param	D3DXVECTOR2			���S���W
	@param	float				�L����ő啝
	@param	float				�L����ő卂���@

------------------------------------------*/
CGameWindow::CGameWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth, float _maxHeight, D3DXVECTOR2 _nextPosition) :
m_pDevice( _pDevice ), m_position( _position ), m_maxWidth( _maxWidth ), m_maxHeight( _maxHeight ), m_nextPosition( _nextPosition ),
m_state( STATE_SPREAD ), m_width( 0.f ), m_height( 0.f )
{
	// �L���镔����128�~2�������������Ȃ̂ōő啝�A�ő卂������128�~2�����������̂��ő啝�A�ő卂���Ƃ���
	m_maxHeight -= NOMOVE_PARTS_SIZE.y*2;
	m_maxWidth -= NOMOVE_PARTS_SIZE.x*2;

	// ���ɍL���镝�⍂�����v�Z�ɂ���ċ��߂�
	// �ő卂�����L���鎞�ԂŊ���
	m_spreadHeight = m_maxHeight / SPREAD_TIME;
	if( m_spreadHeight <= 0.f ) {	// �L���鍂����0�ȉ��ɂȂ�����0�ŌŒ肷��
		m_spreadHeight = 0.f;
	}

	// �ő啝���L���鎞�ԂŊ���
	m_spreadWidth = m_maxWidth / SPREAD_TIME;
	if( m_spreadWidth <= 0.f ) {	// �L���镝��0�ȉ��ɂȂ�����0�ŌŒ肷��
		m_spreadWidth = 0.f;
	}

	// �ړ���̍��W�����̒l����Ȃ���Έ��(1frame)�̈ړ��ʂ����肵�Ă���
	if( !(m_nextPosition.x < 0.f && m_nextPosition.y < 0.f) )
	{
		// �i�ޕ���(�㉺or���E)�Ɛi�ޗʂ�����
		if( m_nextPosition.x > m_position.x || m_nextPosition.x < m_position.x ) {
			m_direction = DIR_HORIZONTAL;
			m_move = (m_nextPosition.x-m_position.x)/MOVE_TIME;
		}
		else if( m_nextPosition.y > m_position.y || m_nextPosition.y < m_position.y ) {
			m_direction = DIR_VIRTICAL;
			m_move = (m_position.y-m_nextPosition.y)/MOVE_TIME;
		}
	}
	// �摜�ǂݍ���
	m_texture = CTexMgr.Get( TEX_WINDOW );

	// �X�e���V���o�b�t�@�̐ݒ�
	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
}

CGameWindow::~CGameWindow()
{

}

/*------------------------------------------
   
    ����
	@param	�Ȃ�
	@return	�Ȃ��@

------------------------------------------*/
void CGameWindow::Control()
{
	// ��Ԃŕ���
	switch( m_state ) {
	case STATE_SPREAD:	// �L�����Ă�����

		// ���݂̍����ƕ���1��̈ړ��ʂ�������
		if( m_height < m_maxHeight ) m_height += m_spreadHeight;
		if( m_width < m_maxWidth ) m_width += m_spreadWidth;

		// ���݂̍���or�����L����ő啝or�ő卂���𒴂������Ԃ𓮂��Ȃ���Ԃ�
		if( m_height >= m_maxHeight && m_width >= m_maxWidth ) {
			m_state = STATE_WAIT;
		}
		break;
	case STATE_MOVE:	// �ړ����

		// ���݂̈ʒu�Ɉړ��ʂ�������
		switch( m_direction ) {
		case DIR_HORIZONTAL:
			m_position.x += m_move;

			// ����0.1�����ɂȂ�����ړ��I���
			if( fabs(m_position.x-m_nextPosition.x) <= 0.1f ) m_state = STATE_WAIT;
			break;
		case DIR_VIRTICAL:
			m_position.y += m_move;

			// ����0.1�����ɂȂ�����ړ��I���
			if( fabs(m_position.y-m_nextPosition.y) <= 0.1f ) m_state = STATE_WAIT;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

/*------------------------------------------
   
    �`��
	@param	�Ȃ�
	@return	�Ȃ��@

------------------------------------------*/
void CGameWindow::Draw()
{
	// �摜�̕��A�������擾
	float texWidth =272; //m_texture.GetWidth();
	float texHeight =272;// m_texture.GetHeight();

//	m_pDevice->SetRenderState(D3DRS_STENCILREF, 1);
//	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);	// �X�e���V����o�b�t�@�L��

	// ����̋�
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2,0.f, 0.f, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y); 
	// �E��̋�
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2,texWidth-NOMOVE_PARTS_SIZE.x, 0.f, texWidth, NOMOVE_PARTS_SIZE.y); 
	// �����̋�
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y+m_height/2,0.f, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x, texHeight); 
	// �E���̋�
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y+m_height/2,texWidth-NOMOVE_PARTS_SIZE.x, texHeight-NOMOVE_PARTS_SIZE.y, texWidth, texHeight); 

	// �������̊Ԃ̕����`��
	for( int i = 0, w = (int)m_width; i < m_width; i++ ) {
		if( w / 16 > 0 ) {	// ���݂̕���16px���傫���ꍇ�͈�C��16px���`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2, NOMOVE_PARTS_SIZE.x, 0.f, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y+m_height/2, NOMOVE_PARTS_SIZE.x, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+16, texHeight);
			i += 15;
		} else {			// ���݂̕���16px��菬�����ꍇ��1px���`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2, NOMOVE_PARTS_SIZE.x+i%16, 0.f, NOMOVE_PARTS_SIZE.x+i%16+1, NOMOVE_PARTS_SIZE.y);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y+m_height/2, NOMOVE_PARTS_SIZE.x+i%16, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+i%16+1, texHeight);
		}
		w -= 16;
	}

	// �c�����̊Ԃ̕����`��
	for( int i = 0, h = (int)m_height; i < m_height; i++ ) {
		if( h / 16 > 0 ) {	// ���݂̍�����16px���傫���ꍇ�͈�C��16px���`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-m_height/2+i, 0.f, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+16);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-m_height/2+i, texWidth-NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y, texWidth, NOMOVE_PARTS_SIZE.y+16);
			i += 15;
		} else {			// ���݂̍�����16px��菬�����ꍇ��1px���`��
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-m_height/2+i, 0.f, NOMOVE_PARTS_SIZE.y+i%16, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+i%16+1);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-m_height/2+i, texWidth-NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+i%16, texWidth, NOMOVE_PARTS_SIZE.y+i%16+1);
		}
		h -= 16;
	}

	// �����̕����`��
	for( int i = 0, w = (int)m_width; i < m_width; i++ ) {
		bool is16pxDraw = false;
		for( int j = 0, h = (int)m_height; j < m_height; j++ ) {
			if( w / 16 > 0 && h / 16 > 0 ) {			// ���݂̍����A����16px���傫���ꍇ�͈�C��16px���`��
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y+16);
				j += 15;
				is16pxDraw = true;
				h -= 16;
			} else if( w / 16 > 0 && h / 16 <= 0 ){		// ���݂̍�����16px���傫���ꍇ��16*1px���`��	
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+1, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y+2);
			} else if( w / 16 <= 0 && h / 16 > 0 ) {	// ���݂̕���16px���傫���ꍇ��1*16px���`��
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x+1, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+2, NOMOVE_PARTS_SIZE.y+16);
				j += 15;
				h -= 16;
			} else {									// ���݂̍����A����16px��菬�����ꍇ��1px���`��
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x+1, NOMOVE_PARTS_SIZE.y+1, NOMOVE_PARTS_SIZE.x+2, NOMOVE_PARTS_SIZE.y+2);
			}
		}
		if( is16pxDraw ) {
			i += 15;
			w -= 16;
		}
	}
	//kore
	//for( DWORD i = 0; i < m_strLst.size(); i++ ) {
	//	int alpha = m_isSelLst[i] ? 255 : 128;
	//	m_strLst[i]->Draw(800+50.f, 100+30.f+30.f*i, D3DCOLOR_ARGB(alpha,255,255,255), m_strLst[i]->getLength());
	//}
	//	m_strLst[PIC_7]->Draw(800,500,D3DCOLOR_ARGB(255,255,255,255),m_strLst[PIC_7]->getLength());

//	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// �X�e���V����o�b�t�@����
}
/*--------------------------------------------------------------

	�ړ���̍��W���Z�b�g
	@param	D3DXVECTOR2 
	@return �Ȃ�

--------------------------------------------------------------*/	
void CGameWindow::SetNextPosition(D3DXVECTOR2 _nextPosition)
{
	m_nextPosition.x = _nextPosition.x;
	m_nextPosition.y = _nextPosition.y;

	// X���������̏ꍇ�c�Ɉړ�
	if( m_nextPosition.x == m_position.x ) {
		m_direction = DIR_VIRTICAL;
		m_state = STATE_MOVE;
		// ���̈ړ���
		m_move = (m_nextPosition.y - m_position.y) / MOVE_TIME;
	}
	// Y���������̏ꍇ���Ɉړ�
	else if( m_nextPosition.y == m_position.y ) {
		m_direction = DIR_HORIZONTAL;
		m_state = STATE_MOVE;
		// ���̈ړ���
		m_move = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
}
/*--------------------------------------------------------------

	�ړ���̍��W���Z�b�g
	@param	int �T���A�C�e���̔ԍ�
	@param  ItemType �T��List�̃^�C�v(����or����A�C�e��)
	@return List�̔z��ԍ�

--------------------------------------------------------------*/	
int CGameWindow::Search(int _itemNum,ItemType _type)
{
	int head,tail,center;
	if( _type == TYPE_EQUIP ){
		// �������X�g���猟��
		head = 0;
		tail = m_pGameData->m_equipList.size();
		while( head <= tail){
			center = (head + tail) / 2;
			if( m_pGameData->m_equipList[center].no == _itemNum )
				return center; // �����������͔��������z��̗v�f��Ԃ�
			else if( m_pGameData->m_equipList[center].no <_itemNum )
				head = center + 1;
			else
				tail = center -1;
		}
	}else{
		// �A�C�e�����X�g���猟��
		head = 0;
		tail = m_pGameData->m_itemList.size();
		while( head <= tail){
			center = (head + tail) / 2;
			if( m_pGameData->m_itemList[center].no == _itemNum )
				return center; // �����������͔��������z��̗v�f��Ԃ�
			else if( m_pGameData->m_itemList[center].no <_itemNum )
				head = center + 1;
			else
				tail = center -1;
		}
	}
	// ������Ȃ�����
	return -1;
}
/*--------------------------------------------------------------

	�E�C���h�E�̏�Ԃ��擾
	@param  �Ȃ�
	@return ���

--------------------------------------------------------------*/
CGameWindow::State CGameWindow::Get()
{
	return m_state;
}
/*--------------------------------------------------------------

	�Q�[���f�[�^���Z�b�g����
	@param  CGameData* �Q�[���f�[�^

--------------------------------------------------------------*/
void CGameWindow::SetGameData(CGameData* _pGameData)
{
	m_pGameData = _pGameData;
}

