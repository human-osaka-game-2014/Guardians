#include "stdafx.h"
/* 定数 */
// 広がる際に変動しない部分のサイズ(隅１個分(128×128) 
const D3DXVECTOR2 CGameWindow::NOMOVE_PARTS_SIZE = D3DXVECTOR2(128.f, 128.f);

/*------------------------------------------
   
    コンストラクタ(デバイス、座標、最大幅、高さ、移動先の位置をセット, その他メンバ変数の初期化を行う)　
	@param	LPDIRECT3DDEVICE9	デバイス
	@param	D3DXVECTOR2			中心座標
	@param	float				広がる最大幅
	@param	float				広がる最大高さ　

------------------------------------------*/
CGameWindow::CGameWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, float _maxWidth, float _maxHeight, D3DXVECTOR2 _nextPosition) :
m_pDevice( _pDevice ), m_position( _position ), m_maxWidth( _maxWidth ), m_maxHeight( _maxHeight ), m_nextPosition( _nextPosition ),
m_state( STATE_SPREAD ), m_width( 0.f ), m_height( 0.f )
{
	// 広がる部分は128×2を除いた部分なので最大幅、最大高さから128×2を引いたものを最大幅、最大高さとする
	m_maxHeight -= NOMOVE_PARTS_SIZE.y*2;
	m_maxWidth -= NOMOVE_PARTS_SIZE.x*2;

	// 一回に広がる幅や高さを計算によって求める
	// 最大高さを広がる時間で割る
	m_spreadHeight = m_maxHeight / SPREAD_TIME;
	if( m_spreadHeight <= 0.f ) {	// 広がる高さが0以下になったら0で固定する
		m_spreadHeight = 0.f;
	}

	// 最大幅を広がる時間で割る
	m_spreadWidth = m_maxWidth / SPREAD_TIME;
	if( m_spreadWidth <= 0.f ) {	// 広がる幅が0以下になったら0で固定する
		m_spreadWidth = 0.f;
	}

	// 移動先の座標が負の値じゃなければ一回(1frame)の移動量も決定しておく
	if( !(m_nextPosition.x < 0.f && m_nextPosition.y < 0.f) )
	{
		// 進む方向(上下or左右)と進む量を決定
		if( m_nextPosition.x > m_position.x || m_nextPosition.x < m_position.x ) {
			m_direction = DIR_HORIZONTAL;
			m_move = (m_nextPosition.x-m_position.x)/MOVE_TIME;
		}
		else if( m_nextPosition.y > m_position.y || m_nextPosition.y < m_position.y ) {
			m_direction = DIR_VIRTICAL;
			m_move = (m_position.y-m_nextPosition.y)/MOVE_TIME;
		}
	}
	// 画像読み込み
	m_texture = CTexMgr.Get( TEX_WINDOW );

	// ステンシルバッファの設定
	m_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	m_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	m_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
}

CGameWindow::~CGameWindow()
{

}

/*------------------------------------------
   
    制御
	@param	なし
	@return	なし　

------------------------------------------*/
void CGameWindow::Control()
{
	// 状態で分岐
	switch( m_state ) {
	case STATE_SPREAD:	// 広がっている状態

		// 現在の高さと幅に1回の移動量を加える
		if( m_height < m_maxHeight ) m_height += m_spreadHeight;
		if( m_width < m_maxWidth ) m_width += m_spreadWidth;

		// 現在の高さor幅が広がる最大幅or最大高さを超えたら状態を動かない状態へ
		if( m_height >= m_maxHeight && m_width >= m_maxWidth ) {
			m_state = STATE_WAIT;
		}
		break;
	case STATE_MOVE:	// 移動状態

		// 現在の位置に移動量を加える
		switch( m_direction ) {
		case DIR_HORIZONTAL:
			m_position.x += m_move;

			// 差が0.1未満になったら移動終わり
			if( fabs(m_position.x-m_nextPosition.x) <= 0.1f ) m_state = STATE_WAIT;
			break;
		case DIR_VIRTICAL:
			m_position.y += m_move;

			// 差が0.1未満になったら移動終わり
			if( fabs(m_position.y-m_nextPosition.y) <= 0.1f ) m_state = STATE_WAIT;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

/*------------------------------------------
   
    描画
	@param	なし
	@return	なし　

------------------------------------------*/
void CGameWindow::Draw()
{
	// 画像の幅、高さを取得
	float texWidth =272; //m_texture.GetWidth();
	float texHeight =272;// m_texture.GetHeight();

//	m_pDevice->SetRenderState(D3DRS_STENCILREF, 1);
//	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);	// ステンシル･バッファ有効

	// 左上の隅
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2,0.f, 0.f, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y); 
	// 右上の隅
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2,texWidth-NOMOVE_PARTS_SIZE.x, 0.f, texWidth, NOMOVE_PARTS_SIZE.y); 
	// 左下の隅
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y+m_height/2,0.f, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x, texHeight); 
	// 右下の隅
	m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y+m_height/2,texWidth-NOMOVE_PARTS_SIZE.x, texHeight-NOMOVE_PARTS_SIZE.y, texWidth, texHeight); 

	// 横方向の間の部分描画
	for( int i = 0, w = (int)m_width; i < m_width; i++ ) {
		if( w / 16 > 0 ) {	// 現在の幅が16pxより大きい場合は一気に16px分描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2, NOMOVE_PARTS_SIZE.x, 0.f, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y+m_height/2, NOMOVE_PARTS_SIZE.x, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+16, texHeight);
			i += 15;
		} else {			// 現在の幅が16pxより小さい場合は1pxずつ描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-NOMOVE_PARTS_SIZE.y-m_height/2, NOMOVE_PARTS_SIZE.x+i%16, 0.f, NOMOVE_PARTS_SIZE.x+i%16+1, NOMOVE_PARTS_SIZE.y);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y+m_height/2, NOMOVE_PARTS_SIZE.x+i%16, texHeight-NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+i%16+1, texHeight);
		}
		w -= 16;
	}

	// 縦方向の間の部分描画
	for( int i = 0, h = (int)m_height; i < m_height; i++ ) {
		if( h / 16 > 0 ) {	// 現在の高さが16pxより大きい場合は一気に16px分描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-m_height/2+i, 0.f, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+16);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-m_height/2+i, texWidth-NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y, texWidth, NOMOVE_PARTS_SIZE.y+16);
			i += 15;
		} else {			// 現在の高さが16pxより小さい場合は1pxずつ描画
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-NOMOVE_PARTS_SIZE.x-m_width/2, m_position.y-m_height/2+i, 0.f, NOMOVE_PARTS_SIZE.y+i%16, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+i%16+1);
			m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x+m_width/2, m_position.y-m_height/2+i, texWidth-NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+i%16, texWidth, NOMOVE_PARTS_SIZE.y+i%16+1);
		}
		h -= 16;
	}

	// 中央の部分描画
	for( int i = 0, w = (int)m_width; i < m_width; i++ ) {
		bool is16pxDraw = false;
		for( int j = 0, h = (int)m_height; j < m_height; j++ ) {
			if( w / 16 > 0 && h / 16 > 0 ) {			// 現在の高さ、幅が16pxより大きい場合は一気に16px分描画
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y+16);
				j += 15;
				is16pxDraw = true;
				h -= 16;
			} else if( w / 16 > 0 && h / 16 <= 0 ){		// 現在の高さが16pxより大きい場合は16*1pxずつ描画	
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x, NOMOVE_PARTS_SIZE.y+1, NOMOVE_PARTS_SIZE.x+16, NOMOVE_PARTS_SIZE.y+2);
			} else if( w / 16 <= 0 && h / 16 > 0 ) {	// 現在の幅が16pxより大きい場合は1*16pxずつ描画
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x+1, NOMOVE_PARTS_SIZE.y, NOMOVE_PARTS_SIZE.x+2, NOMOVE_PARTS_SIZE.y+16);
				j += 15;
				h -= 16;
			} else {									// 現在の高さ、幅が16pxより小さい場合は1pxずつ描画
				m_vertex.DrawTextureLT(m_pDevice, m_texture, m_position.x-m_width/2+i, m_position.y-m_height/2+j, NOMOVE_PARTS_SIZE.x+1, NOMOVE_PARTS_SIZE.y+1, NOMOVE_PARTS_SIZE.x+2, NOMOVE_PARTS_SIZE.y+2);
			}
		}
		if( is16pxDraw ) {
			i += 15;
			w -= 16;
		}
	}
	//kore
	//for( DWORD i = 0; i < m_strLst.size(); i++ ) {
	//	int alpha = m_isSelLst[i] ? 255 : 128;
	//	m_strLst[i]->Draw(800+50.f, 100+30.f+30.f*i, D3DCOLOR_ARGB(alpha,255,255,255), m_strLst[i]->getLength());
	//}
	//	m_strLst[PIC_7]->Draw(800,500,D3DCOLOR_ARGB(255,255,255,255),m_strLst[PIC_7]->getLength());

//	m_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// ステンシル･バッファ無効
}
/*--------------------------------------------------------------

	移動先の座標をセット
	@param	D3DXVECTOR2 
	@return なし

--------------------------------------------------------------*/	
void CGameWindow::SetNextPosition(D3DXVECTOR2 _nextPosition)
{
	m_nextPosition.x = _nextPosition.x;
	m_nextPosition.y = _nextPosition.y;

	// X軸が同じの場合縦に移動
	if( m_nextPosition.x == m_position.x ) {
		m_direction = DIR_VIRTICAL;
		m_state = STATE_MOVE;
		// 一回の移動量
		m_move = (m_nextPosition.y - m_position.y) / MOVE_TIME;
	}
	// Y軸が同じの場合横に移動
	else if( m_nextPosition.y == m_position.y ) {
		m_direction = DIR_HORIZONTAL;
		m_state = STATE_MOVE;
		// 一回の移動量
		m_move = (m_nextPosition.x - m_position.x) / MOVE_TIME;
	}
}
/*--------------------------------------------------------------

	移動先の座標をセット
	@param	int 探すアイテムの番号
	@param  ItemType 探すListのタイプ(装備or消費アイテム)
	@return Listの配列番号

--------------------------------------------------------------*/	
int CGameWindow::Search(int _itemNum,ItemType _type)
{
	int head,tail,center;
	if( _type == TYPE_EQUIP ){
		// 装備リストから検索
		head = 0;
		tail = m_pGameData->m_equipList.size();
		while( head <= tail){
			center = (head + tail) / 2;
			if( m_pGameData->m_equipList[center].no == _itemNum )
				return center; // 発見した時は発見した配列の要素を返す
			else if( m_pGameData->m_equipList[center].no <_itemNum )
				head = center + 1;
			else
				tail = center -1;
		}
	}else{
		// アイテムリストから検索
		head = 0;
		tail = m_pGameData->m_itemList.size();
		while( head <= tail){
			center = (head + tail) / 2;
			if( m_pGameData->m_itemList[center].no == _itemNum )
				return center; // 発見した時は発見した配列の要素を返す
			else if( m_pGameData->m_itemList[center].no <_itemNum )
				head = center + 1;
			else
				tail = center -1;
		}
	}
	// 見つからなかった
	return -1;
}
/*--------------------------------------------------------------

	ウインドウの状態を取得
	@param  なし
	@return 状態

--------------------------------------------------------------*/
CGameWindow::State CGameWindow::Get()
{
	return m_state;
}
/*--------------------------------------------------------------

	ゲームデータをセットする
	@param  CGameData* ゲームデータ

--------------------------------------------------------------*/
void CGameWindow::SetGameData(CGameData* _pGameData)
{
	m_pGameData = _pGameData;
}

