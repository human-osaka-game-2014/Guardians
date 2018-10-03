#ifndef _GAME_CHARA_TELOP_H_
#define _GAME_CHARA_TELOP_H_


class CGameCharaTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 STAGE_CURSOR_INIT_POSITION;	// �J�[�\���������W(�o�����Ԍ��莞)
	static const D3DXVECTOR2 STATUS_CURSOR_INIT_POSITION;	// �J�[�\���������W(�X�e�[�^�X��ʎ�)
	static const D3DXVECTOR2 STAGE_CHARA1_POSITION;			// �u�X�e�[�W���j���[����1�l�ڂ̃L�����v�`��ʒu
	static const D3DXVECTOR2 STATUS_CHARA1_POSITION;		// �u�X�e�[�^�X���j���[����1�l�ڂ̃L�����v�`��ʒu

	static const float TELOP_HEIGHT;			// �e���b�v�̍���
	static const float TELOP_MAX_WIDTH;			// �e���b�v�ő啝
	//static const int TEX_CHARA_ID = 13;
	
	CTexture            m_charaTex;
	CVertex				m_vertex;	
	CGameData*			m_pGameData;		// �Q�[���f�[�^�̎Q��
	int					m_menuID;			// ���j���[ID(�X�e�[�W�I��or�X�e�[�^�X)

public:
	CGameCharaTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A���j���[ID���Z�b�g)
	~CGameCharaTelop();
	void Control();																		// ����
	void Draw();																		// �`��

};

#endif