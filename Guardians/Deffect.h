class CEffectt
{
public:
	
private:
	LPDIRECT3DDEVICE9						m_pDevice;			// 描画デバイス
	D3DXVECTOR3								m_position;			// 描画位置
	D3DXVECTOR3								m_scale;			// スケール
	IXAudio2*								m_xAudio;
	IXAudio2MasteringVoice*					m_xa_master;

	float									m_charaHeight;		// キャラの高さ
	int										m_time;				// エフェクト描画時間
	float									m_angle;			// エフェクトの向き
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
	// ゲッタ
	D3DXVECTOR3 GetPosition();
	int			GetDrawTime();

	void  SetRotate(float _angle);
	void  SetCharaHeight(float _height);
	void  SetLocation(D3DXVECTOR3);
private:
};