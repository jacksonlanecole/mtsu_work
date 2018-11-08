// spline.hpp
// ------------------------------------------------------------------------- //
// File Name   : spline.hpp
// Due Date    : 11/06/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #08
// Description : Header file of a spline function class
// ------------------------------------------------------------------------- //
#ifndef SPLINE_H_
#define SPLINE_H_

/* ------------------------------------------------------------------------- */
// Includes
/* ------------------------------------------------------------------------- */
#include <vector>
#include <cmath>
#include "tdm.hpp"
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
// Type definitions
/* ------------------------------------------------------------------------- */
typedef std::vector< double > Array1D;
typedef double (*function_type)(double);
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
// Structs
/* ------------------------------------------------------------------------- */
struct Point {
	/*
	 * Struct for points that are input...
	 * I didn't need a 2D Array, but I needed a convenient way to carry around
	 * the points while meeting the specifications.
	 */
	double t;
	double y;
	Point(double t, double y) : t(t) , y(y) {}
};

struct Coeff {
	/* Coefficient struct for completed spline function piece */
	double A;
	double B;
	double C;
	double D;
	Coeff(double A, double B, double C, double D) : A(A), B(B), C(C), D(D) {}
};
/* ------------------------------------------------------------------------- */

class Spline {
	private:
		Array1D hVec;
		Array1D bVec;
		Array1D uVec;
		Array1D vVec;
		Array1D zVec;
		Array1D solutions;
		int pieces;                    // Number of spline pieces
		std::vector< Point > dataVec;  // vector of Point structs
		std::vector< Coeff > coeffVec; // vector of coefficient structs for
		                               //   passing around spline coeffs

 	public:
		TDM tdm;    // the tdm member is public as we want to access several of
		            //  it's member functions.
		/* ----------------------------------------------------------------- */
		// Constructors
		/* ----------------------------------------------------------------- */
		Spline();
		Spline(Array1D&, Array1D&);
		// Disregarding the rule of threes...
		// Omitting the destructor...
 		/* ----------------------------------------------------------------- */

 		/* ----------------------------------------------------------------- */
		// Methods
 		/* ----------------------------------------------------------------- */
		// Accessors
		void setDataVec(Array1D&, Array1D&);
		void set_hVec();
		void set_bVec();
		void set_uvVec();
		void set_coeffVec();
		Array1D getSolutions();

		// Approximators
		Array1D Approximate(Array1D&);
		double Approximate(double);

		// Computation
		Coeff ComputeCoeff(int i);

		// Printers
		void printCoeffVec();
		void printSplines();
 		/* ----------------------------------------------------------------- */

};


#endif
