#include "stdafx.h"

#pragma comment(lib,"Strmiids.lib")

/*------------------------------------------------

	�R���X�g���N�^
	@param HWND �E�C���h�E�n���h��

 -------------------------------------------------*/
CDirectShow::CDirectShow(HWND hDrawWnd)
{
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	HRESULT hr;
	//////////// DirectShow �C���^�[�t�F�C�X������ ///////////////
	// �C���X�^���X����
	CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID*)&pGraphBuilder);
 
	// �e�C���^�[�t�F�C�X�̎擾
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
	// DirectShow�֕`��̈˗�
	hr = pMediaControl->RenderFile(_bstr_t("movie\\op.mp4"));
	// �Đ��J�n 
	if ( hr != S_OK ) return;
	// �ʒm���b�Z�[�W�̐ݒ�
	hr = pMediaEvent->SetNotifyWindow((OAHWND)hNotifyWnd, nGraphNotifyMsg, NULL);
	// �`���E�B���h�E�̐ݒ�
	hr = pVideoWindow->put_Owner((OAHWND)hDrawWnd);
	if ( hr != S_OK ) return;
	hr = pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
	if ( hr != S_OK ) return;
	hr = pVideoWindow->put_Visible(OATRUE);
	if ( hr != S_OK ) return;


	// �Đ��f���̐ݒ�

	// �`���E�B���h�E���̕`��ʒu�̐ݒ�
	pVideoWindow->SetWindowPosition(0, 0, 1280, 730);

	// �f���̍Đ��ʒu�i�n�߂��牽�~���b���j��+�ݒ�
	pMediaPosition->put_CurrentPosition((REFTIME)0.0);
}
/*------------------------------------------------

	�f�X�g���N�^

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

	���[�r�̍Đ�
	@param		�Ȃ�
	@return		�Ȃ�

 -------------------------------------------------*/
void CDirectShow::Run()
{
	// �f���̍Đ��J�n
	pMediaControl->Run();
}
/*------------------------------------------------

	���[�r�[���I�����Ă��邩�`�F�b�N����
	@param		�Ȃ�
	@return		true  : isEnd(�Đ��I������)���Ă�ŏI��
				false : �������Ȃ�

 -------------------------------------------------*/
bool CDirectShow::CheckEnd()
{
	// DirectShow����̒ʒm�҂� 
	long evCode;
	LONG param1, param2;
	while(SUCCEEDED(pMediaEvent->GetEvent(&evCode, &param1, &param2, 0)))
	{
		pMediaEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
			// �Đ��I��
			isEnd();
			return true;
		};
	};
	return false;
}

/*------------------------------------------------

	�{�����[���̒���
	@param int �{�����[��
	@return �Ȃ�
	
	�����̒l�ɂ���
	�g����l��-10000�`0�ł��B
	�ő剹�ʂ�0��-10000�͖����B
	���̒l��100�Ŋ������������ʁidB�j�ɂȂ�܂��B

 -------------------------------------------------*/
void CDirectShow::Volume(int _volume )
{
	// ���E�̃o�����X�@(���E�ϓ��̈� 0 )
	pBasicAudio->put_Balance(0);
	// �f���̍Đ��J�n
	pBasicAudio->put_Volume(_volume);
}
/*------------------------------------------------

	�Đ��I��
	@param		�Ȃ�
	@return		�Ȃ�

 -------------------------------------------------*/
void CDirectShow::isEnd()
{
	// �f���̒�~����
	pMediaControl->Stop();

	// �`��E�B���h�E����̐؂藣��
	pVideoWindow->put_Visible(OAFALSE);
	pVideoWindow->put_MessageDrain(NULL);
	pVideoWindow->put_Owner(NULL);

	
}
