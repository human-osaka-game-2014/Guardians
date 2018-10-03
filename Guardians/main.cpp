

#include "stdafx.h"

#pragma comment (lib,"winmm.lib")


// �O���[�o���ϐ�
TCHAR szTitle[] = {"Guardians"};					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[] = {"mainWindowClass"};	// ���C�� �E�B���h�E �N���X��

SIZE  g_sizeWindowMode = { 1280, 720 };  // �E�C���h�E�E���[�h
SIZE  g_sizeFullMode = { 640, 480 };  // �t���X�N���[���E���[�h

HWND  hWnd  = NULL; // �E�C���h�E�E�n���h��
HMENU  g_hMenu   = NULL; // ���j���[�E�n���h��
RECT  g_rectWindow;       // �E�C���h�E�E���[�h�ł̍Ō�̈ʒu
bool  g_bWindow = true;      // �N�����̉�ʃ��[�h
bool  m_isActive;
CGraphicsDevice* graphics = NULL;
CSceneManager* scene;

/*--------------------------------------------------------------

	���b�Z�[�W����

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
	case WM_KEYDOWN:		// �L�[�������ꂽ��
		if( _wp == VK_ESCAPE ) {
//			DestroyWindow(_hWnd);
			PostQuitMessage(0);
		}
		break;
	case WM_SYSKEYDOWN:     // Alt + ����L�[�̏����Ɏg��
		switch(_wp)
		{
		case VK_RETURN:     // Alt + Enter�������Ɛ؂�ւ�
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

	�E�B���h�E�N���X�̓o�^

-------------------------------------------------------------*/
ATOM RegistWindowClass(HINSTANCE _hInstance)
{
	WNDCLASS winc;

	//Windows���̐ݒ�
	winc.style 			= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= _hInstance;
	winc.hIcon			= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= szWindowClass;
	
	//Windows�̓o�^
	return RegisterClass(&winc);
}

/*-------------------------------------------------------------

	�E�B���h�E����

--------------------------------------------------------------*/
BOOL CreateMainWindow(HINSTANCE _hInstance, int _nCmdShow, int _clientWidth, int _clientHeight)
{
	int dH = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME) * 2;
	int dW = GetSystemMetrics(SM_CXFRAME) * 2;

		// ���C���E�E�C���h�E�쐬
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
		// (�E�C���h�E�E���[�h�p)
		rect.top = CW_USEDEFAULT;
		rect.left = CW_USEDEFAULT;
		rect.right = g_rectWindow.right;
		rect.bottom = g_rectWindow.bottom;
	}
	else
	{
		// (�t���X�N���[���E���[�h�p)
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


	// �E�C���h�E�\��
	ShowWindow( hWnd, SW_SHOWNORMAL);
	UpdateWindow( hWnd );

	return TRUE;
}


/*-------------------------------------------------------------

	���C�����[�`��

-------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE _hInstance , HINSTANCE _hPrevInstance ,
			PSTR _lpCmdLine , int _nCmdShow)

{
	// ���������[�N���o
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �g�p���Ă��Ȃ������͎g�p���Ă��Ȃ����Ƃ𖾋L
	UNREFERENCED_PARAMETER(_hPrevInstance);
	UNREFERENCED_PARAMETER(_lpCmdLine);

//#ifdef _DEBUG
	g_bWindow = true;
//#else
//	g_bWindow = false;
//#endif


	MSG msg;

	//Windows�̓o�^
	RegistWindowClass(_hInstance);

	//Windows�̐���
	if (!CreateMainWindow(_hInstance, _nCmdShow,1280,730 )) return 0;

	graphics = new CGraphicsDevice();

	graphics->InitD3D(hWnd,g_bWindow);	// Direct3D������

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
				DestroyWindow( hWnd );	// �G���[������ꍇ�C�A�v���P�[�V�������I������

				SyncOld = SyncNow;
			}
		}
	}

	timeEndPeriod(1);

	SAFE_DELETE(scene);
	SAFE_DELETE(graphics);
	// �A�v���P�[�V�������
	//app.Release();
//	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}