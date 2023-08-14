#include "../include/sparse_matrix.h"


// Constructor with three input vectors; one data, one row_indices, and one
// col_indices vector; the data vector should only contain non-zero values
template <typename T>
SparseMatrix<T>::SparseMatrix(const std::vector<T>& data_in, 
						   const std::vector<size_t>& row_indices_in,
						   const std::vector<size_t>& col_indices_in, 
						   const size_t rows_in, 
						   const size_t cols_in) :
	Matrix(rows_in, cols_in), 
	data(data_in), 
	row_indices(row_indices_in),
	col_indices(col_indices_in), 
	num_nonzero(data_in.size()) 
{ }

// Constructor with only one input vector; this vector contains every element
// in the matrix, including zero values
// The input vector's storage type is equal to the given storage type
template <typename T>
SparseMatrix<T>::SparseMatrix(const std::vector<T>& data_in,
							  const StorageType storage_type_in,
							  const size_t rows_in, 
							  const size_t cols_in) :
	Matrix(rows_in, cols_in) 
{

	// If data_in is not row major, convert it to row major
	if (storage_type_in == StorageType::ColumnMajor) {
		data_in = convertToRowMajorHelper(data_in, rows_in, cols_in);
	}

	// Iterates through data_in and puts all non-zero elements into the data vector; 
	// stores the row and column indices of each non-zero element in row_indices and
	// col_indices respectively
	num_nonzero = 0;
	for (size_t i = 0; i < data_in.size(); ++i) {
		T elt = data_in[i];
		if (elt != 0) {
			size_t row = rowIndex(i, cols_in);
			size_t col = colIndex(i, cols_in);
			data.push_back(elt);
			row_indices.push_back(row);
			col_indices.push_back(col);
			++num_nonzero;
		}
	}

	// Remove any extra memory allocated to data, row_indices, or col_indices
	data.resize(num_nonzero);
	row_indices.resize(num_nonzero);
	col_indices.resize(num_nonzero);
}
