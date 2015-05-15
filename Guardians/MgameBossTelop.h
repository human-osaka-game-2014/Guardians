#ifndef _GAME_BOSS_TELOP_H_
#define _GAME_BOSS_TELOP_H_


class CGameBossTelop : public CGameTelop
{
	static const D3DXVECTOR2 BOSSNAME_POSITION;	// 「ボス名」描画位置
	static const float TELOP_HEIGHT;			// テロップの高さ
	static const float TELOP_MAX_WIDTH;			// テロップ最大幅
//	static const int TEX_BOSS_ID = 0;
	CTexture         m_bossTex;

	int m_stageID;	// ステージ番号

public:
	CGameBossTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID);	// コンストラクタ(デバイス、座標、ステージIDをセット)
	~CGameBossTelop();
	void Control();																		// 制御
	void Draw();																		// 描画

};

#endif