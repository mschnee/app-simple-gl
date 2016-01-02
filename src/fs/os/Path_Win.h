#pragma once
#include "IPath.h"
#include <locale>
#include <codecvt>
#include <sstream>
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")

namespace fs {
namespace os {

namespace
{

// TODO move these to a common place
static std::wstring s_applicationName = L"Sprites";
static std::wstring s_companyName = L"TwoPiTau.com";

// from 
std::string ws2s(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}

} // anonymous namespace 

class Path_Win : public IPath {
public:
    std::string GetApplicationPath() override {
        if (!m_applicationPathInitialized) {
            InitApplicationPath();
			m_applicationPathInitialized = true;
        }
        return m_applicationPath;
    };

	std::string GetSharedPath() override {
		if (!m_sharedPathInitialized) {
			InitSharedPath();
			m_sharedPathInitialized = true;
		}
		return m_sharedPath;
	};

	std::string GetUserPath() override {
		if (!m_userPathInitialized) {
			InitUserPath();
			m_userPathInitialized = true;
		}
		return m_userPath;
	};

private:
    void InitApplicationPath() {
        char buffer[MAX_PATH];
        GetModuleFileName(nullptr, buffer, MAX_PATH);
        auto pos = std::string(buffer).find_last_of("\\/");
        m_applicationPath = std::string(buffer).substr(0, pos);
    }

	void InitUserPath()
    {
		PWSTR location;
		CoInitialize(nullptr);
		SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &location);

		std::wstringstream ss;
		ss << location << L"\\" << s_companyName << L"\\" << s_applicationName;
		m_userPath = ws2s(ss.str());
		CoTaskMemFree(static_cast<void*>(location));
    }

	void InitSharedPath()
    {
		PWSTR location;
		CoInitialize(nullptr);
		SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, &location);

		std::wstringstream ss;
		ss << location << L"\\" << s_companyName << L"\\" << s_applicationName;
		m_sharedPath = ws2s(ss.str());
		CoTaskMemFree(static_cast<void*>(location));
    }

    bool m_applicationPathInitialized { false };
	bool m_sharedPathInitialized{ false };
	bool m_userPathInitialized{ false };

    std::string m_applicationPath;
	std::string m_userPath;
	std::string m_sharedPath;
};

} // namespace fs::os
} // namespace fs