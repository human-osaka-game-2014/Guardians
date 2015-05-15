#ifndef _GAME_DATA_WINDOW_H_
#define _GAME_DATA_WINDOW_H_

class CGameDataWindow : public CGameWindow
{
private:
	static const D3DXVECTOR2 WINDOW_POSITION;	// 「ウィンドウ」移動後座標
	static const D3DXVECTOR2 TIME_POSITION;		// 「プレイ時間」描画座標
	static const D3DXVECTOR2 MONEY_POSITION;	// 「所持金」描画座標

	static const int MAX_WIDTH	= 270+128;		// ウィンドウ最大幅
	static const int MAX_HEIGHT = 256;			// ウィンドウ最大高さ
	
	DWORD					m_digits;			// Money桁数格納用
	
	CGameData* m_pGameData;		// ゲームデータの参照
public:
	CGameDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData);	// コンストラクタ(デバイス、座標、ゲームデータをセット)
	~CGameDataWindow();
	void Control();																				// 制御
	void Draw();																				// 描画

};

#endif