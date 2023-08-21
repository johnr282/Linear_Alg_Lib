#ifndef TESTS_H
#define TESTS_H

#include <cassert>
#include <numeric>
#include "dense_matrix.h"
#include "sparse_matrix.h"

// ------------------------------------------------------------------
// Unit testing functions
// ------------------------------------------------------------------


// DenseMatrix unit tests

void testDenseMatrix();

void testDenseMatrixCtor();

void testDenseMatrixSetData();

void testDenseMatrixConvertColMajor();

void testDenseMatrixConvertRowMajor();

void testDensePrintMatrix();

void testDenseAdd();

void testDenseSub();

void testDenseMult();


// SparseMatrix unit tests

void testSparseMatrix();

void testSparseCtor();



#endif