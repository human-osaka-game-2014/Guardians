#include "stdafx.h"

CFontPolygon::CFontPolygon(LPDIRECT3DDEVICE9 _pDevice) : 
m_pDevice( _pDevice )
{
	// �P�ʃt�H���g�|���S���쐬
    Vtx vtx[4] = {
            {0.0f, -1.0f, 0.5f,   0.0f, 1.0f},
            {0.0f,  0.0f, 0.5f,   0.0f, 0.0f},
            {1.0f, -1.0f, 0.5f,   1.0f, 1.0f},
            {1.0f,  0.0f, 0.5f,   1.0f, 0.0f},
    };
    Vtx *p = 0;
    _pDevice->CreateVertexBuffer( sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, 0 );
    pVertexBuffer->Lock(0, 0, (void**)&p, 0);
    memcpy( p, vtx, sizeof(vtx) );
    pVertexBuffer->Unlock();
}

void CFontPolygon::Draw( float x, float y, CTexCharacter* _texChar  )
{
	 // �e��s��
    D3DXMATRIX localScale;
	D3DXMatrixScaling( &localScale, (float)_texChar->getFontWidth(), (float)_texChar->getFontHeight(), 1.0f );
    D3DXMATRIX localOffset;
	D3DXMatrixTranslation( &localOffset, (float)_texChar->getGm().gmptGlyphOrigin.x, (float)_texChar->getGm().gmptGlyphOrigin.y, 0.0f );
    D3DXMATRIX localMat = localScale * localOffset;

    D3DXMATRIX world;
    D3DXMATRIX worldOffset;
	x -= 1280 / 2 ;
	y -= 720 / 2 - _texChar->getFontSize() / 3;
	y *= -1;
    D3DXMatrixTranslation( &worldOffset, x - 0.5f, y + 0.5f, 0.0f );
    world = localMat * worldOffset;

    D3DXMATRIX ortho;
    D3DXMatrixOrthoLH( &ortho, 1280, 720.f, 0.0f, 1000.0f );
    m_pDevice->SetTransform( D3DTS_PROJECTION, &ortho );

	// ���C�g�̓I�t��
    m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Z�\�[�g�̓I�t
	m_pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

    // ���u�����h�ݒ�
    m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    m_pDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// �`��
    m_pDevice->SetTransform( D3DTS_WORLD, &world );
    m_pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vtx));
    m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
	m_pDevice->SetTexture( 0, _texChar->getTexture() );
    m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	// �`��I������Z�\�[�g�̓I��
	m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	// ���C�g�̓I�t��
    m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

}