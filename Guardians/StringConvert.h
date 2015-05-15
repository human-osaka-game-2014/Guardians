

class CStringConvert
{
public:
	/**
 *	ワイド文字列からマルチバイト文字列への変換
 *	@param マルチバイト文字列へ変換したいワイド文字列
 *	@param 変換後のマルチバイト文字列
 */
	static void Narrow(const std::wstring& src, std::string &dest);

/**
 *	マルチバイト文字列からワイド文字列への変換
 *	@param ワイド文字列へ変換したいマルチバイト文字列
 *	@param 変換後のワイド文字列
 */
	static void Widen(const std::string& src, std::wstring &dest);
/**
 *	マルチバイト文字列からワイド文字列への変換
 *	@param ワイド文字列へ変換したいマルチバイト文字列
 *	@param 変換後のワイド文字列
 */
	static void Widen(const char* src, std::wstring &dest);

	/**
 *	マルチバイト文字列からワイド文字列への変換
 *	@param ワイド文字列へ変換したいマルチバイト文字列
 *	@param 変換後のワイド文字列
 */
	//static void Widen(const char src[], std::wstring &dest);


	static char* BSTRtoCString(BSTR bstr);
};