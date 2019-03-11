#include "pch.h"
#include "Matrix.h"

namespace HighMath {

	Matrix::Matrix() {
		matrix = nullptr;
		length = 0;
	}
	Matrix::Matrix(unsigned size) {
		matrix = new Vector *[size];
		for (int i = 0; i < size; i++) {
			matrix[i] = new Vector(size);
		}
		length = size;

	}
	Matrix::Matrix(unsigned rows, unsigned cols) {
		matrix = new Vector *[rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new Vector(cols);
		}
		length = rows;
	}
	Matrix::Matrix(const Matrix& matr) {
		matrix = new Vector*[matr.length];
		length = matr.length;
		for (int i = 0; i < length; i++)
		{
			matrix[i] = new Vector(*(matr.matrix[i]));
		}
	}
	Matrix::~Matrix() {
		for (int i = 0; i < length; i++) {
			delete matrix[i];
		}
		delete[] matrix;
		length = 0;
	}

	int Matrix::GetRows() {
		return length;
	}
	int Matrix::GetCols() {
		if (length > 0)
			return matrix[0][0].Length();
		else return 0;
	}
	Matrix Matrix::Transpose(Matrix matr) {
		Matrix ans(matr.GetCols(), matr.GetRows());
		for (int i = 0; i < matr.GetRows(); i++) {
			for (int j = 0; j < matr.GetCols(); j++) {
				ans[j][i] = matr[i][j];
			}
		}
		return ans;
	}
	int Matrix::Determinant(Matrix matr) {
		if (matr.GetRows() != matr.GetCols())
			throw std::length_error("Determinant can be calculated only for square Matrix.");

		int ans = 0;

		if (matr.length == 2) {
			ans = matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
		}
		else {
			for (int i = 0; i < matr.length; i++) {
				Matrix ma = MainMinor(matr, 0, i);
				ans += pow(-1, i) * matr[0][i] * Determinant(ma);
			}
		}
		return ans;
	}
	Matrix Matrix::MainMinor(Matrix matr, int row, int col) {
		if (matr.length < 2)
			throw std::length_error("Matrix is small to find algebraic addition.");

		Matrix ans(matr.length - 1);
		int l = 0;
		for (int j = 0; j < matr.length; j++) {
			if (j != row) {
				int m = 0;
				for (int k = 0; k < matr.length; k++) {
					if (k != col) {
						ans[l][m] = matr[j][k];
						m++;
					}
				}
				l++;
			}
		}

		return ans;
	}
	Matrix Matrix::Inverse(Matrix matr) {
		int det = Determinant(matr);
		if (!det)
			throw std::MathException("Can not find inverse Matrix for this, because this Matrix is degenerate.");
		
		Matrix ans(matr.length);
		for (int i = 0; i < matr.length; i++) {
			for (int j = 0; j < matr.length; j++) {
				ans[i][j] = pow(-1, i + j) * Determinant(MainMinor(matr, i, j));
			}
		}
		
		return (Transpose(ans) / det);
	}

	Vector &Matrix::operator[](int row) {
		if (row < 0 || row >= GetRows()) {
			throw std::out_of_range("Row out of the range.");
		}
		else return matrix[row][0];
	}
	Matrix Matrix::operator-() {
		Matrix ans(GetRows(), GetCols());
		for (int i = 0; i < GetRows(); i++) {
			for (int j = 0; j < GetCols(); j++) {
				ans[i] = -*(matrix[i]);
			}
		}
		return ans;
	}
	Matrix Matrix::operator+(Matrix matr) {
		if (GetRows() != matr.GetRows() || GetCols() != matr.GetCols())
			throw std::length_error("Size of the left Matrix not equal to the right.");
		Matrix ans(GetRows(), GetCols());
		for (int i = 0; i < GetRows(); i++) {
			ans[i] = *(matrix[i]) + matr[i];
		}
		return ans;
	}
	Matrix Matrix::operator-(Matrix matr) {
		if (GetRows() != matr.GetRows() || GetCols() != matr.GetCols())
			throw std::length_error("Size of the left Matrix not equal to the right.");
		Matrix ans(GetRows(), GetCols());
		for (int i = 0; i < GetRows(); i++) {
			ans[i] = *(matrix[i]) - matr[i];
		}
		return ans;
	}
	Matrix Matrix::operator=(Matrix matr) {
		if (GetRows() != matr.GetRows() || GetCols() != matr.GetCols())
			throw std::length_error("Size of the left Matrix not equal to the right.");

		for (int i = 0; i < GetRows(); i++) {
			*(matrix[i]) = matr[i];
		}
		return *this;

	}
	Matrix Matrix::operator*(Matrix matr) {
		if (GetCols() != matr.GetRows())
			throw std::length_error("The number of the cols of the left Matrix not equal to the number of rows to right Matrix");

		Matrix ans(GetRows(), matr.GetCols());
		for (int i = 0; i < ans.GetRows(); i++) {
			for (int j = 0; j < ans.GetCols(); j++) {
				for (int k = 0; k < GetCols(); k++) {
					ans[i][j] += (*this)[i][k] * matr[k][j];
				}
			}
		}
		return ans;
	}
	Matrix Matrix::operator+=(Matrix matr) {
		if (GetRows() != matr.GetRows() || GetCols() != matr.GetCols())
			throw std::length_error("Size of the left Matrix not equal to the right.");
		
		for (int i = 0; i < GetRows(); i++) {
			*(matrix[i]) += matr[i];
		}
		return *this;
	}
	Matrix Matrix::operator-=(Matrix matr) {
		if (GetRows() != matr.GetRows() || GetCols() != matr.GetCols())
			throw std::length_error("Size of the left Matrix not equal to the right.");

		for (int i = 0; i < GetRows(); i++) {
			*(matrix[i]) -= matr[i];
		}
		return *this;
	}
	Matrix Matrix::operator*(double num) {
		Matrix ans(GetRows(), GetCols());

		for (int i = 0; i < GetRows(); i++) {
			ans[i] = (*this)[i] * num;
		}

		return ans;
	}
	Matrix Matrix::operator/(double num) {
		Matrix ans(GetRows(), GetCols());

		for (int i = 0; i < GetRows(); i++) {
			ans[i] = (*this)[i] / num;
		}

		return ans;
	}
	Matrix Matrix::operator*=(double num) {

		for (int i = 0; i < GetRows(); i++) {
			(*this)[i] *= num;
		}

		return *this;
	}
	Matrix Matrix::operator/=(double num) {
		
		for (int i = 0; i < GetRows(); i++) {
			(*this)[i] /= num;
		}

		return *this;
	}

	bool Matrix::operator==(Matrix matr) {
		if (length != matr.length) return false;
		else {
			for (int i = 0; i < length; i++){
				if (*(matrix[i]) != matr[i]) return false;
			}
			return true;
		}
	}
	bool Matrix::operator!=(Matrix matr) {
		if (length != matr.length) return true;
		else {
			for (int i = 0; i < length; i++) {
				if (*(matrix[i]) != matr[i]) return true;
			}
			return false;
		}
	}

	std::ostream &operator<<(std::ostream &out, Matrix matr) {
		for (int i = 0; i < matr.length; i++)
		{
			out << (matr[i]) << "\n";
		}
		return out;
	}
	std::istream &operator>>(std::istream &in, Matrix &matr) {
		for (int i = 0; i < matr.length; i++)
		{
			in >> (matr[i]);
		}
		return in;
	}
}