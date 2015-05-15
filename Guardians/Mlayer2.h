#ifndef _LAYER2_H_
#define _LAYER2_H_

class CLayer2 : public CLayer
{
private:
	
public:
	CLayer2(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif