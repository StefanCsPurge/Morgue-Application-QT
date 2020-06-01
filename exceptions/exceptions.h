#pragma once
#include <exception>
#include <string>


class ValidationException : public std::exception
{
private:
	std::string message;
public:
	ValidationException(std::string msg = "");
	const char* what() const noexcept override;
};

class RepositoryException : public std::exception
{
private:
	std::string message;
public:
	RepositoryException(std::string msg = ""); 
	const char* what() const noexcept override;
};

