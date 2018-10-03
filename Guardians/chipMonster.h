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
	int m_state;			// �`�b�v�̏��
	static const FRECT	monAnimRect[];
	FRECT m_animRect;		// �\����`
	int  m_alpha;			//�A���t�@�l
	int  m_alphaSpeed;		//�A���t�@�l�����Ԋu
	CChipMonster(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,ChipType _type, bool _isAnim);	// �R���X�g���N�^(�f�o�C�X�A���W�A�`�b�vID���Z�b�g)
	void Control();
	void Draw();
};

#endif