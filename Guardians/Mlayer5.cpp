/*--------------------------------------------------------------

	処理内容:レイヤー5(木)の制御、描画
	作成者:三浦
	作成日:10/24
	更新日:
	更新内容:
		
	関数　
		コンストラクタ
		SetCharaSpeed 
		　キャラのスピードによってレイヤーの移動速度計算、登録
		Control
		　レイヤーを移動させる
		Draw
	変数　

--------------------------------------------------------------*/
#include "stdafx.h"

CLayer5::CLayer5(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer(_pDevice,D3DXVECTOR3(-90,15.f,3) , _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane5.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_TREE+(_stageID*7) );
	m_plane->SetScale( D3DXVECTOR3( 35.f,140.f,1.f));
}


void CLayer5::SetCharaSpeed(D3DXVECTOR2 _speed)
{
	//m_speed.x = _speed.x*1.f;
//	m_speed.y = _speed.y*0.9f;
	//m_speed.y = _speed.y;
}

