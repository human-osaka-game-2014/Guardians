#ifndef _GAME_DATA_WINDOW_H_
#define _GAME_DATA_WINDOW_H_

class CGameDataWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 WINDOW_POSITION;	// �u�E�B���h�E�v�ړ�����W
	static const D3DXVECTOR2 TIME_POSITION;		// �u�v���C���ԁv�`����W
	static const D3DXVECTOR2 MONEY_POSITION;	// �u�������v�`����W

	static const int MAX_WIDTH	= 270+128;		// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 256;			// �E�B���h�E�ő卂��
	
	DWORD					m_digits;			// Money�����i�[�p
	
	CGameData* m_pGameData;		// �Q�[���f�[�^�̎Q��
public:
	CGameDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^���Z�b�g)
	~CGameDataWindow();
	void Control();																				// ����
	void Draw();																				// �`��

};

#endif