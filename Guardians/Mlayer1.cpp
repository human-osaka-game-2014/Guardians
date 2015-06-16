/*--------------------------------------------------------------

	処理内容:レイヤー1(空)の制御、描画
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

CLayer1::CLayer1(LPDIRECT3DDEVICE9 _pDevice, int _stageID) :
	CLayer( _pDevice, D3DXVECTOR3(-100.f,30.f,3.f), _stageID)
{
	m_plane = new C3DModel("image\\xfile\\plane1.x", _pDevice);
//	m_tex = CTexMgr.Get( TEX_SKY+(_stageID*7) ); // stageID*7をすることでステージごとのレイヤー変化
	m_plane->SetScale(D3DXVECTOR3( 80.f,160.f,1.f));
}
void CLayer1::SetCharaSpeed(D3DXVECTOR2 _speed) 
{
	m_speed.x = _speed.x * 0.9f;
	m_speed.y = _speed.y * 0.55f;
}

