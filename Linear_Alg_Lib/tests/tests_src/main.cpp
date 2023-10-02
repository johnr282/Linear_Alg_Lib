#include <iostream>

#include "../tests_include/math_vector_tests.h"
#include "../tests_include/dense_matrix_tests.h"
#include "../tests_include/benchmarks.h"

// ------------------------------------------------------------------
// Runs tests and benchmarks
// ------------------------------------------------------------------

bool processArgs(const int argc,
	char* argv[],
	bool& run_tests,
	bool& run_benchmarks);

int	main(int argc, char* argv[]) 
{
	bool run_tests = false;
	bool run_benchmarks = false;
	bool valid_args = processArgs(argc, argv, run_tests, run_benchmarks);

	if (!valid_args)
		return 1;

	if (run_tests)
	{
		testMathVector();
		testDenseMatrix();

		std::cout << "All tests complete\n";
	}

	if (run_benchmarks)
	{
		runBenchmarks();

		std::cout << "All benchmarks complete\n";
	}

	return 0;
}

// Process command line arguments and sets parameters run_tests and
// run benchmarks; returns true if args are valid, false if not
bool processArgs(const int argc, 
	char* argv[], 
	bool& run_tests, 
	bool& run_benchmarks)
{
	std::string usage =
		"Usage: -t to run tests, -b to run benchmarks, -tb to run both tests and benchmarks\n";

	if (argc != 2)
	{
		std::cout << usage;
		return false;
	}

	std::string options(argv[1]);

	if (options == "-tb")
	{
		run_tests = true;
		run_benchmarks = true;
	}
	else if (options == "-t")
	{
		run_tests = true;
	}
	else if (options == "-b")
	{
		run_benchmarks = true;
	}
	else
	{
		std::cout << usage;
		return false;
	}

	return true;
}