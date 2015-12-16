#include "FileWriter.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

namespace fs
{
namespace
{

struct DocStream
{
	DocStream(std::ofstream* outFileStream) : m_of(outFileStream){}
	std::ofstream* m_of;
	void Put(char ch) { m_of->put(ch); }
	void Flush() {}
};

void writeFileFromString(const std::wstring& fileName, const std::string& data, std::function<void()> callback)
{
	std::ofstream t(fileName, std::ifstream::out | std::ifstream::trunc);
	
	t << data.c_str();
	t.close();
	callback();
}

} // private namespace
	

template <>
void writeFile<std::string>(
	const std::wstring& fileName,
	const std::string& data,
	std::function<void()> callback)
{
	writeFileFromString(fileName, data, callback);
}

template <>
void writeFile<rapidjson::Document>(
	const std::wstring& fileName,
	const rapidjson::Document& doc,
	std::function<void()> callback)
{
	std::ofstream t(fileName, std::ifstream::out | std::ifstream::trunc);
	DocStream d(&t);
	rapidjson::Writer<DocStream> writer(d);

	doc.Accept(writer);
	callback();
}

} // namespace fs