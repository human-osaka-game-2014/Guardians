#ifndef _LAYER3_H_
#define _LAYER3_H_

class CLayer3 : public CLayer
{
private:

public:
	CLayer3(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif