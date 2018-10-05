// ------------------------------------------------------------------------- //
// File Name   : Cole5.cpp
// Due Date    : 10/04/2018
// Author      : Jackson Cole
// MNumber     : M01250797
// Affilitation: Middle Tennessee State University
// Course      : CSCI/MATH 3180 // Assignment  : Lab Assignment #05
// Description :
//     1. Create a C++ console application project in Visual Studio 2015 and
//        name your project YourLastName5.
//     2. Write a program that implements
//            1) the Naïve Gaussian Elimination and
//            2) Gaussian Elimination with Partial Pivoting for linear systems.
//     3. All floating point arithmetic will be double precision.
//     4. Input to the main program: Name of a data file that contains a
//        sequence of augmented matrices each of which represents a linear
//        system
//     5. Program output:
//            For each linear system
//            - Original augmented matrix
//            - Upper triangular matrix obtained by the Naïve Gaussian
//              Elimination
//            - Solution from the Naïve Gaussian Elimination
//            - Upper triangular matrix obtained by the Gaussian Elimination
//              with Partial Pivoting
//            - Solution from the Gaussian Elimination with Partial Pivoting
//     6. Analyze your output and write a short report including the following
//            - Description of your experiment
//            - For each of the data sets
//                  - Program input
//                  - Program output
//            - Your conclusion/findings
//            - Save your report as YourLastNameReport5.
// ------------------------------------------------------------------------- //
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

// ------------------------------------------------------------------------- //
// Type Definitions
// ------------------------------------------------------------------------- //
typedef std::vector< std::vector<double> > Matrix;  // functions as a matrix
typedef std::vector< Matrix > MatrixList;           // vector of matrices
typedef std::vector< double > vecD;                 // vector of doubles
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Function Prototypes
// ------------------------------------------------------------------------- //
void ReadData(MatrixList&, string); // Reads data in from a file

void NGE(Matrix&);                  // Naive Gaussian Elimintation
void GEPP(Matrix&);                 // Gaussian Elimination w/ Partial Pivoting
vecD BackSubstitution(Matrix&);     // Generic back substitution routine

void PrintAugmentedMatrix(Matrix&); // Prints a formatted augmented matrix
void PrintSolutions(vecD&);         // Prints the list of solutions
void PrintAllOutput(Matrix&);            // Prints desired output for a given
                                    // // augmented matrix
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Main Function
// ------------------------------------------------------------------------- //
int main(int argc, char* argv[]) {
	// --------------------------------------------------------------------- //
	// Variable Declarations
	// --------------------------------------------------------------------- //
	string input;                   // for storing user input of file path
	string filePath;                // path to data file
	MatrixList matList;             // list of matricies from file
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Getting user input to select file path for data file, subsequently
	// // assigning file path to filePath
	// --------------------------------------------------------------------- //
	cout << "You may now enter the path to a data file or choose the" << endl;
	cout << "default by pressing enter. The default is './data.txt'." << endl;
	cout << "> "; getline(cin, input);
	if (input.empty())
		filePath = "./data/data.txt";
	else
		filePath = input;
	// --------------------------------------------------------------------- //

	// --------------------------------------------------------------------- //
	// Reading data from file, printing appropriate output for each matrix
	// --------------------------------------------------------------------- //
	ReadData(matList, filePath);

	for (unsigned int i = 0; i < matList.size(); i++) {
		PrintAllOutput(matList[i]);
	}
	// --------------------------------------------------------------------- //

	return 0;
} // end main
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Functions
// ------------------------------------------------------------------------- //
void ReadData(MatrixList& matList, string filePath) {
	//        IN/OUT               IN
	ifstream dataFile;
	string line;
	Matrix tempMat;
	double tempDoub;
	unsigned int rows;

	dataFile.open(filePath);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			rows = stoi(line);
			tempMat.clear();
			tempMat.resize(rows);

			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < rows + 1; j++) {
					dataFile >> tempDoub;
					tempMat[i].push_back(tempDoub);
				}
			}
			matList.push_back(tempMat);

			dataFile.get();
			getline(dataFile, line);
		}
	}

	else
		cout << "ERROR: File not opened for reading" << endl;

} // end ReadData

void NGE(Matrix& mat) {
	//   IN/OUT
	// --------------------------------------------------------------------- //
	// Naive Gaussian Eliminiation
	// --------------------------------------------------------------------- //
	unsigned int size = mat[0].size() - 1;
	double m;

	for (unsigned int k = 0; k < size - 1; k++) {
		for (unsigned int row = k + 1; row < size; row++) {
			m = mat[row][k]/mat[k][k];

			for (unsigned int col = k; col < size + 1; col++)
				mat[row][col] = mat[row][col] - m * mat[k][col];
		}
	}
} // end NGE

void GEPP(Matrix& mat) {
	//    IN/OUT
	// --------------------------------------------------------------------- //
	// Gaussian Eliminiation with Partial Pivoting
	// --------------------------------------------------------------------- //
	unsigned int size = mat[0].size() - 1;
	double m;
	unsigned int maxRow;
	double max;

	for (unsigned int pivot = 0; pivot < size - 1; pivot++) {
		for (unsigned int row = pivot; row < size - 1; row++)
			maxRow = (mat[row][pivot] < mat[row + 1][pivot]) ? row + 1 : row;

		if (maxRow != pivot)
			mat[pivot].swap(mat[maxRow]);

		for (unsigned int row = pivot + 1; row < size; row++) {
			m = mat[row][pivot]/mat[pivot][pivot];

			for (unsigned int col = pivot; col < size + 1; col++)
				mat[row][col] = mat[row][col] - m * mat[pivot][col];
		}
	}
} // end GEPP

vecD BackSubstitution(Matrix& mat) {
	//                IN
	// --------------------------------------------------------------------- //
	// Back Substitution (given an upper triangular matrix)
	// --------------------------------------------------------------------- //
	unsigned int size = mat.size();
	unsigned int n = size - 1;
	double sum;
	vecD solutions;

	solutions.resize(size);

	for (unsigned int i = 0; i < size; i++)
		solutions[i] = mat[i][size];

	solutions[n] = solutions[n] / mat[n][n];

	for (unsigned int i = n - 1; i >= 0; i--) {
		sum = 0;

		for (unsigned int j = i + 1; j <= n; j++)
			sum += mat[i][j] * solutions[j];

		solutions[i] = (solutions[i] - sum) / mat[i][i];
	}

	return solutions;
} // end BackSubstitution

void PrintAllOutput(Matrix& mat) {
	//         IN
	// --------------------------------------------------------------------- //
	// PrintAllOutput
	// --------------------------------------------------------------------- //
	vecD solutions;
	const string DIVIDER = string(80, '*');
	Matrix NGEmat = mat;
	Matrix GEPPmat = mat;

	cout << DIVIDER << endl;

	cout << "Original Augmented Matrix:" << endl;
	PrintAugmentedMatrix(mat);
	cout << endl;

	cout << "Naive Gaussian Elimination" << endl;
	cout << "> Upper triangular matrix obtained:" << endl;
	NGE(NGEmat);
	PrintAugmentedMatrix(NGEmat);
	cout << "> SOLUTION:" << endl;
	solutions = BackSubstitution(NGEmat);
	PrintSolutions(solutions);
	solutions.clear();
	cout << endl;

	cout << "Gaussian Elimination with Partial Pivoting" << endl;
	cout << "> Upper triangular matrix obtained:" << endl;
	GEPP(GEPPmat);
	PrintAugmentedMatrix(GEPPmat);
	cout << "> SOLUTION:" << endl;
	solutions = BackSubstitution(GEPPmat);
	PrintSolutions(solutions);
	solutions.clear();

	cout << DIVIDER << endl;
	cout << endl;

} // end PrintAllOutput


void PrintAugmentedMatrix(Matrix& mat) {
	//                    IN
	// --------------------------------------------------------------------- //
	// PrintAugmentedMatrix
	// --------------------------------------------------------------------- //
	unsigned int i, j;
	unsigned int size = mat[0].size() - 1;
	unsigned int width = 8;
	cout.precision(3);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size + 1; j++) {
			cout << fixed << setw(width) << right;
			if (j == size - 1) {
				cout << mat[i][j];
				cout << setw(width/2) << right;
				cout << "|";
			}
			else
				cout << mat[i][j];
		}
		cout << endl;
	}
} // end PrintAugmentedMatrix


void PrintSolutions(vecD& solutions) {
	//              IN
	// --------------------------------------------------------------------- //
	// PrintSolutions
	// --------------------------------------------------------------------- //
	for (unsigned int i = 0; i < solutions.size(); i++)
		cout << "x" << i + 1 << " = " << solutions[i] << endl;

} // end PrintSolutions
