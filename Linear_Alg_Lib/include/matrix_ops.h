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
	// == operator overload for DenseMatrix class; only use with 
	// integral data types
	template <typename DataType>
	inline bool operator==(const DenseMatrix<DataType>& lhs,
		const DenseMatrix<DataType>& rhs)
	{
		return (lhs.size() == rhs.size()) &&
			(lhs.rows() == rhs.rows()) &&
			(lhs.cols() == rhs.cols()) &&
			(lhs.getStorageType() == rhs.getStorageType()) &&
			(lhs.getData() == rhs.getData());
	}

	// != operator overload for DenseMatrix class
	template <typename DataType>
	inline bool operator!=(const DenseMatrix<DataType>& lhs,
		const DenseMatrix<DataType>& rhs)
	{
		return !(lhs == rhs);
	}

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
	template <typename DataType>
	inline std::ostream& operator<<(std::ostream& stream,
		const DenseMatrix<DataType>& mat)
	{
		std::vector<DataType> data = mat.getData();
		size_t rows = mat.rows();
		size_t cols = mat.cols();

		// Finds maximum number of digits in any element in matrix data
		size_t max_digits = findMaxDigits(data);

		// Column width is largest number of digits + 2 spaces wide
		size_t column_width = max_digits + 2;

		// Get data vector into row major form to make printing easier
		if (mat.getStorageType() == StorageType::ColumnMajor)
			data = convertToRowMajorHelper(data, rows, cols);

		// Print matrix
		for (size_t i = 0; i < mat.size(); ++i)
		{
			DataType curr_elt = data[i];
			size_t num_spaces = column_width - numDigits<DataType>(curr_elt);
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
	template <typename DataType>
	inline DenseMatrix<DataType> operator+(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		// Check that both matrices have the same dimensions
		if (!sameDimension(mat1, mat2))
			throw InvalidDimensions("matrix addition");

		// Check that both matrices have the same storage format
		if (mat1.getStorageType() == mat2.getStorageType())
		{
			// Add the data vectors together and return a new DenseMatrix
			std::vector<DataType> result_data = addStdVectors(mat1.getData(), mat2.getData());
			DenseMatrix<DataType> result(
				result_data, mat1.rows(), mat1.cols(), mat1.getStorageType());
			return result;
		}
		// If the matrices' storage formats don't match
		std::vector<DataType> data2_converted;

		if (mat1.getStorageType() == StorageType::RowMajor)
		{
			// Mat2 must be column major, so convert it's data vector to 
			// row major for easy addition
			data2_converted = convertToRowMajorHelper(
				mat2.getData(), mat2.rows(), mat2.cols());
		}
		else
		{
			// Mat2 must be row major, so convert it's data vector to column major
			data2_converted = convertToColMajorHelper(
				mat2.getData(), mat2.rows(), mat2.cols());
		}

		std::vector<DataType> result_data = addStdVectors(mat1.getData(), data2_converted);
		DenseMatrix<DataType> result(
			result_data, mat1.rows(), mat2.cols(), mat1.getStorageType());
		return result;
	}

	// Subtraction overload for DenseMatrix class; returns a DenseMatrix with 
	// the same StorageType as mat1
	template <typename DataType>
	inline DenseMatrix<DataType> operator-(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		// Check that both matrices have the same dimensions
		if (!sameDimension(mat1, mat2))
			throw InvalidDimensions("matrix subtraction");

		// Check that both matrices have the same storage format
		if (mat1.getStorageType() == mat2.getStorageType())
		{
			// Subract the data vectors and return a new DenseMatrix
			std::vector<DataType> result_data = subtractStdVectors(
				mat1.getData(), mat2.getData());
			DenseMatrix<DataType> result(
				result_data, mat1.rows(), mat1.cols(), mat1.getStorageType());
			return result;
		}

		// If the matrices' storage formats don't match
		std::vector<DataType> data2_converted;

		if (mat1.getStorageType() == StorageType::RowMajor)
		{
			// Mat2 must be column major, so convert it's data vector to row 
			// major for easy addition
			data2_converted = convertToRowMajorHelper(
				mat2.getData(), mat2.rows(), mat2.cols());
		}
		else
		{
			// Mat2 must be row major, so convert it's data vector to column major
			data2_converted = convertToColMajorHelper(
				mat2.getData(), mat2.rows(), mat2.cols());
		}

		std::vector<DataType> result_data = subtractStdVectors(
			mat1.getData(), data2_converted);
		DenseMatrix<DataType> result(
			result_data, mat1.rows(), mat2.cols(), mat1.getStorageType());
		return result;
	}

	// Multiplication overload for DenseMatrix; returns a DenseMatrix with the 
	// the same storage type as mat1
	template <typename DataType>
	inline DenseMatrix<DataType> operator*(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		if (mat1.cols() != mat2.rows())
			throw InvalidDimensions("matrix multiplication");

		return basicMult2(mat1, mat2);
	}

	// Performs basic multiplication algorithm based on mathematical 
	// definition of matrix multiplication
	template<typename DataType>
	inline DenseMatrix<DataType> basicMult1(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		// Multiplication is most efficient when mat1 is row major 
		// and mat2 is column major

		std::vector<DataType> product_data(mat1.rows() * mat2.cols());
		DenseMatrix<DataType> product(
			product_data, mat1.rows(), mat2.cols(), mat1.getStorageType());

		for (size_t i = 0; i < product.rows(); ++i)
		{
			for (size_t j = 0; j < product.cols(); ++j)
			{
				product.at(i, j) = dotProduct(mat1.row(i), mat2.col(j));
			}
		}

		return product;
	}

	template<typename DataType>
	inline DenseMatrix<DataType> basicMult2(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		std::vector<DataType> product_data(mat1.rows() * mat2.cols());
		DenseMatrix<DataType> product(
			product_data, mat1.rows(), mat2.cols(), mat1.getStorageType());

		// Multiplication is most efficient when mat1 is row major 
		// and mat2 is column major
		DenseMatrix<DataType> converted_mat1 = mat1.convertToRowMajor();
		DenseMatrix<DataType> converted_mat2 = mat2.convertToColMajor();

		for (size_t i = 0; i < product.rows(); ++i)
		{
			for (size_t j = 0; j < product.cols(); ++j)
			{
				product.at(i, j) = 
					dotProduct(converted_mat1.row(i), converted_mat2.col(j));
			}
		}

		return product;
	}
}

#endif