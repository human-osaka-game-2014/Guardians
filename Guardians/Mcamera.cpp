#include  "stdafx.h"

/*------------------------------------------
   
    コンストラクタ(デバイス情報のコピー)       
	@param LPDIRECT3DDEVICE9  描画デバイス

------------------------------------------*/
CCamera::CCamera(LPDIRECT3DDEVICE9 _pDevice) : m_pDevice(_pDevice)
{
	m_pDevice->GetTransform( D3DTS_VIEW, &m_InitMatView );
	m_pDevice->GetTransform( D3DTS_PROJECTION, &m_InitMatProj );
}
CCamera::~CCamera()
{
	m_pDevice->SetTransform( D3DTS_VIEW, &m_InitMatView );
	m_pDevice->SetTransform( D3DTS_PROJECTION, &m_InitMatProj );
}
/*------------------------------------------
   
    カメラの位置と注視点の設定    
	@param D3DXVECTOR3  カメラの位置
	@oaram D3DXVECTOR3  注視点

------------------------------------------*/
void CCamera::Look(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookAtPos)
{
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // カメラの上方向を設定
	float viewAngle = D3DXToRadian(50);       // 視野角
	float aspect = 1280.f/720.f;              // アスペクト比
	float nearZ = 10.f;                       // 最近点
	float farZ = 100.f;                       // 最遠点

	// ビュー変換用の行列に変換
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &_eyePos, &_lookAtPos, &upVec);
	// 射影変換用の行列に変換
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);
	//デバイスに登録
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}