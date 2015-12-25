#pragma once
#include <functional>
#include <memory>

namespace fs
{

/**
*  Asynchronously reads fileName
*  The generic version is not implemented.  If T converts nicely to std::string, it should.  If it doesn't,
*  write a specialization that does.
*  Calls callback with a std::move()'d std::unique_ptr to the loaded data.
*/
template<typename T = std::string>
void readFile(const std::wstring& fileName, std::function<void(std::unique_ptr<T>)> callback);

} // namespace fs