#ifndef _GAME_EQUIP_WINDOW_H_
#define _GAME_EQUIP_WINDOW_H_

#include <string>

class CGameEquipWindow : public CGameWindow
{
private:


	static const D3DXVECTOR2 CURSOR_INIT_POSITION;	// カーソル初期座標
	static const D3DXVECTOR2 EQUIP_POSITION;		// 「装備」描画座標
	static const D3DXVECTOR2 EQUIP1_POSITION;		// 「1つ目の装備」描画座標
	static const D3DXVECTOR2 TOOL_POSITION;			// 「道具」描画座標
	static const D3DXVECTOR2 TOOL1_POSITION;		// 「1つ目の道具」描画座標

	static const int MAX_WIDTH_CHARA	= 530;		// ウィンドウ最大幅(キャラセレクト)
	static const int MAX_HEIGHT_CHARA	= 450;		// ウィンドウ最大高さ(キャラセレクト)
	static const int MAX_WIDTH_STATUS	= 535;		// ウィンドウ最大幅(ステータス)
	static const int MAX_HEIGHT_STATUS	= 480;		// ウィンドウ最大高さ(ステータス)
	
	CTexture	        m_textureicon[2];	//アイテム,装備アイコン
	CGameData*			m_pGameData;		// ゲームデータの参照
	CGameItemCursor*	m_pCursor;			// 選択用カーソル
	int					m_charaID;			// キャラクターID
	int					m_menuID;			// メニューID
	int					m_selectEquipID;

public:
	CGameEquipWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData, int _menuID);	// コンストラクタ(デバイス、座標、ゲームデータ、メニューIDをセット)
	~CGameEquipWindow();
	void Control();																								// 制御
	void Draw();										// 描画
	void SetSelectEquipID(int _selectEquipID);// 選択されている装備のIDをセット								
	void SetCharaID(int _charaID);
};

#endif