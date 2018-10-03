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
	 *	�R���X�g���N�^
	 *	@param �f�o�C�X
	 *	@param �쐬���镶��
	 *	@param �T�C�Y
	 *	@param ����
	 */
	CTexCharacter(LPDIRECT3DDEVICE9 pDevice, const TCHAR* character, int size, int weight);

	LPDIRECT3DTEXTURE9 getTexture() { return m_pTexture; }

	int getFontHeight() { return m_fontH; }
	int getFontWidth() { return m_fontW; }
	int getFontSize() { return m_fontSize; }
	GLYPHMETRICS getGm() { return gm; }

	// �T�C�Y���Z�b�g����֐�
	void SetFontWidth(int _fontW);
	void SetFontHeight(int _fontH);
};

#endif