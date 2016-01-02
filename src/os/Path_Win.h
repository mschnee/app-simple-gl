#pragma once
#include "IPath.h"
#include <locale>
#include <codecvt>
#include <sstream>
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")

namespace os {

static std::wstring s_wApplicationName = L"Sprites";
static std::wstring s_wCompanyName = L"TwoPiTau.com";
static std::string s_applicationName = "Sprites";
static std::string s_companyName = "TwoPiTau.com";

class Path_Win : public IPath {
public:
	std::string GetApplicationPath() override;
	std::string GetSharedPath() override;
	std::string GetUserPath() override;

private:
	void InitApplicationPath();
	void InitUserPath();
	void InitSharedPath();
	
private:
	bool m_applicationPathInitialized { false };
	bool m_sharedPathInitialized{ false };
	bool m_userPathInitialized{ false };

	std::string m_applicationPath;
	std::string m_userPath;
	std::string m_sharedPath;
};

} // namespace os
