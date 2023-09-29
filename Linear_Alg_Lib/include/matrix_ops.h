#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include "dense_matrix.h"
#include "math_vector.h"
#include "ops_utils.h"

// ------------------------------------------------------------------
// Operator overloads for DenseMatrix class
// ------------------------------------------------------------------

namespace LinAlg
{
	// Insertion operator overload for DenseMatrix class
	// Outputs DenseMatrix in row major format:
	/*
		a  b  c  d
		e  f  g  h
		i  j  k  l
		m  n  o  p
	*/
	// Ensures columns are aligned, even with different amounts of digits
	// Doesn't work well with non integer types
	template <typename T>
	inline std::ostream& operator<<(std::ostream& stream,
		const DenseMatrix<T> mat)
	{
		std::vector<T> data = mat.getData();
		size_t rows = mat.getRows();
		size_t cols = mat.getCols();

		// Finds maximum number of digits in any element in matrix data
		size_t max_digits = findMaxDigits(data);

		// Column width is largest number of digits + 2 spaces wide
		size_t column_width = max_digits + 2;

		// Get data vector into row major form to make printing easier
		if (mat.getStorageType() == StorageType::ColumnMajor)
			data = convertToRowMajorHelper(data, rows, cols);

		// Print matrix
		for (size_t i = 0; i < mat.getSize(); ++i)
		{
			T curr_elt = data[i];
			size_t num_spaces = column_width - numDigits<T>(curr_elt);
			stream << curr_elt;
			printSpaces(stream, num_spaces);

			// Prints newline after every row
			if (colIndex(i, cols) == cols - 1)
			{
				stream << "\n";
			}
		}
		return stream;
	}

	// Addition overload for DenseMatrix class; returns a DenseMatrix with 
	// the same StorageType as mat1
	template <typename T>
	inline DenseMatrix<T> operator+(const DenseMatrix<T>& mat1,
		const DenseMatrix<T>& mat2)
	{
		// Check that both matrices have the same dimensions
		if (!sameDimension(mat1, mat2))
			throw InvalidDimensions("Matrix addition");

		// Check that both matrices have the same storage format
		if (mat1.getStorageType() == mat2.getStorageType())
		{
			// Add the data vectors together and return a new DenseMatrix
			std::vector<T> result_data = addStdVectors(mat1.getData(), mat2.getData());
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

		std::vector<T> result_data = addStdVectors(mat1.getData(), data2_converted);
		DenseMatrix<T> result(
			result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
		return result;
	}

	// Subtraction overload for DenseMatrix class; returns a DenseMatrix with 
	// the same StorageType as mat1
	template <typename T>
	inline DenseMatrix<T> operator-(const DenseMatrix<T>& mat1,
		const DenseMatrix<T>& mat2)
	{
		// Check that both matrices have the same dimensions
		if (!sameDimension(mat1, mat2))
			throw InvalidDimensions("Matrix subtraction");

		// Check that both matrices have the same storage format
		if (mat1.getStorageType() == mat2.getStorageType())
		{
			// Subract the data vectors and return a new DenseMatrix
			std::vector<T> result_data = subtractStdVectors(
				mat1.getData(), mat2.getData());
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

		std::vector<T> result_data = subtractStdVectors(
			mat1.getData(), data2_converted);
		DenseMatrix<T> result(
			result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
		return result;
	}

	// Multiplication overload for DenseMatrix; returns a DenseMatrix with the 
	// the same storage type as mat1
	template <typename T>
	inline DenseMatrix<T> operator*(const DenseMatrix<T>& mat1,
		const DenseMatrix<T>& mat2)
	{
		if (mat1.getCols() != mat2.getRows())
			throw InvalidDimensions("Matrix multiplication");



		// TODO
		DenseMatrix<T> result(3, 3);
		return result;
	}
}

#endif