#pragma once
#include "Path_Win.h"
#include <locale>
#include <codecvt>
#include <sstream>
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")

namespace os {

namespace
{

// from 
std::string ws2s(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}

} // anonymous namespace 


std::string Path_Win::GetApplicationPath()
{
	if (!m_applicationPathInitialized) {
		InitApplicationPath();
		m_applicationPathInitialized = true;
	}
	return m_applicationPath;
};

std::string Path_Win::GetSharedPath()
{
	if (!m_sharedPathInitialized) {
		InitSharedPath();
		m_sharedPathInitialized = true;
	}
	return m_sharedPath;
};

std::string Path_Win::GetUserPath()
{
	if (!m_userPathInitialized) {
		InitUserPath();
		m_userPathInitialized = true;
	}
	return m_userPath;
};


void Path_Win::InitApplicationPath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(nullptr, buffer, MAX_PATH);
	auto pos = std::string(buffer).find_last_of("\\/");
	m_applicationPath = std::string(buffer).substr(0, pos);
}

void Path_Win::InitUserPath()
{
	PWSTR location;
	CoInitialize(nullptr);
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &location);

	std::wstringstream ss;
	ss << location << L"\\" << s_wCompanyName << L"\\" << s_wApplicationName;
	m_userPath = ws2s(ss.str());
	CoTaskMemFree(static_cast<void*>(location));
}

void Path_Win::InitSharedPath()
{
	PWSTR location;
	CoInitialize(nullptr);
	SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, &location);

	std::wstringstream ss;
	ss << location << L"\\" << s_wCompanyName << L"\\" << s_wApplicationName;
	m_sharedPath = ws2s(ss.str());
	CoTaskMemFree(static_cast<void*>(location));
}

} // namespace os
