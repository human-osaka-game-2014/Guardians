#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

class CGameWindow
{
public:
	enum SelectType {	// 選択されたタイプ
		EQUIP,			// 装備
		TOOLS,			// 道具
	};
enum State			// ウィンドウの状態
	{
		STATE_WAIT,		// 動いていない状態
		STATE_SPREAD,	// 広がっている状態
		STATE_MOVE,		// 移動している状態
	};

protected:
	static const D3DXVECTOR2 NOMOVE_PARTS_SIZE;	// 広がる際に変動しない部分のサイズ(４隅) 

	static const int SPREAD_TIME = 10;		// 最大サイズになるまでの時間(10frame)
	static const int MOVE_TIME = 10;		// 移動時間(10frame)
	static const int TEX_GAME_WINDOW = 7;

	enum Direction		// 方向
	{
		DIR_HORIZONTAL,	// 水平方向
		DIR_VIRTICAL,	// 垂直方向
	};

    LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	D3DXVECTOR2			m_position;		// 中心座標
	D3DXVECTOR2			m_nextPosition;	// 移動先座標
	Direction			m_direction;	// 進む方向
	State				m_state;		// 状態
	float				m_width;		// 幅
	float				m_height;		// 高さ
	float				m_maxWidth;		// 最大幅
	float				m_maxHeight;	// 最大高さ
	float				m_spreadWidth;	// 一回(1frame)に広がる幅
	float				m_spreadHeight;	// 一回(1frame)に広がる高さ
	float				m_move;			// 一回(1frame)の移動量
	bool				m_cursorFlag;	// カーソルの有無
	bool				m_scrollFlag;	// スクロールの有無
	bool				m_moveFlag;		// 移動中かどうか
	int					m_textureID;	// 使用画像ID
	int					m_charaID;
	int					m_selectEquipID;
	CGameData*			m_pGameData;
	CVertex				m_vertex;		// 頂点座標管理
	// テクスチャ管理クラスができるまで仮でここに作成
	CTexture			m_texture;		// 画像
public:
	
	CGameWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth, float _maxHeight, D3DXVECTOR2 _nextPosition = D3DXVECTOR2(-1.f,-1.f) );	// コンストラクタ(デバイス、座標、最大幅、高さ、移動先の位置をセット)
	
	virtual ~CGameWindow();
	virtual void Control();																						// 制御
	virtual void Draw();																						// 描画
	// アイテムサーチ
	int Search(int _itemNum,ItemType _type);
	// アクセッサ
	void SetNextPosition(D3DXVECTOR2 _nextPosition);			// 移動先の座標をセット
	bool IsMove();												// 移動中かどうかを取得	

	//ゲッタ
	// ウインドウの状態を取得
	State Get();
	// ゲームデータをセット
	void SetGameData(CGameData* _pGameData);
};

#endif