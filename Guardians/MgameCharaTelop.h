#ifndef _GAME_CHARA_TELOP_H_
#define _GAME_CHARA_TELOP_H_


class CGameCharaTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 STAGE_CURSOR_INIT_POSITION;	// カーソル初期座標(出撃順番決定時)
	static const D3DXVECTOR2 STATUS_CURSOR_INIT_POSITION;	// カーソル初期座標(ステータス画面時)
	static const D3DXVECTOR2 STAGE_CHARA1_POSITION;			// 「ステージメニュー時の1人目のキャラ」描画位置
	static const D3DXVECTOR2 STATUS_CHARA1_POSITION;		// 「ステータスメニュー時の1人目のキャラ」描画位置

	static const float TELOP_HEIGHT;			// テロップの高さ
	static const float TELOP_MAX_WIDTH;			// テロップ最大幅
	//static const int TEX_CHARA_ID = 13;
	
	CTexture            m_charaTex;
	CVertex				m_vertex;	
	CGameData*			m_pGameData;		// ゲームデータの参照
	int					m_menuID;			// メニューID(ステージ選択orステータス)

public:
	CGameCharaTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID);	// コンストラクタ(デバイス、座標、ゲームデータ、メニューIDをセット)
	~CGameCharaTelop();
	void Control();																		// 制御
	void Draw();																		// 描画

};

#endif