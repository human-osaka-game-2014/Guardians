/*--------------------------------------------------------------

	�������e: �`�[�����S�̐���
	�쐬��: �h��
	�쐬��: 11/1
	�X�V��: 11/1
	�X�V���e:
		�R���X�g���N�^
		�t�F�[�h�C���E�t�F�[�h�A�E�g
		�`�揈��
	�ϐ��@
		

--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	�R���X�g���N�^(�f�o�C�X���Z�b�g)
	@param LPDIRECT3DDEVICE9	�`��f�o�C�X

--------------------------------------------------------------*/
CLogo::CLogo(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice),m_alpha( 0 ),m_fadeType(FADE_IN),m_addAlpha( 255 / 120),m_timeCount(0),m_transition(false)
{
	m_texture = CTexMgr.Get(0);
}
/*--------------------------------------------------------------

	�f�X�g���N�^

--------------------------------------------------------------*/
CLogo::~CLogo()
{

}	
/*--------------------------------------------------------------

	�`��̐���@�`�[�����S�̃t�F�[�h�C���E�t�F�[�h�A�E�g
	@param	�Ȃ�
	@return �Ȃ� 

--------------------------------------------------------------*/
void CLogo::Control()
{
	//�_�����Ă����ԂȂ�alpha�l�����炷
	if(m_fadeType == FADE_IN){
		m_alpha += m_addAlpha;
		if(m_alpha >= 255){
			m_alpha = 255;
			m_fadeType = FADE_STOP;
			m_timeCount = 0;
		}
	}

	if( m_fadeType == FADE_STOP ){
		m_timeCount++;
		if( m_timeCount == 120 )
			m_fadeType = FADE_OUT;
	}

	if(m_fadeType == FADE_OUT){
		m_alpha -= m_addAlpha;
		if(m_alpha <= 0){
			m_alpha = 0;
			m_fadeType = FADE_END;
			m_transition = true;

		}
	}
}
/*--------------------------------------------------------------

	�`��
	@param	�Ȃ�
	@return �Ȃ� 

--------------------------------------------------------------*/
void CLogo::Draw()
{
	//m_vertex.DrawTexture( m_pDevice,100,0,D3DCOLOR_ARGB(m_alpha,255,255,255) );
	m_vertex.DrawTextureLT( m_pDevice,m_texture,200,-50,D3DCOLOR_ARGB(m_alpha,255,255,255) );
}
/*--------------------------------------------------------------

	�V�[���X�L�b�v�t���O��Ԃ�
	@return �V�[���J�ڃt���O 

--------------------------------------------------------------*/
bool CLogo::GetFlag()
{
	return m_transition;
}
