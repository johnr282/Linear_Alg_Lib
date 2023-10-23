#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include "linalg.h"

// ------------------------------------------------------------------
// Implementations of matrix multiplication algorithms
// These functions should be hidden, don't include this file in linalg.h
// ------------------------------------------------------------------

namespace LinAlg
{
	// Performs basic multiplication algorithm based on mathematical 
	// definition of matrix multiplication; doesn't worry about storage
	// formats of A and B; found to be slower than basicMultWithConversion, 
	// so not used
	template<typename DataType>
	inline DenseMatrix<DataType> basicMultNoConversion(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B)
	{
		std::vector<DataType> product_data(A.rows() * B.cols());
		DenseMatrix<DataType> product(
			product_data, A.rows(), B.cols(), A.getStorageType());

		for (size_t i = 0; i < product.rows(); ++i)
		{
			for (size_t j = 0; j < product.cols(); ++j)
			{
				product.at(i, j) = dotProduct(A.row(i), B.col(j));
			}
		}

		return product;
	}

	// Performs basic multiplication algorithm based on mathematical 
	// definition of matrix multiplication
	// Converting A to RowMajor and B to ColMajor improves performance
	// over not doing the conversion
	// For multiplying two 300 x 300 matrices: 
	// ColMajor * ColMajor: 30% faster
	// ColMajor * RowMajor: 55% faster
	// RowMajor * RowMajor: 34% faster
	// RowMajor * ColMajor: 1% slower
	template<typename DataType>
	inline DenseMatrix<DataType> basicMultWithConversion(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B)
	{
		std::vector<DataType> product_data(A.rows() * B.cols());
		DenseMatrix<DataType> product(
			product_data, A.rows(), B.cols(), A.getStorageType());

		DenseMatrix<DataType> converted_A = A.convertToRowMajor();
		DenseMatrix<DataType> converted_B = B.convertToColMajor();

		for (size_t i = 0; i < product.rows(); ++i)
		{
			for (size_t j = 0; j < product.cols(); ++j)
			{
				product.at(i, j) =
					dotProduct(converted_A.row(i), converted_B.col(j));
			}
		}

		return product;
	}

	// Performs Strassen's algorithm for matrix multiplication; switches
	// back to basicMultWithConversion once one dimension of matrix drops
	// below threshold
	template<typename DataType>
	inline DenseMatrix<DataType> strassen(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B,
		const size_t threshold)
	{
		DenseMatrix<DataType> padded_A = padMatrix(A);
		DenseMatrix<DataType> padded_B = padMatrix(B);

		return strassenHelper(padded_A, padded_B, threshold);
	}

	// Helper for strassen; makes sure padMatrix is only called on initial
	// matrices; assumes A and B have an even number of rows and columns
	template<typename DataType>
	inline DenseMatrix<DataType> strassenHelper(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B,
		const size_t threshold)
	{
		if (A.rows() < threshold ||
			A.cols() < threshold ||
			B.rows() < threshold ||
			B.cols < threshold)
		{
			return basicMultWithConversion(A, B);
		}

		DenseMatrix<DataType> A_11, A_12, A_21, A_22;

		DenseMatrix<DataType> B_11, B_12, B_21, B_22;

	}

	// Returns a matrix with same data as A, but with an extra row 
	// and/or column filled with zeros for "padding", ensuring A has 
	// an even number of rows and columns
	template<typename DataType>
	inline DenseMatrix<DataType> padMatrix(const DenseMatrix<DataType>& A)
	{
		DenseMatrix<DataType> padded_A = A;
		if (!isEven(A.rows()))
		{
			std::vector<DataType> zeros(A.cols(), 0);
			MathVector<DataType> padding(zeros);
			padded_A.addRow(padding);
		}

		if (!isEven(A.cols()))
		{
			std::vector<DataType> zeros(A.rows(), 0);
			MathVector<DataType> padding(zeros);
			padded_A.addCol(padding);
		}

		return padded_A;
	}

	// Partitions given matrix into 4 equal sub-matrices; puts sub-matrices
	// into output parameters
	template<typename DataType>
	inline void partitionMatrix(const DenseMatrix<DataType>& A,
		DenseMatrix<DataType>& A_11,
		DenseMatrix<DataType>& A_12,
		DenseMatrix<DataType>& A_21,
		DenseMatrix<DataType>& A_22)
	{
		size_t new_rows = A.rows() / 2;
		size_t new_cols = A.cols() / 2;
	}



}


#endif