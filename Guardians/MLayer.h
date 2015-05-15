#ifndef _LAYER_H_
#define _LAYER_H_

class CLayer
{
protected:
	D3DXVECTOR2			m_speed;        // レイヤーの移動速度
	D3DXVECTOR3			m_angle;	// フィールドの角度
	LPDIRECT3DDEVICE9	m_pDevice;
	D3DXVECTOR3			m_position;		// レイヤー座標
	D3DXVECTOR3			m_initPosition;	// 初期座標
	CTexture			m_tex;
	CTexture			m_tex2;
	C3DModel*			m_plane;  

public:
	enum TEX_ID {	// テクスチャ番号
	TEX_SKY, 
	TEX_MOUNTAIN,
	TEX_HILL_TREE,
	TEX_HILL,
	TEX_TREE,
	TEX_ROAD,
	TEX_STONE,
	TEX_NERU,
	TEX_NERU2,
	};



	CLayer( LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR3 _position, int _stageID ); // コンストラクタ(デバイス、ステージIDをセット)
	~CLayer();
	void Control();
	void Draw();
	virtual void SetCharaSpeed(D3DXVECTOR2 _speed) = 0;
	void SetPosition(D3DXVECTOR2 _position);
	D3DXVECTOR3 GetPosition();
	void SetInitPosition();
};

#endif