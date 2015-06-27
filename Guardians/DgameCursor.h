/**
 * @file DgameCursor.h
 */

/**
 * カーソルの制御
 */

#ifndef _GAME_CURSOR_H_
#define _GAME_CURSOR_H_

class CGameCursor
{
public:
	enum State		// カーソルの状態
	{
		STATE_WAIT,		// 動いていない状態(明滅はしている)
		STATE_MOVE,		// 横or縦に移動している状態
	};
	static const D3DXVECTOR2 NOMOVE_PARTS_SIZE;			//広がる際に変動しない部分のサイズ(隅１個分(24×24) 
protected:
	static const int MOVE_TIME		= 5;	// 移動時間(5frame)
	static const int FLICKER_TIME	= 60;	// 明滅時間(2秒=120frame)

	enum Direction	// 方向
	{
		DIR_HORIZONTAL,	// 水平方向
		DIR_VIRTICAL,	// 垂直方向
		DIR_DIAGONAL,	//斜め方向
	};
	enum FadeType	//点滅状態
	{
		FADE_IN,		
		FADE_OUT,
	};
	typedef struct _RECT
	{
		float left;
		float top;
		float right;
		float bottom;
	}RECT;

	RECT				m_rect;			//テクスチャ座標
	CVertex				m_vertex;		// Vertexクラスオブジェクト
	CTexture			m_texture;		// テクスチャクラスオブジェクト
	
	LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャデバイス

	D3DXVECTOR2			m_position;		// 座標
	D3DXVECTOR2			m_nextPosition;	// 移動先座標
	FadeType			m_fadeType;		// 点滅状態
	Direction			m_direction;	// 進む方向
	State				m_state;		// 状態
	
	float				m_moveX;			// 一回(1frame)の移動量
	float				m_moveY;
	bool				m_flickFlag;	// 点滅するかどうかのフラグ
	int					m_itemMax;		// 選択項目最大数
	int					m_selectID;		// 選択されている項目の番号
	int					m_alpha;		// α値(明滅アニメーションに使用)
	int					m_addAlpha;		// α変動値
	int					m_count;		// 点滅アニメーションのカウント
public:
	CGameCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position);	// コンストラクタ(デバイス、座標、使用画像IDをセット)
	virtual ~CGameCursor();
	void Control();																	// 制御
	virtual void Draw();																	// 描画
	void ControlFlicker();															// 点滅の制御
	void Move();																	// 移動
	// アクセッサ
	void SetNextPosition(D3DXVECTOR2 _nextPosition);								// 移動先の座標をセット
	int GetSelectID();																// 選択されている項目番号を取得
	int GetState();																	// 状態を取得
};

#endif