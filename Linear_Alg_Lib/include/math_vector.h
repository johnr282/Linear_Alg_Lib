#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>
#include <cmath>

// ------------------------------------------------------------------
// Templated class defining a column vector
// ------------------------------------------------------------------

template <typename T>
class MathVector
{
public:

	// Constructor
	MathVector(const std::vector<T>& data_in) :
		_data(data_in)
	{ }

	// Getter and setter functions

	std::vector<T> getData() const
	{
		return _data;
	}

	void setData(const std::vector<T>& data_in)
	{
		_data = data_in;
	}

	size_t getSize() const
	{
		return _data.size();
	}

	// Subscript operator overload for MathVector class, const version
	T operator[](int index) const
	{
		return _data[index];
	}

	// Subscript operator overload for MathVector class, non-const version
	T& operator[](int index) 
	{
		return _data[index];
	}

	// Returns the magnitude of the vector
	double magnitude() const
	{
		return std::sqrt(dotProduct(*this, *this));
	}



private:

	// Stores data in the column vector
	std::vector<T> _data;
};





#endif