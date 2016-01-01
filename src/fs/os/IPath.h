#pragma once
#include <string>
namespace fs {
namespace os {
class IPath {
public:
    virtual std::string  GetApplicationPath() = 0;
};
} // namespace fs::os
} // namespace fs