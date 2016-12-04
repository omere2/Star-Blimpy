#ifndef __BASEEXCEPTION_H__
#define __BASEEXCEPTION_H__

#include <string>

class BaseException
{
public:
	BaseException(std::string = std::string());
	virtual ~BaseException();

	const std::string& GetDescription() const;
private:
	std::string _error_description;
};

#endif
