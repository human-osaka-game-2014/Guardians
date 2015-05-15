#ifndef _CAMERA_H_
#define _CAMERA_H_


class CCamera
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;

	D3DXMATRIX m_InitMatView;
	D3DXMATRIX m_InitMatProj;
public:
	CCamera(LPDIRECT3DDEVICE9 _pDevice);
	~CCamera();
	void Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos);
};

#endif