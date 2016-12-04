#include "BaseException.h"

BaseException::BaseException(std::string error_desc):
	_error_description(error_desc)
{
}

BaseException::~BaseException()
{
}

const std::string& BaseException::GetDescription() const
{
	return _error_description;
}