#include "stdafx.h"


CBillBoard::~CBillBoard()
{
	//SAFE_RELEASE(m_buffer);
}
void CBillBoard::Draw(LPDIRECT3DDEVICE9 _pDevice,CTexture _texture,D3DXVECTOR3 _pos,float _scale,D3DXMATRIX _attitude,D3DCOLOR _color)
{
	Draw(_pDevice,_texture,_pos,_scale,FRECT(0.f,0.f,_texture.GetWidth(),_texture.GetHeight()),_attitude,_color);
}
void CBillBoard::Draw(LPDIRECT3DDEVICE9 _pDevice,CTexture _texture,D3DXVECTOR3 _pos,float _scale,FRECT _rect,D3DXMATRIX _attitude,D3DCOLOR _color)
{
	// �e�N�X�`�����W�ɕϊ�
	float u1 = _rect.left / _texture.GetWidth();
	float u2 = _rect.right / _texture.GetWidth();
	float v1 = _rect.top / _texture.GetHeight();
	float v2 = _rect.bottom / _texture.GetHeight();

	// �T�C�Y�v�Z
	float width = abs(_rect.right - _rect.left);
	float height = abs(_rect.bottom - _rect.top);

	D3DXVECTOR2 texRatio = D3DXVECTOR2(1.0f, height / width);
	BILLVERTEX vertex[] = {
		{  D3DXVECTOR3(-texRatio.x, -texRatio.y, 0), _color,D3DXVECTOR2(u1, v1) },
		{  D3DXVECTOR3( texRatio.x, -texRatio.y, 0), _color,D3DXVECTOR2(u2, v1) },
		{  D3DXVECTOR3( texRatio.x,  texRatio.y, 0), _color,D3DXVECTOR2(u2, v2) },
		{  D3DXVECTOR3(-texRatio.x,  texRatio.y, 0), _color,D3DXVECTOR2(u1, v2) },
	};

	D3DXMATRIX matWorld,matTrans,matScale;	
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans,_pos.x,_pos.y,_pos.z);
	D3DXMatrixScaling(&matScale,_scale,_scale,0);
	matWorld = _attitude;
	matWorld = matWorld * matScale * matTrans;

	_pDevice->SetTransform(D3DTS_WORLD,&matWorld);
	// ���C�g�̓I�t
	_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	// ���u�����h�ݒ�
	_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	_pDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		// �|���S���̓����x���e�N�X�`���ɔ��f
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// ���ʕ`�惂�[�h�̎w��
	_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//// �y��r���s�Ȃ�
	_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		// �f�B�U�����O���s�Ȃ��i���i���`��j
	_pDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE);
	// �`��
	_pDevice->SetTexture(0,_texture.Get());
	_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertex,sizeof(BILLVERTEX));

	// ���C�g���I���ɖ߂�
	_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}