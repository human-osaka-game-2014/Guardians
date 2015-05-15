#ifndef _3DVERTEX_H_
#define _3DVERTEX_H_

class CTexture;

class C3DVertex {
private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};
	static const DWORD D3DFVF_CUSTOM3DVERTEX;
	int m_alpha;
	DWORD m_color;
	D3DXVECTOR3 m_scale;
	IDirect3DVertexBuffer9* m_vertex;
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	C3DVertex(LPDIRECT3DDEVICE9 _pDevice, float z);
	void SetAlpha(int _alpha);
	void SetColor(DWORD _color);
	void SetScale(D3DXVECTOR3 _scale);
	void DrawTexture(CTexture _texture, D3DXVECTOR3);
	void DrawTexture(CTexture _texture, D3DXVECTOR3, float _srcL, float _srcT, float _srcR, float _srcB);
};

#endif	// _VERTEX_H_