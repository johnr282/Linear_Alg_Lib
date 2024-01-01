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

		// Default constructor
		Matrix() :
			_rows(0), 
			_cols(0),
			_size(0)
		{ }

		size_t rows() const
		{
			return _rows;
		}

		size_t cols() const
		{
			return _cols;
		}

		size_t size() const
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

		// += operator overload
		MatrixType& operator+=(const MatrixType& mat)
		{
			*this = *this + mat;
			return *this;
		}

		// -= operator overload
		MatrixType& operator-=(const MatrixType& mat)
		{
			*this = *this - mat;
			return *this;
		}

		// Returns element at location (row, col), const version
		virtual DataType at(const size_t row, const size_t col) const = 0;

		// Returns element at location (row, col), non-const version
		virtual DataType& at(const size_t row, const size_t col) = 0;

		// Returns row pos as a MathVector
		virtual MathVector<DataType> row(const size_t pos) const = 0;

		// Returns col pos as a MathVector
		virtual MathVector<DataType> col(const size_t pos) const = 0;

		// Sets row pos to given MathVector
		virtual void setRow(const size_t pos, 
			const MathVector<DataType>& new_row) = 0;

		// Sets col pos to given MathVector
		virtual void setCol(const size_t pos,
			const MathVector<DataType>& new_col) = 0;

		// Adds given row to the matrix above row pos
		virtual void addRow(const size_t pos, 
			const MathVector<DataType>& new_row) = 0;

		// Adds given col to the matrix to the left of col pos
		virtual void addCol(const size_t pos, 
			const MathVector<DataType>& new_col) = 0;

		// Removes row pos from the matrix entirely
		virtual void removeRow(const size_t pos) = 0;

		// Removes col pos from the matrix entirely
		virtual void removeCol(const size_t pos) = 0;

		// Swaps the two rows at given positions
		virtual void swapRows(const size_t pos1, const size_t pos2) = 0;

		// Swaps the two columns at given positions
		virtual void swapCols(const size_t pos1, const size_t pos2) = 0;

		// Scales row pos by the given factor
		virtual void scaleRow(const size_t pos, const DataType factor) = 0;

		// Scales row col by the given factor
		virtual void scaleCol(const size_t pos, const DataType factor) = 0;

		// Returns matrix containing rows first_row to last_row and 
		// columns first_col to last_col
		virtual MatrixType getSubMatrix(const size_t first_row,
			const size_t last_row,
			const size_t first_col,
			const size_t last_col) const = 0;

		// Sets section of matrix including rows [first_row, last_row)
		// and columns [first_col, last_col) to given matrix
		virtual void setSubMatrix(const size_t first_row,
			const size_t last_row,
			const size_t first_col,
			const size_t last_col,
			const MatrixType& new_sub_matrix) = 0;

	protected:

		// Number of rows/columns and total number of elements
		size_t _rows;
		size_t _cols;
		size_t _size;
	};
}

#endif