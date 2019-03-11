#pragma once
#include <stdexcept>

namespace std{
	class MathException : public std::exception
	{
	public:
		MathException(char const* const _Message);
	};
}