#include "Path.h"

#if defined(WIN32)
	#include "os/Path_Win.h"
#elif defined(MACOS)
#else
	#include "os/Path_Linux.h"
#endif

#include <memory>

namespace fs
{

namespace
{
#if defined(WIN32)
	std::unique_ptr<os::IPath> s_path = std::make_unique<os::Path_Win>();
#elif defined(MACOS)
	std::unique_ptr<os::IPath> s_path(new os::Path_Mac);
#else
	std::unique_ptr<os::IPath> s_path(new os::Path_Linux);
#endif

} // anonymous namespace

std::string GetApplicationPath() {
	return s_path->GetApplicationPath();
}

std::string GetSharedPath() {
	return s_path->GetSharedPath();
}


std::string GetUserPath() {
	return s_path->GetUserPath();
}


} //namespace fs