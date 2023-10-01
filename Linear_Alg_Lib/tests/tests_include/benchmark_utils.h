#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

#include <chrono>

// ------------------------------------------------------------------
// Utility functions necessary for running benchmarks
// ------------------------------------------------------------------

// Returns execution time in microseconds of given function
template<typename Func>
std::chrono::microseconds measureExecutionTime(const Func& f);

// Returns average execution time in microseconds of given function
// called n times
template<typename Func>
std::chrono::microseconds measureAverageExecutionTime(const Func& f, 
	const size_t n);

#endif