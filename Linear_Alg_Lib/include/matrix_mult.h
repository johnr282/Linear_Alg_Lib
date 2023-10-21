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
	// formats of mat1 and mat2; found to be slower than basicMultWithConversion, 
	// so not used
	template<typename DataType>
	inline DenseMatrix<DataType> basicMultNoConversion(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
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

	// Performs basic multiplication algorithm based on mathematical 
	// definition of matrix multiplication
	// Converting mat1 to RowMajor and mat2 to ColMajor improves performance
	// over not doing the conversion
	// For multiplying two 300 x 300 matrices: 
	// ColMajor * ColMajor: 30% faster
	// ColMajor * RowMajor: 55% faster
	// RowMajor * RowMajor: 34% faster
	// RowMajor * ColMajor: 1% slower
	template<typename DataType>
	inline DenseMatrix<DataType> basicMultWithConversion(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		std::vector<DataType> product_data(mat1.rows() * mat2.cols());
		DenseMatrix<DataType> product(
			product_data, mat1.rows(), mat2.cols(), mat1.getStorageType());

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