#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include "dense_matrix.h"


// Contains operator overloads for matrices

// Addition operator for std::vector; adds element-wise
template <typename T>
std::vector<T> operator+(const std::vector<T>& vec1, 
						 const std::vector<T>& vec2);

// Subtraction operator for std::vector; subtracts element-wise
template <typename T>
std::vector<T> operator-(const std::vector<T>& vec1, 
						 const std::vector<T>& vec2);

// Addition overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
template <typename T>
DenseMatrix<T> operator+(DenseMatrix<T>& mat1, 
						 DenseMatrix<T>& mat2);

// Subtraction overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
template <typename T>
DenseMatrix<T> operator-(DenseMatrix<T>& mat1, 
						 DenseMatrix<T>& mat2);


#endif