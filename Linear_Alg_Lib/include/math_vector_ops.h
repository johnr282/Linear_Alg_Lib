#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include "math_vector.h"
#include "ops_utils.h"

// ------------------------------------------------------------------
// Operator overloads and other operations for MathVector class
// ------------------------------------------------------------------

namespace LinAlg
{
	// == operator overload for MathVector class; only use with integral
	// data types
	template <typename DataType>
	inline bool operator==(const MathVector<DataType>& lhs,
		const MathVector<DataType>& rhs)
	{
		return lhs.getData() == rhs.getData();
	}

	// != operator overload for MathVector class
	template <typename DataType>
	inline bool operator!=(const MathVector<DataType>& lhs,
		const MathVector<DataType>& rhs)
	{
		return !(lhs == rhs);
	}

	// Insertion operator overload for MathVector class
	// Outputs MathVector in following format:
	/*
		a
		b
		c
	*/
	template <typename DataType>
	inline std::ostream& operator<<(std::ostream& stream,
		const MathVector<DataType>& vector)
	{
		std::vector<DataType> data = vector.getData();
		for (DataType elt : data)
		{
			stream << elt << "\n";
		}
		return stream;
	}

	// Addition operator overload for MathVector class
	template <typename DataType>
	inline MathVector<DataType> operator+(const MathVector<DataType>& vec1,
		const MathVector<DataType>& vec2)
	{
		if (vec1.size() != vec2.size())
			throw InvalidDimensions();

		std::vector<DataType> result_data = addStdVectors(
			vec1.getData(), vec2.getData());
		MathVector<DataType> result(result_data);
		return result;
	}

	// Subtraction operator overload for MathVector class
	template <typename DataType>
	inline MathVector<DataType> operator-(const MathVector<DataType>& vec1,
		const MathVector<DataType>& vec2)
	{
		if (vec1.size() != vec2.size())
			throw InvalidDimensions();

		std::vector<DataType> result_data = subtractStdVectors(
			vec1.getData(), vec2.getData());
		MathVector<DataType> result(result_data);
		return result;
	}

	// Returns dot product of two given vectors; vectors must be of equal 
	// length
	template <typename DataType>
	inline DataType dotProduct(const MathVector<DataType>& vec1,
		const MathVector<DataType>& vec2)
	{
		if (vec1.size() != vec2.size())
			throw InvalidDimensions();

		std::vector<DataType> data1 = vec1.getData();
		std::vector<DataType> data2 = vec2.getData();

		DataType result = 0;
		for (size_t i = 0; i < vec1.size(); ++i)
		{
			result += data1[i] * data2[i];
		}
		return result;
	}

	// Returns cross product of two given vectors; vectors both must 
	// of length 3, otherwise the cross product isn't defined
	// Note: Could cause issues with a MathVector<size_t>, as the cross 
	// product of two positive vectors can have negative values
	template <typename DataType>
	inline MathVector<DataType> crossProduct(const MathVector<DataType>& vec1,
		const MathVector<DataType>& vec2)
	{
		if (vec1.size() != 3 || vec2.size() != 3)
			throw InvalidDimensions();

		DataType i_component = vec1[1] * vec2[2] - vec1[2] * vec2[1];
		DataType j_component = vec1[2] * vec2[0] - vec1[0] * vec2[2];
		DataType k_component = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		MathVector<DataType> result({ i_component, j_component, k_component });
		return result;
	}
}

#endif