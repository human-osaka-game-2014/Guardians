#ifndef _GAME_STAGE_TELOP_H_
#define _GAME_STAGE_TELOP_H_


class CGameStageTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 STAGENAME_POSITION;	// 「ステージ名」描画位置
	static const float TELOP_HEIGHT;				// テロップの高さ
	static const float TELOP_MAX_WIDTH;				// テロップ最大幅
	static const int TEX_STAGE_ID = 3;
	CTexture         m_stageTex;

	int m_stageID;	// ステージ番号

public:
	CGameStageTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _stageID);	// コンストラクタ(デバイス、座標、ステージIDをセット)
	~CGameStageTelop();
	void Control();																		// 制御
	void Draw();																		// 描画

};

#endif