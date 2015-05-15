#include "stdafx.h"

#pragma comment(lib,"Strmiids.lib")

/*------------------------------------------------

	コンストラクタ
	@param HWND ウインドウハンドル

 -------------------------------------------------*/
CDirectShow::CDirectShow(HWND hDrawWnd)
{
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	HRESULT hr;
	//////////// DirectShow インターフェイス初期化 ///////////////
	// インスタンス生成
	CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID*)&pGraphBuilder);
 
	// 各インターフェイスの取得
	hr = pGraphBuilder->QueryInterface(
		IID_IMediaControl, (LPVOID*)&pMediaControl);
	if ( hr != S_OK ) return;

	hr = pGraphBuilder->QueryInterface(
		IID_IMediaEventEx, (LPVOID*)&pMediaEvent);
	
	if ( hr != S_OK ) return;
	hr = pGraphBuilder->QueryInterface(
		IID_IMediaPosition, (LPVOID*)&pMediaPosition);
	if ( hr != S_OK ) return;
	hr = pGraphBuilder->QueryInterface(
		IID_IVideoWindow, (LPVOID*)&pVideoWindow);
	if ( hr != S_OK ) return;
	hr = pGraphBuilder->QueryInterface(
		IID_IBasicAudio,(LPVOID *)&pBasicAudio);
	if ( hr != S_OK ) return;
	// DirectShowへ描画の依頼
	hr = pMediaControl->RenderFile(_bstr_t("movie\\op.mp4"));
	// 再生開始 
	if ( hr != S_OK ) return;
	// 通知メッセージの設定
	hr = pMediaEvent->SetNotifyWindow((OAHWND)hNotifyWnd, nGraphNotifyMsg, NULL);
	// 描画先ウィンドウの設定
	hr = pVideoWindow->put_Owner((OAHWND)hDrawWnd);
	if ( hr != S_OK ) return;
	hr = pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
	if ( hr != S_OK ) return;
	hr = pVideoWindow->put_Visible(OATRUE);
	if ( hr != S_OK ) return;


	// 再生映像の設定

	// 描画先ウィンドウ内の描画位置の設定
	pVideoWindow->SetWindowPosition(0, 0, 1280, 730);

	// 映像の再生位置（始めから何ミリ秒か）の+設定
	pMediaPosition->put_CurrentPosition((REFTIME)0.0);
}
/*------------------------------------------------

	デストラクタ

 -------------------------------------------------*/
CDirectShow::~CDirectShow()
{
	//isEnd();
	SAFE_RELEASE(pVideoWindow);
	SAFE_RELEASE(pMediaPosition);
	SAFE_RELEASE(pMediaControl);
	SAFE_RELEASE(pMediaEvent);
	SAFE_RELEASE(pGraphBuilder);
	SAFE_RELEASE(pBasicAudio);
	CoUninitialize();
}
/*------------------------------------------------

	ムービの再生
	@param		なし
	@return		なし

 -------------------------------------------------*/
void CDirectShow::Run()
{
	// 映像の再生開始
	pMediaControl->Run();
}
/*------------------------------------------------

	ムービーが終了しているかチェックする
	@param		なし
	@return		true  : isEnd(再生終了処理)を呼んで終了
				false : 何もしない

 -------------------------------------------------*/
bool CDirectShow::CheckEnd()
{
	// DirectShowからの通知待ち 
	long evCode;
	LONG param1, param2;
	while(SUCCEEDED(pMediaEvent->GetEvent(&evCode, &param1, &param2, 0)))
	{
		pMediaEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
			// 再生終了
			isEnd();
			return true;
		};
	};
	return false;
}

/*------------------------------------------------

	ボリュームの調整
	@param int ボリューム
	@return なし
	
	引数の値について
	使える値は-10000～0です。
	最大音量は0で-10000は無音。
	この値を100で割った物が音量（dB）になります。

 -------------------------------------------------*/
void CDirectShow::Volume(int _volume )
{
	// 左右のバランス　(左右均等の為 0 )
	pBasicAudio->put_Balance(0);
	// 映像の再生開始
	pBasicAudio->put_Volume(_volume);
}
/*------------------------------------------------

	再生終了
	@param		なし
	@return		なし

 -------------------------------------------------*/
void CDirectShow::isEnd()
{
	// 映像の停止処理
	pMediaControl->Stop();

	// 描画ウィンドウからの切り離し
	pVideoWindow->put_Visible(OAFALSE);
	pVideoWindow->put_MessageDrain(NULL);
	pVideoWindow->put_Owner(NULL);

	
}
