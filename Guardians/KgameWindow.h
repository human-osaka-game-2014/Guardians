#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

class CGameWindow
{
public:
	enum SelectType {	// �I�����ꂽ�^�C�v
		EQUIP,			// ����
		TOOLS,			// ����
	};
enum State			// �E�B���h�E�̏��
	{
		STATE_WAIT,		// �����Ă��Ȃ����
		STATE_SPREAD,	// �L�����Ă�����
		STATE_MOVE,		// �ړ����Ă�����
	};

protected:
	static const D3DXVECTOR2 NOMOVE_PARTS_SIZE;	// �L����ۂɕϓ����Ȃ������̃T�C�Y(�S��) 

	static const int SPREAD_TIME = 10;		// �ő�T�C�Y�ɂȂ�܂ł̎���(10frame)
	static const int MOVE_TIME = 10;		// �ړ�����(10frame)
	static const int TEX_GAME_WINDOW = 7;

	enum Direction		// ����
	{
		DIR_HORIZONTAL,	// ��������
		DIR_VIRTICAL,	// ��������
	};

    LPDIRECT3DDEVICE9	m_pDevice;		// �`��f�o�C�X
	D3DXVECTOR2			m_position;		// ���S���W
	D3DXVECTOR2			m_nextPosition;	// �ړ�����W
	Direction			m_direction;	// �i�ޕ���
	State				m_state;		// ���
	float				m_width;		// ��
	float				m_height;		// ����
	float				m_maxWidth;		// �ő啝
	float				m_maxHeight;	// �ő卂��
	float				m_spreadWidth;	// ���(1frame)�ɍL���镝
	float				m_spreadHeight;	// ���(1frame)�ɍL���鍂��
	float				m_move;			// ���(1frame)�̈ړ���
	bool				m_cursorFlag;	// �J�[�\���̗L��
	bool				m_scrollFlag;	// �X�N���[���̗L��
	bool				m_moveFlag;		// �ړ������ǂ���
	int					m_textureID;	// �g�p�摜ID
	int					m_charaID;
	int					m_selectEquipID;
	CGameData*			m_pGameData;
	CVertex				m_vertex;		// ���_���W�Ǘ�
	// �e�N�X�`���Ǘ��N���X���ł���܂ŉ��ł����ɍ쐬
	CTexture			m_texture;		// �摜
public:
	
	CGameWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth, float _maxHeight, D3DXVECTOR2 _nextPosition = D3DXVECTOR2(-1.f,-1.f) );	// �R���X�g���N�^(�f�o�C�X�A���W�A�ő啝�A�����A�ړ���̈ʒu���Z�b�g)
	
	virtual ~CGameWindow();
	virtual void Control();																						// ����
	virtual void Draw();																						// �`��
	// �A�C�e���T�[�`
	int Search(int _itemNum,ItemType _type);
	// �A�N�Z�b�T
	void SetNextPosition(D3DXVECTOR2 _nextPosition);			// �ړ���̍��W���Z�b�g
	bool IsMove();												// �ړ������ǂ������擾	

	//�Q�b�^
	// �E�C���h�E�̏�Ԃ��擾
	State Get();
	// �Q�[���f�[�^���Z�b�g
	void SetGameData(CGameData* _pGameData);
};

#endif