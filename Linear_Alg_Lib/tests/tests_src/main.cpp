#include <iostream>
#include "../tests_include/math_vector_tests.h"
#include "../tests_include/dense_matrix_tests.h"

// ------------------------------------------------------------------
// Runs all tests
// ------------------------------------------------------------------

int	main(int argc, char* argv[]) {
	testMathVector();
	testDenseMatrix();
	return 0;
}