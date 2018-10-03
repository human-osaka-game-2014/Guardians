#ifndef _GAME_EQUIP_WINDOW_H_
#define _GAME_EQUIP_WINDOW_H_

#include <string>

class CGameEquipWindow : public CGameWindow
{
private:


	static const D3DXVECTOR2 CURSOR_INIT_POSITION;	// �J�[�\���������W
	static const D3DXVECTOR2 EQUIP_POSITION;		// �u�����v�`����W
	static const D3DXVECTOR2 EQUIP1_POSITION;		// �u1�ڂ̑����v�`����W
	static const D3DXVECTOR2 TOOL_POSITION;			// �u����v�`����W
	static const D3DXVECTOR2 TOOL1_POSITION;		// �u1�ڂ̓���v�`����W

	static const int MAX_WIDTH_CHARA	= 530;		// �E�B���h�E�ő啝(�L�����Z���N�g)
	static const int MAX_HEIGHT_CHARA	= 450;		// �E�B���h�E�ő卂��(�L�����Z���N�g)
	static const int MAX_WIDTH_STATUS	= 535;		// �E�B���h�E�ő啝(�X�e�[�^�X)
	static const int MAX_HEIGHT_STATUS	= 480;		// �E�B���h�E�ő卂��(�X�e�[�^�X)
	
	CTexture	        m_textureicon[2];	//�A�C�e��,�����A�C�R��
	CGameData*			m_pGameData;		// �Q�[���f�[�^�̎Q��
	CGameItemCursor*	m_pCursor;			// �I��p�J�[�\��
	int					m_charaID;			// �L�����N�^�[ID
	int					m_menuID;			// ���j���[ID
	int					m_selectEquipID;

public:
	CGameEquipWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^�A���j���[ID���Z�b�g)
	~CGameEquipWindow();
	void Control();																								// ����
	void Draw();										// �`��
	void SetSelectEquipID(int _selectEquipID);// �I������Ă��鑕����ID���Z�b�g								
	void SetCharaID(int _charaID);
};

#endif