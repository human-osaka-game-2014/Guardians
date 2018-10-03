class CEffectt
{
public:
	
private:
	LPDIRECT3DDEVICE9						m_pDevice;			// �`��f�o�C�X
	D3DXVECTOR3								m_position;			// �`��ʒu
	D3DXVECTOR3								m_scale;			// �X�P�[��
	IXAudio2*								m_xAudio;
	IXAudio2MasteringVoice*					m_xa_master;

	float									m_charaHeight;		// �L�����̍���
	int										m_time;				// �G�t�F�N�g�`�掞��
	float									m_angle;			// �G�t�F�N�g�̌���
public:
	Effekseer::Manager*						efk_manager;
	EffekseerRenderer::Renderer*			efk_renderer;
	Effekseer::Effect*						efk_effect;
	Effekseer::Handle						efk_handle;
	EffekseerSound::Sound*					efk_sound;
public:
	CEffectt( D3DXVECTOR3 _position ,LPDIRECT3DDEVICE9 _device );
	~CEffectt();

	void Create( LPCWSTR _fileName,	D3DXVECTOR3	_position);
	void Control( D3DXVECTOR3 _value , D3DXVECTOR3 _position);
	void StopEffect( );
	void Release();

	bool Play( D3DXVECTOR3 _position,D3DXVECTOR3 _scale );
	bool replay(D3DXVECTOR3 _position,D3DXVECTOR3 _scale);
	bool checkEnd();

	Effekseer::Matrix44 D3DXMATRIXtoMatrix44( D3DXMATRIX* _matrix);
	// �Q�b�^
	D3DXVECTOR3 GetPosition();
	int			GetDrawTime();

	void  SetRotate(float _angle);
	void  SetCharaHeight(float _height);
	void  SetLocation(D3DXVECTOR3);
private:
};