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

		// Default constructor with optional storage type parameter; data 
		// vector initialized to empty vector, rows, cols, and size 
		// initialized to 0
		DenseMatrix(
			const StorageType storage_type_in = StorageType::ColumnMajor) :
			Matrix<DataType, DenseMatrix<DataType> >(),
			_data(std::vector<DataType>()),
			_storage_type(storage_type_in)
		{ }

		// Getter and setter functions

		std::vector<DataType> getData() const
		{
			return _data;
		}

		void setData(const std::vector<DataType>& data_in)
		{
			// Check that data_in vector matches matrix size
			if (data_in.size() != this->size())
				throw InvalidDimensions();

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

		// Returns row pos as a MathVector
		MathVector<DataType> row(const size_t pos) const override
		{
			return rowColHelper(pos, rowBounds(pos), rowIndices(pos), 
				this->_rows, this->_cols, StorageType::RowMajor);
		}

		// Returns col pos as a MathVector
		MathVector<DataType> col(const size_t pos) const override
		{
			return rowColHelper(pos, colBounds(pos), colIndices(pos),
				this->_cols, this->_rows, StorageType::ColumnMajor);
		}

		// Sets row pos to given MathVector
		void setRow(const size_t pos,
			const MathVector<DataType>& new_row) override
		{
			setHelper(pos, new_row, rowBounds(pos), rowIndices(pos),
				this->_rows, this->_cols, StorageType::RowMajor);
		}

		// Sets col pos to given MathVector
		void setCol(const size_t pos,
			const MathVector<DataType>& new_col) override
		{
			setHelper(pos, new_col, colBounds(pos), colIndices(pos),
				this->_cols, this->_rows, StorageType::ColumnMajor);
		}

		// Adds given row to the matrix above row pos
		void addRow(const size_t pos, 
			const MathVector<DataType>& new_row) override
		{
			addHelper(pos, new_row, rowBounds(pos),
				this->_rows, this->_cols, StorageType::RowMajor);
		}

		// Adds given col to the matrix to the left of col pos
		void addCol(const size_t pos, 
			const MathVector<DataType>& new_col) override
		{
			addHelper(pos, new_col, colBounds(pos),
				this->_cols, this->_rows, StorageType::ColumnMajor);
		}

		// Removes row pos from the matrix entirely
		void removeRow(const size_t pos) override
		{
			removeHelper(pos, rowBounds(pos), this->_rows, this->_cols, 
				StorageType::RowMajor);
		}

		// Removes col pos from the matrix entirely
		void removeCol(const size_t pos) override
		{
			removeHelper(pos, colBounds(pos), this->_cols, this->_rows,
				StorageType::ColumnMajor);
		}

		// Swaps the two rows at given positions
		void swapRows(const size_t pos1, const size_t pos2) override
		{
			MathVector<DataType> row1 = row(pos1);
			MathVector<DataType> row2 = row(pos2);
			setRow(pos1, row2);
			setRow(pos2, row1);
		}

		// Swaps the two columns at given positions
		void swapCols(const size_t pos1, const size_t pos2) override
		{
			MathVector<DataType> col1 = col(pos1);
			MathVector<DataType> col2 = col(pos2);
			setCol(pos1, col2);
			setCol(pos2, col1);
		}

		// Scales row pos by the given factor
		void scaleRow(const size_t pos, const DataType factor)
		{
			MathVector<DataType> row_to_scale = row(pos);
			row_to_scale.scale(factor);
			setRow(pos, row_to_scale);
		}

		// Scales row col by the given factor
		void scaleCol(const size_t pos, const DataType factor)
		{
			MathVector<DataType> col_to_scale = col(pos);
			col_to_scale.scale(factor);
			setCol(pos, col_to_scale);
		}

		// Returns matrix containing rows [first_row, last_row) and 
		// columns [first_col, last_col)
		DenseMatrix<DataType> getSubMatrix(const size_t first_row,
			const size_t last_row,
			const size_t first_col,
			const size_t last_col) const override
		{
			if (first_row > this->_rows ||
				last_row > this->_rows ||
				first_col > this->_cols ||
				last_col > this->_cols)
			{
				throw OutOfBounds();
			}

			DenseMatrix<DataType> sub_matrix(_storage_type);

			// Build matrix row by row or col by col depending on 
			// storage type for performance purposes
			if (_storage_type == StorageType::RowMajor)
			{
				for (size_t i = first_row; i < last_row; ++i)
				{
					MathVector<DataType> row_i = 
						row(i).getSubVector(first_col, last_col);
					sub_matrix.addRow(sub_matrix.rows(), row_i);
				}
			}
			else
			{
				for (size_t i = first_col; i < last_col; ++i)
				{
					MathVector<DataType> col_i =
						col(i).getSubVector(first_row, last_row);
					sub_matrix.addCol(sub_matrix.cols(), col_i);
				}
			}

			return sub_matrix;
		}

		// Sets section of matrix including rows [first_row, last_row)
		// and columns [first_col, last_col) to given matrix
		void setSubMatrix(const size_t first_row,
			const size_t last_row,
			const size_t first_col,
			const size_t last_col,
			const DenseMatrix<DataType>& new_sub_matrix) override
		{
			if (first_row > this->_rows ||
				last_row > this->_rows ||
				first_col > this->_cols ||
				last_col > this->_cols)
			{
				throw OutOfBounds();
			}

			if (new_sub_matrix.rows() != last_row - first_row ||
				new_sub_matrix.cols() != last_col - first_col)
			{
				throw InvalidDimensions();
			}

			if (_storage_type == StorageType::RowMajor)
			{
				size_t sub_matrix_i = 0;
				for (size_t i = first_row; i < last_row; ++i)
				{
					MathVector<DataType> sub_row = 
						new_sub_matrix.row(sub_matrix_i);
					MathVector<DataType> new_row = row(i);
					new_row.setSubVector(first_col, last_col, sub_row);
					setRow(i, new_row);
					++sub_matrix_i;
				}
			}
			else
			{
				size_t sub_matrix_i = 0;
				for (size_t i = first_col; i < last_col; ++i)
				{
					MathVector<DataType> sub_col =
						new_sub_matrix.col(sub_matrix_i);
					MathVector<DataType> new_col = col(i);
					new_col.setSubVector(first_row, last_row, sub_col);
					setCol(i, new_col);
					++sub_matrix_i;
				}
			}
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

		// Helper for row() and col()
		MathVector<DataType> rowColHelper(const size_t pos,
			const std::pair<size_t, size_t>& bounds,
			const std::vector<size_t>& indices,
			const size_t num_of,
			const size_t size_of,
			const StorageType desired_storage_type) const
		{
			if (pos >= num_of)
				throw OutOfBounds();

			std::vector<DataType> row_col_data(size_of);

			if (_storage_type == desired_storage_type)
			{
				row_col_data = std::vector<DataType>(
					_data.begin() + bounds.first, _data.begin() + bounds.second);
			}
			else
			{
				for (size_t i = 0; i < row_col_data.size(); ++i)
				{
					row_col_data[i] = _data[indices[i]];
				}
			}

			return MathVector<DataType>(row_col_data);
		}

		// Helper for setRow() and setCol()
		void setHelper(const size_t pos,
			const MathVector<DataType>& new_row_col,
			const std::pair<size_t, size_t>& bounds,
			const std::vector<size_t>& indices,
			const size_t num_of,
			const size_t size_of,
			const StorageType desired_storage_type)
		{
			if (pos >= num_of)
				throw OutOfBounds();

			if (new_row_col.size() != size_of)
				throw InvalidDimensions();

			std::vector<DataType> new_row_col_data = new_row_col.getData();

			if (_storage_type == desired_storage_type)
			{
				std::copy(new_row_col_data.begin(), new_row_col_data.end(),
					_data.begin() + bounds.first);
			}
			else
			{
				for (size_t i = 0; i < new_row_col_data.size(); ++i)
				{
					_data[indices[i]] = new_row_col_data[i];
				}
			}
		}

		// Helper for addRow() and addCol()
		void addHelper(const size_t pos,
			const MathVector<DataType>& new_row_col,
			const std::pair<size_t, size_t>& bounds,
			size_t& num_of,
			size_t& size_of,
			const StorageType desired_storage_type)
		{
			if (pos > num_of)
				throw OutOfBounds();

			if (!this->isEmpty() && new_row_col.size() != size_of)
				throw InvalidDimensions();

			std::vector<DataType> new_row_col_data = new_row_col.getData();
			_data.reserve(_data.size() + new_row_col.size());

			if (_storage_type == desired_storage_type)
			{
				_data.insert(_data.begin() + bounds.first,
					new_row_col_data.begin(), new_row_col_data.end());
			}
			else
			{
				size_t i = pos;
				for (DataType elt : new_row_col_data)
				{
					_data.insert(_data.begin() + i, elt);
					// Need the + 1 to account for the new element
					i += num_of + 1;
				}
			}

			// If matrix is empty, adding a row will change number of
			// columns and vice versa
			if (this->isEmpty())
				size_of += new_row_col.size();

			++num_of;
			this->_size += new_row_col.size();
		}
	
		// Helper for removeRow() and removeCol()
		void removeHelper(const size_t pos,
			const std::pair<size_t, size_t>& bounds,
			size_t& num_of,
			const size_t size_of,
			const StorageType desired_storage_type)
		{
			if (pos >= num_of)
				throw OutOfBounds();

			if (_storage_type == desired_storage_type)
			{
				_data.erase(
					_data.begin() + bounds.first, _data.begin() + bounds.second);
			}
			else
			{
				// Add num_of - 1 to account for erased element
				for (size_t i = pos; i < _data.size(); i += num_of - 1)
				{
					_data.erase(_data.begin() + i);
				}
			}

			--num_of;
			this->_size = _data.size();
		}

		// Returns [start, end) indices of row pos; assumes 
		// _storage_type is RowMajor and pos is in bounds
		std::pair<size_t, size_t> rowBounds(const size_t pos) const
		{
			size_t row_start = pos * this->_cols;
			size_t row_end = row_start + this->_cols;
			return { row_start, row_end };
		}

		// Returns [start, end) indices of col pos; assumes 
		// _storage_type is ColMajor and pos is in bounds
		std::pair<size_t, size_t> colBounds(const size_t pos) const
		{
			size_t col_start = pos * this->_rows;
			size_t col_end = col_start + this->_rows;
			return { col_start, col_end };
		}

		// Returns vector of indices of the elements in row pos;
		// assumes _storage_type is ColumnMajor and pos is in bounds
		std::vector<size_t> rowIndices(const size_t pos) const
		{
			std::vector<size_t> row_indices(this->_cols);
			size_t row_elt_index = pos;

			for (size_t i = 0; i < row_indices.size(); ++i)
			{
				row_indices[i] = row_elt_index;
				row_elt_index += this->_rows;
			}

			return row_indices;
		}

		// Returns vector of indices of the elements in col pos; 
		// assumes _storage_type is RowMajor and pos is in bounds
		std::vector<size_t> colIndices(const size_t pos) const
		{
			std::vector<size_t> col_indices(this->_rows);
			size_t col_elt_index = pos;

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