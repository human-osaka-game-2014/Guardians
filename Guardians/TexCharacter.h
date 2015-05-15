#ifndef _TEXCHARACTER_H_
#define _TEXCHARACTER_H_

#include <d3d9.h>


class CTexCharacter {
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_fontH, m_fontW;
	int					m_fontSize;
	GLYPHMETRICS		gm;
public:
	/**
	 *	コンストラクタ
	 *	@param デバイス
	 *	@param 作成する文字
	 *	@param サイズ
	 *	@param 太さ
	 */
	CTexCharacter(LPDIRECT3DDEVICE9 pDevice, const TCHAR* character, int size, int weight);

	LPDIRECT3DTEXTURE9 getTexture() { return m_pTexture; }

	int getFontHeight() { return m_fontH; }
	int getFontWidth() { return m_fontW; }
	int getFontSize() { return m_fontSize; }
	GLYPHMETRICS getGm() { return gm; }

	// サイズをセットする関数
	void SetFontWidth(int _fontW);
	void SetFontHeight(int _fontH);
};

#endif