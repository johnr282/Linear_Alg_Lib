#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"


// DenseMatrix class, derived from base Matrix class; stores all data, zero and nonzero,
// in one-dimensional array; supports both RowMajor and ColumnMajor storage, but defaults
// to ColumnMajor
template <typename T>
class DenseMatrix : public Matrix {

public:

	// Constructor
	DenseMatrix(const std::vector<T>& data_in, 
				const size_t rows_in, 
				const size_t cols_in,
				const StorageType storage_type_in = StorageType::ColumnMajor);

	// Constructor with no given data vector; default initializes all elements in matrix
	DenseMatrix(const size_t rows_in, 
				const size_t cols_in,
				const StorageType storage_type_in = StorageType::ColumnMajor);

	// Getter and setter functions

	std::vector<T> getData() const;

	void setData(const std::vector<T>& data_in);

	StorageType getStorageType() const;

	// Prints matrix to cout in row major format, regardless of storage type: 
	/*
		a  b  c  d
		e  f  g  h
		i  j  k  l
		m  n  o  p
	*/
	// Ensures columns are aligned, even with different amounts of digits
	// Doesn't work well with non integer types
	void printMatrix() const;

	// Converts storage type from column major to row major by rearranging data vector; 
	// if storage type is already row major, does nothing
	void convertToRowMajor();

	// Converts storage type from row major to column major by rearranging data vector; 
	// if storage type is already column major, does nothing
	void convertToColMajor();


private:

	// Vector to store data 
	std::vector<T> data;

	// Determines method of data storage, either column major or row major
	// Column major by default
	StorageType storage_type;

};

#endif