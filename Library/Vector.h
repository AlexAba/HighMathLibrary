#pragma once
#include <stdexcept>
#include <iostream>

namespace HighMath {
	class Vector {
	private:
		int length;
		double *vector;
	public:
		Vector();
		Vector(int size);
		Vector(const Vector & vec);
		~Vector();
		int Length();
		//	Unary operators.
		double &operator[](int index);
		Vector operator-();
		//	Binary operators.
		Vector operator=(Vector vec);
		Vector operator+(Vector vec);
		Vector operator-(Vector vec);
		double operator*(Vector vec);
		Vector operator+=(Vector vec);
		Vector operator-=(Vector vec);
		bool operator==(Vector vec);
		bool operator!=(Vector vec);
		Vector operator*(double num);
		Vector operator/(double num);
		Vector operator*=(double num);
		Vector operator/=(double num);
		friend std::ostream &operator<<(std::ostream &out, Vector vec);
		friend std::istream &operator>>(std::istream &in, Vector &vec);
	};

}
