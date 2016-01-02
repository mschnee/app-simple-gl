#include "SettingsController.h"
#include "Events/Events.h"
#include "fs/fs.h"
#include <rapidjson/pointer.h>
#include <future>
#include <sstream>
#include <locale>
#include <codecvt>

#if defined(WIN32)
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")
#endif

namespace Backend
{

SettingsController::SettingsController()
	: m_appSettingsPath		(fs::GetApplicationPath()	+ "\\settings.json")
	, m_systemSettingsPath	(fs::GetSharedPath()		+ "\\settings.json")
	, m_userSettingsPath	(fs::GetUserPath()			+ "\\settings.json")
{
	
}

SettingsController::~SettingsController()
{
}

rapidjson::Value* SettingsController::GetValue(const std::string& key) const
{
	auto v = rapidjson::Pointer(key.c_str()).Get(*m_appJson);

	if (!v)
	{
		v = rapidjson::Pointer(key.c_str()).Get(*m_userJson);
	}

	if (!v)
	{
		v = rapidjson::Pointer(key.c_str()).Get(*m_systemJson);
	}

	return v;
}

template<>
int SettingsController::GetValue(const std::string& key, const int& defaultValue)
{
	auto v = GetValue(key);
	if (!v || v->IsNull() || !v->IsNumber())
	{
		return defaultValue;
	}
	
	return v->GetInt();
}

template<>
double SettingsController::GetValue(const std::string& key, const double& defaultValue)
{
	auto v = GetValue(key);
	if (!v || v->IsNull() || !v->IsNumber())
	{
		return defaultValue;
	}

	return v->GetDouble();
}

template<>
std::string SettingsController::GetValue(const std::string& key, const std::string& defaultValue)
{
	auto v = GetValue(key);
	if (!v || v->IsNull() || !v->IsString())
	{
		return defaultValue;
	}

	return v->GetString();
}

template <>
void SettingsController::SetValue(const std::string& key, const std::string& value, Scope scope)
{
	auto d = m_appJson.get();
	if (scope == User)
	{
		d = m_userJson.get();
	} 
	else if (scope == System)
	{
		d = m_systemJson.get();
	}

	rapidjson::Pointer(key.c_str()).Set(*d, value.c_str());
	// notify if necessary
	// Emit(Events::SettingsUpdated);
}

/**
 * Load Settings from the three files and create the settings model
 */
void SettingsController::LoadSettings()
{
	std::async(std::launch::async, &SettingsController::SaveSettingsAsyncInternal, this);
}

/**
 * Asynchronously save settings?
 */
void SettingsController::SaveSettings()
{
	std::async(std::launch::async, &SettingsController::SaveSettingsAsyncInternal, this);
}

void SettingsController::LoadSettingsAsyncInternal()
{
	m_systemSettingsLoaded = m_appSettingsLoaded = m_userSettingsLoaded = false;

	
	fs::readFile<rapidjson::Document>(m_systemSettingsPath, [this](std::unique_ptr<rapidjson::Document> doc)
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
	fs::readFile<rapidjson::Document>(m_userSettingsPath, [this](std::unique_ptr<rapidjson::Document> doc)
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
	fs::readFile<rapidjson::Document>(m_appSettingsPath, [this](std::unique_ptr<rapidjson::Document> doc)
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

	Emit(Events::SettingsReloaded);
}

void SettingsController::SaveSettingsAsyncInternal()
{
	if (m_systemJson && !m_systemJson->IsNull())
	{
		m_updateSystemSettingsMutex.lock();
		fs::writeFile<rapidjson::Document>(m_systemSettingsPath, *m_systemJson, [this]()
		{
			m_updateSystemSettingsMutex.unlock();
		});
	}

	if (m_userJson && !m_userJson->IsNull())
	{
		m_updateUserSettingsMutex.lock();
		fs::writeFile<rapidjson::Document>(m_systemSettingsPath, *m_userJson, [this]()
		{
			m_updateUserSettingsMutex.unlock();
		});
	}

	if (m_appJson && !m_appJson->IsNull())
	{
		m_updateAppSettingsMutex.lock();
		fs::writeFile<rapidjson::Document>(m_systemSettingsPath, *m_appJson, [this]()
		{
			m_updateAppSettingsMutex.unlock();
		});
	}
}

} // namespace Backend