#include "../tests_include/benchmark_utils.h"

#include <iostream>

// ------------------------------------------------------------------
// Implementations for non-templated benchmark utility functions
// ------------------------------------------------------------------

// Prints out given two names and execution times, along with which
// one was faster
void printExecutionTimes(const std::string& name1,
	const std::string& name2,
	const int time1,
	const int time2)
{
	std::cout << name1 << ": " << time1 << "\n";
	std::cout << name2 << ": " << time2 << "\n";

	int diff = std::abs(time2 - time1);

	if (time1 < time2)
	{
		double percent = percentFaster(diff, time2);
		std::cout << name1 << " " << percent << "% faster than " << name2;
	}
	else if (time2 < time1)
	{
		double percent = percentFaster(diff, time1);
		std::cout << name2 << " " << percent << "% faster than " << name1;
	}
	else
	{
		std::cout << name1 << " same speed as " << name2;
	}

	std::cout << "\n\n";
}

// Returns diff percentage of slower_time
double percentFaster(const int diff, const int slower_time)
{
	return ((double)diff / (double)slower_time) * 100.0;
}