#pragma once
#include <exception>

struct A : public std::exception
{
	const char* what() const throw()
	{
		return "Trying to a\n";
	}
};