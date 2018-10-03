
#include "stdafx.h"

void CStringConvert::Narrow(const std::wstring &src, std::string &dest) {
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	size_t ret;
	wcstombs_s(&ret, mbs, src.length() * MB_CUR_MAX + 1, src.c_str(), _TRUNCATE);
	dest = mbs;
	delete [] mbs;
}

/*----------------------------------------------------------
 
	�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
 	@param ���C�h������֕ϊ��������}���`�o�C�g������
 	@param �ϊ���̃��C�h������

-----------------------------------------------------------*/
void CStringConvert::Widen(const std::string& src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	size_t ret;
	mbstowcs_s(&ret, wcs, src.length() + 1, src.c_str(), _TRUNCATE);
	dest = wcs;
	delete [] wcs;

}

/*----------------------------------------------------------

 	�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
 	@param ���C�h������֕ϊ��������}���`�o�C�g������
 	@param �ϊ���̃��C�h������

 -----------------------------------------------------------*/
void CStringConvert::Widen(const char* src, std::wstring &dest)
{
	wchar_t *wcs = new wchar_t[strlen(src) + 1];
	size_t ret;
	mbstowcs_s(&ret, wcs, strlen(src) + 1, src,  _TRUNCATE);
	dest = wcs;
	delete [] wcs;

}

char* CStringConvert::BSTRtoCString(BSTR bstr){
    int    out_size;
    char   *cstring;
    // UTF-16�����񂩂�Shift-JIS�ɕϊ������Ƃ��̕����񒷂����߂�B
    out_size = WideCharToMultiByte(CP_ACP, 0, (OLECHAR*)bstr, -1,NULL, 0, NULL, NULL);
    // Shift-JIS������̗̈���m�ۂ���B
    cstring  = (char*)malloc((out_size+1) * sizeof(char));
    // UTF-16�����񂩂�Shift-JIS�ɕϊ�����B
    WideCharToMultiByte(CP_ACP, 0, (OLECHAR*)bstr, -1, cstring,out_size, NULL, NULL);
    return cstring;
}
