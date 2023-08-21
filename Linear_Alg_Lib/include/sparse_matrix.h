#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"


// Matrix class for sparse matrices; stores data in three vectors; one for the actual data, 
// one for row indices, and one for column indices
template <typename T>
class SparseMatrix : public Matrix 
{
public:

	// Constructor with three input vectors; one _data, one _row_indices, and one
	// _col_indices vector; the data vector should only contain non-zero values
	SparseMatrix(const std::vector<T>& data_in, 
				 const std::vector<size_t>& row_indices_in,
				 const std::vector<size_t>& col_indices_in, 
				 const size_t rows_in, 
				 const size_t cols_in) :
		Matrix(rows_in, cols_in),
		_data(data_in),
		_row_indices(row_indices_in),
		_col_indices(col_indices_in),
		_num_nonzero(data_in.size())
	{ }

	// Constructor with only one input vector; this vector contains every element
	// in the matrix, including zero values
	// The input vector's storage type is equal to the given storage type
	SparseMatrix(const std::vector<T>& data_in, 
				 const StorageType storage_type_in,
				 const size_t rows_in, 
				 const size_t cols_in) :
		Matrix(rows_in, cols_in)
	{
		// If data_in is not row major, convert it to row major
		if (storage_type_in == StorageType::ColumnMajor)
			data_in = convertToRowMajorHelper(data_in, rows_in, cols_in);

		// Iterates through data_in and puts all non-zero elements into the data vector; 
		// stores the row and column indices of each non-zero element in _row_indices and
		// _col_indices respectively
		_num_nonzero = 0;
		for (size_t i = 0; i < data_in.size(); ++i) 
		{
			T elt = data_in[i];
			if (elt != 0) 
			{
				size_t row = rowIndex(i, cols_in);
				size_t col = colIndex(i, cols_in);
				_data.push_back(elt);
				_row_indices.push_back(row);
				_col_indices.push_back(col);
				++_num_nonzero;
			}
		}

		// Remove any extra memory allocated to data, _row_indices, or _col_indices
		_data.resize(_num_nonzero);
		_row_indices.resize(_num_nonzero);
		_col_indices.resize(_num_nonzero);
	}

	// Returns _data vector
	std::vector<T> getData() const
	{
		return _data;
	}

	// Returns _row_indices vector
	std::vector<size_t> getRowIndices() const
	{
		return _row_indices;
	}

	// Returns _col_indices vector
	std::vector<size_t> getColIndices() const
	{
		return _col_indices;
	}

	// Returns _num_nonzero
	size_t getNumNonzero() const
	{
		return _num_nonzero;
	}



	// Prints matrix to cout:
	/*
		a  b  c  d
		e  f  g  h
		i  j  k  l
		m  n  o  p
	*/
	// Ensures columns are aligned, even with different amounts of digits
	// Doesn't work well with non integer types
	void printMatrix() const
	{
		//TODO
	}

private:

	// Vector to store non-zero data
	std::vector<T> _data;

	// Vectors to store row and column indices; the three vectors _data, _row_indices, 
	// and _col_indices will always be the same size
	// The value _data[i] is in the position (_row_indices[i], _col_indices[i])
	// All other locations in the matrix are zeroes
	std::vector<size_t> _row_indices;
	std::vector<size_t> _col_indices;

	// Number of non-zero elements in the matrix; this is also the size of the _data, 
	// _row_indices, and _col_indices vectors
	size_t _num_nonzero;
};

#endif