#ifndef _ANIM_VERTEX_H_
#define _ANIM_VERTEX_H_

class CTexture;

class CAnimVertex : public CVertex{
private:
	struct Rect {
		float left;
		float top;
		float right;
		float bottom;
	};
	
	int m_animTime;
	int m_animCount;
	int m_xDelim;
	int m_yDelim;
	int m_cut;
	int m_animMax;
	bool m_stop;
	CTexture m_texture;
	Rect** m_rect;
public:
	CAnimVertex(CTexture _texture, int _xDelim, int _yDelim, int _animTime, float _texWidth = -1.f, float _texHeight = -1.f);
	~CAnimVertex();
public:
	void DrawAnimTextureLT(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y, int _wDir, int _hDir = 0, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void DrawAnimTextureCC(LPDIRECT3DDEVICE9 _pDevice, float _x, float _y, int _wDir, int _hDir = 0, D3DCOLOR _color = D3DCOLOR_ARGB(255,255,255,255));
	void SetCut(int _cut, bool _stop);
	int MoveAnimation();
	void SetAnimMax(int _animMax);
};

#endif	// _ANIM_VERTEX_H_