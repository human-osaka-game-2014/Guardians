#ifndef _CHIP_H_
#define _CHIP_H_

class CChip
{
public:
	static const int ANIM_TIME = 60*2;	// �P���̉摜���\������鎞��(2�b=120frame)(�d�l�ɂȂ��̂ł��Ƃŕ���)

	enum ChipType
	{
		STAGE1BOSS,
		STAGE2BOSS,
		STAGE3BOSS,
		STAGE4BOSS,
		STAGE5BOSS,
		STAGE6BOSS,
		START,		// �J�n�n�_
		CHECKPOINT_NOCLEAR,	//���N���A�̃`�b�N�|�C���g�i���j
		CHECKPOINT_CLEAR,	//�N���A�ς݂̃`�b�N�|�C���g�i�j���X�^�[�g�|�C���g
		ROAD_LINE,			//�i�s���C��
		SHADOW,				//�e
		MONSCHIP_STAGE1BOSS,		
		MONSCHIP_STAGE2BOSS,
		MONSCHIP_STAGE3BOSS,
		MONSCHIP_STAGE4BOSS,
		MONSCHIP_STAGE5BOSS,
		MONSCHIP_STAGE6BOSS,
		CHIP_MAX,
	};
protected:
	static const FRECT animRect[];
	static const int ANIM_NO_LIST[];		// �A�j���[�V��������
	FRECT				rect;
	FRECT				shadowRect;
	LPDIRECT3DDEVICE9	m_pDevice;			// �`��f�o�C�X
	D3DXVECTOR2			m_position;			// ���W
	D3DXVECTOR2			m_cameraPosition;	// �J����(�}�b�v���W)
	ChipType			m_type;				// �`�b�v�^�C�v
	int					m_time;				//�����A�j���[�V�����Ԋu			
	int					m_animeCount;		//�����A�j���[�V�����p
	bool				m_animFlag;			// �A�j���[�V�����̗L��
	int					m_animCount;		// �A�j���[�V�����J�E���g
	int					m_animID;			// �A�j���[�V����ID(���݉����ڂ̉摜��)
	CVertex				m_vertex;			// ���_���Ǘ�
	// �e�N�X�`���Ǘ��N���X���ł���܂ŉ��ł����ɍ쐬
	CTexture			m_texture;			// �摜
	CTexture			m_animTexture;		// �摜
	CTexture			m_shadowtexture;	// �摜

	void MoveAnimation();
public:
	CChip(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, ChipType _type, bool _animFlag = false);	// �R���X�g���N�^(�f�o�C�X�A���W�A�`�b�vID�A�A�j���[�V�����̗L�����Z�b�g)
	virtual void Control();																				// ����
	void SetAnimePosition();																			//�A�j���t���O��on,off
	virtual void Draw();																						// �`��

	// �A�N�Z�b�T
	void SetCameraPosition(D3DXVECTOR2 _cameraPosition);
	void SetAnimeFlag(bool _animFlag);
	void ChangeType(ChipType _type);
};

#endif