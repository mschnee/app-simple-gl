#include "FileReader.h"

#include <fstream>
#include <thread>
#include <sstream>
#include <future>
#include <rapidjson/document.h>
#include "Events/Events.h"
namespace fs
{

namespace
{

void readFileToString(
	const std::string& fileName,
	std::function<void(std::unique_ptr<std::string>)> callback )
{
	std::ifstream t(fileName, std::ifstream::in);
	std::stringstream buffer;
	buffer << t.rdbuf();
	
	if (buffer.str().length() == 0)
	{
		callback(std::unique_ptr<std::string>(new std::string("")));
	}
	else
	{
		callback(std::unique_ptr<std::string>(new std::string(std::move(buffer.str()))));
	}
}

} // private namespace


/**
 * Reads a file into a string asyncronously.
 */
template<> 
void readFile<std::string>(
	const std::string& fileName,
	std::function<void(std::unique_ptr<std::string>)> callback)
{
	std::async(std::launch::async, readFileToString, fileName, callback);
};

template<>
void readFile<rapidjson::Document>(
	const std::string& fileName,
	std::function<void(std::unique_ptr<rapidjson::Document>)> callback)
{
	readFile<std::string>(fileName, [callback](std::unique_ptr<std::string> result)
	{
		auto r = std::unique_ptr<rapidjson::Document>(new rapidjson::Document);
		r->Parse(result->c_str());
		callback(std::move(r));
	});
}
} // namespace fs