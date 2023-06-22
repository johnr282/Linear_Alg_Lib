#pragma once

#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <algorithm>
#include <string>
#include "matrix_helpers.h"


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
		: rows(rows_in), cols(cols_in), size(rows_in * cols_in) { }

	// All derived classes have some form of printMatrix() function
	virtual void printMatrix() const = 0;

	// Getter functions

	size_t getRows() const {
		return rows;
	}

	size_t getCols() const {
		return cols;
	}

	size_t getSize() const {
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

	std::vector<T> getData() const {
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

	StorageType getStorageType() const {
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
	// Doesn't work well with non integer types
	void printMatrix() const {
		// Finds maximum number of digits in any element in matrix data
		size_t max_digits = findMaxDigits(data);

		// Column width is largest number of digits + 2 spaces wide
		size_t column_width = max_digits + 2;

		// Get data vector into row major form to make printing easier
		std::vector<T> row_maj_data = convertToRowMajorHelper(getData(), getRows(), getCols());

		// Print matrix
		for (size_t i = 0; i < getSize(); ++i) {
			T curr_elt = row_maj_data[i];
			size_t num_spaces = column_width - numDigits<T>(curr_elt);
			std::cout << curr_elt;
			printSpaces(num_spaces);

			// Prints newline after every row
			if (colIndex(i, getCols()) == getCols() - 1) {
				std::cout << "\n";
			}
		}
	}

	// Converts storage type from column major to row major by rearranging data vector; 
	// if storage type is already row major, does nothing
	void convertToRowMajor() {
		if (storage_type == StorageType::RowMajor) {
			return;
		}

		data = convertToRowMajorHelper(getData(), getRows(), getCols());
		storage_type = StorageType::RowMajor;
	}

	// Converts storage type from row major to column major by rearranging data vector; 
	// if storage type is already column major, does nothing
	void convertToColMajor() {
		if (storage_type == StorageType::ColumnMajor) {
			return;
		}

		data = convertToColMajorHelper(getData(), getRows(), getCols());
		storage_type = StorageType::ColumnMajor;
	}


private:
// Private helper functions

};


// Matrix class for sparse matrices; stores data in three vectors; one for the actual data, 
// one for row indices, and one for column indices
template <typename T>
class SparseMatrix: public Matrix {
private:

	// Vector to store data
	std::vector<T> data;

	// Vectors to store row and column indices; the three vectors data, row_indices, 
	// and col_indices will always be the same size
	// The value data[i] is in the position (row_indices[i], col_indices[i])
	// All other locations in the matrix are zeroes
	std::vector<size_t> row_indices;
	std::vector<size_t> col_indices;

	// Number of non-zero elements in the matrix; this is also the size of the data, 
	// row_indices, and col_indices vectors
	size_t num_nonzero;

public:

	// Constructor with three input vectors; one data, one row_indices, and one
	// col_indices vector; the data vector should only contain non-zero values
	SparseMatrix(const std::vector<T>& data_in, const std::vector<size_t>& row_indices_in,
		const std::vector<size_t>& col_indices_in, const size_t rows_in, const size_t cols_in)
		: Matrix(rows_in, cols_in), data(data_in), row_indices(row_indices_in), 
		  col_indices(col_indices_in), num_nonzero(data_in.size()) { }
	
	// Constructor with only one input vector; this vector contains every element
	// in the matrix, including zero values
	// The input vector's storage type is equal to the given storage type
	SparseMatrix(const std::vector<T>& data_in, const StorageType storage_type_in,
		const size_t rows_in, const size_t cols_in)
		: Matrix(rows_in, cols_in) {
		
		// If data_in is not row major, convert it to row major
		if (storage_type_in == StorageType::ColumnMajor) {
			data_in = convertToRowMajorHelper(data_in, rows_in, cols_in);
		}
		
		// Iterates through data_in and puts all non-zero elements into the data vector; 
		// stores the row and column indices of each non-zero element in row_indices and
		// col_indices respectively
		num_nonzero = 0;
		for (size_t i = 0; i < data_in.size(); ++i) {
			T elt = data_in[i];
			if (elt != 0) {
				size_t row = rowIndex(i, cols_in);
				size_t col = colIndex(i, cols_in);
				data.push_back(elt);
				row_indices.push_back(row);
				col_indices.push_back(col);
				++num_nonzero;
			}
		}

		// Remove any extra memory allocated to data, row_indices, or col_indices
		data.resize(num_nonzero);
		row_indices.resize(num_nonzero);
		col_indices.resize(num_nonzero);
	}


};


#endif
