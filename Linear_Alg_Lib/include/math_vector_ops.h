#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include "math_vector.h"
#include "ops_utils.h"

// ------------------------------------------------------------------
// Operator overloads and other operations for MathVector class
// ------------------------------------------------------------------

namespace LinAlg
{
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
		if (vec1.getSize() != vec2.getSize())
			throw InvalidDimensions("Vector addition");

		std::vector<T> result_data = addStdVectors(
			vec1.getData(), vec2.getData());
		MathVector<T> result(result_data);
		return result;
	}

	// Subtraction operator overload for MathVector class
	template <typename T>
	inline MathVector<T> operator-(const MathVector<T>& vec1,
		const MathVector<T>& vec2)
	{
		if (vec1.getSize() != vec2.getSize())
			throw InvalidDimensions("Vector subtraction");

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
			throw InvalidDimensions("dotProduct()");

		std::vector<T> data1 = vec1.getData();
		std::vector<T> data2 = vec2.getData();

		T result = 0;
		for (size_t i = 0; i < vec1.getSize(); ++i)
		{
			result += data1[i] * data2[i];
		}
		return result;
	}

	// Returns cross product of two given vectors; vectors both must 
	// of length 3, otherwise the cross product isn't defined
	// Note: Could cause issues with a MathVector<size_t>, as the cross 
	// product of two positive vectors can have negative values
	template <typename T>
	inline MathVector<T> crossProduct(const MathVector<T>& vec1,
		const MathVector<T>& vec2)
	{
		if (vec1.getSize() != 3 || vec2.getSize() != 3)
			throw InvalidDimensions("crossProduct()");

		T i_component = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		T j_component = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		T k_component = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		MathVector<T> result({ i_component, j_component, k_component });
		return result;
	}
}

#endif