#ifndef TESTS_UTILS_H
#define TESTS_UTILS_H

#include "../../include/dense_matrix.h"
#include "../../include/sparse_matrix.h"
#include "../../include/lib_utils.h"

using namespace LinAlg;

// ------------------------------------------------------------------
// Helpers for unit testing
// ------------------------------------------------------------------

// Checks if given vectors are approximately equal
template <typename DataType>
void checkVectors(const std::vector<DataType>& vec1, 
				  const std::vector<DataType>& vec2)
{
	assert(vec1.size() == vec2.size());

	for (size_t i = 0; i < vec1.size(); ++i)
	{
		assert(areEqual(vec1[i], vec2[i]));
	}
}

// Checks if given dense matrix has given data vector, row and column 
// numbers, size, and storage type
template <typename DataType>
inline void checkDenseMatrix(const DenseMatrix<DataType>& mat, 
							 const std::vector<DataType>& data, 
							 size_t rows,
							 size_t cols, 
							 StorageType type)
{
	assert(mat.getData() == data);
	assert(mat.rows() == rows);
	assert(mat.cols() == cols);
	assert(mat.size() == (rows * cols));
	assert(mat.getStorageType() == type);
}

// Checks if given sparse matrix has given data, row indices, col indices, 
// number of nonzero elements, and number of rows and columns
template <typename DataType>
inline void checkSparseMatrix(const SparseMatrix<DataType>& mat, 
							  const std::vector<DataType>& data,
							  const std::vector<size_t>& row_indices,
							  const std::vector<size_t>& col_indices, 
							  size_t num_nonzero,
							  size_t rows,
							  size_t cols)
{
	assert(mat.getData() == data);
	assert(mat.getRowIndices() == row_indices);
	assert(mat.getColIndices() == col_indices);
	assert(mat.getNumNonzero() == num_nonzero);
	assert(mat.rows() == rows);
	assert(mat.cols() == cols);
}


#endif