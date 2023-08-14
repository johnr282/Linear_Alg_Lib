#ifndef TESTS_H
#define TESTS_H

#include <cassert>
#include <numeric>
#include "dense_matrix.h"
#include "sparse_matrix.h"
#include "matrix_ops.h"


// Contains unit testing functions

void testDenseMatrix();

void testDenseMatrixCtor();

void testDenseMatrixSetData();

void testDenseMatrixConvertColMajor();

void testDenseMatrixConvertRowMajor();

void testDensePrintMatrix();

void testDenseAdd();

template <typename T>
void checkMatrix(const DenseMatrix<T>&, const std::vector<T>&, size_t, size_t, StorageType);

void testDenseSub();


#endif