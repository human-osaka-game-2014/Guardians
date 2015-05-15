#ifndef _LAYER7_H_
#define _LAYER7_H_

class CLayer7 : public CLayer
{
private:

public:
	CLayer7(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif