#include "pch.h"
#include "EquationsSystem.h"

namespace HighMath {

	EquationsSystem::EquationsSystem(int size)
	{
		this->size = size;
		this->system = std::vector<SystemFunc>(size);
	}
	EquationsSystem::EquationsSystem(int size, SystemFunc *system)
	{
		this->size = size;
		this->system = std::vector<SystemFunc>(size);
		for (int i = 0; i < size; i++) {
			this->system[i] = system[i];
		}
	}
	void EquationsSystem::Resize(int size) {
		system.resize(size);
		this->size = size;
	}
	int EquationsSystem::Size() {
		return size;
	}
	SystemFunc &EquationsSystem::operator[](int i) {
		if (i < 0 || i >= size) throw std::out_of_range("Index out of range");
		return system[i];
	}
	Vector EquationsSystem::operator()(Vector vect) {
		Vector ans(size);
		for (int i = 0; i < size; i++) {
			//if(system[i] == nullptr or system[i] == NULL)
			//	throw SomeException
			ans[i] = system[i](vect);
		}
		return ans;
	}
}