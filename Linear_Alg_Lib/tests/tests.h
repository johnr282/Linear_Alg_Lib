#ifndef TESTS_H
#define TESTS_H

#include <cassert>
#include <numeric>
#include "../include/dense_matrix.h"
#include "../include/sparse_matrix.h"

// ------------------------------------------------------------------
// Unit testing functions
// ------------------------------------------------------------------

// MathVector unit tests

void testMathVector();

void testMathVectorInsertion();

void testMathVectorSubscript();

void testMathVectorAdd();

void testMathVectorSubtract();

void testMathVectorDotProduct();

void testMathVectorCrossProduct();

void testMathVectorMagnitude();

void testMathVectorGetUnitVector();


// DenseMatrix unit tests

void testDenseMatrix();

void testDenseMatrixCtor();

void testDenseMatrixInsertion();

void testDenseMatrixSetData();

void testDenseMatrixConvertColMajor();

void testDenseMatrixConvertRowMajor();

void testDenseAdd();

void testDenseSub();

void testDenseMult();


// SparseMatrix unit tests

void testSparseMatrix();

void testSparseCtor();



#endif