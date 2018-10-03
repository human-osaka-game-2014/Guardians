#ifndef _GAME_TELOP_H_
#define _GAME_TELOP_H_

class CGameTelop
{
protected:
	static const int SPREAD_TIME = 60 * 1;	// �ő�T�C�Y�ɂȂ�܂ł̎���(1�b=60frame)
	static const int TEX_ID = 8;			// ���ƂŕύX

	enum State			// �e���b�v�̏��
	{
		STATE_WAIT,		// �����Ă��Ȃ����
		STATE_SPREAD,	// �L�����Ă�����
	};

	LPDIRECT3DDEVICE9	m_pDevice;		// �`��f�o�C�X
	D3DXVECTOR2			m_position;		// ���W
	State				m_state;		// ���
	float				m_width;		// ��
	float				m_height;		// ����
	float				m_maxWidth;		// �ő啝
	float				m_spreadWidth;	// ���(1frame)�ɍL���镝
	CVertex             m_vertex;
	CTexture            m_tex;

public:
	CGameTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth);		// �R���X�g���N�^(�f�o�C�X�A���W�A�ő啝���Z�b�g)
	virtual ~CGameTelop(){};
	virtual void Control(){};															// ����
	virtual void Draw();																		// �`��

	// �A�N�Z�b�T
	void SetMaxWidth(float _maxWidth);													// �ő啝���Z�b�g
};

#endif