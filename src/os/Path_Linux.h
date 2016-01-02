#pragma once
#include "IPath.h"

namespace os {

class Path_Linux : public IPath {
public:
	std::string  GetApplicationPath() override ;
private:
	void InitApplicationPath();
	
	bool m_applicationPathInitialized { false };
	std::string m_applicationPath;
};

} // namespace os
