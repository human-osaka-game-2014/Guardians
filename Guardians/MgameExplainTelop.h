#ifndef _GAME_EXPLAIN_TELOP_H_
#define _GAME_EXPLAIN_TELOP_H_

class CGameExplainTelop : public CGameTelop
{
private:
	static const D3DXVECTOR2 EXPLAIN_POSITION;	// 「アイテム説明」描画位置
	static const float TELOP_HEIGHT;			// テロップの高さ
	static const float TELOP_MAX_WIDTH;			// テロップ最大幅
	//static const int TEX_TOOL_ID = ??
	//CTexture           m_toolID;

	int m_toolID;	// アイテム番号
		

	CGameData* m_pGameData;
public:
	CGameExplainTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CGameData* _pGameData);	// コンストラクタ(デバイス、座標、アイテムIDをセット)
	~CGameExplainTelop();
	void Control();																		// 制御
	void Draw(int _no);																		// 描画
	int Search(int _No);
};

#endif