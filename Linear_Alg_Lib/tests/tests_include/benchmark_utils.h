#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

#include <chrono>

// ------------------------------------------------------------------
// Utility functions necessary for running benchmarks
// ------------------------------------------------------------------

// Returns execution time in microseconds of given function
template<typename Func>
std::chrono::microseconds measureExecutionTime(const Func& f)
{
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	f();
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	return duration;
}

// Returns average execution time in microseconds of given function
// called n times
template<typename Func>
std::chrono::microseconds measureAverageExecutionTime(const Func& f, 
	const size_t n)
{
	using namespace std::chrono_literals;

	std::chrono::microseconds total_time = 0us;
	for (size_t i = 0; i < n; ++i)
	{
		total_time += measureExecutionTime(f);
	}

	std::chrono::microseconds average_time = total_time / n;
	return average_time;
}

#endif