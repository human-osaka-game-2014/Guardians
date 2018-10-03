#ifndef _GAME_MAP_POINTER_H_
#define _GAME_MAP_POINTER_H_


class CGameMapPointer:public CChip
{
public:
		enum State	// �}�b�v�|�C���^�̏��
	{
		STATE_WAIT,		// �����Ă��Ȃ����(�㉺�ɗh���/�A�j���[�V�����͍s��)
		STATE_MOVE,
		STATE_MOVE_RIGHT,		// �`�b�v�Ԃ��ړ����Ă�����
		STATE_MOVE_LEFT,
	};
private:
	static const int ANIM_TIME = 60 * 1;	// �P���̉摜���\������鎞��(�d�l�ɂȂ��̂ł��Ƃŕ���)
	static const int SLIDE_TIME = 5;		// �_�Ԉړ�����(5frame)
	static const int MOVE_TIME = 60*3;		// �㉺�ړ�����(3�b=180frame)
	static const FRECT	pointAnimRect[];
	static const int POINT_ANIM_NO[];			// �A�j���[�V�����̏���

	static const int POINTER_MOVE_FRAME = 60;	// �|�C���^�[�̈ړ�����
	static const D3DXVECTOR2 m_checkPointPos[CHECK_POINT_NUM];
	static const D3DXVECTOR2 POINTER_SIZE;
//	std::vector<D3DXVECTOR2>			m_position;			//���I�ȍ��W
	std::vector<D3DXVECTOR2>			m_staticPosition;	//�ÓI�ȍ��W
	D3DXVECTOR2			m_nextPosition;	// �ړ�����W
	D3DXVECTOR2			m_move;			// ���(1frame)�̈ړ���
	State				m_state;		// ���
	float				m_shake;		// ��or���h����
	float				m_shakeSpeed;	// ����ʂ̑���
	int					m_shakeCount;	// ��or���h���J�E���g
	int					m_animID;		// �A�j���[�V�����ԍ�(���݉����ڂ̉摜��)
	int					m_animCount;	// �A�j���[�V�����J�E���g
	int					m_pCount;		//�|�C���^�̉摜�ԍ�
	int					m_pTime;		//�|�C���^�_�Ŏ��ԊԊu
	int					m_clearCount;	//�`�F�b�N�|�C���g�N���A�L��
	int					m_checkPointNum;	//�`�F�b�N�|�C���g�̔ԍ�
	int					m_nextCheckPointNum;	//���̃`�F�b�N�|�C���g�̔ԍ�
	int					m_backCount;			//�߂�Ƃ��̈ړ�����W����̂���
	//int					m_selectStageNum;
	int					m_pMoveTime;
	CTexture			m_pointTexture;
	CVertex				m_vertex;

	CGameData*			m_pGameData;
public:
	CGameMapPointer(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,int clearStageNum,CGameData* _pGameData);	// �R���X�g���N�^(�f�o�C�X�A���W���Z�b�g)
	void Control();														// ����
	void Draw();														// �`��

	// �A�N�Z�b�T
	void SetNextPosition(D3DXVECTOR2 _nextPosition);					// �ړ���̍��W���Z�b�g
	void SetClearCount(int _clearCount);								//�`�F�b�N�|�C���g�N���A�L�^�Z�b�g
	void SetMoveDirection(State _state);								//�i�s�����Z�b�g
	State GetState();													//�|�C���^�̏�Ԃ��Z�b�g
};

#endif