#ifndef _GAME_STATUS_WINDOW_H_
#define _GAME_STATUS_WINDOW_H_


class CGameStatusWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 STT_NAME_POSITION;		// �u���O�v�`����W
	static const D3DXVECTOR2 STT_MAXHP_POSITION;	// �u�ő�HP�v�`����W
	static const D3DXVECTOR2 STT_MAXMP_POSITION;	// �u�ő�MP�v�`����W
	static const D3DXVECTOR2 STT_ATK_POSITION;		// �u�U���́v�`����W
	static const D3DXVECTOR2 STT_DEF_POSITION;		// �u�h��́v�`����W
	static const D3DXVECTOR2 STT_SPD_POSITION;		// �u���x�v�`����W
	static const D3DXVECTOR2 STT_INS_POSITION;		// �u�u���́v�`����W
	static const D3DXVECTOR2 STT_CHARA_POSITION;	// �u�L�����摜�v�`����W
	static const int MAX_WIDTH	= 560;				// �E�B���h�E�ő啝
	static const int MAX_HEIGHT = 520;				// �E�B���h�E�ő卂��

	enum ChangeType			// �\�͕ω��^�C�v
	{
		UP,
		DOWN,
	};

	enum StatusType			// �\�̓^�C�v
	{
		STT_HP,
		STT_MP,
		STT_ATTACK,			// �U����
		STT_DEFENCE,		// �h���
		STT_SPEED,			// ���x
		STT_INSTANTANEOUS,	// �u����
		STT_TYPE_MAX,		// �\�͂̎��
	};
	struct ChangeStatus		// �\�͕ω�
	{
		ChangeType	type;		// �ω��^�C�v(�㏸or���~)
		bool		isDecide;	// ���肳��Ă��邩�ǂ���
		int			power;		// �ω���
	};

	CGameData*			m_pGameData;				// �Q�[���f�[�^�̎Q��
	ChangeStatus		m_chgStatus[STT_TYPE_MAX];	// �\�͕ω�
	int					m_charaID;					// �L�����N�^�[ID
	int					m_selectEquipID;			// �I������Ă��鑕����ID
	int					m_hp;						//HP
	int					m_mp;						//MP
	int					m_atk;						//�U����	
	int					m_def;						//�����
	int					m_spd;						//���x��
	int					m_ins;						//�u����

	// 11/1 �ǉ�
	CTexture			m_texChara;					// �L�����N�^�[�C���[�W
public:
	CGameStatusWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData);	// �R���X�g���N�^(�f�o�C�X�A���W�A�Q�[���f�[�^���Z�b�g)
	~CGameStatusWindow();
	void Control();																					// ����
	void Draw();																					// �`��

	// �A�N�Z�b�T
	void SetSelectEquipID(int _selectEquipID);														// �I������Ă��鑕����ID���Z�b�g
	void SetCharaID(int _charaID);																	// �L�����N�^�[ID���Z�b�g
};

#endif