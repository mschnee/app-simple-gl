#include "StringUtil.h"
#include <sstream>

namespace Util
{

std::vector<std::string> split(const std::string& base, char delim)
{
	std::vector<std::string> strings;
	std::istringstream f(base);
	std::string s;
	while (getline(f, s, delim)) {
		strings.push_back(s);
	}
	return move(strings);
}

std::vector<const char*> c_split(const std::string& base, char delim)
{
	std::vector<const char*> strings;
	std::istringstream f(base);
	std::string s;
	while (getline(f, s, delim)) {
		strings.push_back(s.c_str());
	}
	return move(strings);
}
}