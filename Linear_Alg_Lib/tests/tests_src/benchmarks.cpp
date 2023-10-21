#include "../tests_include/benchmarks.h"

#include <cstdlib>
#include <functional>

#include "../tests_include/benchmark_utils.h"
#include "../tests_include/tests_utils.h"
#include "../../include/linalg.h"
#include "../../include/matrix_mult.h"

// ------------------------------------------------------------------
// Implementations of benchmark execution time tests
// ------------------------------------------------------------------

// Runs all benchmark tests
void runBenchmarks()
{
	benchmarkDenseMatrixMult();
}

// Used to determine that converting mat1 to RowMajor and mat2 to 
// ColMajor improved performance of multiplication
void benchmarkDenseMatrixMult()
{
	std::vector<int> data1 = generateRandomVector(90000);
	std::vector<int> data2 = generateRandomVector(90000);

	DenseMatrix<int> mat1_colmaj(data1, 300, 300);
	DenseMatrix<int> mat1_rowmaj(data1, 300, 300, StorageType::RowMajor);
	DenseMatrix<int> mat2_colmaj(data2, 300, 300);
	DenseMatrix<int> mat2_rowmaj(data2, 300, 300, StorageType::RowMajor);

	auto mult1 = [](DenseMatrix<int> mat1, DenseMatrix<int> mat2)
		{
			DenseMatrix<int> mat3 = basicMultNoConversion(mat1, mat2);
		};

	auto mult2 = [](DenseMatrix<int> mat1, DenseMatrix<int> mat2)
		{
			DenseMatrix<int> mat3 = basicMultWithConversion(mat1, mat2);
		};

	compareExecutionTimes(
		mult1, mult2, 10, "mult1_colcol", "mult2_colcol", mat1_colmaj, mat2_colmaj);
	compareExecutionTimes(
		mult1, mult2, 10, "mult1_colrow", "mult2_colrow", mat1_colmaj, mat2_rowmaj);
	compareExecutionTimes(
		mult1, mult2, 10, "mult1_rowrow", "mult2_rowrow", mat1_rowmaj, mat2_rowmaj);
	compareExecutionTimes(
		mult1, mult2, 10, "mult1_rowcol", "mult2_rowcol", mat1_rowmaj, mat2_colmaj);
}
