

class CFontPolygon
{
private:
	struct Vtx {
		float x, y, z;
		float u, v;
	};
	LPDIRECT3DDEVICE9	m_pDevice;
	IDirect3DVertexBuffer9 *pVertexBuffer;
public:
	CFontPolygon(LPDIRECT3DDEVICE9 _pDevice);

	void Draw( float x, float y, CTexCharacter* texChr );
};

