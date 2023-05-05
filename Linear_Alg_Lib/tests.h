#pragma once

#ifndef TESTS_H
#define TESTS_H


#include <cassert>
#include <numeric>
#include "matrix.h"



// Contains unit testing functions


// ********** Helper function prototypes **********

void testDenseMatrixCtor();
void testDenseMatrixSetData();
void testDenseMatrixConvertColMajor();
void testDenseMatrixConvertRowMajor();


// ********** End helper function prototypes **********


// Runs all DenseMatrix tests
void testDenseMatrix() {
	testDenseMatrixCtor();
	testDenseMatrixSetData();
	testDenseMatrixConvertColMajor();
	testDenseMatrixConvertRowMajor();

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
	








#endif