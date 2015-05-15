#include "stdafx.h"
/*--------------------------------------------------------------

	処理内容:TIMEやMONEY、数字の表示
	作成者:岸
	更新日:11/08
	関数　
		TIMEの計算の修正
	変数　
		追加なし
		文字の修正

--------------------------------------------------------------*/
const D3DXVECTOR2 CGameDataWindow::WINDOW_POSITION = D3DXVECTOR2(71.f, 768.f);	// 「ウィンドウ」移動後座標
const D3DXVECTOR2 CGameDataWindow::TIME_POSITION = D3DXVECTOR2(10.f, 660.f);	// 「プレイ時間」描画座標
const D3DXVECTOR2 CGameDataWindow::MONEY_POSITION = D3DXVECTOR2(10.f, 665.f);	// 「所持金」描画座標


/*------------------------------------------
   
    コンストラクタ(デバイス、座標、ゲームデータをセット, その他メンバ変数の初期化を行う)　
	@param	LPDIRECT3DDEVICE9	デバイス
	@param	D3DXVECTOR2			中心座標
	@param	float				広がる最大幅
	@param	float				広がる最大高さ　

------------------------------------------*/
CGameDataWindow::CGameDataWindow(LPDIRECT3DDEVICE9 _pDevice, D3DXVECTOR2 _position, CGameData* _pGameData) : 
CGameWindow(_pDevice, _position,static_cast<float>(MAX_WIDTH),static_cast<float>(MAX_HEIGHT), WINDOW_POSITION), m_pGameData( _pGameData )
{
	// このウィンドウでは広がる状態はカットして移動状態からスタート
	m_state = STATE_MOVE;
	m_width = MAX_WIDTH - NOMOVE_PARTS_SIZE.x*2;
	m_height = MAX_HEIGHT;

}
CGameDataWindow::~CGameDataWindow()
{

}

/*------------------------------------------
   
    制御
	@param	なし
	@return	なし　

------------------------------------------*/
void CGameDataWindow::Control()
{
	CGameWindow::Control();
}

/*------------------------------------------
   
    描画
	@param	なし
	@return	なし　

------------------------------------------*/
void CGameDataWindow::Draw()
{
	CGameWindow::Draw();

   
	int l_time=m_pGameData->m_playTime;		//TIMEの取得	
	int l_timeSeconds=l_time%60;					//秒のみの計算
	int l_timeMinutes=l_time/60%100%60;				//分のみの計算
	int l_timeHours=l_time/3600;					//時間のみの計算
	int l_money = m_pGameData->m_money ;	
	int l_timediv[6];								//TIMEを分割
	int l_moneydiv[6];
	for(int i = 0; i < 6;i++){
		l_moneydiv[i] = -1;
	}//MONEYを分割
	for(int i=5;i>=4;i--){							//TIME(秒)のステータスを1桁ずつ格納
		l_timediv[i]=l_timeSeconds%10;	
		l_timeSeconds/=10;
	}
	for(int i=3;i>=2;i--){							//TIME(分)のステータスを1桁ずつ格納
		l_timediv[i]=l_timeMinutes%10;	
		l_timeMinutes/=10;
	}
	for(int i=1;i>=0;i--){							//TIME(時間)のステータスを1桁ずつ格納
		l_timediv[i]=l_timeHours%10;	
		l_timeHours/=10;
	}
	m_digits = 6;
	int digits = 0;
	while( l_money != 0 ){
		//MONEYのステータスを1桁ずつ格納
		l_moneydiv[digits] = l_money % 10;
		l_money /= 10;
		digits++;
	}

	/*TIMEの表示*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x, TIME_POSITION.y,254,412,382,428);						//TIMEの表示

	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x + 130, TIME_POSITION.y,340,412,352,428);				//コロンの表示	
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x + 168, TIME_POSITION.y,340,412,352,428);				//コロンの表示
	for( int i = 0; i < 2; i++ ) {																										    //TIME(時間)の表示を処理
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+100+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	for( int i = 2; i < 4; i++ ) {																											//TIME(分)の表示を処理
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+108+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	for( int i = 4; i < 6; i++ ) {																										    //TIME(秒)の表示を処理
		CStringList::smallNumberStrList[l_timediv[i]]->Draw( TIME_POSITION.x+116+16*i,  TIME_POSITION.y+8, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
	m_vertex.DrawTextureLT(m_pDevice, m_texture, TIME_POSITION.x-10, TIME_POSITION.y+20,600,272,800,274);										//仕切りの表示
	/*MONEYの表示*/
	m_vertex.DrawTextureLT(m_pDevice, m_texture,  MONEY_POSITION.x,MONEY_POSITION.y+25,384,412,512,428);										//MONEYの表示
	
	for( int i = 0; i < 6; i++ ) { 	//所持金の表示
		if( i == 5 && l_moneydiv[m_digits-1-5] == -1 ){	
			m_vertex.DrawTextureLT(m_pDevice, m_texture,  MONEY_POSITION.x,MONEY_POSITION.y+25,384,412,512,428);										//MONEYの表示
			CStringList::smallNumberStrList[0]->Draw( MONEY_POSITION.x+100+16*5,  MONEY_POSITION.y+32, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[0]->getLength());
		}
		if(	l_moneydiv[m_digits-1-i] == -1 ) continue;
		CStringList::smallNumberStrList[l_moneydiv[m_digits-1-i]]->Draw( MONEY_POSITION.x+100+16*i,  MONEY_POSITION.y+32, D3DCOLOR_ARGB(255,255,255,255), CStringList::smallNumberStrList[i]->getLength());
	}
}
