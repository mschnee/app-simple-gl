#include "SceneController.h"

namespace Frontend
{

void SceneController::SetApplication(Backend::Application* app)
{
	m_application = app;
}

Scene* SceneController::GetCurrentScene() const
{
	return m_currentScene;
}

} // namespace Frontend