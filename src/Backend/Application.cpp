#include "Application.h"
#include "Events/Events.h"
#include "Frontend/SceneController.h"
#include <EventEmitter/Registry.h>
#include <cassert>
#include <iostream>

namespace Backend
{

int Application::Exec()
{
	while (m_running)
	{
		if (!m_sceneController) {
			m_sceneController = new Frontend::SceneController;
			m_sceneController->SetApplication(this);
			ConnectSceneController();
		}
		if (!m_settingsController)
		{
			m_settingsController = new SettingsController;
			ConnectSettingsController();
			m_settingsController->LoadSettings();
		}
		EventEmitter::Registry::ProcessEvents();

		// We need settings before we can resume.  So......
		if (!m_settingsReady)
		{
			std::cout << "waiting..." << std::endl;
			continue;
		}
		std::cout << "ready..." << std::endl;
		
	}
	return 0;
}

void Application::ConnectSceneController()
{
	assert(("ScreenController must be set prior to connection", m_sceneController));
}

void Application::ConnectSettingsController()
{
	m_settingsController->On(Events::SettingsReloaded, [this]()
	{
		OnUpdateSettings();
	}, EventEmitter::Dispatch);
}

void Application::OnUpdateSettings()
{
	m_settingsReady = true;
}

} // namespace Backend