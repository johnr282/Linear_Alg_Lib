#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include "dense_matrix.h"
#include "math_vector.h"

// ------------------------------------------------------------------
// Functions for solving lineary systems
// ------------------------------------------------------------------

namespace LinAlg
{
	inline MathVector<double> solveUpperTriangularSystem(const DenseMatrix<double>& U,
		const MathVector<double>& y);


	// Given a matrix A and vector b representing a system Ax = b, tries to
	// solve the system; if successful, returns true and puts the solution vector 
	// into the output parameter x; if not, returns false.
	// Will fail if the given matrix A is not invertible
	template <typename DataType>
	inline bool solveLinearEquation(const DenseMatrix<DataType>& A,
		const MathVector<DataType>& b, 
		MathVector<double>& x)
	{
		return gaussianElimination(A, b, x);
	}

	// Given a matrix A and vector b representing a system Ax = b, uses Guassian 
	// elimination to try to solve the system; if successful, returns true and 
	// puts the solution vector into the output parameter x; if not, returns false.
	// Guassian elimination will fail if the given matrix A is not invertible
	template <typename DataType>
	inline bool gaussianElimination(const DenseMatrix<DataType>& A,
		const MathVector<DataType>& b,
		MathVector<double>& x)
	{
		DenseMatrix<double> U;
		MathVector<double> y;

		if (!convertToUpperTriangular(A, b, U, y))
			return false;

		x = solveUpperTriangularSystem(U, y);
		return true;
	}

	// Given a matrix A and vector b representing a system Ax = b, calculates the 
	// equivalent system Ux = y, where U is an upper triangular matrix; puts U and
	// y into output parameters; returns true if given system can be converted to
	// an upper triangular system, and false if not
	template <typename DataType>
	inline bool convertToUpperTriangular(const DenseMatrix<DataType>& A,
		const MathVector<DataType>& b,
		DenseMatrix<double>& U,
		MathVector<double> y)
	{
		return false;
	}

	// Given an upper triangular matrix U and vector y representing a system
	// Ux = y, returns the solution to the system as a vector
	inline MathVector<double> solveUpperTriangularSystem(const DenseMatrix<double>& U,
		const MathVector<double>& y)
	{
		return MathVector<double>({ 0, 0, 0 });
	}



}



#endif