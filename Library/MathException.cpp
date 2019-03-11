#include "pch.h"
#include "MathException.h"

namespace std {
	MathException::MathException(char const* const _Message) : std::exception(_Message)
	{

	}
}