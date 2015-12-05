#include "Application.h"
#include "Frontend/SceneController.h"
#include <EventEmitter/Registry.h>
#include <cassert>

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
		EventEmitter::Registry::ProcessEvents();
	}
	return 0;
}

void Application::ConnectSceneController()
{
	assert(m_sceneController);
}

}