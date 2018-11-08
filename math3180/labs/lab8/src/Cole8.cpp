/* ----------------------------------------------------------------------------
 * File Name   : Cole8.cpp
 * Due Date    : 11/06/2018
 * Author      : Jackson Cole
 * MNumber     : M01250797
 * Affilitation: Middle Tennessee State University
 * Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #08
 * Description :
 *     2. Write a program that implements the systematic procedure for
 *        constructing a natural spline discussed in class.
 *     3. The program must use single dimensional arrays only; no two
 *        dimensional arrays are allowed.
 *     4. Program input: not required.
 *     5. Program output:
 *        - Data points, (ti, yi), 0 ≤ i ≤ n
 *        - Tri-diagonal system for zi, 1 ≤ i ≤ n-1 before Forward Elimination
 *        - Tri-diagonal system for zi, 1 ≤ i ≤ n-1 after Forward Elimination
 *        - Solution for zi, 0 ≤ i ≤ n after Back Substitution
 *        - Coefficients Ai, Bi, Ci, Di, 0 ≤ i ≤ n-1 for Natural Cubic Spline
 *              in nested form
 *        - Natural Cubic Spline, Si, 0 ≤ i ≤ n-1 in nested form
 *        - Table containing x, f(x), S(x), and |f(x)-S(x)|
 *              for x = -8, -6, -5, -4, -3,-2, -1, 0, 1, 2, 3, 4, 5, 6, 8.
 *  ------------------------------------------------------------------------ */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include "spline.hpp"

using namespace std;

// ------------------------------------------------------------------------- //
// Type Definitions
// ------------------------------------------------------------------------- //
typedef std::vector< double > Array1D;
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Function Prototypes
// ------------------------------------------------------------------------- //
double Function(double);
       // The function 1/(x**2 + 1)
void   PrintDataPoints(Array1D&, Array1D&);
       // Prints the input data and the function evaluated at those points
void   PrintResults(Array1D&, Array1D&, Array1D&, Array1D&);
       // Prints the results of the interpolation
// ------------------------------------------------------------------------- //

int main() {
	// --------------------------------------------------------------------- //
	// Variable Declarations
	// --------------------------------------------------------------------- //
	Array1D inVec {-8., -6., -4., -2., 0., 2., 4., 6., 8};
	Array1D testVec {-8., -6., -5., -4., -3., -2., -1., 0., 1., 2., 3., 4., 5., 6., 8.};
	//Array1D inVec {-4., -2., 0., 2., 4.};
	//Array1D testVec {-4., -3., -2., -1., 0., 1., 2., 3., 4.};

	Array1D inVecResults;

	Array1D testVecResults;
	Array1D zVec;

	Array1D approxVec;
	Array1D absDiffVec;
	// --------------------------------------------------------------------- //

	for (int i = 0; i < inVec.size(); i++)
		inVecResults.push_back(Function(inVec[i]));

	PrintDataPoints(inVec, inVecResults);

	Spline spline3(inVec, inVecResults); // instantiating spline class

	cout << "\nTri-diagonal system for z1 through z(n-1)" << endl;
	cout << string(60, '-') << endl;
	spline3.tdm.Print();
	cout << string(60, '-') << endl;

	spline3.tdm.Solve();
	zVec = spline3.getSolutions();
	cout << "\nTri-diagonal system after Forward Elimination" << endl;
	cout << string(60, '-') << endl;
	spline3.tdm.Print();
	cout << string(60, '-') << endl;

	cout << "\nSolutions for S''(ti) = zi" << endl;
	cout << string(40, '-') << endl;
	for (int i = 0; i < zVec.size(); i++) {
		cout << "z" << i << ": " << zVec[i] << endl;
	}
	cout << string(40, '-') << endl;

	cout << "\nCoefficients for Natural Cubic Spline in nested form" << endl;
	cout << string(80, '-') << endl;
	spline3.set_coeffVec();
	spline3.printCoeffVec();
	cout << string(80, '-') << endl;

	cout << "\nNatural Cubic Spline in nested form" << endl;
	cout << string(100, '-') << endl;
	spline3.printSplines();
	cout << string(100, '-') << endl;

	cout << "\nEvaluation of Original and Spline functions and the absolute errors" << endl;
	approxVec = spline3.Approximate(testVec);
	for (int i = 0; i < testVec.size(); i++) {
		testVecResults.push_back(Function(testVec[i]));
		absDiffVec.push_back(abs(testVecResults[i] - approxVec[i]));
	}

	PrintResults(testVec, testVecResults, approxVec, absDiffVec);

	return 0;
} // end main


// ------------------------------------------------------------------------- //
// Functions
// ------------------------------------------------------------------------- //
double Function(double x) {
	return 1/(pow(x, 2) + 1);
}


void PrintDataPoints(Array1D& inVec, Array1D& inVecResults) {
	int size = inVec.size();
	cout << "Data points (ti, yi)" << endl;
	for (int i = 0; i < size; i++) {
		cout << "(t" << i << ", y" << i << ") = (" <<
			 inVec[i] << ", " << inVecResults[i] << ")" << endl;
	}
}


void PrintResults(Array1D& testVec, Array1D& actualVec, Array1D& approxVec,
	              Array1D& absDiffVec) {
	int size = approxVec.size();
	cout << "SIZE = " << size << endl;
	int width = 20;
	int total_width = width*4 + 3;

	//PrintDataPoints(inVec, inVecResults);

	cout << string(total_width, '-') << endl;
	cout << setw(3) << right << fixed;
	cout << "i";
	cout << setw(width) << right << fixed;
	cout << "xi";
	cout << setw(width) << right;
	cout << "f(xi)";
	cout << setw(width) << right;
	cout << "S(xi)";
	cout << setw(width) << right;
	cout << "|f(xi) - S(xi)|" << endl;
	cout << string(total_width, '-') << endl;

	for (int i = 0; i < size; i++) {
		cout << setw(3) << right;
		cout << i;
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << testVec[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << actualVec[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << approxVec[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << absDiffVec[i] << endl;
	}
	cout << string(total_width, '-') << endl;
}
