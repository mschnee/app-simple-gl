#include "Path.h"

#if defined(WIN32)
	#include "os/Path_Win.h"
#elseif defined(MACOS)
#else
	#include "os/Path_Linux.h"
#endif

#include <memory>

namespace fs
{

namespace
{
#if defined(WIN32)
	std::unique_ptr<IPath> s_path = make_unique<Path_Win>();
#elseif defined(MACOS)
#else
	std::unique_ptr<os::IPath> s_path(new os::Path_Linux);
#endif

} // anonymous namespace

std::string GetApplicationPath() {
	return s_path->GetApplicationPath();
}

} //namespace fs