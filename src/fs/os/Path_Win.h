#pragma once
#include "IPath.h"
#if defined(WIN32)
#include <Shlobj.h>
#pragma comment(lib, "comsuppw")
#endif

namespace fs {
namespace os {
class Path_Win : public IPath {
public:
    std::string  GetApplicationPath() override {
        if (!m_applicationPathInitialized) {
            InitApplicationPath();
        }
        return m_applicationPath;
    };
private:
    void InitApplicationPath() {
        char buffer[MAX_PATH];
        GetModuleFileName(nullptr, buffer, MAX_PATH);
        auto pos = std::string(buffer).find_last_of("\\/");
        auto m_applicationPath = std::string(buffer).substr(0, pos);
        m_applicationPathInitialized = true;
    }
    bool m_applicationPathInitialized { false };
    std::string m_applicationPath;
};
}
}