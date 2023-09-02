#include <iostream>
#include "math_vector_tests.h"
#include "dense_matrix_tests.h"

// ------------------------------------------------------------------
// Runs all tests
// ------------------------------------------------------------------

int	main(int argc, char* argv[]) {
	testMathVector();
	testDenseMatrix();
	return 0;
}