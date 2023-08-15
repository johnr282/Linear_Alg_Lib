#ifndef TESTS_UTILS_H
#define TESTS_UTILS_H

#include "dense_matrix.h"

// ------------------------------------------------------------------
// Helpers for unit testing
// ------------------------------------------------------------------

// Checks if given dense matrix has given data vector, row and column 
// numbers, size, and storage type
template <typename T>
inline void checkMatrix(const DenseMatrix<T>& mat, 
				 const std::vector<T>& data, 
				 size_t rows,
				 size_t cols, 
				 StorageType type)
{
	assert(mat.getData() == data);
	assert(mat.getRows() == rows);
	assert(mat.getCols() == cols);
	assert(mat.getSize() == (rows * cols));
	assert(mat.getStorageType() == type);
}


#endif