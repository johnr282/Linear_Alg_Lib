#ifndef LIB_UTILS_H
#define LIB_UTILS_H

// ------------------------------------------------------------------
// Helpers used in entire library
// ------------------------------------------------------------------

namespace LinAlg
{
	// Returns whether the given doubles are approximately equal
	bool areEqual(const double num1, const double num2);

	// Returns true if given integer is even
	bool isEven(const int num);
}

#endif