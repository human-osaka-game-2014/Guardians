#ifndef _DEFINE_H_
#define _DEFINE_H_

/*--------------------------------------------------------------

	処理内容: 定数の宣言
	作成者: 檀上
	作成日:9/24
	更新日:10/11
	更新内容:
	変数　
		enum PIC_IDの追加
		文字画像配列の追加　0~9
		INIT座標の修正

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
	ALDO,	// アルド・・
	MINE, // ミネル・・
	NERU_MARU,// ネルマル

};

enum State
{
	STATE_MENU_MOVE,		// メニュー移動状態
	STATE_CHANGE_ITEM,
	STATE_CHARA_SELECT,		// キャラ出撃選択
	STATE_STAGE_SELECT,		// ステージ選択(初期画面)
	STATE_VIEW_STATUS,		// ステータス表示
	STATE_SHOP,				// ショップ
	STATE_SAVE,				// セーブ
	STATE_TO_BATTLE,		// 戦闘画面へ
	STATE_CLEAR,			// 戦闘クリア後の次のステージ演出
	STATE_CAMERA_MOVE,		// 次のステージが出現したあとのカメラ移動
	// リザルト用
	STATE_MONEY,	// 獲得資金表示
	STATE_BONUS,	// 獲得ボーナス表示
	STATE_NEXTSCENE,// 次の戦闘へいける状態
};

enum TEX_ID {	// テクスチャ番号
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
	TEX_CURSOR,			// 10/16 追加 檀上
	TEX_CHARA_ICON,		// 11/6　追加　岸
	TEX_EQUIP_ICON,		// 11/6  追加　岸
	TEX_ITEM_ICON,		// 11/6　追加　岸
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
	// 以下11/24 追加
	KEY_S = 512,
	KEY_W = 1024,
	KEY_D = 2048,
	KEY_E = 4096,
	KEY_SPACE = 8192,
	KEYMAX,
};

//サーチ用
enum ItemType{
	TYPE_EQUIP,
	TYPE_ITEM,
};

const int PLAYER_MAX  = 3;  // 操作できるキャラクターは3体
const int ENEMY_MAX = 4;	// １ステージ毎の敵の数は4体
const D3DXVECTOR3 INIT_PLAYER_POSITION = D3DXVECTOR3(5,0,0);
const D3DXVECTOR3 INIT_ENEMY_POSITION  = D3DXVECTOR3(40.f,0.f,0.f);

const float INIT_SCALE = 1.0f;
// クライアントサイズ(追加)
const int CLIENT_WIDTH = 1280;
const int CLIENT_HEIGHT = 720;

const int ANIME_TIME = 10;			//明減エフェクト時間間隔
const int MON_ANIME_TIME = 20;		//モンスターアニメーション時間間隔										
const int ALFA_ANIME_TIME = 1;		//ボスフェードイン時間間隔
const int POINT_ANIME_TIME = 15;	//ポインタ明減エフェクト時間間隔

// ウインドウの初期座標
const D3DXVECTOR2 INIT_STATUS_WINDOW_POSITION		= D3DXVECTOR2(100.f+280.f, 60.f+260.f);
const D3DXVECTOR2 INIT_EQUIP_WINDOW_POSITION		= D3DXVECTOR2(730.f+255.f, 173.f+240.f+5.f);
const D3DXVECTOR2 INIT_SHOPMENU_WINDOW_POSITION		= D3DXVECTOR2(100.f+125.f, 65.f+145.f);
const D3DXVECTOR2 INIT_SAVE_WINDOW_POSITION         = D3DXVECTOR2(675.f,320.f);  

// テロップの初期座標
const D3DXVECTOR2 INIT_EXPLAIN_TELOP_POSITION		= D3DXVECTOR2(64.f, 615.f);
const D3DXVECTOR2 INIT_CHARA_TELOP_POSITION			= D3DXVECTOR2(730.f,43.f);
const D3DXVECTOR2 INIT_BOSS_TELOP_POSITION			= D3DXVECTOR2(950.f,40.f);

// カーソルの初期座標
const D3DXVECTOR2 INIT_SHOP_CURSOR_POSITION			= D3DXVECTOR2(100.f+15.f, 72.f+128.f/2);
const D3DXVECTOR2 INIT_SHOPLIST_CURSOR_POSITION		= D3DXVECTOR2(450,75.f+128.f/2);																					

const D3DXVECTOR2 INIT_CHARA_CURSOR_POSITION		= D3DXVECTOR2(730.f, 40.f);				// キャラ選択カーソル初期位置
const D3DXVECTOR2 INIT_EQUIP_CURSOR_POSITION		= D3DXVECTOR2(730.f+100.f,173.f+30.f);	// 装備選択時のカーソルの初期位置
const D3DXVECTOR2 INIT_ITEM_CURSOR_POSITION			= D3DXVECTOR2(730.f+110.f,173.f+220.f);		// アイテム項目選択時の初期位置
const D3DXVECTOR2 INIT_CHANGE_CURSOR_POSITION		= D3DXVECTOR2(800.f+30.f,173.f+30.f);		// 装備変更時のカーソルの初期位置
const D3DXVECTOR2 INIT_DATA_CURSOR_POSITION			= D3DXVECTOR2(130.f,172.f);        // DATA選択用カーソルの初期位置
const D3DXVECTOR2 INIT_DATAPART_CURSOR_POSITION		= D3DXVECTOR2(230.f,100.f);        // PART選択用カーソルの初期位置
const D3DXVECTOR2 INIT_SELECT_CURSOR_POSITION		= D3DXVECTOR2(520.f,260.f);        // PART選択用カーソルの初期位置
																							
// 10/30追記　フォント名
static const wchar_t* FONT_FAMILY = L"ＭＳ ゴシック";	// 10/30 追記
#endif