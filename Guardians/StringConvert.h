

class CStringConvert
{
public:
	/**
 *	���C�h�����񂩂�}���`�o�C�g������ւ̕ϊ�
 *	@param �}���`�o�C�g������֕ϊ����������C�h������
 *	@param �ϊ���̃}���`�o�C�g������
 */
	static void Narrow(const std::wstring& src, std::string &dest);

/**
 *	�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
 *	@param ���C�h������֕ϊ��������}���`�o�C�g������
 *	@param �ϊ���̃��C�h������
 */
	static void Widen(const std::string& src, std::wstring &dest);
/**
 *	�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
 *	@param ���C�h������֕ϊ��������}���`�o�C�g������
 *	@param �ϊ���̃��C�h������
 */
	static void Widen(const char* src, std::wstring &dest);

	/**
 *	�}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
 *	@param ���C�h������֕ϊ��������}���`�o�C�g������
 *	@param �ϊ���̃��C�h������
 */
	//static void Widen(const char src[], std::wstring &dest);


	static char* BSTRtoCString(BSTR bstr);
};