#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <vector>
#include "matrix.h"
#include "matrix_utils.h"
#include "exceptions.h"

// ------------------------------------------------------------------
// Templated class defining a matrix; stores all data, zero and 
// nonzero, in one-dimensional array; supports both RowMajor and 
// ColumnMajor storage, but defaults to ColumnMajor
// ------------------------------------------------------------------

namespace LinAlg
{
	template <typename DataType>
	class DenseMatrix : public Matrix<DataType, DenseMatrix<DataType> >
	{
	public:

		// Constructor
		DenseMatrix(const std::vector<DataType>& data_in,
			const size_t rows_in,
			const size_t cols_in,
			const StorageType storage_type_in = StorageType::ColumnMajor) :
			Matrix<DataType, DenseMatrix<DataType> >(rows_in, cols_in),
			_data(data_in),
			_storage_type(storage_type_in)
		{
			// Check that size of data vector matches rows_in * cols_in
			if (data_in.size() != rows_in * cols_in)
			{
				throw InvalidDimensions("DenseMatrix()");
			}
		}

		// Constructor with no given data vector; default initializes all elements in matrix
		DenseMatrix(const size_t rows_in,
			const size_t cols_in,
			const StorageType storage_type_in = StorageType::ColumnMajor) :
			Matrix<DataType, DenseMatrix<DataType> >(rows_in, cols_in),
			_storage_type(storage_type_in)
		{
			std::vector<DataType> data_in(rows_in * cols_in);
			_data = data_in;
		}

		// Returns element at location (row, col), const version
		DataType at(size_t row, size_t col) const override
		{
			return atHelper(row, col);
		}

		// Returns element at location (row, col), non-const version
		DataType at(size_t row, size_t col) override
		{
			return atHelper(row, col);
		}

		// Getter and setter functions

		std::vector<DataType> getData() const
		{
			return _data;
		}

		void setData(const std::vector<DataType>& data_in)
		{
			// Check that data_in vector matches matrix size
			if (data_in.size() != this->getSize())
			{
				throw InvalidDimensions("setData()");
			}
			_data = data_in;
		}

		StorageType getStorageType() const
		{
			return _storage_type;
		}

		// Converts storage type from column major to row major by rearranging data vector; 
		// if storage type is already row major, does nothing
		void convertToRowMajor()
		{
			if (_storage_type == StorageType::RowMajor)
				return;

			_data = convertToRowMajorHelper(
				this->getData(), this->getRows(), this->getCols());
			_storage_type = StorageType::RowMajor;
		}

		// Converts storage type from row major to column major by rearranging data vector; 
		// if storage type is already column major, does nothing
		void convertToColMajor()
		{
			if (_storage_type == StorageType::ColumnMajor)
				return;

			_data = convertToColMajorHelper(
				this->getData(), this->getRows(), this->getCols());
			_storage_type = StorageType::ColumnMajor;
		}

		// Returns transpose of matrix
		DenseMatrix<DataType> tranpose() const override
		{
			// TODO
			return *this;
		}

		// Calculates determinant of matrix and puts it in DataType parameter; 
		// only returns false if matrix is not square
		bool determinant(DataType& det) const override
		{
			// TODO
			return false;
		}

		// Returns whether matrix is invertible
		bool isInvertible() const override
		{
			// TODO
			return false;
		}

		// Calculates inverse of matrix and puts it in MatrixType parameter;
		// returns whether the matrix is invertible
		bool inverse(DenseMatrix<DataType>& inv) const override
		{
			// TODO
			return false;
		}

		// Calculates eigenvectors and eigenvalues of matrix; puts eigenvectors
		// in eigenvecs parameter and eigenvalues in eigenvals parameter; 
		// eigenvecs[i]'s eigenvalue is eigenvals[i]
		bool eigenvectors(std::vector<MathVector<double> >& eigenvecs,
						  std::vector<double>& eigenvals) const override
		{
			// TODO
			return false;
		}

	private:

		DataType atHelper(size_t row, size_t col) const
		{
			bool invalid_index = (row >= this->_rows) || (col >= this->_cols);
			if (invalid_index)
				throw OutOfBounds("in DenseMatrix::at()");

			if (_storage_type == StorageType::RowMajor)
				return _data[row * this->_cols + col];
			else // _storage_type == StorageType::ColumnMajor
				return _data[col * this->_rows + row];
		}

		// Vector to store data 
		std::vector<DataType> _data;

		// Determines method of data storage, either column major or row major
		// Column major by default
		StorageType _storage_type;

	};
}

#endif