#pragma once

#include <functional>

namespace fs
{

/**
 *  Asynchronously writes the data d to file fileName
 *  The generic version is not implemented.  If T converts nicely to std::string, it should.  If it doesn't,
 *  write a specialization that does.
 */
template<typename T = std::string>
void writeFile(const std::wstring& fileName, const T& data, std::function<void()> callback);

} // namespace fs