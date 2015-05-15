#ifndef _LAYER5_H_
#define _LAYER5_H_

class CLayer5 : public CLayer
{
private:

public:
	CLayer5(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif