#include "SettingsController.h"
#include "Events/Events.h"
#include "fs/fs.h"
#include <future>
#include <sstream>

#if defined(WIN32)
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")
#endif

namespace Backend
{

namespace
{
std::wstring s_systemSettingsPath;
std::wstring s_appSettingsPath;
std::wstring s_userSettingsPath;

void InitSettingsPaths()
{
#if defined(WIN32)
	PWSTR location;

	// get system settings
	{
		CoInitialize(nullptr);
		SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, &location);

		std::wstringstream ss;
		ss << location << L"/TwoPiTau.com/settings.json";
		s_systemSettingsPath = ss.str();
		CoTaskMemFree(static_cast<void*>(location));
	}

	// get user settings
	{
		CoInitialize(nullptr);
		SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &location);

		std::wstringstream ss;
		ss << location << L"/TwoPiTau.com/settings.json";
		s_userSettingsPath = ss.str();
		CoTaskMemFree(static_cast<void*>(location));
	}
	// get app settings 
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string narrow = std::string(buffer).substr(0, pos);

		std::wstringstream ss;
		std::wstring ws;
		ws.assign(narrow.begin(), narrow.end());
		ss << ws << L"\\settings.json";
		s_appSettingsPath = ss.str();
	}
#endif

}

} // anonymous namespace

SettingsController::SettingsController()
{
	InitSettingsPaths();
}

SettingsController::~SettingsController()
{
}

template <typename T>
T& SettingsController::GetValue(const std::string& key, const T& defaultValue)
{
}

template <typename T>
void SettingsController::SetValue(const std::string& key, const T& value, Scope)
{
}

/**
 * Load Settings from the three files and create the settings model
 */
void SettingsController::LoadSettings()
{
	std::async(&SettingsController::LoadSettingsInternal, this);
}

void SettingsController::LoadSettingsInternal()
{
	m_systemSettingsLoaded = m_appSettingsLoaded = m_userSettingsLoaded = false;

	
	fs::readFile<rapidjson::Document>(s_systemSettingsPath,[this](std::unique_ptr<rapidjson::Document> doc)
	{
		std::lock_guard<std::mutex> lock(m_updateSystemSettingsMutex);
		if (m_systemJson)
		{
			m_systemJson.release();
		}
		m_systemJson = std::move(doc);
		m_systemSettingsLoaded = true;
	});

	// load user settings
	fs::readFile<rapidjson::Document>(s_userSettingsPath, [this](std::unique_ptr<rapidjson::Document> doc)
	{
		std::lock_guard<std::mutex> lock(m_updateSystemSettingsMutex);
		if (m_userJson)
		{
			m_userJson.release();
		}
		m_userJson = std::move(doc);
		m_userSettingsLoaded = true;
	});
	
	// load app settings
	fs::readFile<rapidjson::Document>(s_appSettingsPath, [this](std::unique_ptr<rapidjson::Document> doc)
	{
		std::lock_guard<std::mutex> lock(m_updateSystemSettingsMutex);
		if (m_appJson)
		{
			m_appJson.release();
		}
		m_appJson = std::move(doc);
		m_appSettingsLoaded = true;
	});

	// kick off the file loading.
	do
	{
		// wait...
	//} while (!m_systemSettingsLoaded && !m_appSettingsLoaded && !m_userSettingsLoaded);
	} while (!m_appSettingsLoaded);

	UpdateLivingJson();
	Emit(Events::SettingsReloaded);
}

void SettingsController::UpdateLivingJson()
{
}

} // namespace Backend