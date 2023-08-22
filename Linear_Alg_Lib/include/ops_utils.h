#ifndef OPS_UTILS_H
#define OPS_UTILS_H

#include "math_vector.h"
#include "dense_matrix.h"

// ------------------------------------------------------------------
// Helpers for matrix_ops.h and vector_ops.h
// ------------------------------------------------------------------

// Adds given vectors element-wise and returns result; vec1 and vec2
// must be of equal length
template <typename T>
inline std::vector<T> addStdVectors(const std::vector<T>& vec1,
									const std::vector<T>& vec2)
{
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size())
		throw std::length_error(
			"Can't add std::vectors, invalid dimensions");

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i)
	{
		result[i] = vec1[i] + vec2[i];
	}
	return result;
}

// Subtracts given vectors element-wise and returns result; vec1 and 
// vec2 must be of equal length
template <typename T>
inline std::vector<T> subtractStdVectors(const std::vector<T>& vec1,
										 const std::vector<T>& vec2)
{
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size())
		throw std::length_error(
			"Can't subtract std::vectors, invalid dimensions");

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i)
	{
		result[i] = vec1[i] - vec2[i];
	}
	return result;
}

// Returns true if matrix dimensions match; false otherwise                 
template <typename T>
inline bool sameDimension(const DenseMatrix<T>& mat1,
						  const DenseMatrix<T>& mat2)
{
	return (mat1.getRows() == mat2.getRows()) && 
		   (mat1.getCols() == mat2.getCols());
}

#endif