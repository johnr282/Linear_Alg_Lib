#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>

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


private:

	// Stores data in the column vector
	std::vector<T> _data;
};





#endif