

#include "stdafx.h"

#pragma comment (lib,"winmm.lib")


// グローバル変数
TCHAR szTitle[] = {"Guardians"};					// タイトル バーのテキスト
TCHAR szWindowClass[] = {"mainWindowClass"};	// メイン ウィンドウ クラス名

SIZE  g_sizeWindowMode = { 1280, 720 };  // ウインドウ・モード
SIZE  g_sizeFullMode = { 640, 480 };  // フルスクリーン・モード

HWND  hWnd  = NULL; // ウインドウ・ハンドル
HMENU  g_hMenu   = NULL; // メニュー・ハンドル
RECT  g_rectWindow;       // ウインドウ・モードでの最後の位置
bool  g_bWindow = true;      // 起動時の画面モード
bool  m_isActive;
CGraphicsDevice* graphics = NULL;
CSceneManager* scene;

/*--------------------------------------------------------------

	メッセージ処理

--------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND _hWnd , UINT _msg , WPARAM _wp , LPARAM _lp) {

	switch (_msg) {
	case WM_ACTIVATE:
		if( graphics != NULL ) {
			graphics->SetActiveFlag((LOWORD(_wp) != 0));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:		// キーが押された時
		if( _wp == VK_ESCAPE ) {
//			DestroyWindow(_hWnd);
			PostQuitMessage(0);
		}
		break;
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch(_wp)
		{
		case VK_RETURN:     // Alt + Enterを押すと切り替え
			graphics->ChangeDisplayMode();

			scene->SetGraphics(*graphics);

			break;
		default:
			break;
		}
		break;
	}
	return DefWindowProc(_hWnd , _msg , _wp , _lp);
}

/*-------------------------------------------------------------

	ウィンドウクラスの登録

-------------------------------------------------------------*/
ATOM RegistWindowClass(HINSTANCE _hInstance)
{
	WNDCLASS winc;

	//Windows情報の設定
	winc.style 			= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= _hInstance;
	winc.hIcon			= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= szWindowClass;
	
	//Windowsの登録
	return RegisterClass(&winc);
}

/*-------------------------------------------------------------

	ウィンドウ生成

--------------------------------------------------------------*/
BOOL CreateMainWindow(HINSTANCE _hInstance, int _nCmdShow, int _clientWidth, int _clientHeight)
{
	int dH = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) * 2;
	int dW = GetSystemMetrics(SM_CXFRAME) * 2;

		// メイン・ウインドウ作成
	g_rectWindow.top = 0;
	g_rectWindow.left = 0;
	g_rectWindow.right = g_sizeWindowMode.cx;
	g_rectWindow.bottom = g_sizeWindowMode.cy;
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
	g_rectWindow.right = g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom = g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top = 0;
	g_rectWindow.left = 0;

	RECT rect;
	if (g_bWindow)
	{
		// (ウインドウ・モード用)
		rect.top = CW_USEDEFAULT;
		rect.left = CW_USEDEFAULT;
		rect.right = g_rectWindow.right;
		rect.bottom = g_rectWindow.bottom;
	}
	else
	{
		// (フルスクリーン・モード用)
		rect.top = 0;
		rect.left = 0;
		rect.right = g_sizeFullMode.cx;
		rect.bottom = g_sizeFullMode.cy;

		//g_hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	}


	hWnd = CreateWindow(
		szWindowClass, 
		szTitle,
		g_bWindow ? WS_OVERLAPPEDWINDOW : WS_POPUP,
		rect.left, rect.top, rect.right, rect.bottom,
		NULL, NULL, _hInstance, NULL);
		if ( hWnd == NULL)
		return E_FAIL;


	// ウインドウ表示
	ShowWindow( hWnd, SW_SHOWNORMAL);
	UpdateWindow( hWnd );

	return TRUE;
}


/*-------------------------------------------------------------

	メインルーチン

-------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE _hInstance , HINSTANCE _hPrevInstance ,
			PSTR _lpCmdLine , int _nCmdShow)

{
	// メモリリーク検出
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 使用していない引数は使用していないことを明記
	UNREFERENCED_PARAMETER(_hPrevInstance);
	UNREFERENCED_PARAMETER(_lpCmdLine);

//#ifdef _DEBUG
	g_bWindow = true;
//#else
//	g_bWindow = false;
//#endif


	MSG msg;

	//Windowsの登録
	RegistWindowClass(_hInstance);

	//Windowsの生成
	if (!CreateMainWindow(_hInstance, _nCmdShow,1280,730 )) return 0;

	graphics = new CGraphicsDevice();

	graphics->InitD3D(hWnd,g_bWindow);	// Direct3D初期化

	graphics->SetWindowRect(g_rectWindow);

	
	scene = new CSceneManager(hWnd,*graphics);

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	setlocale(LC_CTYPE, "jpn");

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) {
			
				scene->Run();

				if (!graphics->Idling())
				DestroyWindow( hWnd );	// エラーがある場合，アプリケーションを終了する

				SyncOld = SyncNow;
			}
		}
	}

	timeEndPeriod(1);

	SAFE_DELETE(scene);
	SAFE_DELETE(graphics);
	// アプリケーション解放
	//app.Release();
//	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}