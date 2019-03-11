#pragma once
#include <ostream>
#include <iomanip>
#include <vector>
#include "Vector.h"
#include "MathException.h"

namespace HighMath {

	class Matrix
	{
	private:
		int length; 
		Vector **matrix;

	public:
		Matrix();
		Matrix(unsigned size);
		Matrix(unsigned rows, unsigned cols);
		Matrix(const Matrix &matr);
		~Matrix();

		int GetRows();
		int GetCols();
		static Matrix Transpose(Matrix matr);
		static int Determinant(Matrix matr);
		static Matrix MainMinor(Matrix matr, int row, int col);
		static Matrix Inverse(Matrix matr);

		//	Unary operators.
		Vector &operator[](int row);
		Matrix operator-();
		//	Binary operators.
		Matrix operator=(Matrix matr);
		Matrix operator+(Matrix matr);
		Matrix operator-(Matrix matr);
		Matrix operator*(Matrix matr);
		Matrix operator+=(Matrix matr);
		Matrix operator-=(Matrix matr);
		Matrix operator*(double num);
		Matrix operator/(double num);
		Matrix operator*=(double num);
		Matrix operator/=(double num);
		bool operator==(Matrix matr);
		bool operator!=(Matrix matr);
		friend std::ostream &operator<<(std::ostream &out, Matrix matr);
		friend std::istream &operator>>(std::istream &in, Matrix &matr);
	};
}
