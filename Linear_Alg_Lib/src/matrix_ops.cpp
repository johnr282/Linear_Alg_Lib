#include "../include/matrix_ops.h"
#include "../include/matrix_ops_utils.h"


// Contains operator overloads for matrices

// Addition operator for std::vector; adds element-wise
template <typename T>
std::vector<T> operator+(const std::vector<T>& vec1,
	const std::vector<T>& vec2) {
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size()) {
		std::cerr << "Error in std::vector addition operator: Vector sizes must match.\n";
		exit(1);
	}

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i) {
		result[i] = vec1[i] + vec2[i];
	}
	return result;
}

// Subtraction operator for std::vector; subtracts element-wise
template <typename T>
std::vector<T> operator-(const std::vector<T>& vec1,
	const std::vector<T>& vec2) {
	// Check that both vectors have the same size
	if (vec1.size() != vec2.size()) {
		std::cerr << "Error in std::vector addition operator: Vector sizes must match.\n";
		exit(1);
	}

	std::vector<T> result(vec1.size());
	for (size_t i = 0; i < vec1.size(); ++i) {
		result[i] = vec1[i] - vec2[i];
	}
	return result;
}

// Addition overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
template <typename T>
DenseMatrix<T> operator+(DenseMatrix<T>& mat1,
	DenseMatrix<T>& mat2) {
	// Check that both matrices have the same dimensions
	if (sameDimension(mat1, mat2)) {
		std::cerr << "Error in matrix addition operator: Matrix dimensions must match.\n";
		exit(1);
	}

	// Check that both matrices have the same storage format
	if (mat1.getStorageType() == mat2.getStorageType()) {
		// Simply add the data vectors together and return a new DenseMatrix
		std::vector<T> result_data = mat1.getData() + mat2.getData();
		DenseMatrix<T> result(result_data, mat1.getRows(), mat1.getCols(), mat1.getStorageType());
		return result;
	}
	// If the matrices' storage formats don't match
	else {
		std::vector<T> data2_converted;
		if (mat1.getStorageType() == StorageType::RowMajor) {
			// Mat2 must be column major, so convert it's data vector to row major for easy addition
			data2_converted = convertToRowMajorHelper(mat2.getData(), mat2.getRows(), mat2.getCols());
		}
		else {
			// Mat2 must be row major, so convert it's data vector to column major
			data2_converted = convertToColMajorHelper(mat2.getData(), mat2.getRows(), mat2.getCols());
		}
		std::vector<T> result_data = mat1.getData() + data2_converted;
		DenseMatrix<T> result(result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
		return result;
	}
}

// Subtraction overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
template <typename T>
DenseMatrix<T> operator-(DenseMatrix<T>& mat1,
	DenseMatrix<T>& mat2) {
	// Check that both matrices have the same dimensions
	if (sameDimension(mat1, mat2)) {
		std::cerr << "Error in matrix subtraction operator: Matrix dimensions must match.\n";
		exit(1);
	}

	// Check that both matrices have the same storage format
	if (mat1.getStorageType() == mat2.getStorageType()) {
		// Simply subtract the data vectors and return a new DenseMatrix
		std::vector<T> result_data = mat1.getData() - mat2.getData();
		DenseMatrix<T> result(result_data, mat1.getRows(), mat1.getCols(), mat1.getStorageType());
		return result;
	}
	// If the matrices' storage formats don't match
	else {
		std::vector<T> data2_converted;
		if (mat1.getStorageType() == StorageType::RowMajor) {
			// Mat2 must be column major, so convert it's data vector to row major for easy addition
			data2_converted = convertToRowMajorHelper(mat2.getData(), mat2.getRows(), mat2.getCols());
		}
		else {
			// Mat2 must be row major, so convert it's data vector to column major
			data2_converted = convertToColMajorHelper(mat2.getData(), mat2.getRows(), mat2.getCols());
		}
		std::vector<T> result_data = mat1.getData() - data2_converted;
		DenseMatrix<T> result(result_data, mat1.getRows(), mat2.getCols(), mat1.getStorageType());
		return result;
	}
}
