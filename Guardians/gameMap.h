#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

class CGameMap
{
private:
	enum {
		CHIP_MAX = 32,		// �`�b�v���@	���삪�i�ނɂ�đ����\��
		STAGE_MAX = 18,		// �X�e�[�W��	���삪�i�ނɂ�đ����\��
	};
	enum {
		STATE_CHECKMOVE,	// �`�F�b�N�|�C���g�ړ����
		STATE_MAPMOVE,		// �}�b�v�ړ����
		STATE_POINTMOVE,	// �}�b�v�J�[�\���ړ����
		STATE_MP,			// �}�b�v�ƃJ�[�\���𓯎��Ɉړ�������
	};
	struct ChipData {
		D3DXVECTOR2 position;
		CChip::ChipType type;
	};
	static const D3DXVECTOR2 INIT_CAMERA_POS;	// �����J�������W

	static const int POINT_MOVE_SPD = 5;	// �i�s�|�C���g�`�摬�x

	static const int   STAGE1_LINE_NUMLIST[];	// �X�e�[�W1�i�s���C�������X�g
	static const int   STAGE2_LINE_NUMLIST[];	// �X�e�[�W2�i�s���C�������X�g
	static const int   STAGE3_LINE_NUMLIST[];	// �X�e�[�W3�i�s���C�������X�g
	static const int   STAGE4_LINE_NUMLIST[];	// �X�e�[�W4�i�s���C�������X�g
	static const int   STAGE5_LINE_NUMLIST[];	// �X�e�[�W5�i�s���C�������X�g
	static const int   STAGE6_LINE_NUMLIST[];	// �X�e�[�W6�i�s���C�������X�g
	static const int* STAGE_LINE_NUMLIST[];		// �S�X�e�[�W�i�s���C�������X�g

	static const POINT POINT_LIST[];		// �X�e�[�W���Ƃ̐i�s�|�C���g�\����
	static const POINT CHIP_NUMLIST[];		// �X�e�[�W���Ƃ̃`�b�v�\����
	
	static const ChipData CHIP_DATA[];
	LPDIRECT3DDEVICE9	m_pDevice;			// �`��f�o�C�X
	D3DXVECTOR2			m_cameraPosition;	// �^���J�������W
	CChip*				m_pChip[CHIP_MAX];	// �`�b�v�N���X(�����X�^�[�`�b�v�܂�)
	std::vector<CChip>  m_chipPoint;
	CGameMapPointer*	m_mapPointa;
	CGameData*			m_pGameData;		// �Q�[���f�[�^
	int                 m_clearCount;		//�`�F�b�N�|�C���g�L��
	int					m_pointMin;			// �i�s�|�C���g�̕`��i�ŏ��j
	int					m_pointNow;			// ���݂̐i�s�|�C���g�̕`��ʒu
	int					m_pointMax;			// �i�s�|�C���g�̕`��i�Ō�j
	int					m_pointMoveCnt;		// �i�s�|�C���g�̕`�摬�x
	int					m_state;			// �}�b�v�̌��݂̏��
	int					m_chipMin;			// �}�b�v�`�b�v�̕`��(�ŏ�)
	int					m_chipMax;			// �}�b�v�`�b�v�̕`��(�Ō�)
	int					m_stageID;			// �X�e�[�W�ԍ�
	bool				m_threwBoss;		// �{�X�`�b�v�X���[�t���O
	CGameMapPointer::State	m_dir;

	D3DXVECTOR2			m_mapPosition;		// ���݂̃}�b�v���W(�J�����Ɏg�p)
	D3DXVECTOR2			m_nextMapPosition;	// �ړ���̃}�b�v���W(�X�e�[�W2�ȍ~�Ɏg�p)
	CVertex				m_vertex;			// ���_���W�Ǘ�

	// �e�N�X�`���Ǘ��N���X���ł���܂ŉ��ł����ɍ쐬
	CTexture			m_texture;	// �摜

	// �S�Ẵ`�b�v�ɃJ�������W�Z�b�g
	void SetCameraPositionToAllChip(D3DXVECTOR2 _cameraPosition);
public:
	CGameMap(LPDIRECT3DDEVICE9 _pDevice,CGameData* _pgameData,D3DXVECTOR2 _cameraPosition, int _stageID);	// �R���X�g���N�^(�f�o�C�X�A�J�������W���Z�b�g)
	~CGameMap();
	bool Control();														// ����
	void Draw();														// �`��
	void SetClearCount(int _clearCount);	
	CGameMapPointer* GetMapPointer();

	void SetNextPosition(int,CGameMapPointer::State _state);
};

#endif
