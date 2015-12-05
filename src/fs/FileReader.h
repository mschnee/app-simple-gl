#pragma once
#include <atomic>
#include <fstream>
#include <mutex>

#include <EventEmitter/Emitter.h>
#include <gsl.h>

namespace fs
{

class FileReader;
typedef std::function<void(FileReader*)> FileReaderCallback;

class FileReader : public EventEmitter::Emitter
{
public:
	bool IsError() const
	{
		return m_isError;
	}

private:
	FileReader(const std::string& fileName, FileReaderCallback callback);
	
private:
	FileReaderCallback m_callback;
	std::unique_ptr<std::string> m_data;
	bool m_isError;
};

template<typename T = std::string>
void readFile(const std::wstring& fileName, std::function<void(std::unique_ptr<T>)> callback);

template<>
void readFile<std::string>(const std::wstring& fileName, std::function<void(std::unique_ptr<std::string>)> callback);

} // namespace fs