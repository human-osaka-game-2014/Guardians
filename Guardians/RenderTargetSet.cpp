#include "stdafx.h"

/** @brief メンバーの解放*/
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
@brief	レンダリングターゲットのテクスチャを作成
@param	1[ in ] 描画デバイス
@param	2[ in ] 作成テクスチャの幅
@param	3[ in ] 作成テクスチャの高さ
@return true	成功
@return false	失敗（デバイスが確保されていない可能性があります）
*/
bool RenderTargetSet::CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h )
{
	//デバイスがそもそもないなら失敗
	if( _dev == NULL )
	{
		return false;
	}else{
		//それ以外なら、既存のものを破壊してから作成に入る
		ReleaseParameter();
	}

	//作成テクスチャの基礎情報
	m_width		= _w;
	m_heigth	= _h;

	//デバイスをコピーする（先に消されるとまずいのでAddRefをして参照カウンタをあわせる）
	m_dev = _dev;
	_dev->AddRef();

	//空のテクスチャ作成
	m_dev->CreateTexture(
		_w, _h,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_render_target_textuer,
		NULL 
	);

	//テクスチャへのサーフェース
	m_render_target_textuer->GetSurfaceLevel( 0, &m_textuer_surface );
	//バックバッファへのサーフェイス
	m_dev->GetBackBuffer( 0,0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer_surface );

	//成功
	return true;
}

/**
@brief	レンダリングターゲットを作成したテクスチャに変更する
@param	1[ in ] クリア色の赤
@param	2[ in ] クリア色の緑
@param	3[ in ] クリア色の青
@return 成功	true
@return 失敗	false（空のテクスチャが作成されていない可能性があります）
*/
bool RenderTargetSet::SetTextuerRenderTarget( int _r, int _g, int _b )
{
	//テクスチャの初期化前なら失敗
	if( m_render_target_textuer == NULL ){return false;}

	//テクスチャサーフェイスに移動
	m_dev->SetRenderTarget( 0, m_textuer_surface );
	//描画クリア
	m_dev->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( _r, _g, _b ), 1.0f, 0 );

	//正常終了
	return true;
}

/**
@brief	レンダリングターゲットをバックバッファに変更する
@param	1[ in ] クリア色の赤
@param	2[ in ] クリア色の緑
@param	3[ in ] クリア色の青
@return 成功	true
@return 失敗	false（空のテクスチャが作成されていない可能性があります）
*/
bool RenderTargetSet::SetBackbufferRenderTarget( int _r, int _g, int _b )
{
	//テクスチャの初期化前なら失敗
	if( m_dev == NULL ){return false;}

	//テクスチャサーフェイスに移動
	m_dev->SetRenderTarget( 0, m_backbuffer_surface );
	//描画クリア
	m_dev->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( _r, _g, _b ), 1.0f, 0 );

	//正常終了
	return true;
}

/**
@brief	描画対象テクスチャを返す(カウンタ操作をしないので保存する時は注意)
@return	レンダリングターゲットのテクスチャを返す
*/
IDirect3DTexture9 *RenderTargetSet::GetRenderTargetTextuer()
{
	//対象がNULLなら何もできない
	if( m_render_target_textuer == NULL ){return NULL;}
	return m_render_target_textuer;
}