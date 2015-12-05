#pragma once
#include <EventEmitter/EventEmitter.h>

namespace Backend {
	class Application;
} // namespace Backend

namespace Frontend {

class Scene;
class SceneController : public EventEmitter::Emitter {
public:
	void SetApplication(Backend::Application* app);
	Scene* GetCurrentScene() const;

private:
	Backend::Application *m_application{ nullptr };

	Scene* m_currentScene{ nullptr };
};

} // namespace Frontend