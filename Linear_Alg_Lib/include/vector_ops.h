#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include "math_vector.h"
#include "ops_utils.h"

// ------------------------------------------------------------------
// Operator overloads for MathVector class
// ------------------------------------------------------------------

// Insertion operator overload for MathVector class
// Outputs MathVector in following format:
/*
	a
	b
	c
*/
template <typename T>
inline std::ostream& operator<<(std::ostream& stream,
								const MathVector<T>& vector)
{
	std::vector<T> data = vector.getData();
	for (T elt : data)
	{
		stream << elt << "\n";
	}
	return stream;
}

// Addition operator overload for MathVector class
template <typename T>
inline MathVector<T> operator+(const MathVector<T>& vec1,
							   const MathVector<T>& vec2)
{
	if(vec1.getSize() != vec2.getSize())
		throw std::length_error(
			"Can't add vectors, invalid dimensions");

	std::vector<T> result_data = addStdVectors(vec1.getData(), vec2.getData());
	MathVector<T> result(result_data);
	return result;
}

// Subtraction operator overload for MathVector class
template <typename T>
inline MathVector<T> operator-(const MathVector<T>& vec1,
							   const MathVector<T>& vec2)
{
	if (vec1.getSize() != vec2.getSize())
		throw std::length_error(
			"Can't add vectors, invalid dimensions");

	std::vector<T> result_data = subtractStdVectors(
		vec1.getData(), vec2.getData());
	MathVector<T> result(result_data);
	return result;
}

// Returns dot product of two given vectors; vectors must of equal 
// length
template <typename T>
inline T dotProduct(const MathVector<T>& vec1,
					const MathVector<T>& vec2)
{
	if (vec1.getSize() != vec2.getSize())
		throw std::length_error(
			"Can't compute dot product, invalid dimensions");

	std::vector<T> data1 = vec1.getData();
	std::vector<T> data2 = vec2.getData();

	T result = 0;
	for (size_t i = 0; i < vec1.getSize(); ++i)
	{
		result += data1[i] * data2[i];
	}
	return result;
}


#endif