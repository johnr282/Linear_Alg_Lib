#pragma once

#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <algorithm>
#include <string>
#include "structs.h"


// Contains base Matrix class and the derived classes DenseMatrix, SparseMatrix, DiagonalMatrix


// Base Matrix abstract class for derived classes DenseMatrix, SparseMatrix, DiagonalMatrix
class Matrix {
	
private:

	// Number of rows/columns and total number of elements
	size_t rows;
	size_t cols;
	size_t size;

public:

	// Constructor
	Matrix(size_t rows_in, size_t cols_in)
		: rows(rows_in), cols(cols_in), size(rows_in* cols_in) { }

	// All derived classes have some form of printMatrix() function
	virtual void printMatrix() = 0;

	// Getter functions common to all derived matrix classes

	size_t getRows() {
		return rows;
	}

	size_t getCols() {
		return cols;
	}

	size_t getSize() {
		return size;
	}

};


// DenseMatrix class, derived from base Matrix class; stores all data, zero and nonzero,
// in one-dimensional array; supports both RowMajor and ColumnMajor storage, but defaults
// to ColumnMajor
template <typename T>
class DenseMatrix : public Matrix {

private:

	// Vector to store data 
	std::vector<T> data;

	// Determines method of data storage, either column major or row major
	// Matrices are column major by default
	StorageType storage_type;

public:

	// Constructor
	DenseMatrix(const std::vector<T> &data_in, const size_t rows_in, const size_t cols_in, 
		const StorageType storage_type_in = StorageType::ColumnMajor)
		: Matrix(rows_in, cols_in), data(data_in), storage_type(storage_type_in) { 
		// Check that size of data vector matches rows_in * cols_in
			if (data_in.size() != rows_in * cols_in) {
				std::cerr << "Error in DenseMatrix constructor: Invalid Matrix initialization input vector; "
					<< "size of input vector must equal number of rows times number of columns.\n";
				exit(1);
			}
	}

	// Constructor with no given data vector; default initializes all elements in matrix
	DenseMatrix(const size_t rows_in, const size_t cols_in, 
		const StorageType storage_type_in = StorageType::ColumnMajor)
		: Matrix(rows_in, cols_in), storage_type(storage_type_in) {
		std::vector<T> data_in(rows_in * cols_in);
		data = data_in;
	}

	// Getter and setter functions

	std::vector<T> getData() {
		return data;
	}

	void setData(const std::vector<T>& data_in) {
		// Check that data_in vector matches matrix size
		if (data_in.size() != getSize()) {
			std::cerr << "Error in setData(): Size of input data vector must match size of matrix.\n";
			exit(1);
		}
		data = data_in;
	}

	StorageType getStorageType() {
		return storage_type;
	}

	// Prints matrix to cout in row major format, regardless of storage type: 
	/*	
		a  b  c  d
		e  f  g  h
		i  j  k  l
		m  n  o  p 
	*/
	// Ensures columns are aligned, even with different amounts of digits
	// Doesn't work well with non integer types; lots of trailing 0s in double and
	// float types make matrix much wider than it should be
	void printMatrix() {
		// Sorts data vector to find number with greatest number of digits
		std::vector<T> sorted_data = data;
		std::sort(sorted_data.begin(), sorted_data.end());

		T min_num = sorted_data.front();
		T max_num = sorted_data.back();

		size_t min_num_digits = (std::to_string(min_num)).size();
		size_t max_num_digits = (std::to_string(max_num)).size();

		// Column width is largest number of digits + 2 spaces wide
		size_t column_width = std::max(min_num_digits, max_num_digits) + 2;

		

	}

	// Converts storage type from column major to row major by rearranging data vector; 
	// if storage type is already row major, does nothing
	void convertToRowMajor() {
		data = convertToRowMajorHelper();
		storage_type = StorageType::RowMajor;
	}

	// Converts storage type from row major to column major by rearranging data vector; 
	// if storage type is already column major, does nothing
	void convertToColMajor() {
		data = convertToColMajorHelper();
		storage_type = StorageType::ColumnMajor;
	}


private:
// Private helper functions

	// Returns matrix data vector in row major format
	std::vector<T> convertToRowMajorHelper() {
		if (storage_type == StorageType::RowMajor) {
			return data;
		}

		// Vector to hold rearranged data
		std::vector<T> new_data(getSize());

		int col = -1;
		for (int i = 0; i < getSize(); ++i) {
			size_t row = i % getRows();
			// Increment col every n times, where n is the number of rows
			col += (i % getRows() == 0);
			size_t new_index = row * getCols() + col;
			// Put element in new row major position
			new_data[new_index] = data[i];
		}
		return new_data;
	}

	// Returns matrix data vector in column major format
	std::vector<T> convertToColMajorHelper() {
		if (storage_type == StorageType::ColumnMajor) {
			return data;
		}

		// Vector to hold rearranged data
		std::vector<T> new_data(getSize());

		int row = -1;
		for (int i = 0; i < getSize(); ++i) {
			size_t col = i % getCols();
			// Increment row every m times, where m is the number of columns
			row += (i % getCols() == 0);
			size_t new_index = col * getRows() + row;
			// Put element in new column major position
			new_data[new_index] = data[i];
		}
		return new_data;
	}


	/*
	134   2     9
	1	  2     13
	5     1     3
	2567  1     34
	34	  5     467
	2	  14    2

	0  1  2  3
	4  5  6  7
	8  9  10 11

	row major: 0 1 2 3 4 5 6 7 8 9 10 11

	column major: 0 4 8 1 5 9 2 6 10 3 7 11



	*/
};




#endif
