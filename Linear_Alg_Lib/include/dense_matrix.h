#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"

// ------------------------------------------------------------------
// Templated class defining a matrix; stores all data, zero and 
// nonzero, in one-dimensional array; supports both RowMajor and 
// ColumnMajor storage, but defaults to ColumnMajor
// ------------------------------------------------------------------

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