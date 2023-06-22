#pragma once

#ifndef MATRIX_OPS_HELPERS_H
#define MATRIX_OPS_HELPERS_H

#include "matrix.h"


// Returns true if matrix dimensions match; false otherwise
template <typename T>
bool sameDimension(const DenseMatrix<T>& mat1, const DenseMatrix<T>& mat2) {
	return (mat1.getRows() != mat2.getRows()) || (mat1.getCols() != mat2.getCols());
}



#endif