#include "../include/lib_utils.h"

#include <cmath>

// ------------------------------------------------------------------
// Implementation of lib_utils.h
// ------------------------------------------------------------------

// Returns whether the given doubles are approximately equal
bool areEqual(const double num1, const double num2)
{
	const double epsilon = 0.000001;
	return std::fabs(num1 - num2) < epsilon;
}