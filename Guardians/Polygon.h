#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <d3d9.h>

class CPolygon {
private:
	#define CUSTOM_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット
	struct CustomVertex {
		float x,y,z;
		float rhw;
		DWORD color;
		float u,v;
	};
	LPDIRECT3DDEVICE9	m_pDevice;
public:
	CPolygon(LPDIRECT3DDEVICE9 pDevice);

	void Draw(LPDIRECT3DTEXTURE9 pTexture, float x, float y, float w, float h, DWORD color);
};

#endif	// _POLYGON_H_