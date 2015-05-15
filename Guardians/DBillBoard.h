
class CBillBoard
{
public:
	// ビルボード頂点情報
	struct BILLVERTEX {
		D3DXVECTOR3 pos;
		DWORD color;
		D3DXVECTOR2 t;
	};
private:
	//LPDIRECT3DDEVICE9 m_pDevice;
	//LPDIRECT3DVERTEXBUFFER9  m_buffer;

public:
	CBillBoard( ){};
	~CBillBoard();

	void Draw(LPDIRECT3DDEVICE9 _pDevice,CTexture _texture,D3DXVECTOR3 _pos,float _scale,D3DXMATRIX _attitude,D3DCOLOR _color);
	void Draw(LPDIRECT3DDEVICE9 _pDevice,CTexture _texture,D3DXVECTOR3 _pos,float _scale,FRECT _rect,D3DXMATRIX _attitude,D3DCOLOR _color);

private:
};