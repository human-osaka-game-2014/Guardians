#ifndef _TEXTURE_H_
#define _TEXTURE_H_


class CTexture {
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	float				m_width;
	float				m_height;
public:
	CTexture() {m_pTexture = NULL;} 
	BOOL Load(const wchar_t* _fileName, LPDIRECT3DDEVICE9 _pDevice);
	void Release();

public:
	LPDIRECT3DTEXTURE9 Get() { return m_pTexture; }
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
};

#endif	// _TEXTURE_H_
