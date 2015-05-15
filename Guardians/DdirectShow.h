class CDirectShow
{
public:

private:
	// 描画用DirectShowインターフェイス
	IGraphBuilder*   pGraphBuilder;
	IMediaControl*   pMediaControl;
	IMediaEventEx*   pMediaEvent;
	IVideoWindow*    pVideoWindow;
	IMediaPosition*  pMediaPosition;
	IBasicAudio*	 pBasicAudio;
	HWND     hNotifyWnd;        // DirectShowライブラリからのメッセージ送信先ウィンドウ
	UINT     nGraphNotifyMsg;   // 通知メッセージ

//	LPCTSTR  lpszFilename;      // 再生映像のファイル名

public:
	// コンストラクタ
	CDirectShow(HWND hDrawWnd);
	// デストラクタ
	~CDirectShow();
	// 終わっているかチェック
	bool CheckEnd();
	// ムービーの再生
	void Run();
	// 音量の調整
	void Volume(int _valume = -5000);
	// 終了
	void isEnd();
private:
};