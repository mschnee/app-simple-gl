#pragma once
#include <atomic>
#include <fstream>
#include <mutex>

#include <EventEmitter/Emitter.h>
#include <gsl.h>

namespace fs
{

typedef std::function<void(FileReader*)> FileReaderCallback;
class FileReader : public EventEmitter::Emitter
{
public:
	bool IsError();
	std::unique_ptr<std::string*> GetData();
private:
	FileReader(const std::string& fileName, FileReaderCallback callback);
	
private:
	FileReaderCallback m_callback;
	gsl::owner<std::string*> m_data;
	bool is_error;
};

void readFile(const std::string& fileName, std::function<void(unique_ptr<std::string>)> callback);
} // namespace fs