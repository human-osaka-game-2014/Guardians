#include "stdafx.h"

/**
 *	コンストラクタ
 *	@param デバイス
 *	@param 作成する文字
 *	@param 幅
 *	@param 高さ
 */
CTexCharacter::CTexCharacter(LPDIRECT3DDEVICE9 pDevice, const TCHAR* character, int size, int weight) : 
m_pDevice(pDevice), m_pTexture(0), m_fontSize(size){

	LOGFONTA lf = {size, 0, 0, 0, weight, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "ＭＳ Ｐゴシック"};

	// フォント
	HFONT hFont = CreateFontIndirectA(&lf);
	if( hFont == NULL ) return;

	// デバイスコンテキスト取得
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	// 文字コード取得
	UINT code = 0;
#if UNICODE
	code = (UINT)*character;
#else
	if(IsDBCSLeadByte(*character)) {
		code = static_cast<BYTE>(character[0]) << 8 | static_cast<BYTE>(character[1]);
	} else {
		code = static_cast<BYTE>(character[0]);
	}
#endif
	// ビットマップ取得
	const int gradFlag = GGO_GRAY4_BITMAP;
	int grad = 0;	// 階調の最大値
	switch( gradFlag ) {
	case GGO_GRAY2_BITMAP: grad = 4; break;
	case GGO_GRAY4_BITMAP: grad = 16; break;
	case GGO_GRAY8_BITMAP: grad = 64; break;
	}

	// フォント情報取得
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	const MAT2 mat = {{0,1},{0,0},{0,0},{0,1}};
	DWORD dwSize = GetGlyphOutline(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE* mono = new BYTE[dwSize];
	GetGlyphOutline(hdc, code, gradFlag, &gm, dwSize, mono, &mat);

	// オブジェクト解放
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);

	// テクスチャ作成
	int fontWidth = (gm.gmBlackBoxX + 3) / 4 * 4;
	int fontHeight = gm.gmBlackBoxY;
	pDevice->CreateTexture( fontWidth, fontHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture, NULL );

	// テクスチャにフォントビットマップ情報を書き込み
	D3DLOCKED_RECT lockedRect;
	m_pTexture->LockRect( 0, &lockedRect, NULL, 0);  // ロック
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;   // テクスチャメモリへのポインタ

	for (int y = 0; y < fontHeight; y++ ) {
			for (int x = 0; x < fontWidth; x++ ) {
					DWORD alpha = mono[y * fontWidth + x] * 255 / grad;
					pTexBuf[y * fontWidth + x] = (alpha << 24) | 0x00ffffff;
			}
	}

	m_pTexture->UnlockRect( 0 );  // アンロック
	delete[] mono;

	m_fontH = fontHeight;
	m_fontW = fontWidth;
}

// サイズをセットする関数
void CTexCharacter::SetFontWidth(int _fontW)
{
	m_fontW = _fontW;
}

void CTexCharacter::SetFontHeight(int _fontH)
{
	m_fontH = _fontH;
}
