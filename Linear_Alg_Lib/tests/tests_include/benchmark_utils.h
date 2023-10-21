#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

#include <chrono>
#include <string>

// ------------------------------------------------------------------
// Utility functions necessary for running benchmarks
// ------------------------------------------------------------------

// Returns execution time in microseconds of given function
template<typename Func, class ... Args>
inline std::chrono::microseconds measureExecutionTime(const Func& f, 
	const Args...args)
{
	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	f(args...);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	return duration;
}

// Returns average execution time in microseconds of given function
// called n times
template<typename Func, class ... Args>
inline std::chrono::microseconds measureAverageExecutionTime(const Func& f, 
	const size_t n,
	const Args...args)
{
	using namespace std::chrono_literals;

	std::chrono::microseconds total_time = 0us;
	for (size_t i = 0; i < n; ++i)
	{
		total_time += measureExecutionTime(f, args...);
	}

	std::chrono::microseconds average_time = total_time / n;
	return average_time;
}

// Prints out given two names and execution times, along with which
// one was faster
void printExecutionTimes(const std::string& name1,
	const std::string& name2,
	const int time1,
	const int time2);

// Returns diff percentage of slower_time
double percentFaster(const int diff, const int slower_time);

// Compares execution time of given functions with given args; both 
// functions are called with same args; runs each function n times
template<typename Func1, typename Func2, class ... Args>
inline void compareExecutionTimes(const Func1& f1,
	const Func2& f2,
	const int n,
	const std::string& name1,
	const std::string& name2,
	const Args...args)
{
	auto f1_time = measureAverageExecutionTime(f1, n, args...);
	auto f2_time = measureAverageExecutionTime(f2, n, args...);
	printExecutionTimes(name1, name2, f1_time.count(), f2_time.count());
}

#endif