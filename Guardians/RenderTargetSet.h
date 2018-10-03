#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

/// �����_�����O�^�[�Q�b�g�ύX�p�Z�b�g
/**
 * �e�N�X�`���ւ̃����_�����O�̊J�n�Ƃ��̃e�N�X�`���̕Ԃ���p�ӂ���
 */
class RenderTargetSet
{
	IDirect3DSurface9 *m_backbuffer_surface;	//!< �o�b�N�o�b�t�@�T�[�t�F�C�X
	IDirect3DSurface9 *m_textuer_surface;		//!< �e�N�X�`���T�[�t�F�C�X
	IDirect3DTexture9 *m_render_target_textuer;	//!< �����_�����O�^�[�Q�b�g��e�N�X�`��
	LPDIRECT3DDEVICE9 m_dev;					//!< �`��؂�ւ��悤�ɕێ�����
	UINT m_width;		//!< ��
	UINT m_heigth;		//!< ����

private:
	/// �����o�[�̉��
	void ReleaseParameter();

public:

	RenderTargetSet();
	~RenderTargetSet();

	/// �����_�����O�^�[�Q�b�g�̃e�N�X�`�����쐬
	bool CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h );

	/// �����_�����O�^�[�Q�b�g���쐬�����e�N�X�`���ɕύX����
	bool SetTextuerRenderTarget( int _r, int _g, int _b );

	/// �����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɕύX����
	bool SetBackbufferRenderTarget( int _r, int _g, int _b );

	/// �`��Ώۃe�N�X�`����Ԃ�
	IDirect3DTexture9 *GetRenderTargetTextuer();
};
