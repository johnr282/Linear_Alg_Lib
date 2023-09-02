//#include "tests.h"
//
//#include "tests_utils.h"
//#include "../include/matrix_ops.h"
//#include "../include/vector_ops.h"
//#include "../include/sparse_matrix.h"
//#include "../include/dense_matrix.h"
//#include "../include/lib_utils.h"
//
//using namespace LinAlg;
//
//// ------------------------------------------------------------------
//// Implementations of unit testing functions
//// ------------------------------------------------------------------
//
//// MathVector unit tests
//
//// Runs all MathVector unit tests
//void testMathVector()
//{
//	// testMathVectorInsertion();
//	testMathVectorSubscript();
//	testMathVectorAdd();
//	testMathVectorSubtract();
//	testMathVectorDotProduct();
//	testMathVectorCrossProduct();
//	testMathVectorMagnitude();
//	testMathVectorGetUnitVector();
//
//	std::cout << "MathVector tests complete\n";
//}
//
//void testMathVectorInsertion()
//{
//	std::vector<int> data{ 0, 1, 4, 12, 1, 4, 10 };
//	MathVector<int> vector(data);
//	std::cout << vector;
//}
//
//void testMathVectorSubscript()
//{
//	std::vector<int> data1{ 0, 1, 2 };
//	const MathVector<int> vec1(data1);
//	assert(vec1[0] == 0);	
//
//	MathVector<int> vec2(data1);
//	vec2[1] = 5;
//	assert(vec2[1] == 5);
//}
//
//void testMathVectorAdd()
//{
//	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
//	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
//	MathVector<int> vec1(data1);
//	MathVector<int> vec2(data2);
//	std::vector<int> data3{ 1, 3, 0, 2, 3, 0 };
//	MathVector<int> vec3 = vec1 + vec2;
//	assert(vec3.getData() == data3);
//
//	std::vector<int> data4{ 1, 1, 3, 0 };
//	std::vector<int> data5{ 0, 1, 5, 4 };
//	MathVector<int> vec4(data4);
//	MathVector<int> vec5(data5);
//	std::vector<int> data6{ 1, 2, 8, 4 };
//	MathVector<int> vec6 = vec4 + vec5;
//	assert(vec6.getData() == data6);
//}
//
//void testMathVectorSubtract()
//{
//	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
//	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
//	MathVector<int> vec1(data1);
//	MathVector<int> vec2(data2);
//	std::vector<int> data3{ -1, -1, 0, 2, 1, 0 };
//	MathVector<int> vec3 = vec1 - vec2;
//	assert(vec3.getData() == data3);
//
//	std::vector<int> data4{ 1, 1, 3, 0 };
//	std::vector<int> data5{ 0, 1, 5, 4 };
//	MathVector<int> vec4(data4);
//	MathVector<int> vec5(data5);
//	std::vector<int> data6{ 1, 0, -2, -4 };
//	MathVector<int> vec6 = vec4 - vec5;
//	assert(vec6.getData() == data6);
//}
//
//void testMathVectorDotProduct()
//{
//	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
//	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
//	MathVector<int> vec1(data1);
//	MathVector<int> vec2(data2);
//	int result1 = 4;
//	assert(dotProduct(vec1, vec2) == result1);
//
//	std::vector<int> data3{ 1, 1, 2, 0, 3 };
//	std::vector<int> data4{ 0, 3, 5, 1, 0 };
//	MathVector<int> vec3(data3);
//	MathVector<int> vec4(data4);
//	int result2 = 13;
//	assert(dotProduct(vec3, vec4) == result2);
//}
//
//void testMathVectorCrossProduct()
//{
//	std::vector<int> data1{ 4, 2, 6 };
//	std::vector<int> data2{ 1, 3, -1 };
//	MathVector<int> vec1(data1);
//	MathVector<int> vec2(data2);
//	std::vector<int> data3{ -20, 10, 10 };
//	assert(crossProduct(vec1, vec2).getData() == data3);
//
//	std::vector<int> data4{ 1, 3, -1 };
//	std::vector<int> data5{ 0, 0, 5 };
//	MathVector<int> vec4(data4);
//	MathVector<int> vec5(data5);
//	std::vector<int> data6{ 15, -5, 0 };
//	assert(crossProduct(vec4, vec5).getData() == data6);
//}
//
//void testMathVectorMagnitude()
//{
//	std::vector<int> data1{ 0, 1, 4 };
//	MathVector<int> vec1(data1);
//	double result1 = 4.123105626;
//	assert(areEqual(result1, vec1.magnitude()));
//
//	std::vector<double> data2{ 1.3902, 0.213, 2.493, 5.343 };
//	MathVector<double> vec2(data2);
//	double result2 = 6.061412627;
//	assert(areEqual(result2, vec2.magnitude()));
//
//	std::vector<int> data3{ 0, 0, 0 };
//	MathVector<int> vec3(data3);
//	double result3 = 0.0;
//	assert(areEqual(result3, vec3.magnitude()));
//}
//
//void testMathVectorGetUnitVector()
//{
//	std::vector<int> data1{ 0, 1, 4, 2, 3 };
//	MathVector<int> vec1(data1);
//	double mag1 = vec1.magnitude();
//	std::vector<double> result1{ 
//		0 / mag1, 1 / mag1, 4 / mag1, 2 / mag1, 3 / mag1 };
//	MathVector<double> unit_vec1 = vec1.getUnitVector();
//	checkVectors(result1, unit_vec1.getData());
//
//	std::vector<double> data2{ 1.23, 0.1, 4.99, -8.7, 12.294, -0.23};
//	MathVector<double> vec2(data2);
//	double mag2 = vec2.magnitude();
//	std::vector<double> result2{
//		1.23 / mag2, 0.1 / mag2, 4.99 / mag2, -8.7 / mag2, 12.294 / mag2, -0.23 / mag2 };
//	MathVector<double> unit_vec2 = vec2.getUnitVector();
//	checkVectors(result2, unit_vec2.getData());
//
//	std::vector<double> data3{ 0, 0, 0 };
//	MathVector<double> vec3(data3);
//	std::vector<double> result3{ 0, 0, 0 };
//	MathVector<double> unit_vec3 = vec3.getUnitVector();
//	checkVectors(result3, unit_vec3.getData());
//}
//
//
//
//
//// DenseMatrix unit tests
//
//// Runs all DenseMatrix unit tests
//void testDenseMatrix() 
//{
//	testDenseMatrixCtor();
//	testDenseMatrixSetData();
//	testDenseMatrixConvertColMajor();
//	testDenseMatrixConvertRowMajor();
//	//testDenseMatrixInsertion();
//	testDenseAdd();
//	testDenseSub();
//
//	std::cout << "DenseMatrix tests complete\n";
//}
//
//// Dense Matrix constructor tests
//void testDenseMatrixCtor() 
//{
//	// Test first constructor with data vector
//	std::vector<int> data(12, 1);
//	DenseMatrix<int> mat(data, 3, 4, StorageType::RowMajor);
//	// Check if data is correct
//	assert(mat.getData() == data);
//	assert(mat.getRows() == 3);
//	assert(mat.getCols() == 4);
//	assert(mat.getSize() == 12);
//	assert(mat.getStorageType() == StorageType::RowMajor);
//
//	// Test with default storage type
//	std::vector<double> data2(12, 1.5);
//	DenseMatrix<double> mat2(data2, 3, 4);
//	assert(mat2.getStorageType() == StorageType::ColumnMajor);
//
//	// Test second constructor with no data vector
//	DenseMatrix<uint32_t> mat3(4, 5);
//	assert(mat3.getRows() == 4);
//	assert(mat3.getCols() == 5);
//	assert(mat3.getSize() == 20);
//	assert(mat3.getStorageType() == StorageType::ColumnMajor);
//
//	DenseMatrix<float> mat4(6, 6, StorageType::RowMajor);
//	assert(mat4.getRows() == 6);
//	assert(mat4.getCols() == 6);
//	assert(mat4.getSize() == 36);
//	assert(mat4.getStorageType() == StorageType::RowMajor);
//}
//
//void testDenseMatrixInsertion()
//{
//	std::vector<int> data1(9);
//	std::iota(data1.begin(), data1.end(), 0);
//	DenseMatrix<int> mat1(data1, 3, 3, StorageType::RowMajor);
//	std::cout << mat1;
//	std::cout << "\n";
//
//	DenseMatrix<int> mat1_col(data1, 3, 3, StorageType::ColumnMajor);
//	std::cout << mat1_col;
//	std::cout << "\n";
//
//	std::vector<int> data2{ 23, 0, 0, 0 };
//	DenseMatrix<int> mat2(data2, 2, 2);
//	std::cout << mat2;
//	std::cout << "\n";
//
//	std::vector<int> data3{ -25, 1, 23, 0, 0, 0 };
//	DenseMatrix<int> mat3(data3, 2, 3);
//	std::cout << mat3;
//	std::cout << "\n";
//
//	std::vector<int> data4{ -1, 9999, 0, 0, 0, 0 };
//	DenseMatrix<int> mat4(data4, 3, 2);
//	std::cout << mat4;
//	std::cout << "\n";
//
//	std::vector<size_t> data5(144);
//	std::iota(data5.begin(), data5.end(), 0);
//	DenseMatrix<size_t> mat5(data5, 12, 12);
//	std::cout << mat5;
//	std::cout << "\n";
//
//	DenseMatrix<size_t> mat5_row(data5, 12, 12, StorageType::RowMajor);
//	std::cout << mat5_row;
//	std::cout << "\n";
//}
//
//
//void testDenseMatrixSetData() 
//{
//	std::vector<int> data(10, 5);
//	DenseMatrix<int> mat(data, 5, 2);
//	std::vector<int> data2(10, 2);
//	mat.setData(data2);
//	assert(mat.getData() == data2);
//}
//
//// Test conversions from row major to column major
//void testDenseMatrixConvertColMajor() 
//{
//	// To column major conversion
//	std::vector<int> data1(12);
//	std::iota(data1.begin(), data1.end(), 0);
//	DenseMatrix<int> mat1(data1, 3, 4, StorageType::RowMajor);
//	mat1.convertToColMajor();
//	assert(mat1.getStorageType() == StorageType::ColumnMajor);
//	std::vector<int> data1_col_maj{ 0, 4, 8, 1, 5, 9, 2, 6, 10, 3, 7, 11 };
//	assert(mat1.getData() == data1_col_maj);
//
//	std::vector<int> data2(9);
//	std::iota(data2.begin(), data2.end(), 0);
//	DenseMatrix<int> mat2(data2, 3, 3, StorageType::RowMajor);
//	mat2.convertToColMajor();
//	assert(mat2.getStorageType() == StorageType::ColumnMajor);
//	std::vector<int> data2_col_maj{ 0, 3, 6, 1, 4, 7, 2, 5, 8 };
//	assert(mat2.getData() == data2_col_maj);
//
//	std::vector<int> data3{ 2, 2, 2, 3, 1, 0, 3, 5, 3, 5, 7, 1 };
//	DenseMatrix<int> mat3(data3, 6, 2, StorageType::RowMajor);
//	mat3.convertToColMajor();
//	std::vector<int> data3_col_major{ 2, 2, 1, 3, 3, 7, 2, 3, 0, 5, 5, 1 };
//	assert(mat3.getData() == data3_col_major);
//
//	// Column vector
//	std::vector<int> data4{ 0, 3, 2, 5 };
//	DenseMatrix<int> mat4(data4, 4, 1, StorageType::RowMajor);
//	mat3.convertToColMajor();
//	assert(mat4.getData() == data4);
//
//	// Row vector
//	DenseMatrix<int> mat5(data4, 1, 4, StorageType::RowMajor);
//	mat4.convertToColMajor();
//	assert(mat5.getData() == data4);
//
//}
//
//void testDenseMatrixConvertRowMajor() 
//{
//	std::vector<int> data1(12);
//	std::iota(data1.begin(), data1.end(), 0);
//	DenseMatrix<int> mat1(data1, 3, 4);
//	mat1.convertToRowMajor();
//	assert(mat1.getStorageType() == StorageType::RowMajor);
//	std::vector<int> data1_row_maj{ 0, 3, 6, 9, 1, 4, 7, 10, 2, 5, 8, 11 };
//	assert(mat1.getData() == data1_row_maj);
//
//	std::vector<int> data2(9);
//	std::iota(data2.begin(), data2.end(), 0);
//	DenseMatrix<int> mat2(data2, 3, 3);
//	mat2.convertToRowMajor();
//	assert(mat2.getStorageType() == StorageType::RowMajor);
//	std::vector<int> data2_row_maj{ 0, 3, 6, 1, 4, 7, 2, 5, 8 };
//	assert(mat2.getData() == data2_row_maj);
//
//	std::vector<int> data3{ 2, 2, 2, 3, 1, 0, 3, 5, 3, 5, 7, 1 };
//	DenseMatrix<int> mat3(data3, 6, 2);
//	mat3.convertToRowMajor();
//	std::vector<int> data3_row_maj{ 2, 3, 2, 5, 2, 3, 3, 5, 1, 7, 0, 1 };
//	assert(mat3.getData() == data3_row_maj);
//
//	// Column vector
//	std::vector<int> data4{ 0, 3, 2, 5 };
//	DenseMatrix<int> mat4(data4, 4, 1);
//	mat3.convertToRowMajor();
//	assert(mat4.getData() == data4);
//
//	// Row vector
//	DenseMatrix<int> mat5(data4, 1, 4);
//	mat4.convertToRowMajor();
//	assert(mat5.getData() == data4);
//}
//
//void testDenseAdd() 
//{
//	// colmaj + colmaj
//	std::vector<int> data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	DenseMatrix<int> mat1(data1, 3, 3);
//	std::vector<int> data2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	DenseMatrix<int> mat2(data2, 3, 3);
//	DenseMatrix<int> mat3 = mat1 + mat2;
//	std::vector<int> data3{ 2, 4, 6, 8, 10, 12, 14, 16, 18 };
//	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);
//
//	// colmaj + colmaj
//	std::vector<int> data4{ 1, 2, 4, 5, 6, 7, 1, 3, 10 };
//	DenseMatrix<int> mat4(data4, 3, 3);
//	DenseMatrix<int> mat5 = mat1 + mat4;
//	std::vector<int> data5{ 2, 4, 7, 9, 11, 13, 8, 11, 19 };
//	checkDenseMatrix(mat5, data5, 3, 3, StorageType::ColumnMajor);
//
//	// rowmaj + rowmaj
//	std::vector<int> data6{ 1, 0, 0, 2, 3, 0 };
//	std::vector<int> data7{ 0, 0, 1, 2, 3, 0 };
//	DenseMatrix<int> mat6(data6, 2, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat7(data7, 2, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat8 = mat6 + mat7;
//	std::vector<int> data8{ 1, 0, 1, 4, 6, 0 };
//	checkDenseMatrix(mat8, data8, 2, 3, StorageType::RowMajor);
//
//	// rowmaj + rowmaj
//	DenseMatrix<int> mat9(data6, 3, 2, StorageType::RowMajor);
//	DenseMatrix<int> mat10(data7, 3, 2, StorageType::RowMajor);
//	DenseMatrix<int> mat11 = mat9 + mat10;
//	checkDenseMatrix(mat11, data8, 3, 2, StorageType::RowMajor);
//
//	// rowmaj + colmaj
//	std::vector<int> data12{ 1, 0, 0, 3, 2, 2, 1, 0, 0, 0, 1, 2 };
//	std::vector<int> data13{ 0, 0, 0, 1, 1, 2, 4, 1, 1, 0, 0, 1 };
//	DenseMatrix<int> mat12(data12, 4, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat13(data13, 4, 3, StorageType::ColumnMajor);
//	DenseMatrix<int> mat14 = mat12 + mat13;
//	std::vector<int> data14{ 1, 1, 1, 3, 4, 2, 1, 4, 0, 1, 2, 3 };
//	checkDenseMatrix(mat14, data14, 4, 3, StorageType::RowMajor);
//
//	// colmaj + rowmaj
//	std::vector<int> data15{ 0, 1, 1, 4, 9, 0, 0, 1, 2, 0 };
//	std::vector<int> data16{ 0, 0, 4, 2, 1, 0, 9, 1, 2, 0 };
//	DenseMatrix<int> mat15(data15, 2, 5, StorageType::ColumnMajor);
//	DenseMatrix<int> mat16(data16, 2, 5, StorageType::RowMajor);
//	DenseMatrix<int> mat17 = mat15 + mat16;
//	std::vector<int> data17{ 0, 1, 1, 13, 13, 1, 2, 3, 3, 0 };
//	checkDenseMatrix(mat17, data17, 2, 5, StorageType::ColumnMajor);
//}
//
//void testDenseSub() 
//{
//	// colmaj - colmaj
//	std::vector<int> data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	DenseMatrix<int> mat1(data1, 3, 3);
//	std::vector<int> data2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	DenseMatrix<int> mat2(data2, 3, 3);
//	DenseMatrix<int> mat3 = mat1 - mat2;
//	std::vector<int> data3{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);
//
//	// colmaj - colmaj
//	std::vector<int> data4{ 1, 2, 4, 5, 6, 7, 1, 3, 10 };
//	DenseMatrix<int> mat4(data4, 3, 3);
//	DenseMatrix<int> mat5 = mat1 - mat4;
//	std::vector<int> data5{ 0, 0, -1, -1, -1, -1, 6, 5, -1 };
//	checkDenseMatrix(mat5, data5, 3, 3, StorageType::ColumnMajor);
//
//	// rowmaj - rowmaj
//	std::vector<int> data6{ 1, 0, 0, 2, 3, 0 };
//	std::vector<int> data7{ 0, 0, 1, 2, 3, 0 };
//	DenseMatrix<int> mat6(data6, 2, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat7(data7, 2, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat8 = mat6 - mat7;
//	std::vector<int> data8{ 1, 0, -1, 0, 0, 0 };
//	checkDenseMatrix(mat8, data8, 2, 3, StorageType::RowMajor);
//
//	// rowmaj - rowmaj
//	DenseMatrix<int> mat9(data6, 3, 2, StorageType::RowMajor);
//	DenseMatrix<int> mat10(data7, 3, 2, StorageType::RowMajor);
//	DenseMatrix<int> mat11 = mat9 - mat10;
//	checkDenseMatrix(mat11, data8, 3, 2, StorageType::RowMajor);
//
//	// rowmaj - colmaj
//	std::vector<int> data12{ 1, 0, 0, 3, 2, 2, 1, 0, 0, 0, 1, 2 };
//	std::vector<int> data13{ 0, 0, 0, 1, 1, 2, 4, 1, 1, 0, 0, 1 };
//	DenseMatrix<int> mat12(data12, 4, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat13(data13, 4, 3, StorageType::ColumnMajor);
//	DenseMatrix<int> mat14 = mat12 - mat13;
//	std::vector<int> data14{ 1, -1, -1, 3, 0, 2, 1, -4, 0, -1, 0, 1 };
//	checkDenseMatrix(mat14, data14, 4, 3, StorageType::RowMajor);
//
//	// colmaj - rowmaj
//	std::vector<int> data15{ 0, 1, 1, 4, 9, 0, 0, 1, 2, 0 };
//	std::vector<int> data16{ 0, 0, 4, 2, 1, 0, 9, 1, 2, 0 };
//	DenseMatrix<int> mat15(data15, 2, 5, StorageType::ColumnMajor);
//	DenseMatrix<int> mat16(data16, 2, 5, StorageType::RowMajor);
//	DenseMatrix<int> mat17 = mat15 - mat16;
//	std::vector<int> data17{ 0, 1, 1, -5, 5, -1, -2, -1, 1, 0 };
//	checkDenseMatrix(mat17, data17, 2, 5, StorageType::ColumnMajor);
//}
//
//void testDenseMult()
//{
//	// colmaj * colmaj, square 
//	std::vector<int> data1{ 0, 1, 1, 0, 2, 3, 1, 1, 2 };
//	std::vector<int> data2{ 1, 1, 0, 0, 0, 1, 2, 1, 3 };
//	DenseMatrix<int> mat1(data1, 3, 3, StorageType::ColumnMajor);
//	DenseMatrix<int> mat2(data2, 3, 3, StorageType::ColumnMajor);
//	DenseMatrix<int> mat3 = mat1 * mat2;
//	std::vector<int> data3{ 0, 3, 4, 1, 1, 2, 3, 7, 11 };
//	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);
//
//	std::vector<int> data4{ 0, 0, 1, 4, 5, 11, 4, 1, 0, 0, 1, 1, 0, 13, 10, 0, 1, 1, 5, 9, 1, 9, 15, 0, 2 };
//	std::vector<int> data5{ 1, 3, 4, 9, 0, 1, 13, 5, 1, 0, 1, 4, 5, 2, 9, 0, 0, 2, 0, 5, 1, 2, 0, 4, 6 };
//	DenseMatrix<int> mat4(data4, 5, 5, StorageType::ColumnMajor);
//	DenseMatrix<int> mat5(data5, 5, 5, StorageType::ColumnMajor);
//	DenseMatrix<int> mat6 = mat4 * mat5;
//	std::vector<int> data6{ 37, 25, 13, 101, 126, 148, 58, 15, 74, 64, 58, 104, 142, 79, 91, 7, 47, 75, 26, 30, 28, 66, 97, 24, 53 };
//	checkDenseMatrix(mat6, data6, 3, 3, StorageType::ColumnMajor);
//
//	// colmaj * colmaj, different dimensions
//	std::vector<int> data7{ 1, 2, 0, 0, 1, 4 };
//	std::vector<int> data8{ 1, 1, 0, 3, 0, 1 };
//	DenseMatrix<int> mat7(data7, 3, 2, StorageType::ColumnMajor);
//	DenseMatrix<int> mat8(data8, 2, 3, StorageType::ColumnMajor);
//	DenseMatrix<int> mat9 = mat7 * mat8;
//	std::vector<int> data9{ 1, 3, 4, 0, 3, 12, 0, 1, 4 };
//	checkDenseMatrix(mat9, data9, 3, 3, StorageType::ColumnMajor);
//
//	// rowmaj * rowmaj, square
//	std::vector<int> data10{ 0, 1, 2, 3, 1, 2, 0, 1, 1 };
//	std::vector<int> data11{ 1, 3, 5, 1, 0, 0, 1, 1, 3 };
//	DenseMatrix<int> mat10(data10, 3, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat11(data11, 3, 3, StorageType::RowMajor);
//	DenseMatrix<int> mat12 = mat10 * mat11;
//	std::vector<int> data12{ 3, 2, 6, 6, 11, 21, 2, 1, 3 };
//	checkDenseMatrix(mat12, data12, 3, 3, StorageType::RowMajor);
//
//	// rowmaj * rowmaj, different dimensions
//	std::vector<int> data13{ 0, 3, 1, 2, 4, 0, 0, 1 };
//	std::vector<int> data14{ 1, 1, 2, 0, 0, 2, 1, 3 };
//	DenseMatrix<int> mat13(data13, 2, 4, StorageType::RowMajor);
//	DenseMatrix<int> mat14(data14, 4, 2, StorageType::RowMajor);
//	DenseMatrix<int> mat15 = mat13 * mat14;
//	std::vector<int> data15{ 8, 8, 5, 7 };
//	checkDenseMatrix(mat15, data15, 2, 2, StorageType::RowMajor);
//
//	// colmaj * rowmaj, square
//	std::vector<int> data16{ 0, 0, 1, 1, 2, 0, 1, 2, 3, 0, 2, 1, 1, 2, 0, 3 };
//	std::vector<int> data17{ 1, 0, 2, 1, 0, 3, 3, 0, 2, 1, 0, 0, 1, 1, 0, 2 };
//	DenseMatrix<int> mat16(data16, 4, 4, StorageType::ColumnMajor);
//	DenseMatrix<int> mat17(data17, 4, 4, StorageType::RowMajor);
//	DenseMatrix<int> mat18 = mat16 * mat17;
//	std::vector<int> data18{ 7, 2, 5, 6, 10, 2, 5, 10, 6, 0, 5, 8, 2, 4, 1, 7 };
//	checkDenseMatrix(mat18, data18, 4, 4, StorageType::ColumnMajor);
//
//	// rowmaj * colmaj, square
//	DenseMatrix<int> mat19 = mat17 * mat16;
//	std::vector<int> data19{ 3, 6, 8, 4, 3, 3, 6, 6, 0, 4, 6, 4, 2, 6, 5, 9 };
//	checkDenseMatrix(mat19, data19, 4, 4, StorageType::RowMajor);
//}
//
//
//// SparseMatrix unit tests
//
//// Runs all SparseMatrix tests
//// TODO, leaving SparseMatrix for now
//void testSparseMatrix() 
//{
//	std::cout << "Sparse matrix tests complete\n";
//}
//
//void testSparseCtor() 
//{
//	// Test ctor with three input vectors
//	std::vector<int> data1{ 1, 1, 1 };
//	std::vector<size_t> rows1{ 0, 1, 2 };
//	std::vector<size_t> cols1{ 0, 1, 2 };
//	SparseMatrix<int> mat1(data1, rows1, cols1, 3, 3);
//	checkSparseMatrix(mat1, data1, rows1, cols1, 3, 3, 3);
//
//	std::vector<int> data2{ 1, 1, 1, 1 };
//	std::vector<size_t> rows2{ 0, 0, 0, 0 };
//}