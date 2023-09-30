#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <algorithm>
#include <string>

#include "math_vector.h"

// ------------------------------------------------------------------
// Base Matrix class for derived classes DenseMatrix and SparseMatrix
// ------------------------------------------------------------------

namespace LinAlg
{
	template <typename DataType, class MatrixType>
	class Matrix 
	{
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

		bool isEmpty() const
		{
			return _size == 0;
		}

		bool isSquare() const
		{
			return _rows == _cols;
		}

		// Returns element at location (row, col), const version
		virtual DataType at(size_t row, size_t col) const = 0;

		// Returns element at location (row, col), non-const version
		virtual DataType at(size_t row, size_t col) = 0;

		//// Returns row i as a MathVector, const version
		//virtual MathVector<DataType> row(size_t i) const = 0;

		//// Returns row i as a MathVector, non-const version
		//virtual MathVector<DataType> row(size_t i) = 0;

		//// Returns col j as a MathVector, const version
		//virtual MathVector<DataType> col(size_t j) const = 0;

		//// Returns col j as a MathVector, non-const version
		//virtual MathVector<DataType> col(size_t j) = 0;

		// Returns transpose of matrix
		virtual MatrixType tranpose() const = 0;

		// Calculates determinant of matrix and puts it in DataType parameter; 
		// only returns false if matrix is not square
		virtual bool determinant(DataType&) const = 0;

		// Returns whether matrix is invertible
		virtual bool isInvertible() const = 0;

		// Calculates inverse of matrix and puts it in MatrixType parameter;
		// returns whether the matrix is invertible
		virtual bool inverse(MatrixType&) const = 0;

		// Calculates eigenvectors and eigenvalues of matrix; puts eigenvectors
		// in eigenvecs parameter and eigenvalues in eigenvals parameter; 
		// eigenvecs[i]'s eigenvalue is eigenvals[i]
		virtual bool eigenvectors(std::vector<MathVector<double> >& eigenvecs,
								  std::vector<double>& eigenvals) const = 0;

	protected:

		// Number of rows/columns and total number of elements
		size_t _rows;
		size_t _cols;
		size_t _size;
	};
}

#endif