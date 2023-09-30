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

		CustomException(std::string func_name,
			std::string exception_type)
		{ 
			_output = exception_type + " in " + func_name;
		}

		const char* what()
		{
			return _output.c_str();
		}

	private:

		// Output of what(), formatted as "Exception type in func()"
		std::string _output;
	};

	// Thrown when a mismatch in dimensions make an operation impossible
	class InvalidDimensions : public CustomException
	{
	public:

		InvalidDimensions(std::string message_in) :
			CustomException(message_in, "Invalid dimensions")
		{ }
	};

	// Thrown when an index is out of bounds
	class OutOfBounds : public CustomException
	{
	public: 

		OutOfBounds(std::string message_in) :
			CustomException(message_in, "Out of bounds index")
		{ }
	};
}


#endif