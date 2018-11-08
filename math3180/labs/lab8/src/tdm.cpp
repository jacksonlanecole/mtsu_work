// tdm.cpp
// ------------------------------------------------------------------------- //
// File Name   : tdm.cpp
// Due Date    : 11/06/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #08
// Description : Implementation of a tridiagonal matrix class
// ------------------------------------------------------------------------- //
#include "tdm.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

TDM::TDM() {}; // default constructor

TDM::TDM(Array1D& _u, Array1D& _d, Array1D& _l, Array1D& _b) {
	/* --------------------------------------------------------------------- */
	// Constructor
	/* --------------------------------------------------------------------- */
	size = _d.size();
	u = _u;
	d = _d;
	l = _l;
	b = _b;
}

void TDM::reset(Array1D& _u, Array1D& _d, Array1D& _l, Array1D& _b) {
	/* --------------------------------------------------------------------- */
	// reset method for constructing TDM instance outside of declaration
	/* --------------------------------------------------------------------- */
	size = _d.size();
	u = _u;
	d = _d;
	l = _l;
	b = _b;
}


bool TDM::isSolved() {
	return solved;
}

void TDM::Solve() {
	/* --------------------------------------------------------------------- */
	// Performs the necessary steps to reduce the tridiagonal matrix
	/* --------------------------------------------------------------------- */
	if (!solved) {
		ForwardElimination();
		BackSubstitution();
		solved = true;
	}
}


void TDM::ForwardElimination() {
	/* --------------------------------------------------------------------- */
	// Forward elimination with setting the lower diagonal = 0
	/* --------------------------------------------------------------------- */
	double m;
	for (int i = 1; i < size; i++) {
		m = l[i-1]/d[i-1];
		d[i] = d[i] - u[i-1]*m;
		b[i] = b[i] - b[i-1]*m;
		l[i - 1] = 0;
	}
}

void TDM::BackSubstitution() {
	/* --------------------------------------------------------------------- */
	// Back substitution
	/* --------------------------------------------------------------------- */
	int n = size - 1;
	double sum;

	solutions.resize(size);
	for (int i = 0; i < size; i++)
		solutions[i] = b[i];

	solutions[n] = b[n] / d[n];

	for (int i = n - 1; i >= 0; i--) {
		sum = u[i] * solutions[i + 1];
		solutions[i] = (solutions[i] - sum) / d[i];
	}
} // end BackSubstitution


void TDM::Print() {
	/* --------------------------------------------------------------------- */
	// Prints out an augmented tridiagonal matrix
	/* --------------------------------------------------------------------- */
	int n = size;
	int width = 10;
	struct zerosNeeded {
		int total;
		int left;
		int right;
	};

	zerosNeeded zn;

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			cout << setw(width) << right;
			cout << d[i];
			cout << setw(width) << right;
			cout << u[i];
			for (int j = 0; j < size - 2; j++) {
				cout << setw(width) << right;
				cout << 0;
			}
		}
		else if (i == n - 1) {
			for (int j = 0; j < size - 2; j++) {
				cout << setw(width) << right;
				cout << 0;
			}
			cout << setw(width) << right;
			cout << l[i-1];
			cout << setw(width) << right;
			cout << d[i];
		}
		else {
			zn.total = size - 3;
			zn.left = i - 1;
			zn.right = zn.total - zn.left;
			for (int j = 0; j < zn.left; j++) {
				cout << setw(width) << right;
				cout << 0;
			}
			cout << setw(width) << right;
			cout << l[i-1];
			cout << setw(width) << right;
			cout << d[i];
			cout << setw(width) << right;
			cout << u[i];
			for (int j = 0; j < zn.right; j++) {
				cout << setw(width) << right;
				cout << 0;
			}
		}

		cout << setw(4) << right;
		cout << "|";
		cout << setw(width) << left;
		cout << " " << b[i] << endl;
	}
}


Array1D TDM::getSolutions() {
	return solutions;
}
