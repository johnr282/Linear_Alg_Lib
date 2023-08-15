#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include "dense_matrix.h"
#include "matrix_ops_utils.h"

// ------------------------------------------------------------------
// Operator overloads for DenseMatrix and SparseMatrix classes
// ------------------------------------------------------------------


// Addition operator for std::vector, adds element-wise; vec1 and vec2
// must be equal length
template <typename T>
inline std::vector<T> operator+(const std::vector<T>& vec1, 
						 const std::vector<T>& vec2) 
{
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size()) 
		throw std::length_error("Vector sizes must match");

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i) 
	{
		result[i] = vec1[i] + vec2[i];
	}
	return result;
}

// Subtraction operator for std::vector, subtracts element-wise; vec1 
// and vec2 must be equal length
template <typename T>
inline std::vector<T> operator-(const std::vector<T>& vec1,
						 const std::vector<T>& vec2) 
{
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size())
		throw std::length_error("Vector sizes don't match");

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i) 
	{
		result[i] = vec1[i] - vec2[i];
	}
	return result;
}

// Addition overload for DenseMatrix class; returns a DenseMatrix with 
// the same StorageType as mat1
template <typename T>
inline DenseMatrix<T> operator+(const DenseMatrix<T>& mat1,
						 const DenseMatrix<T>& mat2)
{
	// Check that both matrices have the same dimensions
	if (sameDimension(mat1, mat2)) 
		throw std::length_error("Matrix dimensions don't match");

	// Check that both matrices have the same storage format
	if (mat1.getStorageType() == mat2.getStorageType()) 
	{
		// Add the data vectors together and return a new DenseMatrix
		std::vector<T> result_data = mat1.getData() + mat2.getData();
		DenseMatrix<T> result(
			result_data, mat1.getRows(), mat1.getCols(), mat1.getStorageType());
		return result;
	}
	// If the matrices' storage formats don't match
	std::vector<T> data2_converted;

	if (mat1.getStorageType() == StorageType::RowMajor) 
	{
		// Mat2 must be column major, so convert it's data vector to 
		// row major for easy addition
		data2_converted = convertToRowMajorHelper(
			mat2.getData(), mat2.getRows(), mat2.getCols());
	}
	else 
	{
		// Mat2 must be row major, so convert it's data vector to column major
		data2_converted = convertToColMajorHelper(
			mat2.getData(), mat2.getRows(), mat2.getCols());
	}

	std::vector<T> result_data = mat1.getData() + data2_converted;
	DenseMatrix<T> result(
		result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
	return result;
}

// Subtraction overload for DenseMatrix class; returns a DenseMatrix with 
// the same StorageType as mat1
template <typename T>
inline DenseMatrix<T> operator-(DenseMatrix<T>& mat1,
						 DenseMatrix<T>& mat2) 
{
	// Check that both matrices have the same dimensions
	if (sameDimension(mat1, mat2))
		throw std::length_error("Matrix dimensions don't match");

	// Check that both matrices have the same storage format
	if (mat1.getStorageType() == mat2.getStorageType()) 
	{
		// Subract the data vectors and return a new DenseMatrix
		std::vector<T> result_data = mat1.getData() - mat2.getData();
		DenseMatrix<T> result(
			result_data, mat1.getRows(), mat1.getCols(), mat1.getStorageType());
		return result;
	}

	// If the matrices' storage formats don't match
	std::vector<T> data2_converted;

	if (mat1.getStorageType() == StorageType::RowMajor) 
	{
		// Mat2 must be column major, so convert it's data vector to row 
		// major for easy addition
		data2_converted = convertToRowMajorHelper(
			mat2.getData(), mat2.getRows(), mat2.getCols());
	}
	else 
	{
		// Mat2 must be row major, so convert it's data vector to column major
		data2_converted = convertToColMajorHelper(
			mat2.getData(), mat2.getRows(), mat2.getCols());
	}

	std::vector<T> result_data = mat1.getData() - data2_converted;
	DenseMatrix<T> result(
		result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
	return result;
}


#endif