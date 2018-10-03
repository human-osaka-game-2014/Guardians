#ifndef _GAME_STAGE_TELOP_H_
#define _GAME_STAGE_TELOP_H_


class CGameStageTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 STAGENAME_POSITION;	// �u�X�e�[�W���v�`��ʒu
	static const float TELOP_HEIGHT;				// �e���b�v�̍���
	static const float TELOP_MAX_WIDTH;				// �e���b�v�ő啝
	static const int TEX_STAGE_ID = 3;
	CTexture         m_stageTex;

	int m_stageID;	// �X�e�[�W�ԍ�

public:
	CGameStageTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID);	// �R���X�g���N�^(�f�o�C�X�A���W�A�X�e�[�WID���Z�b�g)
	~CGameStageTelop();
	void Control();																		// ����
	void Draw();																		// �`��

};

#endif