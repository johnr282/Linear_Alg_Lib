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
	// back to basicMultWithConversion once recursive calls get small
	// enough
	template<typename DataType>
	inline DenseMatrix<DataType> strassen(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B)
	{
		if (A.isSquare() && B.isSquare())
			return squareStrassen(A, B);
	}

	// Performs Strassen's algorithm, assuming both matrices are square
	template<typename DataType>
	inline DenseMatrix<DataType> squareStrassen(
		const DenseMatrix<DataType>& A,
		const DenseMatrix<DataType>& B)
	{
		// If matrices have odd dimensions, need to pad with extra row and 
		// column of zeros
		/*if(!isEven(A.rows()))*/

	}

	// Pads given matrix with n rows and columns filled with zeros

}


#endif