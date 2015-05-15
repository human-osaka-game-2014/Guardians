#ifndef _CHIP_MONSTER_H_
#define _CHIP_MONSTER_H_

#include "chip.h"

class CChipMonster : public CChip
{
private:
	enum {
		STATE_FEEDIN,
		STATE_ANIMATION,
	};
public:
	int m_state;			// チップの状態
	static const FRECT	monAnimRect[];
	FRECT m_animRect;		// 表示矩形
	int  m_alpha;			//アルファ値
	int  m_alphaSpeed;		//アルファ値増加間隔
	CChipMonster(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,ChipType _type, bool _isAnim);	// コンストラクタ(デバイス、座標、チップIDをセット)
	void Control();
	void Draw();
};

#endif