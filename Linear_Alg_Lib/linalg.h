#pragma once

#ifndef LINALG_H
#define LINALG_H


#include <vector>


// Header file for linear algebra library; contains definitions of all classes


// Basic matrix class
template <typename T>
class Matrix {
private: 

	// ********** Member variables **********

	// Vector to store data 
	std::vector<T> data;

	// Number of rows and columns
	int rows;
	int cols;

	// Number of elements
	int size;

	// 
	bool row_major;



};








#endif
