#include "../include/matrix_ops_utils.h"

// Returns true if matrix dimensions match; false otherwise
template <typename T>
bool sameDimension(const DenseMatrix<T>& mat1,
	const DenseMatrix<T>& mat2) {
	return (mat1.getRows() != mat2.getRows()) || (mat1.getCols() != mat2.getCols());
}