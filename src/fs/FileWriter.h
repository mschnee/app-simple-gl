#pragma once

#include <functional>

namespace fs
{

template<typename T = std::string>
void writeFile(const std::wstring& fileName, const T& data, std::function<void()> callback);

} // namespace fs