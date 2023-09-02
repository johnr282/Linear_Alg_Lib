#include "sparse_matrix_tests.h"

#include <cassert>
#include "tests_utils.h"
#include "../include/sparse_matrix.h"

using namespace LinAlg;

// ------------------------------------------------------------------
// Implementations of SparseMatrix unit tests
// ------------------------------------------------------------------

// Runs all SparseMatrix tests
// TODO, leaving SparseMatrix for now
void testSparseMatrix()
{
	std::cout << "Sparse matrix tests complete\n";
}

void testSparseCtor()
{
	// Test ctor with three input vectors
	std::vector<int> data1{ 1, 1, 1 };
	std::vector<size_t> rows1{ 0, 1, 2 };
	std::vector<size_t> cols1{ 0, 1, 2 };
	SparseMatrix<int> mat1(data1, rows1, cols1, 3, 3);
	checkSparseMatrix(mat1, data1, rows1, cols1, 3, 3, 3);

	std::vector<int> data2{ 1, 1, 1, 1 };
	std::vector<size_t> rows2{ 0, 0, 0, 0 };
}