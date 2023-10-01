#include "../tests_include/benchmarks.h"

#include <cstdlib>

#include "../tests_include/benchmark_utils.h"
#include "../tests_include/tests_utils.h"
#include "../../include/linalg.h"

// ------------------------------------------------------------------
// Implementations of benchmark execution time tests
// ------------------------------------------------------------------

// Runs all benchmark tests
void runBenchmarks()
{
	benchmarkDenseMatrixMult();
}

void benchmarkDenseMatrixMult()
{
	auto basicMult1 = []()
		{
			std::vector<int> data1 = generateRandomVector(10000);
			std::vector<int> data2 = generateRandomVector(10000);

			DenseMatrix<int> mat1(data1, 100, 100);
			DenseMatrix<int> mat2(data2, 100, 100);
			
			DenseMatrix<int> mat3 = mat1 * mat2;
		};

	auto execution_time = measureAverageExecutionTime(basicMult1, 10);
	std::cout << execution_time.count() << "\n";
}