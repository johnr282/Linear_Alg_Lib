#pragma once

#ifndef TESTS_H
#define TESTS_H


#include <cassert>
#include <numeric>
#include "matrix.h"
#include "matrix_ops.h"



// Contains unit testing functions


// ********** Helper function prototypes **********

void testDenseMatrixCtor();
void testDenseMatrixSetData();
void testDenseMatrixConvertColMajor();
void testDenseMatrixConvertRowMajor();
void testDensePrintMatrix();
void testDenseAdd();
template <typename T>
void checkMatrix(const DenseMatrix<T>&, const std::vector<T>&, size_t, size_t, size_t, StorageType);


// ********** End helper function prototypes **********


// Runs all DenseMatrix tests
void testDenseMatrix() {
	testDenseMatrixCtor();
	testDenseMatrixSetData();
	testDenseMatrixConvertColMajor();
	testDenseMatrixConvertRowMajor();
	// testDensePrintMatrix();
	testDenseAdd();

}


// Dense Matrix constructor tests
void testDenseMatrixCtor() {
	// Test first constructor with data vector
	std::vector<int> data(12, 1);
	DenseMatrix<int> mat(data, 3, 4, StorageType::RowMajor);
	// Check if data is correct
	assert(mat.getData() == data);
	assert(mat.getRows() == 3);
	assert(mat.getCols() == 4);
	assert(mat.getSize() == 12);
	assert(mat.getStorageType() == StorageType::RowMajor);

	// Test with default storage type
	std::vector<double> data2(12, 1.5);
	DenseMatrix<double> mat2(data2, 3, 4);
	assert(mat2.getStorageType() == StorageType::ColumnMajor);

	// Test second constructor with no data vector
	DenseMatrix<uint32_t> mat3(4, 5);
	assert(mat3.getRows() == 4);
	assert(mat3.getCols() == 5);
	assert(mat3.getSize() == 20);
	assert(mat3.getStorageType() == StorageType::ColumnMajor);

	DenseMatrix<float> mat4(6, 6, StorageType::RowMajor);
	assert(mat4.getRows() == 6);
	assert(mat4.getCols() == 6);
	assert(mat4.getSize() == 36);
	assert(mat4.getStorageType() == StorageType::RowMajor);
}

void testDenseMatrixSetData() {
	std::vector<int> data(10, 5);
	DenseMatrix<int> mat(data, 5, 2);
	std::vector<int> data2(10, 2);
	mat.setData(data2);
	assert(mat.getData() == data2);
}

// Test conversions from row major to column major
void testDenseMatrixConvertColMajor() {
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

void testDenseMatrixConvertRowMajor() {
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

void testDensePrintMatrix() {
	std::vector<int> data1(9);
	std::iota(data1.begin(), data1.end(), 0);
	DenseMatrix<int> mat1(data1, 3, 3, StorageType::RowMajor);
	mat1.printMatrix();
	std::cout << "\n";

	DenseMatrix<int> mat1_col(data1, 3, 3, StorageType::ColumnMajor);
	mat1_col.printMatrix();
	std::cout << "\n";

	std::vector<int> data2{ 23, 0, 0, 0 };
	DenseMatrix<int> mat2(data2, 2, 2);
	mat2.printMatrix();
	std::cout << "\n";

	std::vector<int> data3{ -25, 1, 23, 0, 0, 0 };
	DenseMatrix<int> mat3(data3, 2, 3);
	mat3.printMatrix();
	std::cout << "\n";

	std::vector<int> data4{ -1, 9999, 0, 0, 0, 0 };
	DenseMatrix<int> mat4(data4, 3, 2);
	mat4.printMatrix();
	std::cout << "\n";

	std::vector<size_t> data5(144);
	std::iota(data5.begin(), data5.end(), 0);
	DenseMatrix<size_t> mat5(data5, 12, 12);
	mat5.printMatrix();
	std::cout << "\n";

	DenseMatrix<size_t> mat5_row(data5, 12, 12, StorageType::RowMajor);
	mat5_row.printMatrix();
	std::cout << "\n";
}

void testDenseAdd() {
	// colmaj + colmaj
	std::vector<int> data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat1(data1, 3, 3);
	std::vector<int> data2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	DenseMatrix<int> mat2(data2, 3, 3);
	DenseMatrix<int> mat3 = mat1 + mat2;
	std::vector<int> data3{ 2, 4, 6, 8, 10, 12, 14, 16, 18 };
	checkMatrix(mat3, data3, 3, 3, 9, StorageType::ColumnMajor);

	// colmaj + colmaj
	std::vector<int> data4{ 1, 2, 4, 5, 6, 7, 1, 3, 10 };
	DenseMatrix<int> mat4(data4, 3, 3);
	DenseMatrix<int> mat5 = mat1 + mat4;
	std::vector<int> data5{ 2, 4, 7, 9, 11, 13, 8, 11, 19 };
	checkMatrix(mat5, data5, 3, 3, 9, StorageType::ColumnMajor);

	// rowmaj + rowmaj
	std::vector<int> data6{ 1, 0, 0, 2, 3, 0 };
	std::vector<int> data7{ 0, 0, 1, 2, 3, 0 };
	DenseMatrix<int> mat6(data6, 2, 3, StorageType::RowMajor);
	DenseMatrix<int> mat7(data7, 2, 3, StorageType::RowMajor); 
	DenseMatrix<int> mat8 = mat6 + mat7;
	std::vector<int> data8{ 1, 0, 1, 4, 6, 0 };
	checkMatrix(mat8, data8, 2, 3, 6, StorageType::RowMajor);

	// rowmaj + rowmaj
	DenseMatrix<int> mat9(data6, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat10(data7, 3, 2, StorageType::RowMajor);
	DenseMatrix<int> mat11 = mat9 + mat10;
	checkMatrix(mat11, data8, 3, 2, 6, StorageType::RowMajor);

	// rowmaj + colmaj
	std::vector<int> data12{ 1, 0, 0, 3, 2, 2, 1, 0, 0, 0, 1, 2 };
	std::vector<int> data13{ 0, 0, 0, 1, 1, 2, 4, 1, 1, 0, 0, 1 };
	DenseMatrix<int> mat12(data12, 4, 3, StorageType::RowMajor);
	DenseMatrix<int> mat13(data13, 4, 3, StorageType::ColumnMajor);
	DenseMatrix<int> mat14 = mat12 + mat13;
	std::vector<int> data14{ 1, 1, 1, 3, 4, 2, 1, 4, 0, 1, 2, 3 };
	checkMatrix(mat14, data14, 4, 3, 12, StorageType::RowMajor);

	// colmaj + rowmaj
	std::vector<int> data15{ 0, 1, 1, 4, 9, 0, 0, 1, 2, 0 };
	std::vector<int> data16{ 0, 0, 4, 2, 1, 0, 9, 1, 2, 0 };
	DenseMatrix<int> mat15(data15, 2, 5, StorageType::ColumnMajor);
	DenseMatrix<int> mat16(data16, 2, 5, StorageType::RowMajor);
	DenseMatrix<int> mat17 = mat15 + mat16;
	std::vector<int> data17{ 0, 1, 1, 13, 13, 1, 2, 3, 3, 0 };
	checkMatrix(mat17, data17, 2, 5, 10, StorageType::ColumnMajor);
}

// Checks if given dense matrix has given data vector, row and column numbers, size, and storage type
template <typename T>
void checkMatrix(const DenseMatrix<T>& mat, const std::vector<T>& data, size_t rows,
	size_t cols, size_t size, StorageType type) {
	assert(mat.getData() == data);
	assert(mat.getRows() == rows);
	assert(mat.getCols() == cols);
	assert(mat.getSize() == size);
	assert(mat.getStorageType() == type);
}






#endif