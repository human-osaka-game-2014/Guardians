#include "stdafx.h"


#if _DEBUG
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX9.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Release.lib" )
#endif


/*-----------------------------------------------------------------------------------

	コンストラクタ
	@param	LPCTSTR				ファイル名
	@param	D3DXVECTOR3			描画位置
	@param	D3DXVECTOR3			スケール
	@param	LPDIRECT3DDEVICE9	描画デバイス

------------------------------------------------------------------------------------*/
CEffectt::CEffectt( D3DXVECTOR3 _position , LPDIRECT3DDEVICE9 _device ) : efk_handle(-1) ,
	efk_effect(NULL) , efk_renderer(NULL) , efk_manager(NULL) , m_pDevice(_device) , m_position(_position)
	,m_xAudio( NULL ) , efk_sound(NULL) , m_xa_master(NULL), m_charaHeight(0) , m_angle(0)
{
	//エフェクト関連を初期化
	//描画用インスタンスの生成
	efk_renderer= EffekseerRendererDX9::Renderer::Create(m_pDevice,2000);
	//エフェクト管理用インスタンスの生成
	efk_manager = Effekseer::Manager::Create(2000);
	//描画用インスタンスから描画機能を設定
	efk_manager->SetSpriteRenderer(efk_renderer->CreateSpriteRenderer());
	efk_manager->SetRibbonRenderer(efk_renderer->CreateRibbonRenderer());
	//描画用インスタンスからテクスチャの読み込み機能を設定(独自拡張可能、現在はファイルから読み込んでいる)
	efk_manager->SetTextureLoader(efk_renderer->CreateTextureLoader());
	//座標系の指定(LH : 左手座標系, RH : 右手座標系)
	efk_manager->SetCoordinateSystem(Effekseer::COORDINATE_SYSTEM_LH);

	efk_renderer->SetProjectionMatrix(Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(90),1280.0f/730.0f,0.1f,2000.f));
	
    CoInitializeEx(NULL, COINIT_MULTITHREADED);


	XAudio2Create( &m_xAudio );
	
	m_xAudio->CreateMasteringVoice( &m_xa_master );
	// 音再生用インスタンスの生成
	efk_sound = ::EffekseerSound::Sound::Create( m_xAudio, 16, 16 );

	// 音再生用インスタンスから再生機能を指定
	efk_manager->SetSoundPlayer( efk_sound->CreateSoundPlayer() );
	
	// 音再生用インスタンスからサウンドデータの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	efk_manager->SetSoundLoader( efk_sound->CreateSoundLoader() );
}
/*-----------------------------------------------------------------------------------

	エフェクトの生成
	@param	LPCWSTR ファイル名
	@param	D3DXVECTOR3	位置
	@param	D3DXVECTOR3	スケール
	@return なし

------------------------------------------------------------------------------------*/
void CEffectt::Create( LPCWSTR _fileName,	D3DXVECTOR3	_position)
{

	//カメラ行列を設定
	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	//char a[256];
	//a = new char[256];
	//std::string str;
	//str = "Effect\\FireBall_01.efk";
	//WCHAR wchar;

	//std::wstring wstr;
	//setlocale( LC_CTYPE, "jpn" );
	
	if( efk_effect == NULL)
		efk_effect = Effekseer::Effect::Create(efk_manager,(const EFK_CHAR*)_fileName);// エフェクトの読込
	
	//エフェクト調整
	//efk_manager->SetLocation(efk_handle,m_position.x,m_position.y ,m_position.z);//位置
	//efk_manager->SetRotation(efk_handle,Effekseer::Vector3D(0.0f,0.0f,0.0f),0.0f);//回転
	//efk_manager->SetScale(efk_handle,m_scale.x,m_scale.y,m_scale.x);//倍率
}
void CEffectt::SetRotate(float _angle)
{
	m_angle = _angle + 90;
}
void CEffectt::StopEffect()
{
	// エフェクトの停止
	efk_manager->StopEffect( efk_handle );
}
/*-----------------------------------------------------------------------------------

	デストラクタ

------------------------------------------------------------------------------------*/
CEffectt::~CEffectt()
{
	// エフェクトの停止
	efk_manager->StopEffect( efk_handle );
	// エフェクトを解放(再生中の場合は再生終了時に自動的に解放)
	ES_SAFE_RELEASE(efk_effect);
	
	efk_manager->Destroy();
	efk_sound->Destory();
	efk_renderer->Destory();

	// XAudio2の解放
	if(  m_xa_master != NULL )
	{
		m_xa_master->DestroyVoice();
		m_xa_master = NULL;
	}
	ES_SAFE_RELEASE( m_xAudio );

	//CoUninitialize();
}
/*-----------------------------------------------------------------------------------

	制御
	@param	D3DXVECTOR3 移動量
	@return なし

------------------------------------------------------------------------------------*/
void CEffectt::Control(D3DXVECTOR3 _value , D3DXVECTOR3 _position)
{

	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	//描画
	efk_manager->Update();//エフェクトの更新処理
		
	efk_renderer->BeginRendering();//エフェクトの描画開始処理

	efk_manager->Draw();//エフェクトの描画

	efk_renderer->EndRendering();//エフェクトの描画終了処理

	// エフェクトの移動処理を行う
	efk_manager->AddLocation( efk_handle,Effekseer::Vector3D( _value.x,_value.y,_value.z ) );
	//m_position += _value;
	// エフェクト処理時間を加算
	m_time++;

}
/*-----------------------------------------------------------------------------------

	描画
	@param	なし
	@return true 再生開始 : false 再生中

------------------------------------------------------------------------------------*/
bool CEffectt::Play( D3DXVECTOR3 _position ,D3DXVECTOR3 _scale )
{

	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));
	static float a = 0;
	// エフェクトのインスタンスが存在していなければ再生する
	if(!efk_manager->Exists(efk_handle)){
		m_time = 0;
		m_position = _position;
		m_position.y += m_charaHeight;
		// エフェクト再生位置は原点から高さを足す
		efk_handle = efk_manager->Play(efk_effect,m_position.x,m_position.y,m_position.z);//エフェクトの再生
		
		
		efk_manager->SetRotation(efk_handle,0.f,180.f,0.f );//回転
		efk_manager->SetRotation(efk_handle,D3DXToRadian(m_angle),0.f,0.f );//回転
		efk_manager->SetRotation(efk_handle,0.f,D3DXToRadian(m_angle),0.f );//回転

		efk_manager->SetScale(efk_handle,_scale.x,_scale.y,_scale.x);//倍率
		return true;
	}
	a++;
	return false;
}

bool CEffectt::replay(D3DXVECTOR3 _position,D3DXVECTOR3 _scale)
{
	D3DXMATRIX matView, matProj;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	efk_renderer->SetCameraMatrix(D3DXMATRIXtoMatrix44(&matView));
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	efk_renderer->SetProjectionMatrix(D3DXMATRIXtoMatrix44(&matProj));

	StopEffect();
	// エフェクトのインスタンスが存在していなければ再生する
	if(!efk_manager->Exists(efk_handle)){
		m_time = 0;
		m_position = _position;
		// エフェクト再生位置は原点から高さを足す
		efk_handle = efk_manager->Play(efk_effect,m_position.x,m_position.y + m_charaHeight,m_position.z);//エフェクトの再生
		static float a = 0;
		efk_manager->SetRotation(efk_handle,0.f,180.f,0 );//回転
		efk_manager->SetRotation(efk_handle,D3DXToRadian(m_angle),0.f,0.f );//回転
		efk_manager->SetRotation(efk_handle,0.f,D3DXToRadian(m_angle),0.f );//回転	
		efk_manager->SetScale(efk_handle,_scale.x,_scale.y,_scale.x);//倍率
		return true;
	}
	return false;
}
/*-----------------------------------------------------------------------------------

	エフェクトが再生終了しているかどうか
	@param	なし
	@return bool true 再生終了　: false 再生中

------------------------------------------------------------------------------------*/
bool CEffectt::checkEnd()
{
	return efk_manager->Exists(efk_handle);
}
/*-----------------------------------------------------------------------------------

	描画位置を取得
	@param	なし
	@return D3DXVECTOR3　位置

------------------------------------------------------------------------------------*/
D3DXVECTOR3 CEffectt::GetPosition()
{
	D3DXVECTOR3 pos;
	
	pos.x = efk_manager->GetLocation(efk_handle).X;
	pos.y = efk_manager->GetLocation(efk_handle).Y;
	pos.z = efk_manager->GetLocation(efk_handle).Z;

	return m_position;
}
/*-----------------------------------------------------------------------------------

	開放
	@param	なし
	@return なし

------------------------------------------------------------------------------------*/
void CEffectt::Release()
{
	// エフェクトの停止
	//efk_manager->StopEffect( efk_handle );
	// エフェクトを解放(再生中の場合は再生終了時に自動的に解放)
	ES_SAFE_RELEASE(efk_effect);
}
Effekseer::Matrix44 CEffectt::D3DXMATRIXtoMatrix44( D3DXMATRIX* _matrix)
{
	Effekseer::Matrix44 mat;
	mat.Values[0][0] = _matrix->_11;
	mat.Values[0][1] = _matrix->_12;
	mat.Values[0][2] = _matrix->_13;
	mat.Values[0][3] = _matrix->_14;
	mat.Values[1][0] = _matrix->_21;
	mat.Values[1][1] = _matrix->_22;
	mat.Values[1][2] = _matrix->_23;
	mat.Values[1][3] = _matrix->_24;
	mat.Values[2][0] = _matrix->_31;
	mat.Values[2][1] = _matrix->_32;
	mat.Values[2][2] = _matrix->_33;
	mat.Values[2][3] = _matrix->_34;
	mat.Values[3][0] = _matrix->_41;
	mat.Values[3][1] = _matrix->_42;
	mat.Values[3][2] = _matrix->_43;
	mat.Values[3][3] = _matrix->_44;
	return mat;

}
void CEffectt::SetCharaHeight(float _height)
{
	m_charaHeight = _height;
}
void CEffectt::SetLocation(D3DXVECTOR3 _position)
{
	efk_manager->SetLocation( efk_handle,Effekseer::Vector3D( _position.x,_position.y + m_charaHeight,_position.z ));
}
int CEffectt::GetDrawTime()
{
	// エフェクトが存在していたら描画時間を返す
	if( efk_manager->Exists(efk_handle))
		return m_time;
	else{
		return m_time = 0;
	}
}