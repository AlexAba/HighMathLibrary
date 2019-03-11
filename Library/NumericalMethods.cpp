#include "pch.h"
#include "NumericalMethods.h"
#include <cmath>


namespace HighMath {

	//	Interpolation.
	double Interpolation::Lagrange(double num, Matrix table) {
		double answer = 0;
		for (int j = 0; j < table.GetCols(); j++) {
			// Answer of multiplications
			double mul = 1;
			for (int k = 0; k < table.GetCols(); k++) {
				if (k != j) {
					mul *= (num - table[x][k]) / (table[x][j] - table[x][k]);
				}
			}
			answer += table[y][j] * mul;
		}

		return answer;
	}
	double Interpolation::Interpolate(double num, Matrix table, int type) {
		int *closest;
		double answer = 0;
		closest = FindClosest(num, table, type + 1);

		for (int j = 0; j < type + 1; j++) {
			double mul = 1;
			for (int k = 0; k < type + 1; k++) {
				if (k != j) {
					mul *= (num - table[x][closest[k]]) / (table[x][closest[j]] - table[x][closest[k]]);
				}
			}
			answer += table[y][closest[j]] * mul;
		}
		delete[] closest;
		return answer;
	}
	int *Interpolation::FindClosest(double num, Matrix table, int quantity) {
		//	Contain indexes of closest elenents from table to num.
		int *ans = new int[quantity];
		//	Set impossible value of index of the closest x-value.
		for (int i = 0; i < quantity; i++) {
			ans[i] = table.GetCols();
		}

		double *diff = new double[table.GetCols()];

		for (int i = 0; i < table.GetCols(); i++) {
			//	Find distance between x and number.
			diff[i] = abs(table[x][i] - num);
		}

		for (int i = 0; i < quantity; i++) {
			double min = 10e16;
			for (int j = 0; j < table.GetCols(); j++) {
				if (CheckOccupancy(j, ans, quantity)) {
					if (diff[j] < min) {
						ans[i] = j;
						min = diff[j];
					}
				}

			}
		}

		delete[] diff;
		return ans;
	}
	bool Interpolation::CheckOccupancy(int num, int *table, int size) {
		for (int i = 0; i < size; i++) {
			if (table[i] == num) return false;
		}
		return true;
	}

	//	Differentiation.
	double Differentiation::ApproxCentralFirstDiff(double prev, double next, double step) {
		double ans;
		ans = (prev - next) / (2 * step);
		return ans;
	}
	double Differentiation::ApproxLeftFirstDiff(double prev, double current, double step) {
		double ans;
		ans = (current - prev) / step;
		return ans;
	}
	double Differentiation::ApproxRightFirstDiff(double current, double next, double step) {
		double ans;
		ans = (next - current) / step;
		return ans;
	}
	double Differentiation::ApproxSecondDiff(double prev, double current, double next, double step) {
		double ans;
		ans = (prev + next - 2 * current) / (step * step);
		return ans;
	}
	double Differentiation::FuncFirstDiff(double x, Func1D func, double prec) {
		double result;
		result = (func(x + prec) - func(x)) / prec;
		return result;
	}

	//	Integration.
	double Integration::Quadratic(double down, double up, Func1D function, double precision) {
		int n = int(up - down) + 1;
		double x0, x1;
		double sum, h, error, ans, prevans;
		// To check precision of integration.
		error = precision + 1;

		bool isFirst = true;
		while (error >= precision) {
			h = (up - down) / n;
			sum = 0;
			for (int i = 0; i < n; i++) {
				x0 = down + h * i;
				x1 = x0 + h;
				sum += function((x0 + x1) / 2);
			}
			ans = h * sum;

			if (isFirst) {
				prevans = ans;
				isFirst = false;
				n *= 2;
				continue;
			}

			error = Runge(ans, prevans, 2);
			prevans = ans;
			n *= 2;
		}

		return ans;
	}
	double Integration::Trapeze(double down, double up, Func1D function, double precision) {
		int n = int(up - down) + 1;
		double sum, h, error, ans, prevans;
		// To check precision of integration.
		error = precision + 1;

		bool isFirst = true;
		while (error >= precision) {
			//	Step.
			h = (up - down) / n;
			sum = 0;
			for (int i = 0; i < n; i++) {
				sum += function(down + h * i);
			}

			ans = h / 2 * (function(down) + function(up) + 2 * sum);
			if (isFirst) {
				prevans = ans;
				isFirst = false;
				n *= 2;
				continue;
			}

			error = Runge(ans, prevans, 1);
			prevans = ans;
			n *= 2;
		}

		return ans;
	}
	double Integration::Simpson(double down, double up, Func1D function, double precision) {
		int n = int(up - down) + 1;
		double x0, x1;
		double sum, h, error, ans, prevans;
		// To check precision of integration.
		error = precision + 1;
		bool isFirst = true;

		while (error >= precision) {
			//	Step.
			h = (up - down) / n;
			sum = 0;
			for (int i = 0; i < n; i++) {
				x0 = down + h * i;
				x1 = x0 + h;;
				sum += function(x0) + 4 * function((x0 + x1) / 2) + function(x1);
			}

			ans = h / 6 * sum;
			if (isFirst) {
				prevans = ans;
				isFirst = false;
				n *= 2;
				continue;
			}

			error = Runge(ans, prevans, 4);
			prevans = ans;
			n *= 2;
		}

		return ans;
	}
	double Integration::Runge(double ans, double prevans, int k) {

		return ((ans - prevans) / (pow(2, k) - 1));
	}

	//	Equations.
	double Equation::BisectionMethod(Vector range, Func1D function, double precision) {
		double a = range[0], b = range[1];
		double x;
		double y;

		do {
			x = (a + b) / 2;
			y = function(x);
			if (!y) break;
			else if (function(a) * y < 0) b = x;
			else a = x;
		} while (abs(y) > precision);

		return x;
	}
	double Equation::ChordMethod(Vector range, Func1D function, double precision) {
		double a = range[0], b = range[1];
		double x;
		double y;

		do {
			x = a - (b - a)*function(a) / (function(b) - function(a));
			y = function(x);
			if (!y) break;
			else if (function(a) * y < 0) b = x;
			else a = x;
		} while (abs(y) > precision);

		return x;
	}

	//	IterativeSystems.
	Vector System::SimpleIterations(EquationsSystem system, Vector initApprox, double precision) {
		Vector prev(system.Size());

		do {
			prev = initApprox;
			initApprox = system(prev);
		} while (Precision(prev, initApprox, system.Size()) >= precision);

		return initApprox;
	}
	double System::Precision(Vector prevVars, Vector currVars, int size) {
		double ans = 0;

		for (int i = 0; i < size; i++) {
			ans += abs(currVars[i] - prevVars[i]);
		}

		return ans;
	}

	//	DifferentialEquations.
	double DifferentialEquations::EulerMethod(double xPrev, double yPrev, Func2D func, double h) {
		double result;
		result = yPrev + h * func(xPrev, yPrev);
		return result;
	}
	double DifferentialEquations::RungeKuttaMethod(double xPrev, double yPrev, Func2D func, double h) {
		double result;
		result = yPrev + (h * func((xPrev + h / 2), (yPrev + (h / 2) * func(xPrev, yPrev))));
		return result;
	}

	//	ComplexEquations.
	Matrix MathPhysic::HeatConductionEquation
	(double h, double t, double xFrom, double yFrom,
		double xTo, double yTo, Func1D f1, Func1D f2, Func1D f3)
	{
		unsigned rows = unsigned((yTo - yFrom) / t + 1);
		unsigned cols = unsigned((xTo - xFrom) / h + 1);
		Matrix ans = Matrix(rows, cols);

		double val = xFrom;
		//	Set the bottom of the grig.
		for (unsigned i = 0; i < ans.GetCols(); i++, val += h) {
			ans[0][i] = f1(val);
		}
		val = yFrom;
		//	Set walls of the grig.
		for (unsigned i = 0; i < ans.GetRows(); i++, val += t) {
			ans[i][0] = f2(val);
			ans[i][ans.GetCols() - 1] = f3(val);
		}
		//	Make main calculations.
		for (unsigned j = 0; j < ans.GetRows() - 1; j++) {
			for (unsigned i = 1; i < ans.GetCols() - 1; i++) {
				ans[j + 1][i] = ans[j][i] + (t / (h * h)) * (ans[j][i + 1] + ans[j][i - 1] - 2 * ans[j][i]);
			}
		}

		return ans;
	}
}