/* ----------------------------------------------------------------------------
 * File Name   : Cole9.cpp
 * Due Date    : 11/26/2018
 * Author      : Jackson Cole
 * MNumber     : M01250797
 * Affilitation: Middle Tennessee State University
 * Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #09
 * Description :
 *     1. Create a C++ console application in Visual Studion 2015 and name your
 *        project YourLastName9
 *     2. Write a program that implements
 *         1. the bisection method
 *         2. the secand method
 *         for approximating a zero of a function.
 *         f(x) = x**3 - 2*x**2 - 5x + 6
 *     3. Write a separate function for each of the following:
 *         - Evaluating f(x)
 *         - Bisection method
 *         - Secand method
 *     4. Use the following parameters for both methods:
 *         - double x0: starting approximation 0
 *         - double x1: starting approximation 1
 *         - int maxIterations: maximum number of approximations generated
 *         - double xTolerance: max distance between last 2 approximations
 *         - double yTolerance: max distance from f(last approximation) to 0
 *         The functions should iterate until both stopping criteria are met or
 *         it exceeds the maximum number of iterations
 *      5. Test your program using the following function calls:
 *             secant(    0,  4, 20, 0.001, 0.00001);
 *             secant(    0,  2, 20, 0.001, 0.00001);
 *             secant(    2,  4, 20, 0.001, 0.00001);
 *             secant(    0,  3, 20, 0.001, 0.00001);
 *             secant(    1,  2, 20, 0.001, 0.00001);
 *             secant(    2, 30, 20, 0.001, 0.00001);
 *             secant(   10, 30, 20, 0.001, 0.00001);
 *             bisection( 0,  4, 20, 0.001, 0.00001);
 *             bisection( 0,  2, 20, 0.001, 0.00001);
 *             bisection( 2,  4, 20, 0.001, 0.00001);
 *             bisection( 0,  3, 20, 0.001, 0.00001);
 *             bisection( 1,  2, 20, 0.001, 0.00001);
 *             bisection( 2, 30, 20, 0.001, 0.00001);
 *             bisection(10, 30, 20, 0.001, 0.00001);
 * ------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// ------------------------------------------------------------------------- //
// Type Definitions
// ------------------------------------------------------------------------- //
typedef vector< double > Vec1D;

// ------------------------------------------------------------------------- //
// Structs, struct related typedefinitions
// ------------------------------------------------------------------------- //
struct Iteration {
	/* Iteration is a container for all information related to a particular
	 * iteration. There are two initializer lists which allow for storing
	 * an "initial root," that does not have an associated error. This is
	 * largely an ad-hoc solution.
	 */
	bool   initial_root;
	int    num;
	double approx_root;
	double x_error;
	double y_error;
	Iteration(bool initial_root, int num, double approx_root) :
		initial_root(initial_root), num(num), approx_root(approx_root) {};
	Iteration(int num, double approx_root, double x_error, double y_error) :
		num(num), approx_root(approx_root), x_error(x_error), y_error(y_error) {};
};

typedef vector< Iteration > IterationVec;

// ------------------------------------------------------------------------- //
// Function Prototypes
// ------------------------------------------------------------------------- //
double Function(double);
void   secant(   double, double, int, double, double);
void   bisection(double, double, int, double, double);
void   PrintResults(string, double, double, IterationVec, bool, bool, bool, bool);

int main() {
	cout << string(100, '#') << endl;
	secant(    0,  4, 20, 0.001, 0.00001);
	bisection( 0,  4, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
	secant(    0,  2, 20, 0.001, 0.00001);
	bisection( 0,  2, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
    secant(    2,  4, 20, 0.001, 0.00001);
	bisection( 2,  4, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
	secant(    0,  3, 20, 0.001, 0.00001);
	bisection( 0,  3, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
	secant(    1,  2, 20, 0.001, 0.00001);
	bisection( 1,  2, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
	secant(    2, 30, 20, 0.001, 0.00001);
	bisection( 2, 30, 20, 0.001, 0.00001);

	cout << string(100, '#') << endl;
	secant(   10, 30, 20, 0.001, 0.00001);
	bisection(10, 30, 20, 0.001, 0.00001);

	return 0;
} // end main


// ------------------------------------------------------------------------- //
// Functions
// ------------------------------------------------------------------------- //
double Function(double x) {
	// The function to be evaluated
	return pow(x, 3) - 2*pow(x, 2) - 5*x + 6;
}


void secant(double x0, double x1, int maxIterations,
	double xTolerance, double yTolerance) {
	string method = "Secant Method";

	IterationVec iter_vec;
	double a, b, c;
	double fa, fb;
	bool exceeded_max_iterations;
	double x_error, y_error;
	bool exact_found, initial_root;

	a = x0;
	b = x1;
	fa = Function(a);
	fb = Function(b);

	//if (abs(fa) > abs(fb)) {
	//	double temp = a;
	//	a = b;
	//	b = temp;

	//	temp = fa;
	//	fa = fb;
	//	fb = temp;
	//}


	// initial_root is a boolean that identifies if one of the initial guesses
	// at a root is correct. If initial_root == true, the initial root is
	// appended to the iter_vec vector using a case-specific initializer list.
	int i = 0;

	exact_found = (fa == 0. || fb == 0.);
	initial_root = exact_found;
	if (initial_root) {
		double first_root = (fa == 0. ? a : b);
		iter_vec.push_back(Iteration(initial_root, i, first_root));
	}
	i++; // i is iterated here because the first "iteration" is technically 0

	exceeded_max_iterations = false;
	do {
		c = b - fb*(b - a)/(fb - fa);

		a = b;
		b = c;
		fa = fb;
		fb = Function(c);

		x_error = abs(b - a);
		y_error = abs(fb);
		exact_found = (fa == 0. || fb == 0.);

		iter_vec.push_back(Iteration(i, c, x_error, y_error));

		i++;

		if (i > maxIterations)
			exceeded_max_iterations = true;

	} while ((i <= maxIterations && (x_error >= xTolerance || y_error >= yTolerance)) && !exact_found);


	PrintResults(method, x0, x1, iter_vec, true, exceeded_max_iterations, exact_found, initial_root);

}


void bisection(double x0, double x1, int maxIterations,
	double xTolerance, double yTolerance) {
	string method = "Bisection Method";

	IterationVec iter_vec;
	double a, b;

	double midpoint;
	double approx_root;  // for storing the value of an approximate root
	                     // (midpoint) for more verbosity
	double fa, fb, fc;   // for storing function values
	bool   initial_root; // indicates if one of the initial guesses was a root

	double x_error, y_error;
	bool   exact_found, exceeded_max_iterations, exists;

	a = x0;
	b = x1;
	midpoint = (a + b)/2.;
	approx_root = midpoint;
	fa = Function(a);
	fb = Function(b);
	fc = Function(midpoint);

	// initial_root is a boolean that identifies if one of the initial guesses
	// at a root is correct. If initial_root == true, the initial root is
	// appended to the iter_vec vector using a case-specific initializer list.
	int i = 0;
	initial_root = (fa ==0. || fb == 0.);
	if (initial_root) {
		double first_root = (fa == 0. ? a : b);
		iter_vec.push_back(Iteration(initial_root, i, first_root));
	}

	i++; // i is iterated here because the first "iteration" is technically 0

	exists = (fa * fb < 0);
	x_error = abs(b - a);
	y_error = abs(fc);
	exact_found = (fa == 0. || fb == 0. || fc == 0.);
	exceeded_max_iterations = false;

	iter_vec.push_back(Iteration(i, approx_root, x_error, y_error));
	i++; // The first real iteration is pushed into iter_vec, so i is iterated
	     // again.

	if (fa * fc > 0) {
		a = midpoint;
		fa = fc;
	}
	else {
		b = midpoint;
		fb = fc;
	}

	if (exists) {
		while ((i <= maxIterations && (x_error >= xTolerance || y_error >= yTolerance)) && !exact_found) {
			midpoint = (a + b)/2.;
			approx_root = midpoint;
			exact_found = (fa == 0. || fb == 0. || fc == 0.);
			x_error = abs(b - a);
			y_error = abs(fc);

			// Setting up values for the next iteration
			fc = Function(midpoint);
			if (fa * fc > 0) {
				a = midpoint;
				fa = fc;
			}
			else {
				b = midpoint;
				fb = fc;
			}

			iter_vec.push_back(Iteration(i, approx_root, x_error, y_error));
			i++;

			if (i > maxIterations)
				exceeded_max_iterations = true;
		}
	}

	PrintResults(method, x0, x1, iter_vec, exists, exceeded_max_iterations, exact_found, initial_root);

}


void PrintResults(string method, double x0, double x1, IterationVec iter_vec,
	bool exists, bool exceeded_max_iterations, bool exact_found, bool initial_root) {
	/* --------------------------------------------------------------------- */
	// Printing header
	/* --------------------------------------------------------------------- */
	cout << "Interval: [";
	cout << fixed << setprecision(6);
	cout << x0 << ", ";
	cout << fixed << setprecision(6);
	cout << x1 << "]" << endl;
	cout << method << endl;

	/* --------------------------------------------------------------------- */
	// Printing body
	/* --------------------------------------------------------------------- */
	if (!exists && !initial_root) {
		cout << "\tFound no root on the interval" << endl;
	}
	else {
		if (initial_root) {
			cout << "\tExact root found at ";
			cout << iter_vec.front().approx_root << endl;
			cout << "\tNumber of iterations: ";
			cout << iter_vec.front().num << endl;
		}
		else {
			int width = 80;
			cout << string(width, '-') << endl;
			cout << setw(12) << right << fixed;
			cout << "Iteration";
			cout << setw(20) << right << fixed;
			cout << "Approximate Root";
			cout << setw(20) << right << fixed;
			cout << "x_error";
			cout << setw(20) << right << fixed;
			cout << "y_error" << endl;
			cout << string(width, '-') << endl;

			int num_iterations = iter_vec.size();
			for (int i = 0; i < num_iterations; i++) {
				cout << setw(12) << right << fixed;
				cout << iter_vec[i].num;
				cout << setw(20) << right << fixed;
				cout << iter_vec[i].approx_root;
				cout << setw(20) << right << fixed;
				cout << iter_vec[i].x_error;
				cout << setw(20) << right << fixed;
				cout << iter_vec[i].y_error << endl;
			}
			if (exact_found) {
				cout << "\tExact root found at ";
				cout << iter_vec.back().approx_root << endl;
				cout << "\tNumber of iterations: ";
				cout << iter_vec.back().num << endl;

			}
			else {
				if (exceeded_max_iterations)
					cout << "\tExceeded maximum number of iterations." << endl;

				cout << "\tApproximated root: ";
				cout << fixed << setprecision(6);
				cout << iter_vec.back().approx_root << endl;

				cout << "\t" << (exceeded_max_iterations ? "was found at " : "Number of iterations: ");
				cout << iter_vec.back().num << endl;

				cout << "\tx_error: ";
				cout << fixed << setprecision(6);
				cout << iter_vec.back().x_error << endl;

				cout << "\ty_error: ";
				cout << fixed << setprecision(6);
				cout << iter_vec.back().y_error << endl;
			}
		}
	}
	cout << endl << endl;
}
