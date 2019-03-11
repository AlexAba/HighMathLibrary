#pragma once
#include <vector>
#include "Vector.h"
#include <stdexcept>

namespace HighMath {
	using SystemFunc = double(*)(Vector vars);

	class EquationsSystem
	{

	private:
		unsigned size;
		std::vector<SystemFunc> system;
	public:
		EquationsSystem(int size);
		EquationsSystem(int size, SystemFunc *system);
		void Resize(int size);
		int Size();
		SystemFunc &operator[](int i);
		Vector operator()(Vector vect);
	};
}