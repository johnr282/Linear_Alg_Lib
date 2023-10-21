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
				throw InvalidDimensions();
			}
		}

		// Constructor with no given data vector; default initializes 
		// all elements in matrix
		DenseMatrix(const size_t rows_in,
			const size_t cols_in,
			const StorageType storage_type_in = StorageType::ColumnMajor) :
			Matrix<DataType, DenseMatrix<DataType> >(rows_in, cols_in),
			_storage_type(storage_type_in)
		{
			std::vector<DataType> data_in(rows_in * cols_in);
			_data = data_in;
		}

		// Getter and setter functions

		std::vector<DataType> getData() const
		{
			return _data;
		}

		void setData(const std::vector<DataType>& data_in)
		{
			// Check that data_in vector matches matrix size
			if (data_in.size() != this->size())
			{
				throw InvalidDimensions();
			}
			_data = data_in;
		}

		StorageType getStorageType() const
		{
			return _storage_type;
		}

		// Converts storage type from column major to row major by 
		// rearranging data vector; if storage type is already row 
		// major, does nothing
		void convertToRowMajor()
		{
			if (_storage_type == StorageType::RowMajor)
				return;

			_data = convertToRowMajorHelper(
				this->_data, this->_rows, this->_cols);
			_storage_type = StorageType::RowMajor;
		}

		// Const version, returns converted row major DenseMatrix
		DenseMatrix<DataType> convertToRowMajor() const
		{
			if (_storage_type == StorageType::RowMajor)
				return DenseMatrix<DataType>(*this);

			std::vector<DataType> converted_data = convertToRowMajorHelper(
				this->_data, this->_rows, this->_cols);
			
			return DenseMatrix<DataType>(
				converted_data, this->_rows, this->_cols, StorageType::RowMajor);
		}

		// Converts storage type from row major to column major by 
		// rearranging data vector; if storage type is already column 
		// major, does nothing
		void convertToColMajor()
		{
			if (_storage_type == StorageType::ColumnMajor)
				return;

			_data = convertToColMajorHelper(
				this->_data, this->_rows, this->_cols);
			_storage_type = StorageType::ColumnMajor;
		}

		// Const version, returns converted column major DenseMatrix
		DenseMatrix<DataType> convertToColMajor() const
		{
			if (_storage_type == StorageType::ColumnMajor)
				return DenseMatrix<DataType>(*this);

			std::vector<DataType> converted_data = convertToColMajorHelper(
				this->_data, this->_rows, this->_cols);

			return DenseMatrix<DataType>(
				converted_data, this->_rows, this->_cols, StorageType::ColumnMajor);
		}

		// Returns element at location (row, col), const version
		DataType at(const size_t row, const size_t col) const override
		{
			return _data[atHelper(row, col)];
		}

		// Returns element at location (row, col), non-const version
		DataType& at(const size_t row, const size_t col) override
		{
			return _data[atHelper(row, col)];
		}

		// Returns row row_index as a MathVector
		MathVector<DataType> row(const size_t row_index) const
		{
			bool invalid_index = (row_index >= this->_rows);
			if (invalid_index)
				throw OutOfBounds();

			std::vector<DataType> row_data(this->_cols);

			if (_storage_type == StorageType::RowMajor)
			{
				std::pair<size_t, size_t> row_bounds = rowBounds(row_index);
				size_t row_start = row_bounds.first;
				size_t row_end = row_bounds.second;
				row_data = std::vector<DataType>(
					_data.begin() + row_start, _data.begin() + row_end);
			}
			else
			{
				std::vector<size_t> row_indices = rowIndices(row_index);
				for (size_t i = 0; i < row_data.size(); ++i)
				{
					size_t row_elt_index = row_indices[i];
					row_data[i] = _data[row_elt_index];
				}
			}

			return MathVector<DataType>(row_data);
		}

		// Returns col j as a MathVector
		MathVector<DataType> col(const size_t col_index) const
		{
			bool invalid_index = (col_index >= this->_cols);
			if (invalid_index)
				throw OutOfBounds();

			std::vector<DataType> col_data(this->_rows);

			if (_storage_type == StorageType::ColumnMajor)
			{
				std::pair<size_t, size_t> col_bounds = colBounds(col_index);
				size_t col_start = col_bounds.first;
				size_t col_end = col_bounds.second;
				col_data = std::vector<DataType>(
					_data.begin() + col_start, _data.begin() + col_end);
			}
			else
			{
				std::vector<size_t> col_indices = colIndices(col_index);
				for (size_t i = 0; i < col_data.size(); ++i)
				{
					size_t col_elt_index = col_indices[i];
					col_data[i] = _data[col_elt_index];
				}
			}

			return MathVector<DataType>(col_data);
		}

		// Sets row row_index to given MathVector
		void setRow(const size_t row_index,
			const MathVector<DataType>& new_row)
		{
			bool invalid_index = (row_index >= this->_rows);
			if (invalid_index)
				throw OutOfBounds();

			bool invalid_row = (new_row.size() != this->_cols);
			if (invalid_row)
				throw InvalidDimensions();

			std::vector<DataType> new_row_data = new_row.getData();

			if (_storage_type == StorageType::RowMajor)
			{
				std::pair<size_t, size_t> row_bounds = rowBounds(row_index);
				size_t row_start = row_bounds.first;
				
				std::copy(new_row_data.begin(), new_row_data.end(), 
					_data.begin() + row_start);
			}
			else
			{
				std::vector<size_t> row_indices = rowIndices(row_index);
				for (size_t i = 0; i < new_row_data.size(); ++i)
				{
					size_t row_elt_index = row_indices[i];
					_data[row_elt_index] = new_row_data[i];
				}
			}
		}

		// Sets col j to given MathVector
		void setCol(const size_t col_index,
			const MathVector<DataType>& new_col)
		{
			bool invalid_index = (col_index >= this->_cols);
			if (invalid_index)
				throw OutOfBounds();

			bool invalid_row = (new_col.size() != this->_rows);
			if (invalid_row)
				throw InvalidDimensions();

			std::vector<DataType> new_col_data = new_col.getData();

			if (_storage_type == StorageType::ColumnMajor)
			{
				std::pair<size_t, size_t> col_bounds = colBounds(col_index);
				size_t col_start = col_bounds.first;

				std::copy(new_col_data.begin(), new_col_data.end(),
					_data.begin() + col_start);
			}
			else
			{
				std::vector<size_t> col_indices = colIndices(col_index);
				for (size_t i = 0; i < new_col_data.size(); ++i)
				{
					size_t col_elt_index = col_indices[i];
					_data[col_elt_index] = new_col_data[i];
				}
			}
		}

		// Adds given row to bottom of matrix
		void addRow(const MathVector<DataType>& new_row)
		{

		}

		// Adds given col to right of matrix
		void addCol(const MathVector<DataType>& new_col)
		{

		}

		// Returns transpose of matrix
		DenseMatrix<DataType> tranpose() const override
		{
			// TODO
			return *this;
		}

		// Calculates determinant of matrix and puts it in DataType 
		// parameter; only returns false if matrix is not square
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

		// Calculates inverse of matrix and puts it in MatrixType 
		// parameter; returns whether the matrix is invertible
		bool inverse(DenseMatrix<DataType>& inv) const override
		{
			// TODO
			return false;
		}

		// Calculates eigenvectors and eigenvalues of matrix; puts 
		// eigenvectors in eigenvecs parameter and eigenvalues in 
		// eigenvals parameter; eigenvecs[i]'s eigenvalue is eigenvals[i]
		bool eigenvectors(std::vector<MathVector<double> >& eigenvecs,
						  std::vector<double>& eigenvals) const override
		{
			// TODO
			return false;
		}

	private:

		// Returns index in _data corresponding to given row and col
		size_t atHelper(const size_t row, const size_t col) const
		{
			bool invalid_index = (row >= this->_rows) || 
								 (col >= this->_cols);
			if (invalid_index)
				throw OutOfBounds();

			if (_storage_type == StorageType::RowMajor)
				return row * this->_cols + col;
			else 
				return col * this->_rows + row;
		}

		// Returns [start, end) indices of row row_index; assumes 
		// _storage_type is RowMajor and row_index is in bounds
		std::pair<size_t, size_t> rowBounds(const size_t row_index) const
		{
			size_t row_start = row_index * this->_cols;
			size_t row_end = row_start + this->_cols;
			return { row_start, row_end };
		}

		// Returns [start, end) indices of col col_index; assumes 
		// _storage_type is ColMajor and col_index is in bounds
		std::pair<size_t, size_t> colBounds(const size_t col_index) const
		{
			size_t col_start = col_index * this->_rows;
			size_t col_end = col_start + this->_rows;
			return { col_start, col_end };
		}

		// Returns vector of indices of the elements in row row_index;
		// assumes _storage_type is ColumnMajor and row_index is in bounds
		std::vector<size_t> rowIndices(const size_t row_index) const
		{
			std::vector<size_t> row_indices(this->_cols);
			size_t row_elt_index = row_index;

			for (size_t i = 0; i < row_indices.size(); ++i)
			{
				row_indices[i] = row_elt_index;
				row_elt_index += this->_rows;
			}

			return row_indices;
		}

		// Returns vector of indices of the elements in col col_index; 
		// assumes _storage_type is RowMajor and col_index is in bounds
		std::vector<size_t> colIndices(const size_t col_index) const
		{
			std::vector<size_t> col_indices(this->_rows);
			size_t col_elt_index = col_index;

			for (size_t i = 0; i < col_indices.size(); ++i)
			{
				col_indices[i] = col_elt_index;
				col_elt_index += this->_cols;
			}

			return col_indices;
		}

		// Vector to store data 
		std::vector<DataType> _data;

		// Determines method of data storage, either column major or 
		// row major; column major by default
		StorageType _storage_type;

	};
}

#endif