#pragma once

#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
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

	// All matrices have some form of setData() function to set the elements of the matrix
	virtual void setData() = 0;

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
	DenseMatrix(std::vector<T> data_in, size_t rows_in, size_t cols_in, StorageType storage_type_in = StorageType::ColumnMajor)
		: Matrix(rows_in, cols_in), data(data_in), storage_type(storage_type_in) { 
		// Check that size of data vector matches rows_in * cols_in
			if (data_in.size() != rows_in * cols_in) {
				std::cerr << "Invalid Matrix initialization input vector; "
					<< "size of input vector must equal number of rows times number of columns\n";
				exit(1);
			}
	}

	// Constructor with no given data vector; default initializes all elements in matrix
	DenseMatrix(size_t rows_in, size_t cols_in, StorageType storage_type_in = StorageType::ColumnMajor)
		: Matrix(rows_in, cols_in), storage_type(storage_type_in) {
		std::vector<T> data_in(rows_in * cols_in);
		data = data_in;
	}

	virtual void setData() {
		std::cout << "Setting data\n";
	}

	// Getter functions

	std::vector<T> getData() {
		return data;
	}

	StorageType getStorageType() {
		return storage_type;
	}
};




#endif
