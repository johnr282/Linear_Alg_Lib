#include <string>
#include "../include/matrix_utils.h"
#include "../include/dense_matrix.h"

// Returns number of digits in val; used in printMatrix()
template <typename T>
size_t numDigits(T val) {
	return (std::to_string(val)).size();
}

// Prints n spaces to cout; used in printMatrix()
void printSpaces(const size_t n) {
	for (size_t i = 0; i < n; ++i) {
		std::cout << " ";
	}
}

// Returns maximum number of digits in any single number in given vector; used in printMatrix()
template <typename T>
size_t findMaxDigits(const std::vector<T>& data) {
	size_t max_digits = 0;
	for (T elt : data) {
		max_digits = std::max(max_digits, numDigits<T>(elt));
	}
	return max_digits;
}

// Returns given data vector in column major form; assumes vector is in row major form
template <typename T>
std::vector<T> convertToColMajorHelper(const std::vector<T>& data, const size_t rows, const size_t cols) {
	// Vector to hold rearranged data
	std::vector<T> new_data(data.size());

	int row = -1;
	for (size_t i = 0; i < data.size(); ++i) {
		size_t col = i % cols;
		// Increment row every m times, where m is the number of columns
		row += (i % cols == 0);
		size_t new_index = col * rows + row;
		// Put element in new column major position
		new_data[new_index] = data[i];
	}
	return new_data;
}

// Returns given data vector in row major form; assumes vector is in column major form
template <typename T>
std::vector<T> convertToRowMajorHelper(const std::vector<T>& data, const size_t rows, const size_t cols) {
	// Vector to hold rearranged data
	std::vector<T> new_data(data.size());

	int col = -1;
	for (size_t i = 0; i < data.size(); ++i) {
		size_t row = i % rows;
		// Increment col every n times, where n is the number of rows
		col += (i % rows == 0);
		size_t new_index = row * cols + col;
		// Put element in new row major position
		new_data[new_index] = data[i];
	}
	return new_data;
}

// Given index of a dense row major data vector and how many columns the matrix has, returns 
// the column index corresponding to the vector index
size_t colIndex(const size_t i, const size_t cols) {
	return i % cols;
}

// Given index of a dense row major data vector and how many columns the matrix has, 
// returns the row index corresponding to the vector index
size_t rowIndex(const size_t i, const size_t cols) {
	return (i - colIndex(i, cols)) / cols;
}