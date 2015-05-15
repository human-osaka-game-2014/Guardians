/*--------------------------------------------------------------

	処理内容:ネルの仮描画
	作成者:三浦
	作成日:10/30
	更新日:
	更新内容:
		
	関数　
		コンストラクタ
		
	変数　

--------------------------------------------------------------*/

#include "stdafx.h"

/*--------------------------------------------------------------

	コンストラクタ
	@param	LPDIRECT3DDEVICE9 描画デバイス
	@return なし

--------------------------------------------------------------*/
CNeru::CNeru(LPDIRECT3DDEVICE9 _pDevice) : CPlayer(_pDevice),m_pDevice(_pDevice),m_speed(0.01f)
{
	m_model = new XFileAnimationMesh(_T("image\\neru\\PC_2-1_neru_motion.x"),m_pDevice,D3DXVECTOR3(0.005f,0.005f,0.005f));
	XFileAnimationMesh::SPHERE sphere;
	XFileAnimationMesh::BOX		box;
	// スフィアの生成
	sphere.center = D3DXVECTOR3(0.f,0.f,0.f);
	sphere.radius = 10.f;
	m_sphere.push_back(sphere);
	m_model->CreateSphere(&m_sphere[0]);
	// ボックスの生成
	box.max   = D3DXVECTOR3(50.0f,130.0f,100.0f);
	box.min    = D3DXVECTOR3(0.f,0.f,0.f);
	box.center = D3DXVECTOR3(0.f,0.3f,0.f);
	box.length = box.max - box.min;
	m_box.push_back(box);
	m_model->CreateBox(&m_box[0]);

}
/*--------------------------------------------------------------

	デストラクタ

--------------------------------------------------------------*/
CNeru::~CNeru()
{
	SAFE_DELETE(m_model);
	SAFE_DELETE(m_sphere[0].pShereMaterials);
	SAFE_DELETE(m_box[0].pMaterials)
}
/*--------------------------------------------------------------

	描画
	@param	なし
	@return なし

--------------------------------------------------------------*/
void CNeru::Draw()
{
	m_model->AdvanceTime(1.0f/60.f);
	
	D3DXMATRIX rotation;							// 回転
	D3DXMatrixRotationY(&rotation, m_angle);

	m_model->Draw(m_position,rotation);
	MYFRAME* m_frame;
	D3DXVECTOR3 position;
	if( m_state == STATE_RUN ){
		// 衝突判定用矩形の描画
		m_frame = (MYFRAME*)D3DXFrameFind( m_model->GetFrameRoot(),"Joint_231121111" );
		SetBonePos(&position,m_frame);
		UpdateSphere( position , &m_sphere[0]);
		DrawSphere(m_sphere[0]);
	}
	
	//UpdateBox(m_position,&m_box[0]);
	//DrawBox(m_box[0]);
}

/*--------------------------------------------------------------

	アニメーション変更
	@param	int キー情報
	@return なし

--------------------------------------------------------------*/
void CNeru::SetMotion(int _motionID)
{

}
