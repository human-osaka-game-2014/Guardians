#ifndef _DEFINE_H_
#define _DEFINE_H_

/*--------------------------------------------------------------

	�������e: �萔�̐錾
	�쐬��: �h��
	�쐬��:9/24
	�X�V��:10/11
	�X�V���e:
	�ϐ��@
		enum PIC_ID�̒ǉ�
		�����摜�z��̒ǉ��@0~9
		INIT���W�̏C��

--------------------------------------------------------------*/
const int CHECK_POINT_NUM = 24;

typedef struct FRECT{
		float left;
		float top;
		float right;
		float bottom;

		FRECT() {
		}

		FRECT(float l, float t, float r, float b) {
			left = l;
			top = t;
			right = r;
			bottom = b;
		}
}FRECT;

enum CHARACTER
{
	ALDO,	// �A���h�E�E
	MINE, // �~�l���E�E
	NERU_MARU,// �l���}��

};

enum State
{
	STATE_MENU_MOVE,		// ���j���[�ړ����
	STATE_CHANGE_ITEM,
	STATE_CHARA_SELECT,		// �L�����o���I��
	STATE_STAGE_SELECT,		// �X�e�[�W�I��(�������)
	STATE_VIEW_STATUS,		// �X�e�[�^�X�\��
	STATE_SHOP,				// �V���b�v
	STATE_SAVE,				// �Z�[�u
	STATE_TO_BATTLE,		// �퓬��ʂ�
	STATE_CLEAR,			// �퓬�N���A��̎��̃X�e�[�W���o
	STATE_CAMERA_MOVE,		// ���̃X�e�[�W���o���������Ƃ̃J�����ړ�
	// ���U���g�p
	STATE_MONEY,	// �l�������\��
	STATE_BONUS,	// �l���{�[�i�X�\��
	STATE_NEXTSCENE,// ���̐퓬�ւ�������
};

enum TEX_ID {	// �e�N�X�`���ԍ�
	TEX_BOSS,
	TEX_BUTTON_ICON,
	TEX_CHARA_MENU,
	TEX_FIELD_MENU,
	TEX_MAP,
	TEX_MAP_CHIP,
	TEX_MONSTER_CHIP,
	TEX_ROAD_LINE,
	TEX_TELOP,
	TEX_WINDOW,
	TEX_CURSOR,			// 10/16 �ǉ� �h��
	TEX_CHARA_ICON,		// 11/6�@�ǉ��@��
	TEX_EQUIP_ICON,		// 11/6  �ǉ��@��
	TEX_ITEM_ICON,		// 11/6�@�ǉ��@��
	TEX_BATTLE_UI,
	NO,
	TEX_BATTLE_BLACK,
	TEX_BATTLE_ENEMY_HP,

};


enum PIC_ID {
	PIC_0,
	PIC_1,
	PIC_2,
	PIC_3,
	PIC_4,
	PIC_5,
	PIC_6,
	PIC_7,
	PIC_8,
	PIC_9,
};
enum KEYKIND {
	LEFT = 1,
	RIGHT = 2,
	UP = 4,
	DOWN = 8,
	KEY_Q = 16,
	KEY_T = 32,
	KEY_Z = 64,
	KEY_B = 128,
	KEY_A = 256,
	// �ȉ�11/24 �ǉ�
	KEY_S = 512,
	KEY_W = 1024,
	KEY_D = 2048,
	KEY_E = 4096,
	KEY_SPACE = 8192,
	KEYMAX,
};

//�T�[�`�p
enum ItemType{
	TYPE_EQUIP,
	TYPE_ITEM,
};

const int PLAYER_MAX  = 3;  // ����ł���L�����N�^�[��3��
const int ENEMY_MAX = 4;	// �P�X�e�[�W���̓G�̐���4��
const D3DXVECTOR3 INIT_PLAYER_POSITION = D3DXVECTOR3(5,0,0);
const D3DXVECTOR3 INIT_ENEMY_POSITION  = D3DXVECTOR3(40.f,0.f,0.f);

const float INIT_SCALE = 1.0f;
// �N���C�A���g�T�C�Y(�ǉ�)
const int CLIENT_WIDTH = 1280;
const int CLIENT_HEIGHT = 720;

const int ANIME_TIME = 10;			//�����G�t�F�N�g���ԊԊu
const int MON_ANIME_TIME = 20;		//�����X�^�[�A�j���[�V�������ԊԊu										
const int ALFA_ANIME_TIME = 1;		//�{�X�t�F�[�h�C�����ԊԊu
const int POINT_ANIME_TIME = 15;	//�|�C���^�����G�t�F�N�g���ԊԊu

// �E�C���h�E�̏������W
const D3DXVECTOR2 INIT_STATUS_WINDOW_POSITION		= D3DXVECTOR2(100.f+280.f, 60.f+260.f);
const D3DXVECTOR2 INIT_EQUIP_WINDOW_POSITION		= D3DXVECTOR2(730.f+255.f, 173.f+240.f+5.f);
const D3DXVECTOR2 INIT_SHOPMENU_WINDOW_POSITION		= D3DXVECTOR2(100.f+125.f, 65.f+145.f);
const D3DXVECTOR2 INIT_SAVE_WINDOW_POSITION         = D3DXVECTOR2(675.f,320.f);  

// �e���b�v�̏������W
const D3DXVECTOR2 INIT_EXPLAIN_TELOP_POSITION		= D3DXVECTOR2(64.f, 615.f);
const D3DXVECTOR2 INIT_CHARA_TELOP_POSITION			= D3DXVECTOR2(730.f,43.f);
const D3DXVECTOR2 INIT_BOSS_TELOP_POSITION			= D3DXVECTOR2(950.f,40.f);

// �J�[�\���̏������W
const D3DXVECTOR2 INIT_SHOP_CURSOR_POSITION			= D3DXVECTOR2(100.f+15.f, 72.f+128.f/2);
const D3DXVECTOR2 INIT_SHOPLIST_CURSOR_POSITION		= D3DXVECTOR2(450,75.f+128.f/2);																					

const D3DXVECTOR2 INIT_CHARA_CURSOR_POSITION		= D3DXVECTOR2(730.f, 40.f);				// �L�����I���J�[�\�������ʒu
const D3DXVECTOR2 INIT_EQUIP_CURSOR_POSITION		= D3DXVECTOR2(730.f+100.f,173.f+30.f);	// �����I�����̃J�[�\���̏����ʒu
const D3DXVECTOR2 INIT_ITEM_CURSOR_POSITION			= D3DXVECTOR2(730.f+110.f,173.f+220.f);		// �A�C�e�����ڑI�����̏����ʒu
const D3DXVECTOR2 INIT_CHANGE_CURSOR_POSITION		= D3DXVECTOR2(800.f+30.f,173.f+30.f);		// �����ύX���̃J�[�\���̏����ʒu
const D3DXVECTOR2 INIT_DATA_CURSOR_POSITION			= D3DXVECTOR2(130.f,172.f);        // DATA�I��p�J�[�\���̏����ʒu
const D3DXVECTOR2 INIT_DATAPART_CURSOR_POSITION		= D3DXVECTOR2(230.f,100.f);        // PART�I��p�J�[�\���̏����ʒu
const D3DXVECTOR2 INIT_SELECT_CURSOR_POSITION		= D3DXVECTOR2(520.f,260.f);        // PART�I��p�J�[�\���̏����ʒu
																							
// 10/30�ǋL�@�t�H���g��
static const wchar_t* FONT_FAMILY = L"�l�r �S�V�b�N";	// 10/30 �ǋL
#endif