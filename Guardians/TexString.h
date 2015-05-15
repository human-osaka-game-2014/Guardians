#ifndef _TEXSTRING_H_
#define _TEXSTRING_H_

class CTexString {
private:
	std::vector<CTexCharacter*> m_String;
	CFontPolygon* m_pPolygon;
	float m_width;
	std::vector<UINT> m_NewLineIdx;
	std::vector<DWORD> m_Alpha;
public:
	CTexString(LPDIRECT3DDEVICE9 pDevice, std::string character, int w, int h, LPCWSTR fontName);
	~CTexString() {
		for(UINT i = 0; i < m_String.size(); i++) SAFE_DELETE(m_String[i]);
		SAFE_DELETE(m_pPolygon);
	}
	void Draw(float x, float y, UINT idx);
	void Draw(float x, float y, DWORD color);
	void Draw(float x, float y, DWORD color, UINT idx);
	float getWidth() { return m_width; }
	UINT getLength() { return m_String.size(); }
	int getHeight() { return m_String[0]->getFontHeight(); }

	void SetAlphaMax() {
		for(unsigned int i = 0; i < m_Alpha.size(); i++) {
			m_Alpha[i] = 255;
		}
	}

	void SetSize( int _width, int _height );
};

#endif	// _TEXSTRING_H_