/**
 * @file DgameCursor.h
 */

/**
 * �J�[�\���̐���
 */

#ifndef _GAME_CURSOR_H_
#define _GAME_CURSOR_H_

class CGameCursor
{
public:
	enum State		// �J�[�\���̏��
	{
		STATE_WAIT,		// �����Ă��Ȃ����(���ł͂��Ă���)
		STATE_MOVE,		// ��or�c�Ɉړ����Ă�����
	};
	static const D3DXVECTOR2 NOMOVE_PARTS_SIZE;			//�L����ۂɕϓ����Ȃ������̃T�C�Y(���P��(24�~24) 
protected:
	static const int MOVE_TIME		= 5;	// �ړ�����(5frame)
	static const int FLICKER_TIME	= 60;	// ���Ŏ���(2�b=120frame)

	enum Direction	// ����
	{
		DIR_HORIZONTAL,	// ��������
		DIR_VIRTICAL,	// ��������
		DIR_DIAGONAL,	//�΂ߕ���
	};
	enum FadeType	//�_�ŏ��
	{
		FADE_IN,		
		FADE_OUT,
	};
	typedef struct _RECT
	{
		float left;
		float top;
		float right;
		float bottom;
	}RECT;

	RECT				m_rect;			//�e�N�X�`�����W
	CVertex				m_vertex;		// Vertex�N���X�I�u�W�F�N�g
	CTexture			m_texture;		// �e�N�X�`���N���X�I�u�W�F�N�g
	
	LPDIRECT3DDEVICE9	m_pDevice;		// �`��f�o�C�X
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���f�o�C�X

	D3DXVECTOR2			m_position;		// ���W
	D3DXVECTOR2			m_nextPosition;	// �ړ�����W
	FadeType			m_fadeType;		// �_�ŏ��
	Direction			m_direction;	// �i�ޕ���
	State				m_state;		// ���
	
	float				m_moveX;			// ���(1frame)�̈ړ���
	float				m_moveY;
	bool				m_flickFlag;	// �_�ł��邩�ǂ����̃t���O
	int					m_itemMax;		// �I�����ڍő吔
	int					m_selectID;		// �I������Ă��鍀�ڂ̔ԍ�
	int					m_alpha;		// ���l(���ŃA�j���[�V�����Ɏg�p)
	int					m_addAlpha;		// ���ϓ��l
	int					m_count;		// �_�ŃA�j���[�V�����̃J�E���g
public:
	CGameCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// �R���X�g���N�^(�f�o�C�X�A���W�A�g�p�摜ID���Z�b�g)
	virtual ~CGameCursor();
	void Control();																	// ����
	virtual void Draw();																	// �`��
	void ControlFlicker();															// �_�ł̐���
	void Move();																	// �ړ�
	// �A�N�Z�b�T
	void SetNextPosition(D3DXVECTOR2 _nextPosition);								// �ړ���̍��W���Z�b�g
	int GetSelectID();																// �I������Ă��鍀�ڔԍ����擾
	int GetState();																	// ��Ԃ��擾
};

#endif