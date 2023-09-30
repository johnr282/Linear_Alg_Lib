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

		CustomException(std::string message_in,
			std::string custom_message_in) :
			_message(message_in),
			_custom_message(custom_message_in)
		{ 
			_output = (_custom_message + " in " + _message).c_str();
		}

		const char* what()
		{
			return _output;
		}

	private:

		// Name or description of function in which the exception 
		// is thrown 
		std::string _message;

		// Custom message unique to each custom exception
		std::string _custom_message;

		// Output of what(), prevents dangling pointer errors
		const char* _output;
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