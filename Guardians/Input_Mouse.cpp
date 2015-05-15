// InputMouse.cpp

#include "stdafx.h"

CInputMouse::CInputMouse()
{
	m_hWnd     = NULL;
	m_pDIMouse = NULL;
	m_posX = 0;
	m_posY = 0;
	m_LDown = false;
	m_RDown = false;
	m_MDown = false;
	m_LAction = false;
	m_RAction = false;
	m_MAction = false;

	m_windowMode = true;
}

//マウスデバイスの作成
bool CInputMouse::Create( IDirectInput8* pDInput, HWND hWnd )
{
	HRESULT hr;

	if ( !pDInput ) {
		return false;
	}

	m_hWnd = hWnd;
	RECT rect;
	GetClientRect( m_hWnd, &rect );
	m_wndWid = rect.right - rect.left;
	m_wndHgt = rect.bottom - rect.top;
	m_posX = m_wndWid / 2;
	m_posY = m_wndHgt / 2;

	//マウスデバイスを作成
	hr = pDInput->CreateDevice( GUID_SysMouse, &m_pDIMouse, NULL );
	if ( FAILED( hr ) ) {
		return false;
	}

	//データフォーマットの設定
	hr = m_pDIMouse->SetDataFormat( &c_dfDIMouse2 );
	if ( FAILED( hr ) ) {
		return false;
	}
	
	//バッファサイズの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);							// 構造体のサイズ
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);					// 構造体のヘッダーサイズ
	diprop.diph.dwObj = 0;											// dwHowがDIPH_DIVCEなら0
	diprop.diph.dwHow = DIPH_DEVICE;								// 軸モードを設定する場合はDIPH_DEVICE
	diprop.dwData = 1000;											// バッファサイズ
	hr = m_pDIMouse->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);	// バッファリングデータ取得モード
	if ( FAILED( hr ) ) {
		return false;
	}

	//協調モードの設定
	// DISCL_NOEXCLUSIVE は他のアプリケーションと共有、DISCK_FOREGROUNDはウィンドウがアクティブな状態
	hr = m_pDIMouse->SetCooperativeLevel( m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	if ( FAILED( hr ) ) {
		return false;
	}

	//入力を許可する
	m_pDIMouse->Acquire();
	
	return true;
}

//マウスの入力状態を更新
void CInputMouse::Update()
{
	//リセットする。そのためクリックはUpdateMouse()を次回呼ぶ前に処理しなければならない。
	m_LAction = false;
	m_RAction = false;
	m_MAction = false;

	DIDEVICEOBJECTDATA od;
	DWORD dwItems = 1;
	HRESULT hr;
	while ( true ) {
		hr = m_pDIMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&od,&dwItems,0);
		
		if ( hr == DIERR_INPUTLOST ) {
			m_pDIMouse->Acquire();
		} else
		if ( dwItems == 0 || FAILED(hr) ) {
			
			if ( hr == DIERR_NOTACQUIRED ) {
				m_pDIMouse->Acquire();
			}

			break;
		} else {
			
			switch ( od.dwOfs ) {
				case DIMOFS_X:
					if ( !m_windowMode ) {
						m_posX += (int)od.dwData;
						m_posX = max( 0, min( m_posX, m_wndWid  ) );//ウィンドウからはみ出ないよう調整
					}
					break;
				case DIMOFS_Y:
					if ( !m_windowMode ) {
						m_posY += (int)od.dwData;
						m_posY = max( 0, min( m_posY, m_wndHgt ) );
					}
					break;
				case DIMOFS_BUTTON0://左ボタン
					m_LDown = ( od.dwData & 0x80 )? true : false;
					if ( m_LDown ) { m_LAction = true; }
					break;
				case DIMOFS_BUTTON1://右ボタン
					m_RDown = ( od.dwData & 0x80 )? true : false;
					if ( m_RDown ) { m_RAction = true; }
					break;
				case DIMOFS_BUTTON2://中ボタン
					m_MDown = ( od.dwData & 0x80 )? true : false;
					if ( m_MDown ) { m_MAction = true; }
					break;
			}
		}
	}
}


//マウスデバイスの解放
void CInputMouse::Release()
{
	if ( m_pDIMouse != NULL ) {
		m_pDIMouse->Unacquire();
		m_pDIMouse->Release();
		m_pDIMouse=NULL;
	}

	m_hWnd = NULL;
	m_posX = 0;
	m_posY = 0;
	m_LDown = false;
	m_RDown = false;
	m_MDown = false;
	m_LAction = false;
	m_RAction = false;
	m_MAction = false;

}