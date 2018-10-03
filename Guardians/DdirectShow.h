class CDirectShow
{
public:

private:
	// �`��pDirectShow�C���^�[�t�F�C�X
	IGraphBuilder*   pGraphBuilder;
	IMediaControl*   pMediaControl;
	IMediaEventEx*   pMediaEvent;
	IVideoWindow*    pVideoWindow;
	IMediaPosition*  pMediaPosition;
	IBasicAudio*	 pBasicAudio;
	HWND     hNotifyWnd;        // DirectShow���C�u��������̃��b�Z�[�W���M��E�B���h�E
	UINT     nGraphNotifyMsg;   // �ʒm���b�Z�[�W

//	LPCTSTR  lpszFilename;      // �Đ��f���̃t�@�C����

public:
	// �R���X�g���N�^
	CDirectShow(HWND hDrawWnd);
	// �f�X�g���N�^
	~CDirectShow();
	// �I����Ă��邩�`�F�b�N
	bool CheckEnd();
	// ���[�r�[�̍Đ�
	void Run();
	// ���ʂ̒���
	void Volume(int _valume = -5000);
	// �I��
	void isEnd();
private:
};