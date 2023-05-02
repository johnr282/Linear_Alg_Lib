#pragma once

#ifndef TESTS_H
#define TESTS_H


#include <cassert>
#include "matrix.h"



// Contains unit testing functions


// ********** Helper function prototypes **********


// Dense Matrix constructor tests
void testDenseMatrixCtor() {
	// Test first constructor with data vector
	std::vector<int> data(12, 1);
	Matrix<int> mat(data, 3, 4, StorageType::RowMajor);
	// Check if data is correct
	assert(mat.getData() == data);
	assert(mat.getRows() == 3);
	assert(mat.getCols() == 4);
	assert(mat.getSize() == 12);
	assert(mat.getStorageType() == StorageType::RowMajor);

	// Test with default storage type
	std::vector<double> data2(12, 1.5);
	Matrix<double> mat2(data2, 3, 4);
	assert(mat2.getStorageType() == StorageType::ColumnMajor);

	// Test second constructor with no data vector
	Matrix<uint32_t> mat3(4, 5);
	assert(mat3.getRows() == 4);
	assert(mat3.getCols() == 5);
	assert(mat3.getSize() == 20);
	assert(mat3.getStorageType() == StorageType::ColumnMajor);

	Matrix<float> mat4(6, 6, StorageType::RowMajor);
	assert(mat4.getRows() == 6);
	assert(mat4.getCols() == 6);
	assert(mat4.getSize() == 36);
	assert(mat4.getStorageType() == StorageType::RowMajor);
}







#endif