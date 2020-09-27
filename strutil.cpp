#include "strutil.h"

//#include <locale>
//#include <codecvt>
#include <Windows.h>
#include <stringapiset.h>

std::string wstr_convert(fs::path string_to_convert) {
	/*using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(string_to_convert);*/

	char buffer[250];
	WideCharToMultiByte(CP_OEMCP, WC_COMPOSITECHECK /*| WC_NO_BEST_FIT_CHARS*/, string_to_convert.c_str(), -1, buffer, sizeof(buffer),
		NULL, NULL);
	return buffer;
}