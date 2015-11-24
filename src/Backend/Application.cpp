#include "Application.h"
#include "Frontend/SceneManager.h"
#include <EventEmitter/EventLoop.h>
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
		EventEmitter::EventLoop::ProcessEvents();
	}
	return 0;
}

void Application::ConnectSceneController()
{
	assert(m_sceneController);
}

}