#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

/// レンダリングターゲット変更用セット
/**
 * テクスチャへのレンダリングの開始とそのテクスチャの返しを用意する
 */
class RenderTargetSet
{
	IDirect3DSurface9 *m_backbuffer_surface;	//!< バックバッファサーフェイス
	IDirect3DSurface9 *m_textuer_surface;		//!< テクスチャサーフェイス
	IDirect3DTexture9 *m_render_target_textuer;	//!< レンダリングターゲット先テクスチャ
	LPDIRECT3DDEVICE9 m_dev;					//!< 描画切り替えように保持する
	UINT m_width;		//!< 幅
	UINT m_heigth;		//!< 高さ

private:
	/// メンバーの解放
	void ReleaseParameter();

public:

	RenderTargetSet();
	~RenderTargetSet();

	/// レンダリングターゲットのテクスチャを作成
	bool CreateRenderTargetTexture( LPDIRECT3DDEVICE9 _dev, UINT _w, UINT _h );

	/// レンダリングターゲットを作成したテクスチャに変更する
	bool SetTextuerRenderTarget( int _r, int _g, int _b );

	/// レンダリングターゲットをバックバッファに変更する
	bool SetBackbufferRenderTarget( int _r, int _g, int _b );

	/// 描画対象テクスチャを返す
	IDirect3DTexture9 *GetRenderTargetTextuer();
};
