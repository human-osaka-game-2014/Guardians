/// Xファイルから読込んだメッシュ
class CAnim3DModel sealed {
private:
	LPDIRECT3DDEVICE9	pDevice;		// Direct3Dデバイスオブジェクト
	LPD3DXMESH			pMesh;			// メッシュ
	D3DMATERIAL9*		pMeshMaterials;	// マテリアル配列
	LPDIRECT3DTEXTURE9*	pMeshTextures;	// テクスチャ配列
	DWORD				dwNumMaterials;	// マテリアル・テクスチャ配列の大きさ

public:
	/// コンストラクタ
	/// @param filename 画像ファイル名
	/// @param pDev		Direct3Dデバイスオブジェクト
	CAnim3DModel(LPCTSTR filename, LPDIRECT3DDEVICE9 pDev);
	~CAnim3DModel(void);

	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);
	LPD3DXMESH GetMesh();
};

/// メッシュのビュー変換、射影変換を行なうカメラ
class MeshCamera sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	/// コンストラクタ
	/// @param pDev Direct3Dデバイスオブジェクト
	MeshCamera(LPDIRECT3DDEVICE9 pDev);

	~MeshCamera(void);
	void Look(D3DXVECTOR3 eyePoint, D3DXVECTOR3 lookAtPoint);
};

/// メッシュ用ライト
class MeshLight sealed {
private:
	LPDIRECT3DDEVICE9 pDevice;
	D3DLIGHT9 light;

public:
	/// コンストラクタ
	/// @param pDev Direct3Dデバイスオブジェクト
	MeshLight(LPDIRECT3DDEVICE9 pDev);

	~MeshLight(void);
	void Illume(D3DXVECTOR3 direction);
};


/// Xファイルから読込んだアニメーションメッシュ
class XFileAnimationMesh sealed {
public:
	// レイの情報
	typedef struct _RAY{
		D3DXVECTOR3 position;	// 開始地点
		D3DXVECTOR3 length;		// レイの長さ
	}RAY_PARAM;


	struct SPHERE // スフィア情報格納用構造体
	{
		D3DXVECTOR3 center;				// 中心座標
		D3DXVECTOR3 position;			// 衝突判定用(中心座標)
		float radius;					// 半径
		LPD3DXMESH  pShereMesh;			// メッシュ
		D3DMATERIAL9*  pShereMaterials;	// マテリアル
	};

	struct BOX // ボックス情報格納用構造体
	{
		char*		name;
		D3DXVECTOR3 center;				// 原点
		D3DXVECTOR3 size;
		D3DXVECTOR3 min;				// 最小点座標
		D3DXVECTOR3 max;				// 最大点座標
		D3DXVECTOR3 length;				// 最小点から最大点へのベクトル
		D3DXVECTOR3 position;		// メッシュの位置
		LPD3DXMESH  pMesh;			// メッシュ
		D3DMATERIAL9*  pMaterials;	// マテリアル
		LPD3DXBUFFER		pAdjacency;
	};
	// アニメーション時間格納用
	typedef struct _ANIMLIST
	{
		double startTime;
		double endTime;
		bool   chancel;
	}ANIMLIST;

private:

	struct MYFRAME: public D3DXFRAME {
		D3DXMATRIX CombinedTransformationMatrix;
	};
	struct MYMESHCONTAINER: public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9*  ppTextures;
		DWORD dwWeight;							// 重みの個数（重みとは頂点への影響。）
		DWORD dwBoneAmt;						// ボーンの数
		LPD3DXBUFFER pBoneBuffer;				// ボーン・テーブル
		D3DXMATRIX** ppBoneMatrix;				// 全てのボーンのワールド行列の先頭ポインター
		D3DXMATRIX* pBoneOffsetMatrices;		// フレームとしてのボーンのワールド行列のポインター
	};
	class MyHierarchy : public ID3DXAllocateHierarchy {
	private:
		void CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials);
		void SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer);
	public:
		MyHierarchy(){};
		~MyHierarchy(){};
		STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*, CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD*, LPD3DXSKININFO, LPD3DXMESHCONTAINER*);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);

	};

	LPDIRECT3DDEVICE9			pDevice;										// Direct3Dデバイスオブジェクト
	MyHierarchy					cHierarchy;										// アロケートヒエラルキーオブジェクト
	LPD3DXFRAME					pFrameRoot;										// フレーム
	LPD3DXANIMATIONCONTROLLER	pAnimController;								// アニメーションコントローラ
	LPD3DXANIMATIONSET			pAnimSet[100];									// アニメーションセット
	int							m_curAnimNo;									// 現在のアニメーション番号
	
	double						m_AnimTime;										// 
	std::vector<ANIMLIST>		m_animList;
	_D3DCOLORVALUE				m_color;									// メッシュの色


	HRESULT AllocateBoneMatrix(LPD3DXMESHCONTAINER);							// メッシュに行列を割り振る
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME);								// 再帰コード：フレーム階層を展開して各メッシュに行列を割り振る
	
	D3DXVECTOR3		m_vecScale;
	void UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );						// 再帰コード：フレームのワールド変換
	void RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );	// メッシュコンテナのレンダリング
	void DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );								// 再帰コード：フレームのレンダリング
	void FreeAnim(LPD3DXFRAME pF);												// 再帰コード：全てのメッシュコンテナをリリース
public:

	/// コンストラクタ
	/// @param filename 画像ファイル名
	/// @param pDevice	Direct3Dデバイスオブジェクト
	XFileAnimationMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 _scale);

	/// デストラクタ
	~XFileAnimationMesh(void);

	// 描画
	void Draw(D3DXVECTOR3 position, D3DXMATRIX rotation);

	void CreateSphere(XFileAnimationMesh::SPHERE* _sphere);
	
	// ボックスのマテリアル生成
	void CreateBox(XFileAnimationMesh::BOX* _box);
	// スケールをセット
	void SetScale(D3DXVECTOR3 _vecScale);
	/// 時間を進行
	double AdvanceTime(double time);

	/// 動きを切り替える
	bool ChangeMotion(int motion_number);

	// アニメーション再生時間をセットする
	void SetAnimList(std::vector<ANIMLIST>* _animList);

	// フレームを取得
	LPD3DXFRAME GetFrameRoot();

	void SetMaterial(MYMESHCONTAINER* pMeshContainer);								
	void SetColor(float _a = 1.0f,float _r = 1.0f,float _g = 1.0f,float _b = 1.0f);	// マテリアルの色をセット
	void Scalling(D3DXVECTOR3* _size,D3DXVECTOR3 _scale)							// スケールをセット
	{
		_size->x = _size->x * _scale.x;
		_size->y = _size->y * _scale.y;
		_size->z = _size->z * _scale.z;
	}

};