#include <EventEmitter/EventEmitter.h>

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

private:
	bool m_running{ true };
	Frontend::SceneController* m_sceneController{ nullptr };
};

} // namespace Backend