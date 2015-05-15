#ifndef _LAYER6_H_
#define _LAYER6_H_

class CLayer6 : public CLayer
{
private:

public:
	CLayer6(LPDIRECT3DDEVICE9 _pDevice, int _stageID);

	void SetCharaSpeed(D3DXVECTOR2 _speed);

};

#endif