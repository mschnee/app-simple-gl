#pragma once
#include <EventEmitter/Emitter.h>
#include <rapidjson/document.h>

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
	T& GetValue(const std::string& key, const T& defaultValue);
	
	template<typename T>
	void SetValue(const std::string& key, const T& value, Scope = User);
	void LoadSettingsSync();
	void LoadSettings(); // async

protected:
	void LoadSettingsInternal();
	void UpdateLivingJson();

private:
	rapidjson::Document m_systemJson;
	rapidjson::Document m_appJson;
	rapidjson::Document m_userJson;

	// var living = extend(true, {}, user, app, system);
	rapidjson::Document m_livingJson; 
};

} // namespace Backent