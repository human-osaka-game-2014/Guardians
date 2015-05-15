#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

/**
@brief	レンダリングターゲット変更用セット
		テクスチャへのレンダリングの開始とそのテクスチャの返しを用意する
*/
class RenderTargetSet
{
	IDirect3DSurface9 *m_backbuffer_surface;	//!< @brief バックバッファサーフェイス
	IDirect3DSurface9 *m_textuer_surface;		//!< @brief テクスチャサーフェイス
	IDirect3DTexture9 *m_render_target_textuer;	//!< @brief レンダリングターゲット先テクスチャ
	LPDIRECT3DDEVICE9 m_dev;					//!< @brief 描画切り替えように保持する
	UINT m_width;		//!< @brief 幅
	UINT m_heigth;		//!< @brief 高さ

private:
	/** @brief メンバーの解放*/
	void ReleaseParameter();

public:

	RenderTargetSet();
	~RenderTargetSet();

	/**
	@brief	レンダリングターゲットのテクスチャを作成
	@param	1[ in ] 描画デバイス
	@param	2[ in ] 作成テクスチャの幅
	@param	3[ in ] 作成テクスチャの高さ
	@return true	成功
	@return false	失敗（デバイスが確保されていない可能性があります）
	*/
	bool CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h );

	/**
	@brief	レンダリングターゲットを作成したテクスチャに変更する
	@param	1[ in ] クリア色の赤
	@param	2[ in ] クリア色の緑
	@param	3[ in ] クリア色の青
	@return 成功	true
	@return 失敗	false（空のテクスチャが作成されていない可能性があります）
	*/
	bool SetTextuerRenderTarget( int _r, int _g, int _b );

	/**
	@brief	レンダリングターゲットをバックバッファに変更する
	@param	1[ in ] クリア色の赤
	@param	2[ in ] クリア色の緑
	@param	3[ in ] クリア色の青
	@return 成功	true
	@return 失敗	false（空のテクスチャが作成されていない可能性があります）
	*/
	bool SetBackbufferRenderTarget( int _r, int _g, int _b );

	/**
	@brief	描画対象テクスチャを返す(カウンタ操作をしないので保存する時は注意)
	@return	レンダリングターゲットのテクスチャを返す
	*/
	IDirect3DTexture9 *GetRenderTargetTextuer();
};
