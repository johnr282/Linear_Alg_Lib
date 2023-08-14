#include "../include/dense_matrix.h"
#include "../include/matrix_utils.h"


// Constructor
template <typename T>
DenseMatrix<T>::DenseMatrix(const std::vector<T>& data_in, 
							const size_t rows_in, 
							const size_t cols_in,
							const StorageType storage_type_in) :
	Matrix(rows_in, cols_in), 
	data(data_in), 
	storage_type(storage_type_in) 
{
	// Check that size of data vector matches rows_in * cols_in
	if (data_in.size() != rows_in * cols_in) {
		std::cerr << "Error in DenseMatrix constructor: Invalid Matrix initialization input vector; "
			<< "size of input vector must equal number of rows times number of columns.\n";
		exit(1);
	}
}

// Constructor with no given data vector; default initializes all elements in matrix
template <typename T>
DenseMatrix<T>::DenseMatrix(const size_t rows_in, const size_t cols_in,
	const StorageType storage_type_in)
	: Matrix(rows_in, cols_in), storage_type(storage_type_in) {
	std::vector<T> data_in(rows_in * cols_in);
	data = data_in;
}

// Getter and setter functions

template <typename T>
std::vector<T> DenseMatrix<T>::getData() const {
	return data;
}

template <typename T>
void DenseMatrix<T>::setData(const std::vector<T>& data_in) {
	// Check that data_in vector matches matrix size
	if (data_in.size() != getSize()) {
		std::cerr << "Error in setData(): Size of input data vector must match size of matrix.\n";
		exit(1);
	}
	data = data_in;
}

template <typename T>
StorageType DenseMatrix<T>::getStorageType() const {
	return storage_type;
}

// Prints matrix to cout in row major format, regardless of storage type: 
/*
	a  b  c  d
	e  f  g  h
	i  j  k  l
	m  n  o  p
*/
// Ensures columns are aligned, even with different amounts of digits
// Doesn't work well with non integer types
template <typename T>
void DenseMatrix<T>::printMatrix() const {
	// Finds maximum number of digits in any element in matrix data
	size_t max_digits = findMaxDigits(data);

	// Column width is largest number of digits + 2 spaces wide
	size_t column_width = max_digits + 2;

	// Get data vector into row major form to make printing easier
	std::vector<T> row_maj_data = convertToRowMajorHelper(getData(), getRows(), getCols());

	// Print matrix
	for (size_t i = 0; i < getSize(); ++i) {
		T curr_elt = row_maj_data[i];
		size_t num_spaces = column_width - numDigits<T>(curr_elt);
		std::cout << curr_elt;
		printSpaces(num_spaces);

		// Prints newline after every row
		if (colIndex(i, getCols()) == getCols() - 1) {
			std::cout << "\n";
		}
	}
}

// Converts storage type from column major to row major by rearranging data vector; 
// if storage type is already row major, does nothing
template <typename T>
void DenseMatrix<T>::convertToRowMajor() {
	if (storage_type == StorageType::RowMajor) {
		return;
	}

	data = convertToRowMajorHelper(getData(), getRows(), getCols());
	storage_type = StorageType::RowMajor;
}

// Converts storage type from row major to column major by rearranging data vector; 
// if storage type is already column major, does nothing
template <typename T>
void DenseMatrix<T>::convertToColMajor() {
	if (storage_type == StorageType::ColumnMajor) {
		return;
	}

	data = convertToColMajorHelper(getData(), getRows(), getCols());
	storage_type = StorageType::ColumnMajor;
}