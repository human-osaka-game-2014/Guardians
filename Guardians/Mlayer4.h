#ifndef _LAYER4_H_
#define _LAYER4_H_

class CLayer4 : public CLayer
{
private:

public:
	CLayer4(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif