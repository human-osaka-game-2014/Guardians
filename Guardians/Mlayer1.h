#ifndef _LAYER1_H_
#define _LAYER1_H_

class CLayer1 : public CLayer 
{
private:

public:
	CLayer1(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif