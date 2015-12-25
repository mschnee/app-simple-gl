#include "Path.h"

#if defined(WIN32)
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")
#endif
#include <locale>
#include <codecvt>
#include <string>


namespace fs
{

namespace
{
	std::wstring s_appPath;
	bool s_appPathInitialized{ false };

	void InitApplicationPath()
	{
		// Read the 8-bit file string, remove the executable...
		char buffer[MAX_PATH];
		GetModuleFileName(nullptr, buffer, MAX_PATH);
		auto pos = std::string(buffer).find_last_of("\\/");
		auto narrow = std::string(buffer).substr(0, pos);

		// ...and then convert to wstring
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		s_appPath = converter.from_bytes(narrow);
		s_appPathInitialized = true;
	}

} // anonymous namespace

std::wstring GetApplicationPath() {
	if (!s_appPathInitialized)
	{
		InitApplicationPath();
	}
	return s_appPath;
}

} //namespace fs