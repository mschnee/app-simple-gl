#include <EventEmitter/Emitter.h>
#include "SettingsController.h"

namespace Frontend
{
	class SceneController;
} // namespace Frontend
namespace Backend
{
	
class Application : public EventEmitter::Emitter
{
public:
	int Exec();

private:
	void ConnectSceneController();
	void ConnectSettingsController();

private:
	void OnUpdateSettings();

private:
	bool m_running{ true };
	bool m_settingsReady{ false };
	Frontend::SceneController* m_sceneController{ nullptr };
	Backend::SettingsController* m_settingsController{ nullptr };
};

} // namespace Backend