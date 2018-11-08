// spline.cpp
// ------------------------------------------------------------------------- //
// File Name   : spline.cpp
// Due Date    : 11/06/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #08
// Description : Implementation of a spline function class
// ------------------------------------------------------------------------- //
#include "spline.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Spline::Spline(Array1D& dataArr, Array1D& dataResultsArr) {
	pieces = dataArr.size() - 1;
	setDataVec(dataArr, dataResultsArr);
	set_hVec();
	set_bVec();
	set_uvVec();
	tdm.reset(hVec, uVec, hVec, vVec);
}


void Spline::setDataVec(Array1D& dataArr, Array1D& dataResultsArr) {
	double val, fVal;
	for (int i = 0; i < dataArr.size(); i++) {
		val = dataArr[i];
		fVal = dataResultsArr[i];
		dataVec.push_back(Point(val, fVal));
	}
}


void Spline::set_hVec() {
	double h;
	hVec.resize(dataVec.size() - 1);
	for (int i = 0; i < dataVec.size() - 1; i++) {
		hVec[i] = dataVec[i+1].t - dataVec[i].t;
	}
}


void Spline::set_bVec() {
	bVec.resize(hVec.size());
	for (int i = 0; i < hVec.size(); i++) {
		bVec[i] = (dataVec[i+1].y - dataVec[i].y)/hVec[i];
	}
}


void Spline::set_uvVec() {
	int n = hVec.size() - 1;
	uVec.resize(n);
	vVec.resize(n);
	uVec[0] = 2*(hVec[0] + hVec[1]);
	vVec[0] = 6*(bVec[1] - bVec[0]);
	for (int i = 1; i < n; i++) {
		uVec[i] = 2*(hVec[i + 1] + hVec[i]);
		vVec[i] = 6*(bVec[i + 1] - bVec[i]);
	}
}


void Spline::set_coeffVec() {
	for (int i = 0; i < pieces; i++) {
		coeffVec.push_back(ComputeCoeff(i));
	}
}


Array1D Spline::getSolutions() {
	/*
	 * This method takes the solutions of the tridiagonal matrix and pads the
	 * ends with leading and trailing zeros
	 */
	static bool got = false;  // keeps track of if the solutions have already
	                          //   been gotten, as we don't want pad zeros 2x
	if (!got) {
		if (!tdm.isSolved()) {
			tdm.Solve();
		}

		Array1D newSolutions;
		solutions = tdm.getSolutions();
		newSolutions.push_back(0);

		for (int i = 0; i < solutions.size(); i++)
			newSolutions.push_back(solutions[i]);

		newSolutions.push_back(0);
		solutions = newSolutions;
	}

	return solutions;
}




Coeff Spline::ComputeCoeff(int i) {
	double A, B, C, D;
	A = dataVec[i].y;
	B = -(hVec[i]/6.)*solutions[i + 1] - (hVec[i]/3.)*solutions[i]
		+ (dataVec[i+1].y - dataVec[i].y)/hVec[i];
	C = solutions[i]/2.;
	D = (solutions[i+1] - solutions[i])/(6.*hVec[i]);
	return Coeff(A, B, C, D);
}


Array1D Spline::Approximate(Array1D& arr) {
	Array1D results;
	bool computed;
	double x, ti;
	results.resize(arr.size());
	for (int i = 0; i < arr.size(); i++) {
		computed = false;
		x = arr[i];
		int j = 1;
		while (!computed || j == pieces) {
			ti = dataVec[j - 1].t;
			if (x <= dataVec[j].t && x >= dataVec[j - 1].t) {
				int k = j - 1;
				results[i] =
					coeffVec[k].A + (x - ti)*(coeffVec[k].B
						+ (x - ti)*(coeffVec[k].C + (x - ti)*(coeffVec[k].D)));
				computed = true;
			}
			j++;
		}
	}

	return results;
}


double Spline::Approximate(double val) {
	double x, ti;
	for (int j = 0; j < pieces; j++) {
		ti = dataVec[j + 1].t;
		x = val;
		if (x <= ti) {
			val = coeffVec[j].A + (x - ti)*(coeffVec[j].B
					+ (x - ti)*(coeffVec[j].C + (x - ti)*(coeffVec[j].D)));
		}
	}

	return val;
}


void Spline::printCoeffVec() {
	int width = 12;
	for (int i = 0; i < pieces; i++) {
		cout << "A" << i << ":";
		cout << setw(width) << right;
		cout << coeffVec[i].A;

		cout << setw(5) << right;
		cout << "B" << i << ":";
		cout << setw(width) << right;
		cout << coeffVec[i].B;

		cout << setw(5) << right;
		cout << "C" << i << ":";
		cout << setw(width) << right;
		cout << coeffVec[i].C;

		cout << setw(5) << right;
		cout << "D" << i << ":";
		cout << setw(width) << right;
		cout << coeffVec[i].D;
		cout << endl;
	}
}

void Spline::printSplines() {
	int width = 13;
	for (int i = 0; i < pieces; i++) {
		cout << "S" << i << " : ";
		cout << setw(width) << right;
		cout << coeffVec[i].A;
		cout << " + (";
		cout << setw(width) << coeffVec[i].B << " + (" << setw(4) << dataVec[i].t << ")*";
		cout << "(";
		cout << setw(width) << coeffVec[i].C << " + (" << setw(4) << dataVec[i].t << ")*";
		cout << "(";
		cout << setw(width) << coeffVec[i].D << " + (" << setw(4) << dataVec[i].t << ")";
		cout << ")))" << endl;
	}
}
