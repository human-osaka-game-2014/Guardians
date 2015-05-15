#include "stdafx.h"

using namespace std;

CTexString::CTexString(LPDIRECT3DDEVICE9 pDevice, string character, int w, int h, LPCWSTR fontName) :
m_width(0.f){
	float width = 0.f;
	wstring conv;
	CStringConvert::Widen(character, conv);
	for(UINT i = 0; i < conv.size(); i++) {

		wstring str = conv.substr(i, 1).c_str();
		if(str.c_str() == L"\n") {
			m_width = max(width, m_width);
			m_NewLineIdx.push_back(i);
			width = 0;
		} else {
			string chStr;
			CStringConvert::Narrow(str, chStr);
			m_String.push_back( new CTexCharacter(pDevice, chStr.c_str(), w, h) );
			width += m_String[i-m_NewLineIdx.size()]->getFontWidth();

			if(i == character.size() - 1) { m_width = max(width, m_width); }

			m_Alpha.push_back(0);
		}
	}
	m_pPolygon = new CFontPolygon(pDevice);
	
	m_width = width;
}
void CTexString::Draw(float x, float y, UINT idx) {
	float drawPos = x;
	for(UINT i = 0, newLineCnt = 0; i < idx + m_NewLineIdx.size(); i++) {

		if(m_NewLineIdx.size() > newLineCnt && m_NewLineIdx[newLineCnt] == i) {
			newLineCnt++;
			drawPos = x;
			if(m_NewLineIdx.size() > newLineCnt && m_NewLineIdx[newLineCnt] >= idx + newLineCnt) break;
		} else {
			int strIdx = i-newLineCnt;
			float width = static_cast<float>(m_String[strIdx]->getFontWidth());
			float height = static_cast<float>(m_String[strIdx]->getFontHeight());
			m_pPolygon->Draw(drawPos, y + newLineCnt * height, m_String[strIdx]);
			drawPos += width;
			if(m_Alpha[strIdx] != 255) m_Alpha[strIdx]++;
		}
	}
}

void CTexString::Draw(float x, float y, DWORD color) {
	/*float drawPos = x;
	for(UINT i = 0, newLineCnt = 0; i < m_String.size() + m_NewLineIdx.size(); i++) {
		if(m_NewLineIdx.size() > newLineCnt && m_NewLineIdx[newLineCnt] == i) {
			newLineCnt++;
			drawPos = x;
		} else {
			int strIdx = i-newLineCnt;
			float width = static_cast<float>(m_String[strIdx]->getFontWidth());
			float height = static_cast<float>(m_String[strIdx]->getFontHeight());
			m_pPolygon->Draw(m_String[strIdx]->getTexture(), drawPos, y + newLineCnt * height, width, height, color);
			drawPos += width;
		}
	}*/
	//Draw(x, y, color, m_String.size() + m_NewLineIdx.size());
}

void CTexString::Draw(float x, float y, DWORD color, UINT idx) {
	float drawPos = x;
	for(UINT i = 0, newLineCnt = 0; i < idx + m_NewLineIdx.size(); i++) {

		if(m_NewLineIdx.size() > newLineCnt && m_NewLineIdx[newLineCnt] == i) {
			newLineCnt++;
			drawPos = x;
			if(m_NewLineIdx.size() > newLineCnt && m_NewLineIdx[newLineCnt] >= idx + newLineCnt) break;
		} else {
			int strIdx = i-newLineCnt;
			float width = static_cast<float>(m_String[strIdx]->getFontWidth());
			float height = static_cast<float>(m_String[strIdx]->getFontHeight());
			m_pPolygon->Draw(drawPos, y + newLineCnt * height, m_String[strIdx]);
			drawPos += width;
		}
	}
}

void CTexString::SetSize( int _width, int _height )
{
	for( unsigned i = 0; i < m_String.size(); i++ ) {
		m_String[i]->SetFontHeight(_height);
		m_String[i]->SetFontWidth(_width);
	}
}