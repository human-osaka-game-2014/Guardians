#ifndef _NERU_H_
#define _NERU_H_

class CNeru : public CPlayer
{
public:
	XFileAnimationMesh*			m_model;
private:
	LPDIRECT3DDEVICE9			m_pDevice;		// 描画デバイス
	D3DXVECTOR3					m_position;		// キャラクターの位置

	float						m_speed;
public:
	CNeru(LPDIRECT3DDEVICE9 _pDevice);			// コンストラクタ
	~CNeru();									// デストラクタ
	
	void Draw();								// 描画
	//void SetPosition(D3DXVECTOR3 _position);	// 移動
	void SetMotion(int _motionID);				// モーションID

	// ゲッタ
	float GetCharaSpeed();						// キャラのスピードを返す

private:
};

#endif