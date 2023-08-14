#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>


// Contains helper functions, structs, and enums used in matrix.h, matrix_ops.h

enum class StorageType {
	ColumnMajor,
	RowMajor
};

// Returns number of digits in val; used in printMatrix()
template <typename T>
size_t numDigits(T val);

// Prints n spaces to cout; used in printMatrix()
void printSpaces(const size_t n);

// Returns maximum number of digits in any single number in given vector; used in printMatrix()
template <typename T>
size_t findMaxDigits(const std::vector<T>& data);

// Returns given data vector in column major form; assumes vector is in row major form
template <typename T>
std::vector<T> convertToColMajorHelper(const std::vector<T>& data, 
									   const size_t rows, 
									   const size_t cols);

// Returns given data vector in row major form; assumes vector is in column major form
template <typename T>
std::vector<T> convertToRowMajorHelper(const std::vector<T>& data, 
									   const size_t rows, 
									   const size_t cols);

// Given index of a dense row major data vector and how many columns the matrix has, returns 
// the column index corresponding to the vector index
size_t colIndex(const size_t i, 
				const size_t cols);

// Given index of a dense row major data vector and how many columns the matrix has, 
// returns the row index corresponding to the vector index
size_t rowIndex(const size_t i, 
				const size_t cols);


#endif