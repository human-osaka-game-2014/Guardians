#include "stdafx.h"

/** @brief �����o�[�̉��*/
void RenderTargetSet::ReleaseParameter()
{
	if( m_dev != NULL ){ m_dev->Release(); }
	if( m_backbuffer_surface != NULL ){ m_backbuffer_surface->Release(); }
	if( m_textuer_surface != NULL ){ m_textuer_surface->Release(); }
	if( m_render_target_textuer != NULL ){ m_render_target_textuer->Release(); }
}


RenderTargetSet::RenderTargetSet()
{
	m_dev = NULL;
	m_backbuffer_surface = NULL;
	m_textuer_surface = NULL;
	m_render_target_textuer = NULL;
}

RenderTargetSet::~RenderTargetSet()
{
	ReleaseParameter();
}

/**
@brief	�����_�����O�^�[�Q�b�g�̃e�N�X�`�����쐬
@param	1[ in ] �`��f�o�C�X
@param	2[ in ] �쐬�e�N�X�`���̕�
@param	3[ in ] �쐬�e�N�X�`���̍���
@return true	����
@return false	���s�i�f�o�C�X���m�ۂ���Ă��Ȃ��\��������܂��j
*/
bool RenderTargetSet::CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h )
{
	//�f�o�C�X�����������Ȃ��Ȃ玸�s
	if( _dev == NULL )
	{
		return false;
	}else{
		//����ȊO�Ȃ�A�����̂��̂�j�󂵂Ă���쐬�ɓ���
		ReleaseParameter();
	}

	//�쐬�e�N�X�`���̊�b���
	m_width		= _w;
	m_heigth	= _h;

	//�f�o�C�X���R�s�[����i��ɏ������Ƃ܂����̂�AddRef�����ĎQ�ƃJ�E���^�����킹��j
	m_dev = _dev;
	_dev->AddRef();

	//��̃e�N�X�`���쐬
	m_dev->CreateTexture(
		_w, _h,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_render_target_textuer,
		NULL 
	);

	//�e�N�X�`���ւ̃T�[�t�F�[�X
	m_render_target_textuer->GetSurfaceLevel( 0, &m_textuer_surface );
	//�o�b�N�o�b�t�@�ւ̃T�[�t�F�C�X
	m_dev->GetBackBuffer( 0,0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer_surface );

	//����
	return true;
}

/**
@brief	�����_�����O�^�[�Q�b�g���쐬�����e�N�X�`���ɕύX����
@param	1[ in ] �N���A�F�̐�
@param	2[ in ] �N���A�F�̗�
@param	3[ in ] �N���A�F�̐�
@return ����	true
@return ���s	false�i��̃e�N�X�`�����쐬����Ă��Ȃ��\��������܂��j
*/
bool RenderTargetSet::SetTextuerRenderTarget( int _r, int _g, int _b )
{
	//�e�N�X�`���̏������O�Ȃ玸�s
	if( m_render_target_textuer == NULL ){return false;}

	//�e�N�X�`���T�[�t�F�C�X�Ɉړ�
	m_dev->SetRenderTarget( 0, m_textuer_surface );
	//�`��N���A
	m_dev->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( _r, _g, _b ), 1.0f, 0 );

	//����I��
	return true;
}

/**
@brief	�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɕύX����
@param	1[ in ] �N���A�F�̐�
@param	2[ in ] �N���A�F�̗�
@param	3[ in ] �N���A�F�̐�
@return ����	true
@return ���s	false�i��̃e�N�X�`�����쐬����Ă��Ȃ��\��������܂��j
*/
bool RenderTargetSet::SetBackbufferRenderTarget( int _r, int _g, int _b )
{
	//�e�N�X�`���̏������O�Ȃ玸�s
	if( m_dev == NULL ){return false;}

	//�e�N�X�`���T�[�t�F�C�X�Ɉړ�
	m_dev->SetRenderTarget( 0, m_backbuffer_surface );
	//�`��N���A
	m_dev->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( _r, _g, _b ), 1.0f, 0 );

	//����I��
	return true;
}

/**
@brief	�`��Ώۃe�N�X�`����Ԃ�(�J�E���^��������Ȃ��̂ŕۑ����鎞�͒���)
@return	�����_�����O�^�[�Q�b�g�̃e�N�X�`����Ԃ�
*/
IDirect3DTexture9 *RenderTargetSet::GetRenderTargetTextuer()
{
	//�Ώۂ�NULL�Ȃ牽���ł��Ȃ�
	if( m_render_target_textuer == NULL ){return NULL;}
	return m_render_target_textuer;
}