// ------------------------------------------------------------------------- //
// File Name   : Cole7.cpp
// Due Date    : 10/18/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #07
// Description :
//     2. Write a program that implements the Newton Interpolation discussed
//        in class.
//     3. Write a separate function for each of the following. You may define
//        and call additional functions.
//         - Computation of divided differences
//         - Evaluation of the interpolating polynomial
//             - Must use a nested form as discussed in class.
//     4. Your program must store divided differences in a single dimensional
//        array.
//     5. All floating point arithmetic will be double precision.
//     6. Program input:
//         - Sequence of x values of data points
//         - Sequence of x values to evaluate P(x)
//     7. Program output
//         - Divided differences at each iteration
//         - Table containing f(x), P(x), |f(x) – P(x)| for the 17 data points.
// ------------------------------------------------------------------------- //

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

// ------------------------------------------------------------------------- //
// Type Definitions
// ------------------------------------------------------------------------- //
typedef std::vector< double > Array1D;
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Function Prototypes
// ------------------------------------------------------------------------- //
void   ComputeDividedDifferences(Array1D&, Array1D&, Array1D&, bool);
       // Computes the divided differences w/ option to print the iteration
void   PrintDividedDifferences(Array1D&, int);
       // Prints the divided difference iteration if called
void   Load1DVec(string, Array1D&);
       // Loads a 1D vector from a string of values with a separator
double Function(double);
       // The function 1/(x**2 + 1)
void   SetupyVec(Array1D&, Array1D&);
       // Sets up the vector containing y values using the function given
double InterpolatedFunction(double, Array1D&, Array1D&, Array1D&);
       // The interpolated function from the data points, using nested
       //     multiplication
void   PrintResults(Array1D&, Array1D&, Array1D&, Array1D&);
       // Prints the results of the interpolation
// ------------------------------------------------------------------------- //

int main(int argc, char* argv[]) {
	// --------------------------------------------------------------------- //
	// Variable Declarations
	// --------------------------------------------------------------------- //
	Array1D xVec, yVec, xVals, DD, results, fnResults, absDiff; // 1D vecs
	string xLine;        // string to hold the input, space separated values
	string dummyString;  // dummy string to hold information about the number
	                     //     of values being entered, as this implementation
	                     //     is using vectors and does not care about the
	                     //     number being input
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Getting user input and setting up vectors
	// --------------------------------------------------------------------- //
	cout << "How many data points?  ";
	getline(cin, dummyString);

	cout << "Enter x values separated by spaces: ";
	getline(cin, xLine);
	Load1DVec(xLine, xVec);
	SetupyVec(yVec, xVec);

	cout << "How many test values?  ";
	getline(cin, dummyString);
	cout << "Enter all x values separated by spaces: ";
	getline(cin, xLine);
	Load1DVec(xLine, xVals);
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Calculations
	// --------------------------------------------------------------------- //
	ComputeDividedDifferences(DD, yVec, xVec, true);

	for (int i = 0; i < xVals.size(); i++) {
		results.push_back(InterpolatedFunction(xVals[i], DD, yVec, xVec));
		fnResults.push_back(Function(xVals[i]));
		absDiff.push_back(abs(fnResults[i] - results[i]));
	}
	// --------------------------------------------------------------------- //

	PrintResults(xVals, fnResults, results, absDiff);

	return 0;
} // end main


// ------------------------------------------------------------------------- //
// Functions
// ------------------------------------------------------------------------- //
double Function(double x) {
	return 1/(pow(x, 2) + 1);
}


void Load1DVec(string csString, Array1D& vec) {
	stringstream ss(csString);
	string val;

	while (ss.good()) {
		getline(ss, val, ' ');
		vec.push_back(stod(val));
	}
}


void SetupyVec(Array1D& yVec, Array1D& xVec) {
	int size = xVec.size();

	for (int i = 0; i < size; i++) {
		yVec.push_back(Function(xVec[i]));
	}

}


void ComputeDividedDifferences(Array1D& DD, Array1D& yVec, Array1D& xVec,
	bool print = false) {
	int size = yVec.size();
	int i;
	for (i = 0; i < size; i++)
		DD.push_back(yVec[i]);

	for (i = 1; i < size; i++) {
		if (print)
			PrintDividedDifferences(DD, i - 1);

		for (int j = size; j >= i; j--)
			DD[j] = (DD[j] - DD[j-1])/(xVec[j] - xVec[j-i]);

	}
	if (print)
		PrintDividedDifferences(DD, i - 1);
}


void PrintDividedDifferences(Array1D& DD, int iteration) {
	static bool headerPrinted = false; // keeps track of whether the header
	                                   //     has been printed

	if (!headerPrinted) {
		cout << "\n" << string(40, '-') << endl;
		cout << "Divided Differences" << endl;
		cout << string(40, '-');
		headerPrinted = true;
	}

	cout << "\nIteration: " << iteration << endl;
	cout << string(15, '-') << endl;

	for (int j = 0; j < DD.size(); j++) {
		cout << setprecision(10) << fixed << setw(15) << right;
		cout << DD[j] << endl;
	}
}


double InterpolatedFunction(
	double x, Array1D& DD, Array1D& yVec, Array1D& xVec) {
	double n = DD.size() - 1;
	double result = DD[n];

	// The interpolated polynomial evaluated using Horner's algorithm
	for (int i = n - 1; i >= 0; i--) {
		result = result * (x - xVec[i]) + DD[i];
	}

	return result;
}


void PrintResults(Array1D& xVals, Array1D& fnResults, Array1D& approxResults,
	Array1D& absDiff) {
	int size = approxResults.size();
	int width = 20;
	int total_width = width*4 + 3;

	cout << endl;
	cout << string(total_width, '-') << endl;
	cout << setw(3) << right << fixed;
	cout << "i";
	cout << setw(width) << right << fixed;
	cout << "x";
	cout << setw(width) << right;
	cout << "f(x)";
	cout << setw(width) << right;
	cout << "P8(x)";
	cout << setw(width) << right;
	cout << "|f(x) - P8(x)|" << endl;
	cout << string(total_width, '-') << endl;

	for (int i = 0; i < size; i++) {
		cout << setw(3) << right;
		cout << i;
		cout << setprecision(3) << setw(width) << right << fixed;
		cout << xVals[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << fnResults[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << approxResults[i];
		cout << setprecision(10) << setw(width) << right << fixed;
		cout << absDiff[i] << endl;
	}
	cout << string(total_width, '-') << endl;
}
