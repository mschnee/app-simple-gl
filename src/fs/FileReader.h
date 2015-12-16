#pragma once
#include <functional>
#include <memory>

namespace fs
{

template<typename T = std::string>
void readFile(const std::wstring& fileName, std::function<void(std::unique_ptr<T>)> callback);

} // namespace fs