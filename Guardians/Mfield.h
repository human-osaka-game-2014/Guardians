#ifndef _FIELD_H_
#define _FIELD_H_

class CField
{
public:
static const int  LAYER_TYPE_NUM  = 7;

	typedef struct _FIELD_DATA{
		//CField* m_field[LAYER_TYPE_NUM];
		CField* m_field;
	}FIELD_DATA;
protected:


	enum LayerType
	{
		LAY_1,
		LAY_2,
		LAY_3,
		LAY_4,
		LAY_5,
		LAY_6,
		LAY_7,
		LAY_8,
	};

	LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	D3DXVECTOR2			m_position;		// 座標
	float				m_width;		// 幅
	float				m_height;		// 高
	D3DXVECTOR2			m_speed;		// マップ移動速度
	CVertex				m_vertex;		

	CLayer**			m_layer;
	int					m_keyStateOn; // 仮で作成
	bool				m_isHit;	// 壁との当たり

	CPlayer*			m_pPlayer;	// プレイヤー情報

public:
	CField(LPDIRECT3DDEVICE9 _pDevice,int _stageID);
	~CField();
	void Load(LPDIRECT3DDEVICE9 _pDevice,int _stageID);
	virtual void Control();
	virtual void Draw();
	void SetCharaSpeed(D3DXVECTOR2 _speed);
	void SetKeyState(int _keyStateOn);
	void SetPosition( D3DXVECTOR2 );

	bool GetHitFlag();
	D3DXVECTOR2 GetPosition();
	void SetHitFlag(bool _isHit);
	D3DXVECTOR2 GetFieldSpeed();
	void SetPlayerInfo(CPlayer* _pPlayer);
};

#endif