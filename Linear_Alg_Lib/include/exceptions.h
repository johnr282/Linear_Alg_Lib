#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// ------------------------------------------------------------------
// Contains definitions of custom exceptions used throughout library
// ------------------------------------------------------------------

namespace LinAlg
{
	// Base class for all custom exceptions
	class CustomException : public std::exception
	{
	public:

		CustomException(const std::string& output_in)
		{ 
			_output = output_in;
		}

		const char* what()
		{
			return _output.c_str();
		}

	private:

		// Output of what()
		std::string _output;
	};

	// Thrown when a mismatch in dimensions make an operation impossible
	class InvalidDimensions : public CustomException
	{
	public:

		InvalidDimensions() :
			CustomException("Invalid dimensions")
		{ }
	};

	// Thrown when an index is out of bounds
	class OutOfBounds : public CustomException
	{
	public: 

		OutOfBounds() :
			CustomException("Out of bounds index")
		{ }
	};
}


#endif