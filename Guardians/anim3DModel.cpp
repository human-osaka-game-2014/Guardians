#include "stdafx.h"

///// Xファイル メッシュ /////
CAnim3DModel::CAnim3DModel(LPCTSTR filename, LPDIRECT3DDEVICE9 pDev) : pDevice(pDev) {
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	if (FAILED( D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pD3DXMtrlBuffer, NULL, &dwNumMaterials, &pMesh))) throw TEXT("Xファイルの読み込みに失敗しました");
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
    pMeshTextures  = new LPDIRECT3DTEXTURE9[dwNumMaterials];
	for (DWORD i = 0; i < dwNumMaterials; ++i) { 
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;	
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
        pMeshTextures[i] = NULL;

		// テクスチャファイル名のUnicode対応
		TCHAR textureFilename[256] = {0};
#ifdef UNICODE
		if (d3dxMaterials[i].pTextureFilename) MultiByteToWideChar(CP_OEMCP,MB_PRECOMPOSED, d3dxMaterials[i].pTextureFilename, strlen(d3dxMaterials[i].pTextureFilename), textureFilename, (sizeof textureFilename)/2);
#else
		if (d3dxMaterials[i].pTextureFilename) strcpy_s(textureFilename, d3dxMaterials[i].pTextureFilename);
#endif
		if (textureFilename != NULL && lstrlen(textureFilename) > 0)
			if(FAILED(D3DXCreateTextureFromFileEx(pDevice, textureFilename, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0xff000000, 0, 0, &pMeshTextures[i]))) throw TEXT("テクスチャの読み込みに失敗しました");
	}
	pD3DXMtrlBuffer->Release();
}

CAnim3DModel::~CAnim3DModel() {
	SAFE_RELEASE(pMesh);
	for (DWORD i = 0; i < dwNumMaterials; ++i) {
		SAFE_RELEASE(pMeshTextures[i]);
	}
	SAFE_DELETE(pMeshTextures);
	SAFE_DELETE(pMeshMaterials);
}

void CAnim3DModel::Draw(D3DXVECTOR3 position, D3DXMATRIX attitude) { 
	D3DXMATRIX matWorld, matTrans;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	matWorld = attitude*matTrans;
    pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ポリゴンのDiffuse色の透明度をテクスチャに反映させる
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	for (DWORD i = 0; i < dwNumMaterials; ++i) {
		pDevice->SetMaterial(&pMeshMaterials[i]);
		pDevice->SetTexture(0, pMeshTextures[i]); 
		pMesh->DrawSubset(i);
    }
}

LPD3DXMESH CAnim3DModel::GetMesh() { return pMesh; }


///// メッシュ用カメラ /////
MeshCamera::MeshCamera(LPDIRECT3DDEVICE9 pDev) : pDevice(pDev) {
}

MeshCamera::~MeshCamera() {
}

void MeshCamera::Look(D3DXVECTOR3 eyePoint, D3DXVECTOR3 lookAtPoint) {
	// yukkuri test
	const D3DXVECTOR3 upVec = D3DXVECTOR3(0, 1, 0);							// 上方ベクトル
	const float viewAngle = D3DXToRadian(45);								// 視野角
	const float aspect = (float)730/(float)1280;// アスペクト比 = ビュー空間の高さ/幅
	const float nearZ = 0.1f;												// 最近点 (0にするとポリゴンが近い時にチラツキが起こる)
	const float farZ = 2000.0f;												// 最遠点
	D3DXMATRIXA16 matView, matProj;
	D3DXMatrixLookAtLH(&matView, &eyePoint, &lookAtPoint, &upVec);
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	pDevice->SetTransform( D3DTS_VIEW, &matView );
	pDevice->SetTransform( D3DTS_PROJECTION, &matProj );  
}

///// メッシュ用ライト /////
MeshLight::MeshLight(LPDIRECT3DDEVICE9 pDev) : pDevice(pDev) {
	const D3DCOLORVALUE diffuse = {1, 1, 1, 1};	// ディフューズ
	const D3DCOLORVALUE specular = {1, 1, 1, 1};	// スペキュラー
	const D3DCOLORVALUE ambient = {1, 1, 1, 1};	// アンビエント
	const float range = 200.0f;							// 距離
	const D3DXVECTOR3 direction(-0.1f, -1.0f, -0.1f);	// 方向
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient	= ambient;
	light.Diffuse	= diffuse;
	light.Specular	= specular;
	light.Range     = range;
	light.Direction = direction;
}

MeshLight::~MeshLight() {
}

void MeshLight::Illume(D3DXVECTOR3 direction) {
	light.Direction = direction;
	pDevice->SetLight( 0, &light );
	pDevice->LightEnable( 0, TRUE );
}


///// アニメーションメッシュ /////
HRESULT XFileAnimationMesh::MyHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
    HRESULT hr = S_OK;
    MYFRAME *pFrame;
    *ppNewFrame = NULL;
    pFrame = new MYFRAME;
    if (!pFrame) return E_OUTOFMEMORY;
	pFrame->Name = (LPSTR)(new TCHAR[strlen(Name) + 1]);	
    if (!pFrame->Name) return E_FAIL;
	strcpy_s(pFrame->Name, strlen(Name) + 1, Name);
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
    pFrame->pMeshContainer = NULL;
    pFrame->pFrameSibling = NULL;
    pFrame->pFrameFirstChild = NULL;
    *ppNewFrame = pFrame;
    return S_OK;
}

void XFileAnimationMesh::MyHierarchy::CreateTexture(MYMESHCONTAINER* pMeshContainer, LPDIRECT3DDEVICE9 pDevice, DWORD NumMaterials) {
	for (DWORD iMaterial = 0; iMaterial < NumMaterials; ++iMaterial) {
		if (pMeshContainer->pMaterials[iMaterial].pTextureFilename) {
			// テクスチャファイル名のUnicode対応
			TCHAR strTexturePath[MAX_PATH] = {0};
#ifdef UNICODE
			MultiByteToWideChar(CP_OEMCP, MB_PRECOMPOSED, pMeshContainer->pMaterials[iMaterial].pTextureFilename, strlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename), strTexturePath, (sizeof strTexturePath)/2);
#else
			strcpy_s(strTexturePath, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
#endif
			if(FAILED( D3DXCreateTextureFromFile(pDevice, strTexturePath, &pMeshContainer->ppTextures[iMaterial]))) pMeshContainer->ppTextures[iMaterial] = NULL;
			pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
		}
	}
}

void XFileAnimationMesh::MyHierarchy::SetDefaultMaterial(MYMESHCONTAINER* pMeshContainer) {
	pMeshContainer->pMaterials[0].pTextureFilename = NULL;
	memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
	pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
}

HRESULT XFileAnimationMesh::MyHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppMeshContainer) {
    MYMESHCONTAINER *pMeshContainer = NULL;
    INT iFacesAmount;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    LPD3DXMESH pMesh = NULL;
    *ppMeshContainer = NULL;
	DWORD dwBoneAmt=0;
    pMesh = pMeshData->pMesh;
    pMeshContainer = new MYMESHCONTAINER;
    if (!pMeshContainer) return E_OUTOFMEMORY;

    ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	pMeshContainer->Name = (LPSTR)(new TCHAR[strlen(Name) + 1]);	
    if (!pMeshContainer->Name) return E_FAIL;
	strcpy_s((char*)pMeshContainer->Name, strlen(Name) + 1, Name);
    pMesh->GetDevice(&pDevice);
    iFacesAmount = pMesh->GetNumFaces();  
	pMeshContainer->MeshData.pMesh = pMesh;
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
    pMeshContainer->NumMaterials = max(1, NumMaterials);
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
    pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
    pMeshContainer->pAdjacency = new DWORD[iFacesAmount*3];
    if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL)) return E_FAIL;
    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount*3);
    memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9)*pMeshContainer->NumMaterials);
    if (NumMaterials > 0) {
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)*NumMaterials);
		CreateTexture(pMeshContainer, pDevice, NumMaterials);
    }
    else SetDefaultMaterial(pMeshContainer);
	if (pSkinInfo) {			//当該メッシュがスキン情報を持っている場合（スキンメッシュ固有の処理）
		pMeshContainer->pSkinInfo = pSkinInfo;
        pSkinInfo->AddRef();
		dwBoneAmt = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneAmt];
		for (DWORD i = 0; i < dwBoneAmt; ++i) memcpy(&pMeshContainer->pBoneOffsetMatrices[i], pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX));
		if(FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(pMesh, NULL, pMeshContainer->pAdjacency, NULL, NULL, NULL, &pMeshContainer->dwWeight, &pMeshContainer->dwBoneAmt, &pMeshContainer->pBoneBuffer, &pMeshContainer->MeshData.pMesh))) return E_FAIL;
	}
	*ppMeshContainer = pMeshContainer;
	SAFE_RELEASE(pDevice);
    return S_OK;
}

HRESULT XFileAnimationMesh::MyHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	 SAFE_DELETE_ARRAY(pFrameToFree->Name);

	 if( pFrameToFree->pFrameSibling )
	  DestroyFrame( pFrameToFree->pFrameSibling );
	 if( pFrameToFree->pFrameFirstChild )
	  DestroyFrame( pFrameToFree->pFrameFirstChild );
   
	 SAFE_DELETE(pFrameToFree);
	 return S_OK;
}

HRESULT XFileAnimationMesh::MyHierarchy::DestroyMeshContainer(
	 LPD3DXMESHCONTAINER pMeshContainerBase)
{
	 DWORD material;
	 MYMESHCONTAINER* p = (MYMESHCONTAINER*)pMeshContainerBase;
	 SAFE_DELETE_ARRAY(p->Name);
	 SAFE_RELEASE(p->MeshData.pMesh);
	 SAFE_DELETE_ARRAY(p->pMaterials);
	 SAFE_DELETE_ARRAY(p->pAdjacency);

	 SAFE_RELEASE(p->pSkinInfo);
 
	 SAFE_DELETE_ARRAY(p->ppBoneMatrix);
	 if( p->ppTextures ) {
		for( material = 0; material < p->NumMaterials; material++ ) {
			SAFE_RELEASE(p->ppTextures[material]);
		}
	 }
	 SAFE_DELETE(p->ppTextures);
	 SAFE_RELEASE(p->pBoneBuffer);
	 SAFE_DELETE_ARRAY(p->pBoneOffsetMatrices);
	 SAFE_DELETE_ARRAY(p->ppBoneMatrix);
	 SAFE_DELETE(p);
	 return S_OK;
}

/*-----------------------------------------------------------------------------------------

	スキンメッシュ読み込み

------------------------------------------------------------------------------------------*/

XFileAnimationMesh::XFileAnimationMesh(LPCTSTR filename, LPDIRECT3DDEVICE9 pDev,D3DXVECTOR3 _scale) : pDevice(pDev),m_vecScale(_scale),m_curAnimNo(0),m_AnimTime(0) {
	m_color.a = m_color.r = m_color.g = m_color.b = 1.0f;

	if (FAILED(D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, pDevice, &cHierarchy, NULL, &pFrameRoot, &pAnimController))) throw TEXT("Xファイルの読み込みに失敗しました");
	for(DWORD i = 0; i < pAnimController->GetNumAnimationSets(); ++i) {	//アニメーショントラックを得る
		D3DXTRACK_DESC TrackDesc;
		ZeroMemory(&TrackDesc,sizeof(TrackDesc));
		TrackDesc.Weight = 1;
		TrackDesc.Speed = 1;
		TrackDesc.Enable = 1;
		pAnimController->SetTrackDesc(i, &TrackDesc);
		pAnimController->GetAnimationSet(i, &pAnimSet[i]);
//		pAnimController->SetTrackAnimationSet(i, pAnimSet[i]);
	}
	AllocateAllBoneMatrices(pFrameRoot);
}

XFileAnimationMesh::~XFileAnimationMesh() {
	FreeAnim(pFrameRoot);
	cHierarchy.DestroyFrame(pFrameRoot);
	SAFE_RELEASE( pAnimController);
}

void XFileAnimationMesh::FreeAnim(LPD3DXFRAME pF) {
	if (pF->pMeshContainer) cHierarchy.DestroyMeshContainer(pF->pMeshContainer);
    if (pF->pFrameSibling) FreeAnim(pF->pFrameSibling);
    if (pF->pFrameFirstChild) FreeAnim(pF->pFrameFirstChild);
}

HRESULT XFileAnimationMesh::AllocateBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase) {
    MYFRAME *pFrame = NULL;
	DWORD dwBoneAmt = 0;

    MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
    if (!pMeshContainer->pSkinInfo) return S_OK;
	dwBoneAmt = pMeshContainer->pSkinInfo->GetNumBones();
    pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneAmt];
    for (DWORD i = 0; i < dwBoneAmt; ++i) {
		pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		if (!pFrame) return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
	}    
    return S_OK;
}

HRESULT XFileAnimationMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrame) {
    if (pFrame->pMeshContainer) if (FAILED(AllocateBoneMatrix(pFrame->pMeshContainer))) return E_FAIL;
    if (pFrame->pFrameSibling) if (FAILED(AllocateAllBoneMatrices(pFrame->pFrameSibling))) return E_FAIL;
    if (pFrame->pFrameFirstChild) if (FAILED(AllocateAllBoneMatrices(pFrame->pFrameFirstChild))) return E_FAIL;
    return S_OK;
}

void XFileAnimationMesh::RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice, MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame) {
	DWORD i, k, dwBlendMatrixAmt, dwPrevBoneID;
    LPD3DXBONECOMBINATION pBoneCombination;
    UINT iMatrixIndex;
    D3DXMATRIX matStack;

	if (pMeshContainer->pSkinInfo) {		// スキンメッシュの場合
		pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();
		dwPrevBoneID = UINT_MAX;
		for (i = 0; i < pMeshContainer->dwBoneAmt; ++i) {
			dwBlendMatrixAmt = 0;
			for (k = 0; k < pMeshContainer->dwWeight; ++k) if (pBoneCombination[i].BoneId[k] != UINT_MAX) dwBlendMatrixAmt = k;
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixAmt);
			for (k = 0; k < pMeshContainer->dwWeight; ++k) {
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				if (iMatrixIndex != UINT_MAX) {
					matStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex]*(*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &matStack);
				}
			}
			SetMaterial(pMeshContainer);
			pDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
			dwPrevBoneID = pBoneCombination[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
		}
	}
	else {									// 通常メッシュの場合
		pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
					SetMaterial(pMeshContainer);

		for (i = 0; i < pMeshContainer->NumMaterials; ++i) {
			pDevice->SetMaterial(&pMeshContainer->pMaterials[i].MatD3D);
			pDevice->SetTexture(0, pMeshContainer->ppTextures[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
void XFileAnimationMesh::DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase) {
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
    MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;	
    while (pMeshContainer) {
        RenderMeshContainer(pDevice,pMeshContainer, pFrame);
        pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
    }
    if (pFrame->pFrameSibling) DrawFrame(pDevice,pFrame->pFrameSibling);
    if (pFrame->pFrameFirstChild) DrawFrame(pDevice,pFrame->pFrameFirstChild);
}

void XFileAnimationMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix) {
    MYFRAME *pFrame = (MYFRAME*)pFrameBase;	
    if (pParentMatrix) D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
    else pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
    if (pFrame->pFrameSibling) UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
    if (pFrame->pFrameFirstChild) UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
}
void XFileAnimationMesh::SetMaterial( MYMESHCONTAINER* pMeshContainer ) {
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = m_color.r;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = m_color.g;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = m_color.b;
	pMeshContainer->pMaterials[0].MatD3D.Diffuse.a = m_color.a;
	pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
}
void XFileAnimationMesh::Draw(D3DXVECTOR3 position, D3DXMATRIX attitude) {
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale,m_vecScale.x,m_vecScale.y,m_vecScale.z);

	D3DXMATRIX matWorld = attitude;
	matWorld = matWorld * matScale * matTrans;

    pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	UpdateFrameMatrices(pFrameRoot, &matWorld);
	DrawFrame(pDevice, pFrameRoot);


	// ポリゴンのDiffuse色の透明度をテクスチャに反映させる
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
}
void XFileAnimationMesh::CreateBox(XFileAnimationMesh::BOX* _box)
{
	Scalling( &_box->max,m_vecScale);
	Scalling( &_box->min,m_vecScale);
	Scalling( &_box->center,m_vecScale);
	Scalling( &_box->length,m_vecScale);

	if(FAILED( D3DXCreateBox (
		pDevice,
		_box->length.x,   // ボックスの幅
        _box->length.y,					// ボックスの高さ
        _box->length.z,					// ボックスの奥行き
		&_box->pMesh,
		&_box->pAdjacency)))
    {
		throw;
    }
        
    //スフィアメッシュのマテリアル白色、半透明、光沢有)
    _box->pMaterials = new D3DMATERIAL9; //初期化
    _box->pMaterials->Diffuse.a = 0.5f;  //半透明
    _box->pMaterials->Diffuse.r = 1.0f;
    _box->pMaterials->Diffuse.g = 1.0f;
    _box->pMaterials->Diffuse.b = 1.0f;

    _box->pMaterials->Ambient = _box->pMaterials->Diffuse;

    _box->pMaterials->Specular.r = 1.0f;
    _box->pMaterials->Specular.g = 1.0f;
    _box->pMaterials->Specular.b = 1.0f;

    _box->pMaterials->Emissive.r = 0.1f;
    _box->pMaterials->Emissive.g = 0.1f;
    _box->pMaterials->Emissive.b = 0.1f;

    //光沢の度合い
    _box->pMaterials->Power = 120.0f;

}
void XFileAnimationMesh::CreateSphere(XFileAnimationMesh::SPHERE* _sphere)
{
	// 中心座標と半径にスケールを適応
	_sphere->center = _sphere->center * m_vecScale.x;
	_sphere->radius = _sphere->radius * m_vecScale.x;
	if(FAILED( D3DXCreateSphere(
		pDevice,
        _sphere->radius,    //半径
        24,         //主軸を回転軸としたスライスの数
        24,         //主軸に沿ったスタックの数
        &_sphere->pShereMesh,
        NULL)))
    {
		throw;
    }
        
    //スフィアメッシュのマテリアル白色、半透明、光沢有)
    _sphere->pShereMaterials = new D3DMATERIAL9; //初期化
    _sphere->pShereMaterials->Diffuse.a = 0.5f;  //半透明
    _sphere->pShereMaterials->Diffuse.r = 1.0f;
    _sphere->pShereMaterials->Diffuse.g = 1.0f;
    _sphere->pShereMaterials->Diffuse.b = 0.f;

    _sphere->pShereMaterials->Ambient = _sphere->pShereMaterials->Diffuse;

    _sphere->pShereMaterials->Specular.r = 1.0f;
    _sphere->pShereMaterials->Specular.g = 1.0f;
    _sphere->pShereMaterials->Specular.b = 1.0f;

    _sphere->pShereMaterials->Emissive.r = 0.1f;
    _sphere->pShereMaterials->Emissive.g = 0.1f;
    _sphere->pShereMaterials->Emissive.b = 0.1f;

    //光沢の度合い
    _sphere->pShereMaterials->Power = 120.0f;

}
LPD3DXFRAME XFileAnimationMesh::GetFrameRoot()
{
	return pFrameRoot;
}

void XFileAnimationMesh::SetScale(D3DXVECTOR3 _vecScale)
{
	m_vecScale = _vecScale;
}
void XFileAnimationMesh::SetColor(float _a,float _r,float _g,float _b)
{
	m_color.a = _a;
	m_color.r = _r;
	m_color.g = _g;
	m_color.b = _b;
}
double XFileAnimationMesh::AdvanceTime(double time) 
{
	pAnimController->AdvanceTime(time, 0);

	m_AnimTime += (time * 60);

	return m_AnimTime;
}
bool XFileAnimationMesh::ChangeMotion(int motion_number)
{
	// 今のアニメーションをトラック1に移行
	D3DXTRACK_DESC TD;
	pAnimController->GetTrackDesc( 0, &TD );
	pAnimController->SetTrackAnimationSet( 1, pAnimSet[ m_curAnimNo ] );
	pAnimController->SetTrackDesc( 1, &TD );
	pAnimController->SetTrackEnable(1, false);
	pAnimController->SetTrackEnable(0, false);

	// 新しいアニメーションをトラック0に移行

	pAnimController->SetTrackAnimationSet( 0, pAnimSet[ motion_number ] );
	
	// アニメーション全体時間確認(デバッグ用)
	//double a = pAnimSet[0]->GetPeriod();

	// キャンセル可能で変更したいモーションが現在のモーションと別の時
	if( m_animList[m_curAnimNo].chancel && motion_number != m_curAnimNo ){
		pAnimController->SetTrackPosition(0,m_animList[motion_number].startTime / 60);
		 //アニメーション時間をリセット
		m_AnimTime = m_animList[motion_number].startTime;
		// 現在のアニメーション番号に切り替え
		m_curAnimNo = motion_number;
		pAnimController->SetTrackEnable(0, true);
		pAnimController->SetTrackEnable(1, true);
		return true;
	}
	// キャンセル不可能なモーションはモーションが終わっている時のみ変更
	else{
		if( m_AnimTime >= m_animList[m_curAnimNo].endTime ){
			pAnimController->SetTrackPosition(0,m_animList[motion_number].startTime / 60);
			//アニメーション時間をリセット
			m_AnimTime = m_animList[motion_number].startTime;
			// 現在のアニメーション番号に切り替え
			m_curAnimNo = motion_number;
			pAnimController->SetTrackEnable(0, true);
			pAnimController->SetTrackEnable(1, true);
			return true;
		}
	}

	pAnimController->SetTrackEnable(0, true);
	pAnimController->SetTrackEnable(1, true);

	return false;
}
void XFileAnimationMesh::SetAnimList(std::vector<ANIMLIST>* _animList)
{
	m_animList = *_animList;
}