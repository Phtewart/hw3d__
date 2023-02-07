#include "CustmException.h"
#include <sstream>


CustmException::CustmException(int lineNum, const char* file) noexcept
	:
	lineNum(lineNum),file(file)
{
}

const char* CustmException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* CustmException::GetType() const noexcept
{
	return "Custom Exeption!";
}

int CustmException::GetLine() const noexcept
{
	return lineNum;
}

std::string CustmException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << lineNum;
	return oss.str();
}
