#ifndef _GAME_TELOP_H_
#define _GAME_TELOP_H_

class CGameTelop
{
protected:
	static const int SPREAD_TIME = 60 * 1;	// 最大サイズになるまでの時間(1秒=60frame)
	static const int TEX_ID = 8;			// あとで変更

	enum State			// テロップの状態
	{
		STATE_WAIT,		// 動いていない状態
		STATE_SPREAD,	// 広がっている状態
	};

	LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	D3DXVECTOR2			m_position;		// 座標
	State				m_state;		// 状態
	float				m_width;		// 幅
	float				m_height;		// 高さ
	float				m_maxWidth;		// 最大幅
	float				m_spreadWidth;	// 一回(1frame)に広がる幅
	CVertex             m_vertex;
	CTexture            m_tex;

public:
	CGameTelop(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth);		// コンストラクタ(デバイス、座標、最大幅をセット)
	virtual ~CGameTelop(){};
	virtual void Control(){};															// 制御
	virtual void Draw();																		// 描画

	// アクセッサ
	void SetMaxWidth(float _maxWidth);													// 最大幅をセット
};

#endif