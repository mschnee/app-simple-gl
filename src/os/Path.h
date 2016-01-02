#include "IPath.h"

#if defined(WIN32)
	#include "Path_Win.h"
#elif defined(MACOS)
#else
	#include "Path_Linux.h"
#endif