#include "../include/matrix.h"


// Constructor
Matrix::Matrix(size_t rows_in, 
			   size_t cols_in) :
	rows(rows_in),
	cols(cols_in),
	size(rows_in* cols_in)
{ }

size_t Matrix::getRows() const 
{
	return rows;
}

size_t Matrix::getCols() const 
{
	return cols;
}

size_t Matrix::getSize() const 
{
	return size;
}