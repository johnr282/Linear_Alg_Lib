#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"


// Matrix class for sparse matrices; stores data in three vectors; one for the actual data, 
// one for row indices, and one for column indices
template <typename T>
class SparseMatrix : public Matrix {

private:

	// Vector to store data
	std::vector<T> data;

	// Vectors to store row and column indices; the three vectors data, row_indices, 
	// and col_indices will always be the same size
	// The value data[i] is in the position (row_indices[i], col_indices[i])
	// All other locations in the matrix are zeroes
	std::vector<size_t> row_indices;
	std::vector<size_t> col_indices;

	// Number of non-zero elements in the matrix; this is also the size of the data, 
	// row_indices, and col_indices vectors
	size_t num_nonzero;

public:

	// Constructor with three input vectors; one data, one row_indices, and one
	// col_indices vector; the data vector should only contain non-zero values
	SparseMatrix(const std::vector<T>& data_in, 
				 const std::vector<size_t>& row_indices_in,
				 const std::vector<size_t>& col_indices_in, 
				 const size_t rows_in, 
				 const size_t cols_in);

	// Constructor with only one input vector; this vector contains every element
	// in the matrix, including zero values
	// The input vector's storage type is equal to the given storage type
	SparseMatrix(const std::vector<T>& data_in, 
				 const StorageType storage_type_in,
				 const size_t rows_in, 
				 const size_t cols_in);
};

#endif