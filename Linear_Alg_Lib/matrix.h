#pragma once

#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include "structs.h"


// Header file for linear algebra library; contains definitions of all public classes


// Dense matrix class
template <typename T>
class Matrix {

// ********** Member variables **********
private:


	// Vector to store data 
	std::vector<T> data;

	// Number of rows and columns
	size_t rows;
	size_t cols;

	// Number of elements
	size_t size;

	// Determines method of data storage, either column major or row major
	// Matrices are column major by default
	StorageType storage_type;


// ********** Member functions **********
public:
	
	// Constructor; data_in is assumed to be in correct order given by storage_type_in
	Matrix(const std::vector<T> &data_in, const size_t rows_in, const size_t cols_in, 
		const StorageType storage_type_in = StorageType::ColumnMajor)
		: data{ data_in }, rows{ rows_in }, cols{ cols_in }, storage_type{ storage_type_in } {
		size = rows_in * cols_in;

		// Check that size of data vector matches rows_in * cols_in
		if (data_in.size() != Matrix::size) {
			std::cerr << "Invalid Matrix initialization input vector; "
				<< "size of input vector must equal number of rows times number of columns\n";
			exit(1);
		}
	}


	// Constructor (no data vector provided); default initializes all elements
	Matrix(const size_t rows_in, const size_t cols_in, const StorageType storage_type_in = StorageType::ColumnMajor) 
		: rows{ rows_in }, cols{ cols_in }, storage_type{ storage_type_in } {
		size = rows_in * cols_in;
		std::vector<T> data_in(size);
		data = data_in;
	}


	// Getter and setter functions
	
	std::vector<T> getData() {
		return data;
	}

	void setData(const std::vector<T> &data_in) {
		// Check that size of data_in matches matrix size
		if (data_in.size() != Matrix::size) {
			std::cerr << "Invalid new Matrix data vector; "
				<< "size of new Matrix data vector must equal current size of Matrix\n";
			exit(1);
		}
		data = data_in;
	}

	size_t getRows() {
		return rows;
	}

	size_t getCols() {
		return cols;
	}

	size_t getSize() {
		return size;
	}

	StorageType getStorageType() {
		return storage_type;
	}





};








#endif
