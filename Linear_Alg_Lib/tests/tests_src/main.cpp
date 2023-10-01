#include <iostream>

#include "../tests_include/math_vector_tests.h"
#include "../tests_include/dense_matrix_tests.h"
#include "../tests_include/benchmarks.h"

// ------------------------------------------------------------------
// Runs all tests
// ------------------------------------------------------------------

int	main(int argc, char* argv[]) {
	testMathVector();
	testDenseMatrix();

	std::cout << "All tests complete\n";

	runBenchmarks();

	std::cout << "All benchmarks complete\n";
	
	return 0;
}