#ifndef _VERTEX_H_
#define _VERTEX_H_

class CTexture;

class CVertex {
public:

private:
	struct CUSTOMVERTEX
	{
		FLOAT	x, y, z, rhw;
		DWORD	color;
		FLOAT	tu, tv;
	};


	struct ROTATION
	{
		int angle;
		float centerX;
		float centerY;

		ROTATION(int _angle, float _centerX, float _centerY) {
			angle = _angle;
			centerX = _centerX;
			centerY = _centerY;
		}
	};
	
	static const DWORD D3DFVF_CUSTOMVERTEX;
	float m_sizeX;
	float m_sizeY;
	ROTATION m_rot;
	
public:
	CVertex() : m_sizeX(1.f), m_sizeY(1.f), m_rot(0, 0.f, 0.f) {} 
	void DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureCC(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y,
		float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y, FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureCC(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y,
		float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTextureCC(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture, float _x, float _y, FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	
	void DrawTextureLT(LPDIRECT3DDEVICE9 _pDevice, CTexture _texture,D3DXVECTOR2 _vector2,FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));


	void DrawTexture(LPDIRECT3DDEVICE9 _pDevice,  float _x, float _y, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTexture(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y,
		float _srcL, float _srcT, float _srcR, float _srcB, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawTexture(LPDIRECT3DDEVICE9 _pDevice,float _x, float _y, FRECT _rect, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));


public:
	void SetSizeX(float _sizeX) { m_sizeX = _sizeX; }
	void SetSizeY(float _sizeY) { m_sizeY = _sizeY; }
	void SetRotationCenter(float _cx, float _cy) { m_rot.centerX = _cx; m_rot.centerY = _cy; }
	void SetAngle(int _angle) { m_rot.angle = _angle; }


void SetBillBoardMatrix( LPDIRECT3DDEVICE9 pd3dDevice, D3DXMATRIX* pMatMatrix );
D3DXMATRIX GetBillBoardMatrix( LPDIRECT3DDEVICE9 pd3dDevice, D3DXMATRIX* pMatMatrix );

void CVertex::GetRotCamera(D3DXMATRIX &out,D3DXMATRIX &in);
void GetScreenMatrix(D3DXMATRIX& out,float width,float height);
};

#endif	// _VERTEX_H_