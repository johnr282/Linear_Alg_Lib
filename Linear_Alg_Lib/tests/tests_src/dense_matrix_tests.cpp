#include "../tests_include/dense_matrix_tests.h"

#include <cassert>
#include <numeric>
#include "../tests_include/tests_utils.h"
#include "../../include/linalg.h"

using namespace LinAlg;

// ------------------------------------------------------------------
// Implementations of DenseMatrix unit tests
// ------------------------------------------------------------------

// Runs all DenseMatrix unit tests
void testDenseMatrix()
{
	testDenseMatrixCtor();
	testDenseMatrixSetData();
	testDenseMatrixConvertColMajor();
	testDenseMatrixConvertRowMajor();
	//testDenseMatrixInsertion();
	testDenseAdd();
	testDenseSub();
	testDenseAtRowCol();
	testDenseAddRowCol();
	testDenseRemoveRowCol();
	testDenseSubMatrix();
	testDenseEquals();
	testDenseMult();
	testDenseLinearSolver();

	std::cout << "DenseMatrix tests complete\n";
}

// Dense Matrix constructor tests
void testDenseMatrixCtor()
{
	// Test first constructor with data vector
	std::vector<int> data(12, 1);
	DenseMatrix<int> mat(data, 3, 4, StorageType::RowMajor);
	// Check if data is correct
	assert(mat.getData() == data);
	assert(mat.rows() == 3);
	assert(mat.cols() == 4);
	assert(mat.size() == 12);
	assert(mat.getStorageType() == StorageType::RowMajor);

	// Test with default storage type
	std::vector<double> data2(12, 1.5);
	DenseMatrix<double> mat2(data2, 3, 4);
	assert(mat2.getStorageType() == StorageType::ColumnMajor);

	// Test second constructor with no data vector
	DenseMatrix<uint32_t> mat3(4, 5);
	assert(mat3.rows() == 4);
	assert(mat3.cols() == 5);
	assert(mat3.size() == 20);
	assert(mat3.getStorageType() == StorageType::ColumnMajor);

	DenseMatrix<float> mat4(6, 6, StorageType::RowMajor);
	assert(mat4.rows() == 6);
	assert(mat4.cols() == 6);
	assert(mat4.size() == 36);
	assert(mat4.getStorageType() == StorageType::RowMajor);
}

void testDenseMatrixInsertion()
{
	std::vector<int> data1(9);
	std::iota(data1.begin(), data1.end(), 0);
	DenseMatrix<int> mat1(data1, 3, 3, StorageType::RowMajor);
	std::cout << mat1;
	std::cout << "\n";

	DenseMatrix<int> mat1_col(data1, 3, 3, StorageType::ColumnMajor);
	std::cout << mat1_col;
	std::cout << "\n";

	std::vector<int> data2{ 23, 0, 0, 0 };
	DenseMatrix<int> mat2(data2, 2, 2);
	std::cout << mat2;
	std::cout << "\n";

	std::vector<int> data3{ -25, 1, 23, 0, 0, 0 };
	DenseMatrix<int> mat3(data3, 2, 3);
	std::cout << mat3;
	std::cout << "\n";

	std::vector<int> data4{ -1, 9999, 0, 0, 0, 0 };
	DenseMatrix<int> mat4(data4, 3, 2);
	std::cout << mat4;
	std::cout << "\n";

	std::vector<size_t> data5(144);
	std::iota(data5.begin(), data5.end(), 0);
	DenseMatrix<size_t> mat5(data5, 12, 12);
	std::cout << mat5;
	std::cout << "\n";

	DenseMatrix<size_t> mat5_row(data5, 12, 12, StorageType::RowMajor);
	std::cout << mat5_row;
	std::cout << "\n";
}


void testDenseMatrixSetData()
{
	std::vector<int> data(10, 5);
	DenseMatrix<int> mat(data, 5, 2);
	std::vector<int> data2(10, 2);
	mat.setData(data2);
	assert(mat.getData() == data2);
}

// Test conversions from row major to column major
void testDenseMatrixConvertColMajor()
{
	// To column major conversion
	std::vector<int> data1(12);
	std::iota(data1.begin(), data1.end(), 0);
	DenseMatrix<int> mat1(data1, 3, 4, StorageType::RowMajor);
	mat1.convertToColMajor();
	assert(mat1.getStorageType() == StorageType::ColumnMajor);
	std::vector<int> data1_col_maj{ 0, 4, 8, 1, 5, 9, 2, 6, 10, 3, 7, 11 };
	assert(mat1.getData() == data1_col_maj);

	std::vector<int> data2(9);
	std::iota(data2.begin(), data2.end(), 0);
	DenseMatrix<int> mat2(data2, 3, 3, StorageType::RowMajor);
	mat2.convertToColMajor();
	assert(mat2.getStorageType() == StorageType::ColumnMajor);
	std::vector<int> data2_col_maj{ 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	assert(mat2.getData() == data2_col_maj);

	std::vector<int> data3{ 2, 2, 2, 3, 1, 0, 3, 5, 3, 5, 7, 1 };
	DenseMatrix<int> mat3(data3, 6, 2, StorageType::RowMajor);
	mat3.convertToColMajor();
	std::vector<int> data3_col_major{ 2, 2, 1, 3, 3, 7, 2, 3, 0, 5, 5, 1 };
	assert(mat3.getData() == data3_col_major);

	// Column vector
	std::vector<int> data4{ 0, 3, 2, 5 };
	DenseMatrix<int> mat4(data4, 4, 1, StorageType::RowMajor);
	mat3.convertToColMajor();
	assert(mat4.getData() == data4);

	// Row vector
	DenseMatrix<int> mat5(data4, 1, 4, StorageType::RowMajor);
	mat4.convertToColMajor();
	assert(mat5.getData() == data4);

}

void testDenseMatrixConvertRowMajor()
{
	std::vector<int> data1(12);
	std::iota(data1.begin(), data1.end(), 0);
	DenseMatrix<int> mat1(data1, 3, 4);
	mat1.convertToRowMajor();
	assert(mat1.getStorageType() == StorageType::RowMajor);
	std::vector<int> data1_row_maj{ 0, 3, 6, 9, 1, 4, 7, 10, 2, 5, 8, 11 };
	assert(mat1.getData() == data1_row_maj);

	std::vector<int> data2(9);
	std::iota(data2.begin(), data2.end(), 0);
	DenseMatrix<int> mat2(data2, 3, 3);
	mat2.convertToRowMajor();
	assert(mat2.getStorageType() == StorageType::RowMajor);
	std::vector<int> data2_row_maj{ 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	assert(mat2.getData() == data2_row_maj);

	std::vector<int> data3{ 2, 2, 2, 3, 1, 0, 3, 5, 3, 5, 7, 1 };
	DenseMatrix<int> mat3(data3, 6, 2);
	mat3.convertToRowMajor();
	std::vector<int> data3_row_maj{ 2, 3, 2, 5, 2, 3, 3, 5, 1, 7, 0, 1 };
	assert(mat3.getData() == data3_row_maj);

	// Column vector
	std::vector<int> data4{ 0, 3, 2, 5 };
	DenseMatrix<int> mat4(data4, 4, 1);
	mat3.convertToRowMajor();
	assert(mat4.getData() == data4);

	// Row vector
	DenseMatrix<int> mat5(data4, 1, 4);
	mat4.convertToRowMajor();
	assert(mat5.getData() == data4);
}

void testDenseAdd()
{
	// colmaj + colmaj
	std::vector<int> data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat1(data1, 3, 3);
	std::vector<int> data2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat2(data2, 3, 3);
	DenseMatrix<int> mat3 = mat1 + mat2;
	std::vector<int> data3{ 2, 4, 6, 8, 10, 12, 14, 16, 18 };
	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);

	// colmaj + colmaj
	std::vector<int> data4{ 1, 2, 4, 5, 6, 7, 1, 3, 10 };
	DenseMatrix<int> mat4(data4, 3, 3);
	DenseMatrix<int> mat5 = mat1 + mat4;
	std::vector<int> data5{ 2, 4, 7, 9, 11, 13, 8, 11, 19 };
	checkDenseMatrix(mat5, data5, 3, 3, StorageType::ColumnMajor);

	// rowmaj + rowmaj
	std::vector<int> data6{ 1, 0, 0, 2, 3, 0 };
	std::vector<int> data7{ 0, 0, 1, 2, 3, 0 };
	DenseMatrix<int> mat6(data6, 2, 3, StorageType::RowMajor);
	DenseMatrix<int> mat7(data7, 2, 3, StorageType::RowMajor);
	DenseMatrix<int> mat8 = mat6 + mat7;
	std::vector<int> data8{ 1, 0, 1, 4, 6, 0 };
	checkDenseMatrix(mat8, data8, 2, 3, StorageType::RowMajor);

	// rowmaj + rowmaj
	DenseMatrix<int> mat9(data6, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat10(data7, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat11 = mat9 + mat10;
	checkDenseMatrix(mat11, data8, 3, 2, StorageType::RowMajor);

	// rowmaj + colmaj
	std::vector<int> data12{ 1, 0, 0, 3, 2, 2, 1, 0, 0, 0, 1, 2 };
	std::vector<int> data13{ 0, 0, 0, 1, 1, 2, 4, 1, 1, 0, 0, 1 };
	DenseMatrix<int> mat12(data12, 4, 3, StorageType::RowMajor);
	DenseMatrix<int> mat13(data13, 4, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat14 = mat12 + mat13;
	std::vector<int> data14{ 1, 1, 1, 3, 4, 2, 1, 4, 0, 1, 2, 3 };
	checkDenseMatrix(mat14, data14, 4, 3, StorageType::RowMajor);

	// colmaj + rowmaj
	std::vector<int> data15{ 0, 1, 1, 4, 9, 0, 0, 1, 2, 0 };
	std::vector<int> data16{ 0, 0, 4, 2, 1, 0, 9, 1, 2, 0 };
	DenseMatrix<int> mat15(data15, 2, 5, StorageType::ColumnMajor);
	DenseMatrix<int> mat16(data16, 2, 5, StorageType::RowMajor);
	DenseMatrix<int> mat17 = mat15 + mat16;
	std::vector<int> data17{ 0, 1, 1, 13, 13, 1, 2, 3, 3, 0 };
	checkDenseMatrix(mat17, data17, 2, 5, StorageType::ColumnMajor);
}

void testDenseSub()
{
	// colmaj - colmaj
	std::vector<int> data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat1(data1, 3, 3);
	std::vector<int> data2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat2(data2, 3, 3);
	DenseMatrix<int> mat3 = mat1 - mat2;
	std::vector<int> data3{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);

	// colmaj - colmaj
	std::vector<int> data4{ 1, 2, 4, 5, 6, 7, 1, 3, 10 };
	DenseMatrix<int> mat4(data4, 3, 3);
	DenseMatrix<int> mat5 = mat1 - mat4;
	std::vector<int> data5{ 0, 0, -1, -1, -1, -1, 6, 5, -1 };
	checkDenseMatrix(mat5, data5, 3, 3, StorageType::ColumnMajor);

	// rowmaj - rowmaj
	std::vector<int> data6{ 1, 0, 0, 2, 3, 0 };
	std::vector<int> data7{ 0, 0, 1, 2, 3, 0 };
	DenseMatrix<int> mat6(data6, 2, 3, StorageType::RowMajor);
	DenseMatrix<int> mat7(data7, 2, 3, StorageType::RowMajor);
	DenseMatrix<int> mat8 = mat6 - mat7;
	std::vector<int> data8{ 1, 0, -1, 0, 0, 0 };
	checkDenseMatrix(mat8, data8, 2, 3, StorageType::RowMajor);

	// rowmaj - rowmaj
	DenseMatrix<int> mat9(data6, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat10(data7, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat11 = mat9 - mat10;
	checkDenseMatrix(mat11, data8, 3, 2, StorageType::RowMajor);

	// rowmaj - colmaj
	std::vector<int> data12{ 1, 0, 0, 3, 2, 2, 1, 0, 0, 0, 1, 2 };
	std::vector<int> data13{ 0, 0, 0, 1, 1, 2, 4, 1, 1, 0, 0, 1 };
	DenseMatrix<int> mat12(data12, 4, 3, StorageType::RowMajor);
	DenseMatrix<int> mat13(data13, 4, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat14 = mat12 - mat13;
	std::vector<int> data14{ 1, -1, -1, 3, 0, 2, 1, -4, 0, -1, 0, 1 };
	checkDenseMatrix(mat14, data14, 4, 3, StorageType::RowMajor);

	// colmaj - rowmaj
	std::vector<int> data15{ 0, 1, 1, 4, 9, 0, 0, 1, 2, 0 };
	std::vector<int> data16{ 0, 0, 4, 2, 1, 0, 9, 1, 2, 0 };
	DenseMatrix<int> mat15(data15, 2, 5, StorageType::ColumnMajor);
	DenseMatrix<int> mat16(data16, 2, 5, StorageType::RowMajor);
	DenseMatrix<int> mat17 = mat15 - mat16;
	std::vector<int> data17{ 0, 1, 1, -5, 5, -1, -2, -1, 1, 0 };
	checkDenseMatrix(mat17, data17, 2, 5, StorageType::ColumnMajor);
}

void testDenseAtRowCol()
{
	// rowmaj
	std::vector<size_t> data1{ 0, 9, 2, 1, 4, 2, 0, 3, 6 };
	DenseMatrix<size_t> mat1(data1, 3, 3, StorageType::RowMajor);
	// 0 9 2
	// 1 4 2
	// 0 3 6
	assert(mat1.at(0, 0) == 0);
	assert(mat1.at(0, 2) == 2);
	assert(mat1.at(2, 2) == 6);
	assert(mat1.at(1, 0) == 1);

	mat1.at(1, 2) = 5;
	assert(mat1.at(1, 2) == 5);

	MathVector<size_t> row0({ 0, 9, 2 });
	MathVector<size_t> row1({ 1, 4, 5 });
	MathVector<size_t> row2({ 0, 3, 6 });
	assert(mat1.row(0) == row0);
	assert(mat1.row(1) == row1);
	assert(mat1.row(2) == row2);

	MathVector<size_t> col0({ 0, 1, 0 });
	MathVector<size_t> col1({ 9, 4, 3 });
	MathVector<size_t> col2({ 2, 5, 6 });
	assert(mat1.col(0) == col0);
	assert(mat1.col(1) == col1);
	assert(mat1.col(2) == col2);

	MathVector<size_t> new_row0({ 1, 1, 3 });
	MathVector<size_t> new_row2({ 0, 0, 1 });
	mat1.setRow(0, new_row0);
	mat1.setRow(2, new_row2);
	assert(mat1.row(0) == new_row0);
	assert(mat1.row(2) == new_row2);

	MathVector<size_t> new_col0({ 4, 9, 0 });
	MathVector<size_t> new_col1({ 1, 0, 0 });
	MathVector<size_t> new_col2({ 2, 0, 4 });
	mat1.setCol(0, new_col0);
	mat1.setCol(1, new_col1);
	mat1.setCol(2, new_col2);
	assert(mat1.col(0) == new_col0);
	assert(mat1.col(1) == new_col1);
	assert(mat1.col(2) == new_col2);

	// colmaj
	std::vector<int> data2{ 2, 4, 1, 1, 6, 0, 3, 9 };
	DenseMatrix<int> mat2(data2, 4, 2, StorageType::ColumnMajor);
	// 2 6
	// 4 0
	// 1 3
	// 1 9
	assert(mat2.at(0, 0) == 2);
	assert(mat2.at(2, 1) == 3);
	assert(mat2.at(3, 1) == 9);
	assert(mat2.at(1, 0) == 4);

	mat2.at(1, 1) = 3;
	assert(mat2.at(1, 1) == 3);

	MathVector<int> mat2_row0({ 2, 6 });
	MathVector<int> mat2_row1({ 4, 3 });
	MathVector<int> mat2_row2({ 1, 3 });
	MathVector<int> mat2_row3({ 1, 9 });
	assert(mat2.row(0) == mat2_row0);
	assert(mat2.row(1) == mat2_row1);
	assert(mat2.row(2) == mat2_row2);
	assert(mat2.row(3) == mat2_row3);

	MathVector<int> mat2_col0({ 2, 4, 1, 1 });
	MathVector<int> mat2_col1({ 6, 3, 3, 9 });
	assert(mat2.col(0) == mat2_col0);
	assert(mat2.col(1) == mat2_col1);

	MathVector<int> mat2_new_row0({ 1, 1 });
	MathVector<int> mat2_new_row1({ 1, 5 });
	MathVector<int> mat2_new_row2({ 2, 7 });
	MathVector<int> mat2_new_row3({ 0, 0 });
	mat2.setRow(0, mat2_new_row0);
	mat2.setRow(1, mat2_new_row1);
	mat2.setRow(2, mat2_new_row2);
	mat2.setRow(3, mat2_new_row3);
	assert(mat2.row(0) == mat2_new_row0);
	assert(mat2.row(1) == mat2_new_row1);
	assert(mat2.row(2) == mat2_new_row2);
	assert(mat2.row(3) == mat2_new_row3);

	MathVector<int> mat2_new_col0({ 1, 4, 0, 0 });
	MathVector<int> mat2_new_col1({ 9, 8, 1, 5 });
	mat2.setCol(0, mat2_new_col0);
	mat2.setCol(1, mat2_new_col1);
	assert(mat2.col(0) == mat2_new_col0);
	assert(mat2.col(1) == mat2_new_col1);
}

void testDenseAddRowCol()
{
	std::vector<int> data1{ 0, 1, 3, 2, 1, 4, 5, 1, 2 };
	DenseMatrix<int> mat1(data1, 3, 3, StorageType::RowMajor);
	std::vector<int> new_row_data{ 1, 4, 2 };
	MathVector<int> new_row(new_row_data);

	mat1.addRow(mat1.rows(), new_row);
	std::vector<int> new_data{ 0, 1, 3, 2, 1, 4, 5, 1, 2, 1, 4, 2 };
	checkDenseMatrix(mat1, new_data, 4, 3, StorageType::RowMajor);

	std::vector<int> new_col_data{ 0, 5, 2, 1 };
	MathVector<int> new_col(new_col_data);

	mat1.addCol(mat1.cols(), new_col);
	new_data = { 0, 1, 3, 0, 2, 1, 4, 5, 5, 1, 2, 2, 1, 4, 2, 1 };

	/*
	0 1 3 0
	2 1 4 5
	5 1 2 2
	1 4 2 1
	*/

	checkDenseMatrix(mat1, new_data, 4, 4, StorageType::RowMajor);

	mat1.convertToColMajor();

	new_col_data = { 9, 1, 3, 6 };
	new_col = MathVector<int>(new_col_data);

	mat1.addCol(mat1.cols(), new_col);
	new_data = { 0, 2, 5, 1, 1, 1, 1, 4, 3, 4, 2, 2, 0, 5, 2, 1, 9, 1, 3, 6 };

	checkDenseMatrix(mat1, new_data, 4, 5, StorageType::ColumnMajor);

	new_row_data = { 7, 8, 2, 7, 0 };
	new_row = MathVector<int>(new_row_data);

	mat1.addRow(mat1.rows(), new_row);
	new_data = { 0, 2, 5, 1, 7, 1, 1, 1, 4, 8, 3, 4, 2, 2, 2, 0, 5, 2, 1, 7, 9, 1, 3, 6, 0 };

	checkDenseMatrix(mat1, new_data, 5, 5, StorageType::ColumnMajor);

	mat1 = DenseMatrix<int>({ 1, 3, 4, 0 }, 2, 2);
	new_col = MathVector<int>({ 0, 0 });
	mat1.addCol(0, new_col);
	new_data = { 0, 0, 1, 3, 4, 0 };
	checkDenseMatrix(mat1, new_data, 2, 3, StorageType::ColumnMajor);

	new_col = MathVector<int>({ 1, 2 });
	mat1.addCol(2, new_col);
	new_data = { 0, 0, 1, 3, 1, 2, 4, 0 };
	checkDenseMatrix(mat1, new_data, 2, 4, StorageType::ColumnMajor);

	new_row = MathVector<int>({ 1, 3, 6, 4 });
	mat1.addRow(0, new_row);
	new_data = { 1, 0, 0, 3, 1, 3, 6, 1, 2, 4, 4, 0 };
	checkDenseMatrix(mat1, new_data, 3, 4, StorageType::ColumnMajor);

	new_row = MathVector<int>({ 0, 0, 4, 2 });
	mat1.addRow(1, new_row);
	new_data = { 1, 0, 0, 0, 3, 0, 1, 3, 6, 4, 1, 2, 4, 2, 4, 0 };
	checkDenseMatrix(mat1, new_data, 4, 4, StorageType::ColumnMajor);

	mat1 = DenseMatrix<int>({ 1, 3, 0, 0 }, 2, 2, StorageType::RowMajor);
	new_col = MathVector<int>({ 2, 2 });
	mat1.addCol(0, new_col);
	new_data = { 2, 1, 3, 2, 0, 0 };
	checkDenseMatrix(mat1, new_data, 2, 3, StorageType::RowMajor);

	new_col = MathVector<int>({ 0, 5 });
	mat1.addCol(2, new_col);
	new_data = { 2, 1, 0, 3, 2, 0, 5, 0 };
	checkDenseMatrix(mat1, new_data, 2, 4, StorageType::RowMajor);

	new_row = MathVector<int>({ 0, 1, 2, 3 });
	mat1.addRow(1, new_row);
	new_data = { 2, 1, 0, 3, 0, 1, 2, 3, 2, 0, 5, 0 };
	checkDenseMatrix(mat1, new_data, 3, 4, StorageType::RowMajor);

	new_row = MathVector<int>({ 1, 3, 5, 2 });
	mat1.addRow(0, new_row);
	new_data = { 1, 3, 5, 2, 2, 1, 0, 3, 0, 1, 2, 3, 2, 0, 5, 0 };
	checkDenseMatrix(mat1, new_data, 4, 4, StorageType::RowMajor);
}

void testDenseRemoveRowCol()
{
	DenseMatrix<int> mat({ 1, 4, 2, 0, 1, 2, 4, 0, 2 }, 3, 3);
	mat.removeCol(0);
	std::vector<int> new_data{ 0, 1, 2, 4, 0, 2 };
	checkDenseMatrix(mat, new_data, 3, 2, StorageType::ColumnMajor);

	mat.removeRow(1);
	new_data = { 0, 2, 4, 2 };
	checkDenseMatrix(mat, new_data, 2, 2, StorageType::ColumnMajor);

	mat.removeCol(1);
	new_data = { 0, 2 };
	checkDenseMatrix(mat, new_data, 2, 1, StorageType::ColumnMajor);

	mat.removeRow(1);
	new_data = { 0 };
	checkDenseMatrix(mat, new_data, 1, 1, StorageType::ColumnMajor);

	mat = DenseMatrix<int>({ 0, 1, 3, 2, 5, 4, 0, 0, 2 }, 3, 3, StorageType::RowMajor);
	mat.removeRow(2);
	new_data = { 0, 1, 3, 2, 5, 4 };
	checkDenseMatrix(mat, new_data, 2, 3, StorageType::RowMajor);

	mat.removeCol(0);
	new_data = { 1, 3, 5, 4 };
	checkDenseMatrix(mat, new_data, 2, 2, StorageType::RowMajor);

	mat.removeCol(1);
	new_data = { 1, 5 };
	checkDenseMatrix(mat, new_data, 2, 1, StorageType::RowMajor);

	mat.removeRow(1);
	new_data = { 1 };
	checkDenseMatrix(mat, new_data, 1, 1, StorageType::RowMajor);
}

void testDenseSubMatrix()
{
	std::vector<int> data1{ 1, 4, 2, 3, 4, 5, 1, 2, 5, 1, 7, 2, 1, 6, 3, 4 };
	DenseMatrix<int> mat1(data1, 4, 4);

	/*
	1 4 5 1
	4 5 1 6
	2 1 7 3
	3 2 2 4
	*/

	DenseMatrix<int> sub_mat = mat1.getSubMatrix(0, 2, 0, 2);
	std::vector<int> sub_data = { 1, 4, 4, 5 };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(0, 4, 0, 4);
	assert(sub_mat.getData() == data1);

	sub_mat = mat1.getSubMatrix(1, 4, 1, 3);
	sub_data = { 5, 1, 2, 1, 7, 2 };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(0, 0, 0, 0);
	sub_data = { };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(2, 4, 2, 4);
	mat1.setSubMatrix(2, 4, 2, 4, mat1.getSubMatrix(0, 2, 0, 2));
	assert(mat1.getSubMatrix(0, 2, 0, 2) == mat1.getSubMatrix(2, 4, 2, 4));

	DenseMatrix<int> mat1_copy = mat1;
	mat1.setSubMatrix(0, 0, 0, 0, DenseMatrix<int>());
	assert(mat1 == mat1_copy);

	mat1.setSubMatrix(2, 4, 2, 4, sub_mat);
	sub_mat = mat1.getSubMatrix(0, 4, 0, 2);
	mat1.setSubMatrix(0, 4, 0, 2, mat1.getSubMatrix(0, 4, 2, 4));
	assert(mat1.getSubMatrix(0, 4, 0, 2) == mat1.getSubMatrix(0, 4, 2, 4));
	
	mat1.setSubMatrix(0, 4, 0, 2, sub_mat);

	mat1.convertToRowMajor();

	/*
	1 4 5 1
	4 5 1 6
	2 1 7 3
	3 2 2 4
	*/

	sub_mat = mat1.getSubMatrix(0, 2, 0, 2);
	sub_data = { 1, 4, 4, 5 };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(0, 4, 0, 4);
	sub_data = { 1, 4, 5, 1, 4, 5, 1, 6, 2, 1, 7, 3, 3, 2, 2, 4 };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(1, 4, 1, 3);
	sub_data = { 5, 1, 1, 7, 2, 2 };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(0, 0, 0, 0);
	sub_data = { };
	assert(sub_mat.getData() == sub_data);

	sub_mat = mat1.getSubMatrix(2, 4, 2, 4);
	mat1.setSubMatrix(2, 4, 2, 4, mat1.getSubMatrix(0, 2, 0, 2));
	assert(mat1.getSubMatrix(0, 2, 0, 2) == mat1.getSubMatrix(2, 4, 2, 4));

	mat1_copy = mat1;
	mat1.setSubMatrix(0, 0, 0, 0, DenseMatrix<int>());
	assert(mat1 == mat1_copy);

	mat1.setSubMatrix(2, 4, 2, 4, sub_mat);
	sub_mat = mat1.getSubMatrix(0, 4, 0, 2);
	mat1.setSubMatrix(0, 4, 0, 2, mat1.getSubMatrix(0, 4, 2, 4));
	assert(mat1.getSubMatrix(0, 4, 0, 2) == mat1.getSubMatrix(0, 4, 2, 4));

	mat1.setSubMatrix(0, 4, 0, 2, sub_mat);
}

void testDenseEquals()
{
	std::vector<int> data1{ 1, 4, 2, 3, 4, 6 };
	DenseMatrix<int> mat1(data1, 2, 3);
	DenseMatrix<int> mat2(data1, 3, 2);
	assert(mat1 != mat2);

	DenseMatrix<int> mat3(data1, 2, 3, StorageType::RowMajor);
	assert(mat1 != mat3);

	DenseMatrix<int> mat4(data1, 2, 3);
	assert(mat1 == mat4);

	mat4.at(0, 2) = 0;
	assert(mat1 != mat4);
	mat1.at(0, 2) = 0;
	assert(mat1 == mat4);
}

void testDenseMult()
{
	// colmaj * colmaj, square 
	std::vector<int> data1{ 0, 1, 1, 0, 2, 3, 1, 1, 2 };
	std::vector<int> data2{ 1, 1, 0, 0, 0, 1, 2, 1, 3 };
	DenseMatrix<int> mat1(data1, 3, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat2(data2, 3, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat3 = mat1 * mat2;
	std::vector<int> data3{ 0, 3, 4, 1, 1, 2, 3, 7, 11 };
	checkDenseMatrix(mat3, data3, 3, 3, StorageType::ColumnMajor);

	std::vector<int> data4{ 0, 0, 1, 4, 5, 11, 4, 1, 0, 0, 1, 1, 0, 13, 10, 0, 1, 1, 5, 9, 1, 9, 15, 0, 2 };
	std::vector<int> data5{ 1, 3, 4, 9, 0, 1, 13, 5, 1, 0, 1, 4, 5, 2, 9, 0, 0, 2, 0, 5, 1, 2, 0, 4, 6 };
	DenseMatrix<int> mat4(data4, 5, 5, StorageType::ColumnMajor);
	DenseMatrix<int> mat5(data5, 5, 5, StorageType::ColumnMajor);
	DenseMatrix<int> mat6 = mat4 * mat5;
	std::vector<int> data6{ 37, 25, 13, 101, 126, 148, 58, 15, 74, 64, 58, 104, 142, 79, 91, 7, 47, 75, 26, 30, 28, 66, 97, 24, 53 };
	checkDenseMatrix(mat6, data6, 5, 5, StorageType::ColumnMajor);

	// colmaj * colmaj, different dimensions
	std::vector<int> data7{ 1, 2, 0, 0, 1, 4 };
	std::vector<int> data8{ 1, 1, 0, 3, 0, 1 };
	DenseMatrix<int> mat7(data7, 3, 2, StorageType::ColumnMajor);
	DenseMatrix<int> mat8(data8, 2, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat9 = mat7 * mat8;
	std::vector<int> data9{ 1, 3, 4, 0, 3, 12, 0, 1, 4 };
	checkDenseMatrix(mat9, data9, 3, 3, StorageType::ColumnMajor);

	// rowmaj * rowmaj, square
	std::vector<int> data10{ 0, 1, 2, 3, 1, 2, 0, 1, 1 };
	std::vector<int> data11{ 1, 3, 5, 1, 0, 0, 1, 1, 3 };
	DenseMatrix<int> mat10(data10, 3, 3, StorageType::RowMajor);
	DenseMatrix<int> mat11(data11, 3, 3, StorageType::RowMajor);
	DenseMatrix<int> mat12 = mat10 * mat11;
	std::vector<int> data12{ 3, 2, 6, 6, 11, 21, 2, 1, 3 };
	checkDenseMatrix(mat12, data12, 3, 3, StorageType::RowMajor);

	// rowmaj * rowmaj, different dimensions
	std::vector<int> data13{ 0, 3, 1, 2, 4, 0, 0, 1 };
	std::vector<int> data14{ 1, 1, 2, 0, 0, 2, 1, 3 };
	DenseMatrix<int> mat13(data13, 2, 4, StorageType::RowMajor);
	DenseMatrix<int> mat14(data14, 4, 2, StorageType::RowMajor);
	DenseMatrix<int> mat15 = mat13 * mat14;
	std::vector<int> data15{ 8, 8, 5, 7 };
	checkDenseMatrix(mat15, data15, 2, 2, StorageType::RowMajor);

	// colmaj * rowmaj, square
	std::vector<int> data16{ 0, 0, 1, 1, 2, 0, 1, 2, 3, 0, 2, 1, 1, 2, 0, 3 };
	std::vector<int> data17{ 1, 0, 2, 1, 0, 3, 3, 0, 2, 1, 0, 0, 1, 1, 0, 2 };
	DenseMatrix<int> mat16(data16, 4, 4, StorageType::ColumnMajor);
	DenseMatrix<int> mat17(data17, 4, 4, StorageType::RowMajor);
	DenseMatrix<int> mat18 = mat16 * mat17;
	std::vector<int> data18{ 7, 2, 5, 6, 10, 2, 5, 10, 6, 0, 5, 8, 2, 4, 1, 7 };
	checkDenseMatrix(mat18, data18, 4, 4, StorageType::ColumnMajor);

	// rowmaj * colmaj, square
	DenseMatrix<int> mat19 = mat17 * mat16;
	std::vector<int> data19{ 3, 6, 8, 4, 3, 3, 6, 6, 0, 4, 6, 4, 2, 6, 5, 9 };
	checkDenseMatrix(mat19, data19, 4, 4, StorageType::RowMajor);

	DenseMatrix<int> mat20(generateRandomVector(441), 21, 21);
	DenseMatrix<int> mat21(generateRandomVector(441), 21, 21);
	assert(basicMultWithConversion(mat20, mat21) == strassen(mat20, mat21, 1));
}

void testDenseLinearSolver()
{
	DenseMatrix<int> A1({ 1, 0, 3, 4, 5, 2, 5, 7, 0 }, 3, 3, StorageType::ColumnMajor);
	MathVector<int> b1({ 1, 4, 2 });
	MathVector<double> x;
	assert(solveLinearEquation(A1, x, b1));
	checkVectors(x.getData(), { -32 / 5, 53 / 5, -7 });

	DenseMatrix<int> A2({ 1, 3, 0, 9 }, 2, 2, StorageType::RowMajor);
	MathVector<int> b2({ 0, 1 });
	assert(solveLinearEquation(A2, x, b2));
	checkVectors(x.getData(), {-1 / 3, 1 / 9});

	DenseMatrix<double> A3({ 1.9, -0.2, 3.92, 8.4, -9.3, 0, 1.0, 11.2, -5.9 }, 3, 3, StorageType::RowMajor);
	MathVector<double> b3({ 0.9, -2.1, 4.34 });
	assert(solveLinearEquation(A3, x, b3));
	checkVectors(x.getData(), { 0.2359565, 0.4389284, 0.1376195 });
}