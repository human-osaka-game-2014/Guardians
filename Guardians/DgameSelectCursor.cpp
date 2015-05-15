/*--------------------------------------------------------------

	処理内容:カーソル(選択画面)の制御
	作成者:檀上
	作成日:9/23
	更新日:10/6
	更新内容:
	関数　
		10/6
		コンストラクタの追加
		コンストラクタ内でテクスチャ情報の呼び出し
		rectにテクスチャ座標を格納
		ウインドウを広げるフラグをtrueに
	変数　
		m_rect


--------------------------------------------------------------*/
#include "stdafx.h"
/*--------------------------------------------------------------

	コンストラクタ(デバイス、座標、使用画像IDをセット)
	@param LPDIRECT3DDEVICE9	描画デバイス
	@param D3DXVECTOR2			描画する位置(x,y)
	@param D3DXVECTOR2			ウインドウの最大サイズ(x,y)

--------------------------------------------------------------*/
CGameSelectCursor::CGameSelectCursor(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position,CursorType _curType) : CGameCursor(_pDevice,_position)
{
	m_texture = CTexMgr.Get(TEX_CURSOR);

	switch(_curType){
	case CUR_SELECT:
		m_rect.left		= 384;
		m_rect.top		= 237;
		m_rect.right    = 768;
		m_rect.bottom	= 305;
		break;
	case CUR_DATA:
		m_rect.left		= 229;
		m_rect.top		= 0;
		m_rect.right    = 403;
		m_rect.bottom	= 49;
		break;
	case CUR_SHOP:
		m_rect.left		= 0;
		m_rect.top		= 0;
		m_rect.right    = 229;
		m_rect.bottom	= 54;
	}
}