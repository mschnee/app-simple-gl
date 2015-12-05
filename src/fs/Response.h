#pragma once

namespace fs
{

class Response {
public:
	void SetData(gsl::owner<char*> data)
private:
	bool m_hasError;
	char* data;		
};

}