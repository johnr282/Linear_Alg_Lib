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
		   size_t cols_in) :
		_rows(rows_in),
		_cols(cols_in),
		_size(rows_in* cols_in)
	{ }

	size_t getRows() const
	{
		return _rows;
	}

	size_t getCols() const
	{
		return _cols;
	}

	size_t getSize() const
	{
		return _size;
	}

private:

	// Number of rows/columns and total number of elements
	size_t _rows;
	size_t _cols;
	size_t _size;
};

#endif