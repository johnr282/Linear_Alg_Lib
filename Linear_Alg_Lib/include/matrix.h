#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <algorithm>
#include <string>


// Base Matrix abstract class for derived classes DenseMatrix, SparseMatrix, DiagonalMatrix
class Matrix {

public:

	// Constructor
	Matrix(size_t rows_in, 
		   size_t cols_in);

	// All derived classes have some form of printMatrix() function
	virtual void printMatrix() const = 0;

	size_t getRows() const;

	size_t getCols() const;

	size_t getSize() const;

private:

	// Number of rows/columns and total number of elements
	size_t rows;
	size_t cols;
	size_t size;
};

#endif