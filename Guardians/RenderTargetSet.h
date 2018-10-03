#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

/**
@brief	�����_�����O�^�[�Q�b�g�ύX�p�Z�b�g
		�e�N�X�`���ւ̃����_�����O�̊J�n�Ƃ��̃e�N�X�`���̕Ԃ���p�ӂ���
*/
class RenderTargetSet
{
	IDirect3DSurface9 *m_backbuffer_surface;	//!< @brief �o�b�N�o�b�t�@�T�[�t�F�C�X
	IDirect3DSurface9 *m_textuer_surface;		//!< @brief �e�N�X�`���T�[�t�F�C�X
	IDirect3DTexture9 *m_render_target_textuer;	//!< @brief �����_�����O�^�[�Q�b�g��e�N�X�`��
	LPDIRECT3DDEVICE9 m_dev;					//!< @brief �`��؂�ւ��悤�ɕێ�����
	UINT m_width;		//!< @brief ��
	UINT m_heigth;		//!< @brief ����

private:
	/** @brief �����o�[�̉��*/
	void ReleaseParameter();

public:

	RenderTargetSet();
	~RenderTargetSet();

	/**
	@brief	�����_�����O�^�[�Q�b�g�̃e�N�X�`�����쐬
	@param	1[ in ] �`��f�o�C�X
	@param	2[ in ] �쐬�e�N�X�`���̕�
	@param	3[ in ] �쐬�e�N�X�`���̍���
	@return true	����
	@return false	���s�i�f�o�C�X���m�ۂ���Ă��Ȃ��\��������܂��j
	*/
	bool CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h );

	/**
	@brief	�����_�����O�^�[�Q�b�g���쐬�����e�N�X�`���ɕύX����
	@param	1[ in ] �N���A�F�̐�
	@param	2[ in ] �N���A�F�̗�
	@param	3[ in ] �N���A�F�̐�
	@return ����	true
	@return ���s	false�i��̃e�N�X�`�����쐬����Ă��Ȃ��\��������܂��j
	*/
	bool SetTextuerRenderTarget( int _r, int _g, int _b );

	/**
	@brief	�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɕύX����
	@param	1[ in ] �N���A�F�̐�
	@param	2[ in ] �N���A�F�̗�
	@param	3[ in ] �N���A�F�̐�
	@return ����	true
	@return ���s	false�i��̃e�N�X�`�����쐬����Ă��Ȃ��\��������܂��j
	*/
	bool SetBackbufferRenderTarget( int _r, int _g, int _b );

	/**
	@brief	�`��Ώۃe�N�X�`����Ԃ�(�J�E���^��������Ȃ��̂ŕۑ����鎞�͒���)
	@return	�����_�����O�^�[�Q�b�g�̃e�N�X�`����Ԃ�
	*/
	IDirect3DTexture9 *GetRenderTargetTextuer();
};
