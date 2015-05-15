#ifndef _CHARA_PICTURE_H_
#define _CHARA_PICTURE_H_

class CCharaPicture
{
public:
enum Type
{
	TYPE_STAGE_SELECT,		// 文字-ステージ選択-
	TYPE_STATUS,			// 文字-ステータス-
	TYPE_SHOP,				// 文字-ショップ-
	TYPE_SAVE,				// 文字-セーブ-

	TYPE_MAX,
};
private:
	LPDIRECT3DDEVICE9	m_pDevice;		// 描画デバイス
	D3DXVECTOR2			m_position;		// 座標
	int					m_textureID;	// テクスチャID
	CVertex             m_vertex;    
	CTexture            m_tex;
	Type				m_typeID;

private:

public:


	CCharaPicture(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, int _textureID, Type _typeID);	// コンストラクタ(デバイス、座標、テクスチャIDをセット)
	void Draw();																		// 描画
};

#endif