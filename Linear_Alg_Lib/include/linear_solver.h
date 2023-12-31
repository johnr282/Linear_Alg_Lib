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

	template <typename DataType>
	inline void maximizePivot(DenseMatrix<DataType>& A,
		MathVector<DataType>& b,
		const size_t pivot_row);


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
		MathVector<double>& y)
	{
		// Data type of U and y must be doubles to prevent data loss during scaling
		U = convertToDoublesMatrix(A);
		y = convertToDoublesVector(b);

		// Algorithm is more efficient when U is row major
		U.convertToRowMajor();

		// Iterate through the pivots/diagonal elements of U
		for (int i = 0; i < U.rows(); ++i)
		{
			maximizePivot(U, y, i);
			double pivot = U.at(i, i);

			// If pivot is still 0 after maximizing the pivot, the whole column must
			// be 0s, meaning A is not invertible and no unique solution exists
			if (areEqual(pivot, 0))
				return false;

			// Scale pivot i so pivot is equal to 1
			double scale_factor = 1 / pivot;
			U.scaleRow(i, scale_factor);
			y[i] *= scale_factor;
			MathVector<double> pivot_row = U.row(i);

			// Make all numbers in pivot column below the pivot equal to 0 by subtracting 
			// scaled pivot row
			for (int j = i + 1; j < U.rows(); ++j)
			{
				double pivot_col_elt = U.at(j, i);
				if (areEqual(pivot_col_elt, 0))
					continue;

				MathVector<double> new_row = U.row(j);
				MathVector<double> scaled_pivot_row = pivot_row.scaled(pivot_col_elt);
				new_row -= scaled_pivot_row;
				U.setRow(j, new_row);
				y[j] -= y[i] * pivot_col_elt;
			}
		}

		return true;
	}

	// Rearranges the rows of the matrix A so that the largest value in col pivot_row
	// below pivot_row is in row pivot_row; prevents dividing by a very small number during 
	// Gaussian elimination
	template <typename DataType>
	inline void maximizePivot(DenseMatrix<DataType>& A,
		MathVector<DataType>& b,
		const size_t pivot_row)
	{
		// Find index of max value in pivot column below pivot row
		std::vector<DataType> pivot_col_data = A.col(pivot_row).getData();
		auto max_val_it = std::max_element(pivot_col_data.begin() + pivot_row, pivot_col_data.end());
		size_t max_val_index = max_val_it - pivot_col_data.begin();

		// Swap pivot_row and i of max value in pivot column in both A and b
		A.swapRows(pivot_row, max_val_index);
		b.swap(pivot_row, max_val_index);
	}

	// Given an upper triangular matrix U and vector y representing a system
	// Ux = y, returns the solution to the system as a vector
	inline MathVector<double> solveUpperTriangularSystem(const DenseMatrix<double>& U,
		const MathVector<double>& y)
	{

		MathVector<double> x = y;

		// Iterate backwards over pivots
		for (int i = U.rows() - 1; i >= 0; --i)
		{
			double pivot_soln_elt = x[i];
			// Iterate over elements above pivot
			for (int j = 0; j < i; ++j)
			{
				double pivot_col_elt = U.at(j, i);
				x[j] -= (pivot_col_elt * pivot_soln_elt);
			}
		}

		return x;
	}

	// Given matrix with a templated type, returns a matrix of doubles
	template <typename DataType>
	inline DenseMatrix<double> convertToDoublesMatrix(const DenseMatrix<DataType>& mat)
	{
		std::vector<double> converted_mat_data;
		converted_mat_data.reserve(mat.size());
		std::vector<DataType> mat_data = mat.getData();

		for (DataType val : mat_data)
		{
			converted_mat_data.push_back((double)val);
		}
		
		return DenseMatrix<double>(converted_mat_data, 
			mat.rows(), 
			mat.cols(), 
			mat.getStorageType());
	}

	// Given vector with a templated type, returns a vector of doubles
	template <typename DataType>
	inline MathVector<double> convertToDoublesVector(const MathVector<DataType> vec)
	{
		std::vector<double> converted_vec_data;
		converted_vec_data.reserve(vec.size());
		std::vector<DataType> vec_data = vec.getData();

		for (DataType val : vec_data)
		{
			converted_vec_data.push_back((double)val);
		}

		return MathVector<double>(converted_vec_data);
	}

}



#endif