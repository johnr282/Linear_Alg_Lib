#ifndef OPS_UTILS_H
#define OPS_UTILS_H

#include "math_vector.h"
#include "dense_matrix.h"

// ------------------------------------------------------------------
// Helpers for matrix_ops.h and vector_ops.h
// ------------------------------------------------------------------

namespace LinAlg
{
	// Adds given vectors element-wise and returns result; vec1 and vec2
	// must be of equal length
	template <typename DataType>
	inline std::vector<DataType> addStdVectors(const std::vector<DataType>& vec1,
		const std::vector<DataType>& vec2)
	{
		// Check that both vectors have the same size
		if (vec1.size() != vec2.size())
			throw std::length_error(
				"Can't add std::vectors, invalid dimensions");

		std::vector<DataType> result(vec1.size());
		for (size_t i = 0; i < vec1.size(); ++i)
		{
			result[i] = vec1[i] + vec2[i];
		}
		return result;
	}

	// Subtracts given vectors element-wise and returns result; vec1 and 
	// vec2 must be of equal length
	template <typename DataType>
	inline std::vector<DataType> subtractStdVectors(const std::vector<DataType>& vec1,
		const std::vector<DataType>& vec2)
	{
		// Check that both vectors have the same size
		if (vec1.size() != vec2.size())
			throw std::length_error(
				"Can't subtract std::vectors, invalid dimensions");

		std::vector<DataType> result(vec1.size());
		for (size_t i = 0; i < vec1.size(); ++i)
		{
			result[i] = vec1[i] - vec2[i];
		}
		return result;
	}

	// Returns true if matrix dimensions match; false otherwise                 
	template <typename DataType>
	inline bool sameDimension(const DenseMatrix<DataType>& mat1,
		const DenseMatrix<DataType>& mat2)
	{
		return (mat1.getRows() == mat2.getRows()) &&
			(mat1.getCols() == mat2.getCols());
	}
}

#endif