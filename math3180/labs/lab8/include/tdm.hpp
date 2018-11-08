// tdm.hpp
// ------------------------------------------------------------------------- //
// File Name   : tdm.hpp
// Due Date    : 11/06/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #08
// Description : Header file of a tridiagonal matrix class
// ------------------------------------------------------------------------- //
#ifndef TDM_H_
#define TDM_H_
/* ------------------------------------------------------------------------- */
// Includes
/* ------------------------------------------------------------------------- */
#include <vector>
#include <iostream>
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
// Type definitions
/* ------------------------------------------------------------------------- */
typedef std::vector< double > Array1D;
/* ------------------------------------------------------------------------- */

class TDM {
	private:
		Array1D u, d, l, b, solutions;
		int size;
		bool solved = false;
	public:
		/* ----------------------------------------------------------------- */
		// Constructors
		/* ----------------------------------------------------------------- */
		TDM();
		TDM(Array1D&, Array1D&, Array1D&, Array1D&);
		void reset(Array1D&, Array1D&, Array1D&, Array1D&);
		// Breaking the rule of threes here by omitting copy constructor... sry
		// also omitting destructor... sorry
		/* ----------------------------------------------------------------- */

		/* ----------------------------------------------------------------- */
		// Methods
		/* ----------------------------------------------------------------- */
		bool isSolved();           // returns true if the TDM is solved
		void Solve();              // solves the TDM via tdm methods
		void ForwardElimination(); // TDM Forward elimination
		void BackSubstitution();   // TDM Back substitution

		void Print();              // Prints a well formatted tridiagonal matrix

		Array1D getSolutions();    // Gets solutions of tridiagonal matrix

		// Accessors
		Array1D set_u(Array1D&);
		Array1D set_d(Array1D&);
		Array1D set_l(Array1D&);
		Array1D set_b(Array1D&);
		/* ----------------------------------------------------------------- */
};

#endif
