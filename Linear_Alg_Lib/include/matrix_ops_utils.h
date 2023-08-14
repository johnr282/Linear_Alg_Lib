#ifndef MATRIX_OPS_UTILS_H
#define MATRIX_OPS_UTILS_H

#include "dense_matrix.h"

// Returns true if matrix dimensions match; false otherwise
template <typename T>
bool sameDimension(const DenseMatrix<T>& mat1,
	const DenseMatrix<T>& mat2);

#endif