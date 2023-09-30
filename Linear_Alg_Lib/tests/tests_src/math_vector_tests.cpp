#include "../tests_include/math_vector_tests.h"

#include <cassert>
#include "../tests_include/tests_utils.h"
#include "../../include/math_vector.h"
#include "../../include/math_vector_ops.h"
#include "../../include/lib_utils.h"

using namespace LinAlg;

// ------------------------------------------------------------------
// Implementations of MathVector unit tests
// ------------------------------------------------------------------

// Runs all MathVector unit tests
void testMathVector()
{
	//testMathVectorInsertion();
	testMathVectorSubscript();
	testMathVectorEquals();
	testMathVectorAdd();
	testMathVectorSubtract();
	testMathVectorDotProduct();
	testMathVectorCrossProduct();
	testMathVectorMagnitude();
	testMathVectorNormalize();

	std::cout << "MathVector tests complete\n";
}

void testMathVectorInsertion()
{
	std::vector<int> data{ 0, 1, 4, 12, 1, 4, 10 };
	MathVector<int> vector(data);
	std::cout << vector;
}

void testMathVectorSubscript()
{
	std::vector<int> data1{ 0, 1, 2 };
	const MathVector<int> vec1(data1);
	assert(vec1[0] == 0);

	MathVector<int> vec2(data1);
	vec2[1] = 5;
	assert(vec2[1] == 5);
}

void testMathVectorEquals()
{
	std::vector<int> data1{ 0, 2, 1, 4 };
	MathVector<int> vec1(data1);
	MathVector<int> vec2(data1);
	assert(vec1 == vec2);

	vec1[2] = 5;
	assert(vec1 != vec2);
}

void testMathVectorAdd()
{
	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
	MathVector<int> vec1(data1);
	MathVector<int> vec2(data2);
	std::vector<int> data3{ 1, 3, 0, 2, 3, 0 };
	MathVector<int> vec3 = vec1 + vec2;
	assert(vec3.getData() == data3);

	std::vector<int> data4{ 1, 1, 3, 0 };
	std::vector<int> data5{ 0, 1, 5, 4 };
	MathVector<int> vec4(data4);
	MathVector<int> vec5(data5);
	std::vector<int> data6{ 1, 2, 8, 4 };
	MathVector<int> vec6 = vec4 + vec5;
	assert(vec6.getData() == data6);
}

void testMathVectorSubtract()
{
	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
	MathVector<int> vec1(data1);
	MathVector<int> vec2(data2);
	std::vector<int> data3{ -1, -1, 0, 2, 1, 0 };
	MathVector<int> vec3 = vec1 - vec2;
	assert(vec3.getData() == data3);

	std::vector<int> data4{ 1, 1, 3, 0 };
	std::vector<int> data5{ 0, 1, 5, 4 };
	MathVector<int> vec4(data4);
	MathVector<int> vec5(data5);
	std::vector<int> data6{ 1, 0, -2, -4 };
	MathVector<int> vec6 = vec4 - vec5;
	assert(vec6.getData() == data6);
}

void testMathVectorDotProduct()
{
	std::vector<int> data1{ 0, 1, 0, 2, 2, 0 };
	std::vector<int> data2{ 1, 2, 0, 0, 1, 0 };
	MathVector<int> vec1(data1);
	MathVector<int> vec2(data2);
	int result1 = 4;
	assert(dotProduct(vec1, vec2) == result1);

	std::vector<int> data3{ 1, 1, 2, 0, 3 };
	std::vector<int> data4{ 0, 3, 5, 1, 0 };
	MathVector<int> vec3(data3);
	MathVector<int> vec4(data4);
	int result2 = 13;
	assert(dotProduct(vec3, vec4) == result2);
}

void testMathVectorCrossProduct()
{
	std::vector<int> data1{ 4, 2, 6 };
	std::vector<int> data2{ 1, 3, -1 };
	MathVector<int> vec1(data1);
	MathVector<int> vec2(data2);
	std::vector<int> data3{ -20, 10, 10 };
	assert(crossProduct(vec1, vec2).getData() == data3);

	std::vector<int> data4{ 1, 3, -1 };
	std::vector<int> data5{ 0, 0, 5 };
	MathVector<int> vec4(data4);
	MathVector<int> vec5(data5);
	std::vector<int> data6{ 15, -5, 0 };
	assert(crossProduct(vec4, vec5).getData() == data6);
}

void testMathVectorMagnitude()
{
	std::vector<int> data1{ 0, 1, 4 };
	MathVector<int> vec1(data1);
	double result1 = 4.123105626;
	assert(areEqual(result1, vec1.magnitude()));

	std::vector<double> data2{ 1.3902, 0.213, 2.493, 5.343 };
	MathVector<double> vec2(data2);
	double result2 = 6.061412627;
	assert(areEqual(result2, vec2.magnitude()));

	std::vector<int> data3{ 0, 0, 0 };
	MathVector<int> vec3(data3);
	double result3 = 0.0;
	assert(areEqual(result3, vec3.magnitude()));
}

void testMathVectorNormalize()
{
	std::vector<int> data1{ 0, 1, 4, 2, 3 };
	MathVector<int> vec1(data1);
	double mag1 = vec1.magnitude();
	std::vector<double> result1{
		0 / mag1, 1 / mag1, 4 / mag1, 2 / mag1, 3 / mag1 };
	MathVector<double> unit_vec1 = vec1.normalized();
	checkVectors(result1, unit_vec1.getData());

	std::vector<double> data2{ 1.23, 0.1, 4.99, -8.7, 12.294, -0.23 };
	MathVector<double> vec2(data2);
	double mag2 = vec2.magnitude();
	std::vector<double> result2{
		1.23 / mag2, 0.1 / mag2, 4.99 / mag2, -8.7 / mag2, 12.294 / mag2, -0.23 / mag2 };
	MathVector<double> unit_vec2 = vec2.normalized();
	checkVectors(result2, unit_vec2.getData());

	std::vector<double> data3{ 0, 0, 0 };
	MathVector<double> vec3(data3);
	std::vector<double> result3{ 0, 0, 0 };
	MathVector<double> unit_vec3 = vec3.normalized();
	checkVectors(result3, unit_vec3.getData());
}