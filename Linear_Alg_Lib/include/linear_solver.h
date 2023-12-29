#ifndef LINEAR_SOLVER_H
#define LINEAR_SOLVER_H

#include <algorithm>
#include "dense_matrix.h"
#include "math_vector.h"

// ------------------------------------------------------------------
// Functions for solving linear systems
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
		// If A isn't square, system won't have a unique solution
		// The system is invalid if the size of b isn't equal to the rows in A
		if (!A.isSquare() || A.rows() != b.size())
			return false;

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
		DenseMatrix<DataType> A_copy = A;
		MathVector<DataType> b_copy = b;

		for (int row = 0; row < A.rows(); ++row)
		{
			maximizePivot(A_copy, b_copy, row);

		}


		return false;
	}

	// Rearranges the rows of the matrix A so that the largest value in col pivot_row
	// is in row pivot_row; prevents dividing by a very small number during Gaussian
	// elimination
	template <typename DataType>
	inline void maximizePivot(DenseMatrix<DataType>& A,
		MathVector<DataType>& b,
		const size_t pivot_row)
	{
		// Find index of max value in pivot column
		std::vector<DataType> pivot_col_data = A.col(pivot_row).getData();
		auto max_val_it = std::max_element(pivot_col_data.begin(), pivot_col_data.end());
		size_t max_val_index = max_val_it - pivot_col_data.begin();

		// Swap pivot_row and row of max value in pivot column in both A and b
		A.swapRows(pivot_row, max_val_index);
		b.swap(pivot_row, max_val_index);
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