#pragma once
#include "IPath.h"

#include <unistd.h>
#include <limits.h>

namespace fs {
    namespace os {
        class Path_Linux : public IPath {
        public:
            std::string  GetApplicationPath() override {
                if (!m_applicationPathInitialized) {
                    InitApplicationPath();
                }
                return m_applicationPath;
            };
        private:
            void InitApplicationPath() {
                char buffer[PATH_MAX];
                ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
                if (len != -1) {
                    buffer[len] = '\0';
                }
                auto pos = std::string(buffer).find_last_of("\\/");
                m_applicationPath = std::string(buffer).substr(0, pos);
                m_applicationPathInitialized = true;
            }
            bool m_applicationPathInitialized { false };
            std::string m_applicationPath;
        };
    }
}