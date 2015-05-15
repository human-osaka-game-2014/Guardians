#ifndef _CHIP_H_
#define _CHIP_H_

class CChip
{
public:
	static const int ANIM_TIME = 60*2;	// １枚の画像が表示される時間(2秒=120frame)(仕様にないのであとで聞く)

	enum ChipType
	{
		STAGE1BOSS,
		STAGE2BOSS,
		STAGE3BOSS,
		STAGE4BOSS,
		STAGE5BOSS,
		STAGE6BOSS,
		START,		// 開始地点
		CHECKPOINT_NOCLEAR,	//未クリアのチックポイント（黒）
		CHECKPOINT_CLEAR,	//クリア済みのチックポイント（青）兼スタートポイント
		ROAD_LINE,			//進行ライン
		SHADOW,				//影
		MONSCHIP_STAGE1BOSS,		
		MONSCHIP_STAGE2BOSS,
		MONSCHIP_STAGE3BOSS,
		MONSCHIP_STAGE4BOSS,
		MONSCHIP_STAGE5BOSS,
		MONSCHIP_STAGE6BOSS,
		CHIP_MAX,
	};
protected:
	static const FRECT animRect[];
	static const int ANIM_NO_LIST[];		// アニメーション順番
	FRECT				rect;
	FRECT				shadowRect;
	LPDIRECT3DDEVICE9	m_pDevice;			// 描画デバイス
	D3DXVECTOR2			m_position;			// 座標
	D3DXVECTOR2			m_cameraPosition;	// カメラ(マップ座標)
	ChipType			m_type;				// チップタイプ
	int					m_time;				//明減アニメーション間隔			
	int					m_animeCount;		//明減アニメーション用
	bool				m_animFlag;			// アニメーションの有無
	int					m_animCount;		// アニメーションカウント
	int					m_animID;			// アニメーションID(現在何枚目の画像か)
	CVertex				m_vertex;			// 頂点情報管理
	// テクスチャ管理クラスができるまで仮でここに作成
	CTexture			m_texture;			// 画像
	CTexture			m_animTexture;		// 画像
	CTexture			m_shadowtexture;	// 画像

	void MoveAnimation();
public:
	CChip(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, ChipType _type, bool _animFlag = false);	// コンストラクタ(デバイス、座標、チップID、アニメーションの有無をセット)
	virtual void Control();																				// 制御
	void SetAnimePosition();																			//アニメフラグのon,off
	virtual void Draw();																						// 描画

	// アクセッサ
	void SetCameraPosition(D3DXVECTOR2 _cameraPosition);
	void SetAnimeFlag(bool _animFlag);
	void ChangeType(ChipType _type);
};

#endif