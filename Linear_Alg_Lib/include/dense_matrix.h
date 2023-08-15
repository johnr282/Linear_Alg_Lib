#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"


// DenseMatrix class, derived from base Matrix class; stores all data, zero and nonzero,
// in one-dimensional array; supports both RowMajor and ColumnMajor storage, but defaults
// to ColumnMajor
template <typename T>
class DenseMatrix : public Matrix 
{
public:

	// Constructor
	DenseMatrix(const std::vector<T>& data_in, 
				const size_t rows_in, 
				const size_t cols_in,
				const StorageType storage_type_in = StorageType::ColumnMajor) :
		Matrix(rows_in, cols_in),
		_data(data_in),
		_storage_type(storage_type_in)
	{
		// Check that size of data vector matches rows_in * cols_in
		if (data_in.size() != rows_in * cols_in) 
		{
			throw std::length_error(
				"Size of input vector must equal number of rows times number of columns");
		}
	}

	// Constructor with no given data vector; default initializes all elements in matrix
	DenseMatrix(const size_t rows_in, 
				const size_t cols_in,
				const StorageType storage_type_in = StorageType::ColumnMajor) :
		Matrix(rows_in, cols_in), 
		_storage_type(storage_type_in) 
	{
		std::vector<T> data_in(rows_in * cols_in);
		_data = data_in;
	}

	// Getter and setter functions

	std::vector<T> getData() const 
	{
		return _data;
	}

	void setData(const std::vector<T>& data_in) 
	{
		// Check that data_in vector matches matrix size
		if (data_in.size() != getSize()) 
		{
			throw std::length_error("Size of input data vector must match size of matrix");
		}
		_data = data_in;
	}

	StorageType getStorageType() const 
	{
		return _storage_type;
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
	void printMatrix() const 
	{
		// Finds maximum number of digits in any element in matrix data
		size_t max_digits = findMaxDigits(_data);

		// Column width is largest number of digits + 2 spaces wide
		size_t column_width = max_digits + 2;

		// Get data vector into row major form to make printing easier
		std::vector<T> row_maj_data = convertToRowMajorHelper(getData(), getRows(), getCols());

		// Print matrix
		for (size_t i = 0; i < getSize(); ++i) 
		{
			T curr_elt = row_maj_data[i];
			size_t num_spaces = column_width - numDigits<T>(curr_elt);
			std::cout << curr_elt;
			printSpaces(num_spaces);

			// Prints newline after every row
			if (colIndex(i, getCols()) == getCols() - 1) 
			{
				std::cout << "\n";
			}
		}
	}

	// Converts storage type from column major to row major by rearranging data vector; 
	// if storage type is already row major, does nothing
	void convertToRowMajor() 
	{
		if (_storage_type == StorageType::RowMajor) 
			return;

		_data = convertToRowMajorHelper(getData(), getRows(), getCols());
		_storage_type = StorageType::RowMajor;
	}

	// Converts storage type from row major to column major by rearranging data vector; 
	// if storage type is already column major, does nothing
	void convertToColMajor() 
	{
		if (_storage_type == StorageType::ColumnMajor)
			return;

		_data = convertToColMajorHelper(getData(), getRows(), getCols());
		_storage_type = StorageType::ColumnMajor;
	}


private:

	// Vector to store data 
	std::vector<T> _data;

	// Determines method of data storage, either column major or row major
	// Column major by default
	StorageType _storage_type;

};

#endif