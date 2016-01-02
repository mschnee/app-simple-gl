#pragma once
#include "Path_Linux.h"

#include <unistd.h>
#include <limits.h>

namespace os {

std::string  Path_Linux::GetApplicationPath()
{
	if (!m_applicationPathInitialized) {
		InitApplicationPath();
	}
	return m_applicationPath;
}

void Path_Linux::InitApplicationPath() {
	char buffer[PATH_MAX];
	ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
	if (len != -1) {
		buffer[len] = '\0';
	}
	auto pos = std::string(buffer).find_last_of("\\/");
	m_applicationPath = std::string(buffer).substr(0, pos);
	m_applicationPathInitialized = true;
}

} // namespace os