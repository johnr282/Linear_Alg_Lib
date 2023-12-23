#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include "matrix.h"
#include "math_vector.h"

namespace LinAlg
{
	// Solves a linear equation of the form Ax = b for x, where A is the coefficient
	// matrix and x and b are vectors. Returns true and puts solution vector into 
	// output parameter x if a unique solution exists; returns false if no
	// unique solution exists
	template <typename DataType, class MatrixType>
	bool solveLinearEquation(const Matrix<DataType, MatrixType>& A,
		MathVector<double>& x, 
		const MathVector<DataType>& b)
	{
		return false;
	}



}



#endif