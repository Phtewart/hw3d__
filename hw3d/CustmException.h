#pragma once

#include <exception>
#include <string>

class CustmException : public std::exception
{
public:
	CustmException(int lineNum, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int lineNum;
	std::string file;
protected:
	mutable std::string whatBuffer;
};