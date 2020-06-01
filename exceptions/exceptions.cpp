#include "exceptions.h"

using namespace std;


ValidationException::ValidationException(string _message) : message{ "Victim validation error - " + _message }
{}

const char * ValidationException::what() const noexcept
{
	return message.c_str();
}

RepositoryException::RepositoryException(string _message): message{ "Repository error - " + _message}
{}

const char * RepositoryException::what() const noexcept
{
	return message.c_str();
}