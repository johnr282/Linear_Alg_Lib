#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>
#include <cmath>

#include "lib_utils.h"
#include "exceptions.h"

// ------------------------------------------------------------------
// Templated class defining a column vector
// ------------------------------------------------------------------

namespace LinAlg
{
	template <typename DataType>
	class MathVector
	{
	public:

		// Constructor
		MathVector(const std::vector<DataType>& data_in) :
			_data(data_in)
		{ }

		// Default constructor
		MathVector() :
			_data(std::vector<DataType>())
		{ }

		// Getter and setter functions

		std::vector<DataType> getData() const
		{
			return _data;
		}

		void setData(const std::vector<DataType>& data_in)
		{
			_data = data_in;
		}

		size_t size() const
		{
			return _data.size();
		}

		// Subscript operator overload for MathVector class, const version
		DataType operator[](size_t index) const
		{
			return _data[index];
		}

		// Subscript operator overload for MathVector class, non-const version
		DataType& operator[](size_t index)
		{
			return _data[index];
		}

		// Returns a MathVector containing elements [first_elt, last_elt)
		MathVector<DataType> subVector(size_t first_elt, size_t last_elt)
		{
			if (first_elt >= size() || last_elt > size())
				throw OutOfBounds();

			std::vector<DataType> sub_data(
				_data.begin() + first_elt, _data.begin() + last_elt);
			return MathVector<DataType>(sub_data);
		}

		// Returns the magnitude of the vector
		double magnitude() const
		{
			return std::sqrt(dotProduct(*this, *this));
		}

		// Returns normalized unit vector, or returns zero vector if this is
		// a zero vector
		MathVector<double> normalized() const
		{
			double mag = magnitude();
			if (areEqual(0, mag))
			{
				std::vector<double> zero_vec(_data.size(), 0);
				return MathVector<double>(zero_vec);
			}

			std::vector<double> normalized_data(_data.size());
			for (size_t i = 0; i < normalized_data.size(); ++i)
			{
				normalized_data[i] = static_cast<double>(_data[i]) / mag;
			}

			MathVector<double> unit_vector(normalized_data);
			return unit_vector;
		}

	private:

		// Stores data in the column vector
		std::vector<DataType> _data;
	};
}

#endif