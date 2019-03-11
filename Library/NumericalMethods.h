#pragma once
#include "EquationsSystem.h"
#include "Matrix.h"

namespace HighMath {
	using Func1D = double(*)(double x);
	using Func2D = double(*)(double x, double y);
	using DiffFunc = double(*)(double x, Func1D func, double prec);

	static class Interpolation {
	private:
		static constexpr int x = 0;
		static constexpr int y = 1;
	public:
		static double Lagrange(double num, Matrix table);
		static double Interpolate(double num, Matrix table, int type);

	private:
		static int *FindClosest(double num, Matrix table, int quantity);
		static bool CheckOccupancy(int num, int *table, int size);
	};
	static class Differentiation {
	public:
		static double ApproxCentralFirstDiff(double prev, double next, double step);
		static double ApproxLeftFirstDiff(double prev, double current, double step);
		static double ApproxRightFirstDiff(double current, double next, double step);
		static double ApproxSecondDiff(double prev, double current, double next, double step);
		static double FuncFirstDiff(double x, Func1D func, double prec = 10e-10);
	};
	static class Integration {
	public:
		static double Quadratic(double down, double up, Func1D function, double precision = 10e-4);
		static double Trapeze(double down, double up, Func1D function, double precision = 10e-4);
		static double Simpson(double down, double up, Func1D function, double precision = 10e-4);

	private:
		static double Runge(double ans, double prevans, int k);
	};
	static class Equation {
	public:
		static double BisectionMethod(Vector range, Func1D f, double precision);
		static double ChordMethod(Vector range, Func1D f, double precision);
	};
	static class System{
	public:
		///<summary>
		///<para>system: all functions of system in array;</para>
		///<para>initApprox: initial approximation of the system;</para>
		///<para>precision: precision of the calculations;</para>
		///<para>functions should be x = g(x), where x - vector, g(x) vector-function.</para>
		///</summary>
		static Vector SimpleIterations(EquationsSystem system, Vector initApprox, double precision = 10e-4);
	private:
		static double Precision(Vector prevVars, Vector currVars, int size);
	};
	static class DifferentialEquations {
	public:
		///<summary>
		///<para>xPrev, yPrev: previous or first value of x, y;</para>
		///<para>func: function with 2 params;</para>
		///<para>h: step of calculations.</para>
		///</summary>
		static double EulerMethod(double xPrev, double yPrev, Func2D func, double h);
		///<summary>
		///Runge-Kutta method has coefficient k = 2.
		///<para>_____________________________________________</para>
		///<para>xPrev, yPrev: previous or first value of x, y;</para>
		///<para>func: function with 2 params;</para>
		///<para>h: step of calculations.</para>
		///</summary>
		static double RungeKuttaMethod(double xPrev, double yPrev, Func2D func, double h);
	};
	static class MathPhysic {
	public:
		///<summary>
		///<para>h: step by x-axis; t: step by y-axis;</para>
		///<para>xFrom, yFrom: start value of x, y;</para>
		///<para>xTo, yTo: finish value of x and y;</para>
		///<para>f1: boundary val method when y = 0;</para>
		///<para>f2: boundary val method when x = 0;</para>
		///<para>f3: boundary val method when x = xTo.</para>
		///</summary>
		static Matrix HeatConductionEquation
		(double h, double t, double xFrom, double yFrom,
			double xTo, double yTo, Func1D f1, Func1D f2, Func1D f3);
	};
}
