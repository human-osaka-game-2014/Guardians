/*--------------------------------------------------------------

	�������e:
	�쐬��:�h��
	�쐬��:9/22
	�X�V��:9/25
		   10/5
	�X�V���e:
	�֐��@
		10/5
		Control���ɃJ�[�\�����L���鏈����ǉ�
		Control���̃J�[�\�����ړ��������̏�����maxWidth,Height���ϓ�����悤�ɒǉ�
		9/25
		ControlFricker�̒ǉ�
		GetState�̒ǉ�			����
	�ϐ��@
		10/5
		DIR_DIAGONAL�̒ǉ�
		WARNING�΍��float��RECT�\���̂�錾
		NOMOVE_PARTS_SIZE�̒ǉ�
		9/25
		�_�ŃA�j���[�V�����p�J�E���g�@int	m_count�̒ǉ�
		FRICKER_TIME��60�ɕύX


--------------------------------------------------------------*/
#include "stdafx.h"
/* �萔 */
// �L����ۂɕϓ����Ȃ������̃T�C�Y(���P��(24�~24) 
const D3DXVECTOR2 CGameCursor::NOMOVE_PARTS_SIZE = D3DXVECTOR2(24.f, 24.f);

/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X�A���W�A�g�p�摜ID���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X
	@param D3DXVECTOR2			�`�悷��ʒux,y
	@param int					�g�p����e�N�X�`����ID

--------------------------------------------------------------*/
CGameCursor::CGameCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position) : m_pDevice(_pDevice),m_position(_position.x,_position.y),
	m_alpha(255),m_fadeType(FADE_OUT), m_flickFlag(true),m_addAlpha((m_alpha/2)/FLICKER_TIME)
{

}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CGameCursor::~CGameCursor()
{
//	m_texture.Release();

}
/*--------------------------------------------------------------

	�_�ŃA�j���[�V����
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CGameCursor::ControlFlicker()
{

	//�_�����Ă����ԂȂ�alpha�l�����炷
	if(m_fadeType == FADE_OUT){
		m_alpha -= m_addAlpha;
		if(m_alpha <= 128)	m_fadeType = FADE_IN;
	}

	if(m_fadeType == FADE_IN){
		m_alpha += m_addAlpha;
		if(m_alpha >= 255)	m_fadeType = FADE_OUT;
	}
}
/*--------------------------------------------------------------

	�J�[�\���̐���
	@param	�Ȃ�
	@return �Ȃ�

--------------------------------------------------------------*/
void CGameCursor::Control()	// ����
{
	//�_�ŃA�j���[�V�����̐���
	if(m_flickFlag) ControlFlicker();

	switch( m_state ) {
	case STATE_MOVE:
		switch( m_direction ) {
		case DIR_HORIZONTAL:
			m_position.x += m_moveX;
			if( fabs(m_position.x - m_nextPosition.x) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.x = ROUND_OFF(m_position.x);
			}
			break;
		case DIR_VIRTICAL:
			m_position.y += m_moveY;
			if( fabs(m_position.y - m_nextPosition.y) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.y = ROUND_OFF(m_position.y);
			}
			break;
		case DIR_DIAGONAL:
			m_position.y += m_moveY;
			m_position.x += m_moveX;
			if( fabs(m_position.y - m_nextPosition.y) <= 0.1f ) {
				m_state = STATE_WAIT;
				m_position.x = ROUND_OFF(m_position.x);
				m_position.y = ROUND_OFF(m_position.y);
			}
			break;
		}
		break;
	}
}
/*--------------------------------------------------------------

	�J�[�\���̕`��
	@param	�Ȃ�
	@return	�Ȃ�

--------------------------------------------------------------*/
void CGameCursor::Draw()	// �`��
{
	m_vertex.DrawTextureLT( m_pDevice,m_texture,m_position.x,m_position.y,m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,D3DCOLOR_ARGB(m_alpha,m_alpha,m_alpha,m_alpha) );
}
/*--------------------------------------------------------------

	�ړ���̍��W���Z�b�g
	@param	D3DXVECTOR2 
	@return �Ȃ�

--------------------------------------------------------------*/	
void CGameCursor::SetNextPosition(D3DXVECTOR2 _nextPosition)
{
	m_nextPosition.x = _nextPosition.x;
	m_nextPosition.y = _nextPosition.y;
	// X���������̏ꍇ�c�Ɉړ�
	if( m_nextPosition.x == m_position.x ) {
		m_direction = DIR_VIRTICAL;
		m_state = STATE_MOVE;
		// ���̈ړ���
		m_moveY = (m_nextPosition.y - m_position.y) / MOVE_TIME;
	}
	// Y���������̏ꍇ���Ɉړ�
	else if( m_nextPosition.y == m_position.y ) {
		m_direction = DIR_HORIZONTAL;
		m_state = STATE_MOVE;
		// ���̈ړ���
		m_moveX = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
	else{	//�ǂ�����Ⴄ�ꍇ�͎΂߂Ɉړ�
		m_direction = DIR_DIAGONAL;
		m_state = STATE_MOVE;
		//���̈ړ���
		m_moveY = (m_nextPosition.y - m_position.y) / MOVE_TIME;
		m_moveX = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
}
/*--------------------------------------------------------------

	�I������Ă��鍀�ڔԍ����擾
	@param	�Ȃ�
	@return ����

--------------------------------------------------------------*/
int CGameCursor::GetSelectID()														
{
	return m_selectID;
}

/*--------------------------------------------------------------

	��Ԃ��擾
	@param	�Ȃ�
	@return ���

--------------------------------------------------------------*/
int CGameCursor::GetState()
{
	return m_state;
}