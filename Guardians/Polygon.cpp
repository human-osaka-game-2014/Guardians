#include "stdafx.h"

//const DWORD CPolygon::CUSTOM_FVF;

CPolygon::CPolygon(LPDIRECT3DDEVICE9 pDevice) :
m_pDevice(pDevice)
{

}

void CPolygon::Draw(LPDIRECT3DTEXTURE9 pTexture, float x, float y, float w, float h, DWORD color) {
	CustomVertex v[] = {
		{x - w/2, y - h/2, 0.5f, 1.f, color, 0.f, 0.f},
		{x + w/2, y - h/2, 0.5f, 1.f, color, 1.f, 0.f},
		{x + w/2, y + h/2, 0.5f, 1.f, color, 1.f, 1.f},
		{x - w/2, y + h/2, 0.5f, 1.f, color, 0.f, 1.f},
	};

	// テクスチャセット
	m_pDevice->SetTexture(0, pTexture);
	//m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// レンダリングステート
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetFVF(CUSTOM_FVF);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}