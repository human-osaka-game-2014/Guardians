#ifndef _GAME_BOSS_TELOP_H_
#define _GAME_BOSS_TELOP_H_


class CGameBossTelop : public CGameTelop
{
	static const D3DXVECTOR2 BOSSNAME_POSITION;	// �u�{�X���v�`��ʒu
	static const float TELOP_HEIGHT;			// �e���b�v�̍���
	static const float TELOP_MAX_WIDTH;			// �e���b�v�ő啝
//	static const int TEX_BOSS_ID = 0;
	CTexture         m_bossTex;

	int m_stageID;	// �X�e�[�W�ԍ�

public:
	CGameBossTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID);	// �R���X�g���N�^(�f�o�C�X�A���W�A�X�e�[�WID���Z�b�g)
	~CGameBossTelop();
	void Control();																		// ����
	void Draw();																		// �`��

};

#endif