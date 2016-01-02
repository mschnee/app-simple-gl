#pragma once
#include <EventEmitter/Emitter.h>
#include <rapidjson/document.h>
#include <mutex>

namespace Backend 
{
class SettingsController : public EventEmitter::Emitter
{
	enum Scope 
	{
		System = 0, // setting belongs to the system, goes in system config
		Application, // settings belongs to the application, goes in file next to application
		User // settings is user-specific, goes in user directory
	};
public:
	SettingsController();
	~SettingsController();
	
	template<typename T>
	T GetValue(const std::string& key, const T& defaultValue);
	
	template<typename T>
	void SetValue(const std::string& key, const T& value, Scope = User);
	
	void LoadSettings();
	void SaveSettings();

protected:
	rapidjson::Value* GetValue(const std::string& key) const;
	void LoadSettingsAsyncInternal();
	void SaveSettingsAsyncInternal();

private:
	std::unique_ptr<rapidjson::Document> m_systemJson {nullptr};
	std::unique_ptr<rapidjson::Document> m_appJson {nullptr};
	std::unique_ptr<rapidjson::Document> m_userJson {nullptr};

	// var living = extend(true, {}, user, app, system);
	rapidjson::Document m_livingJson; 

	std::mutex m_updateSystemSettingsMutex;
	std::mutex m_updateAppSettingsMutex;
	std::mutex m_updateUserSettingsMutex;
	std::mutex m_updateLivingSettingsMutex;

	bool m_systemSettingsLoaded{ false };
	bool m_appSettingsLoaded{ false };
	bool m_userSettingsLoaded{ false };

	std::string m_appSettingsPath;
	std::string m_systemSettingsPath;
	std::string m_userSettingsPath;
};

} // namespace Backent