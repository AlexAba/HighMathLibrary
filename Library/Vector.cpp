#include "pch.h"
#include "Vector.h"

namespace HighMath {
	Vector::Vector() {
		vector = nullptr;
		length = 0;
	}
	Vector::Vector(int size) {
		vector = new double[size];
		length = size;

		for (int i = 0; i < length; i++){
			vector[i] = 0;
		}
	}
	Vector::Vector(const Vector &vec) {
		this->vector = new double[vec.length];
		this->length = vec.length;
		for (int i = 0; i < vec.length; i++) {
			vector[i] = vec.vector[i];
		}
	}
	Vector::~Vector() {
		length = 0;
		delete[] vector;
		vector = nullptr;
	}

	int Vector::Length() {
		return Vector::length;
	}

	double &Vector::operator[](int index) {
		if (index < 0 || index >= length) {
			throw std::out_of_range("Vector index out of the range.");
		}
		else return vector[index];
	}
	Vector Vector::operator=(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}
		for (int i = 0; i < length; i++) {
			vector[i] = vec[i];
		}
		return *this;
	}
	Vector Vector::operator+(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}

		Vector result(length);
		for (int i = 0; i < length; i++) {
			result[i] = vector[i] + vec[i];
		}
		return result;
	}
	Vector Vector::operator-(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}

		Vector result(length);
		for (int i = 0; i < length; i++) {
			result[i] = vector[i] - vec[i];
		}
		return result;
	}
	double Vector::operator*(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}
		double result = 0;
		for (int i = 0; i < length; i++) {
			result += vector[i] *
				vec[i];
		}
		return result;
	}
	Vector Vector::operator-() {
		Vector res(length);
		for (int i = 0; i < length; i++) {
			res[i] = -vector[i];
		}
		return res;
	}
	Vector Vector::operator+=(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}

		for (int i = 0; i < length; i++) {
			vector[i] += vec[i];
		}
		return *this;
	}
	Vector Vector::operator-=(Vector vec) {
		if (length != vec.length) {
			throw std::length_error("Length of the right Vector is not equal to the left.");
		}

		for (int i = 0; i < length; i++) {
			vector[i] -= vec[i];
		}
		return *this;
	}
	bool Vector::operator==(Vector vec) {
		if (length != vec.length) return false;
		else {
			for (int i = 0; i < length; i++) {
				if (vector[i] != vec[i]) return false;
			}
			return true;
		}
	}
	bool Vector::operator!=(Vector vec) {
		if (length != vec.length) return true;
		else {
			for (int i = 0; i < length; i++) {
				if (vector[i] != vec[i]) return true;
			}
			return false;
		}
	}
	Vector Vector::operator*(double num) {
		Vector ans(length);
		for (int i = 0; i < length; i++) {
			ans[i] = vector[i] * num;
		}
		return ans;
	}
	Vector Vector::operator/(double num) {
		Vector ans(length);
		for (int i = 0; i < length; i++) {
			ans[i] = vector[i] / num;
		}
		return ans;
	}
	Vector Vector::operator*=(double num) {
		for (int i = 0; i < length; i++) {
			vector[i] *= num;
		}
		return *this;
	}
	Vector Vector::operator/=(double num) {
		for (int i = 0; i < length; i++) {
			vector[i] /= num;
		}
		return *this;
	}

	std::ostream &operator<<(std::ostream &out, Vector vec) {
		for (int i = 0; i < vec.length; i++) {
			out << vec[i] << "\t";
		}
		return out;
	}
	std::istream &operator>>(std::istream &in, Vector &vec) {
		for (int i = 0; i < vec.length; i++) {
			in >> vec[i];
		}
		return in;
	}
}
