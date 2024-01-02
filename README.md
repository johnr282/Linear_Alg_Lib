# Linear_Alg_Lib
This project is a fully templated linear algebra library written in C++. I'm writing it mostly as a learning experience to understand more about all the optimization and data storage decisions required to efficiently work with matrices, as well as the implementations of various numerical algorithms. 

Currently, the library provides a `MathVector` class, which represents an $n$-dimensional mathematical vector, and a `DenseMatrix` class, which is designed to store a $n \times m$ matrix whose elements are mostly nonzero. In the future, I have plans to implement a `SparseMatrix` class as well for matrices whose elements are mostly zero. The library also contains bencharmking utility functions used for measuring and comparing performance of operations. 

Detailed documentation of the classes and operations provided by the library can be found in the Wiki. 

## MathVector
```cpp
LinAlg::MathVector<DataType>
```
- Represents an $n$-dimensional mathematical vector
- Internally uses a `std::vector<DataType>` to store data

### Constructors
- Default constructor; creates a `MathVector` with no elements
```cpp
MathVector::MathVector();
```
<br>

- Creates a `MathVector` with size and elements of given std::vector
```cpp
MathVector::MathVector(const std::vector<DataType>& data_in);
```
<br>

### Public methods
- Returns the data `std::vector`
```cpp
std::vector<DataType> MathVector::getData() const;
```
<br>

- Sets the data `std::vector` to `data_in`
```cpp
void MathVector::setData(const std::vector<DataType>& data_in);
```
<br>

- Returns the number of elements 
```cpp
size_t MathVector::size() const;
```
<br>

- Subscript operator overload for MathVector class, const version; returns element at position index in the data `std::vector`
```cpp
DataType MathVector::operator[](size_t index) const;
```
<br>

- Subscript operator overload for MathVector class, non-const version; returns refernce to element at position index in the data `std::vector`
```cpp
DataType& MathVector::operator[](size_t index);
```
<br>

- Returns a `MathVector` containing elements [first, last)
```cpp
MathVector<DataType> MathVector::getSubVector(const size_t first, 
	const size_t last) const;
```
<br>

- Sets section [first, last) to given `MathVector`
```cpp
void MathVector::setSubVector(const size_t first,
	const size_t last,
	const MathVector<DataType>& new_sub_vec);
```
<br>

- Scales every element of the `MathVector` by the given value
```cpp
void MathVector::scale(const DataType factor);
```
<br>

- Returns this `MathVector` with every element scaled by the given value
```cpp
MathVector<DataType> MathVector::scaled(const DataType factor) const;
```
<br>

- Returns the magnitude of the `MathVector`
```cpp
double MathVector::magnitude() const;
```
<br>

- Returns normalized unit vector form of this `MathVector`, or returns zero vector if this `MathVector` is the zero vector
```cpp
MathVector<double> MathVector::normalized() const;
```
<br>

### Operator overloads and other operations
- == operator overload for `MathVector` class; only use with integral data types
```cpp
inline bool operator==(const MathVector<DataType>& lhs,
	const MathVector<DataType>& rhs);
```
<br>

- != operator overload for MathVector class
```cpp
inline bool operator!=(const MathVector<DataType>& lhs,
	const MathVector<DataType>& rhs);
```
<br>

- Insertion operator overload for MathVector class; outputs MathVector in following format:

$v_1$ <br>
$v_2$ <br>
$\vdots$ <br>
$v_n$ <br>
```cpp
inline std::ostream& operator<<(std::ostream& stream,
	const MathVector<DataType>& vector);
```
<br>

- Addition operator overload for MathVector class; adds vectors element-wise by the mathematical definition of vector addition; throws `InvalidDimension` exception if vectors are not of equal length
```cpp
inline MathVector<DataType> operator+(const MathVector<DataType>& vec1,
	const MathVector<DataType>& vec2);
```
<br>

- Subtraction operator overload for MathVector class; subtracts vectors element-wise; throws `InvalidDimension` exception if vectors are not of equal length
```cpp
inline MathVector<DataType> operator-(const MathVector<DataType>& vec1,
  const MathVector<DataType>& vec2);
```
<br>

- Returns dot product of two given vectors; throws `InvalidDimension` exception if vectors are not of equal length
```cpp
inline DataType dotProduct(const MathVector<DataType>& vec1,
	const MathVector<DataType>& vec2);
```
<br>

- Returns cross product of two given vectors; cross product is only defined for 3-dimensional vectors, so throws `InvalidDimension` exception if vectors are not both of length 3
```cpp
inline MathVector<DataType> crossProduct(const MathVector<DataType>& vec1,
	const MathVector<DataType>& vec2);
```
<br>

## DenseMatrix
`LinAlg::DenseMatrix<DataType>`
- Represents an $n \times m$ matrix
- ELements of matrix is stored in a `std::vector<DataType>`
- Supports both column major and row major storage formats
  - Column major: columns are stored contiguously in data vector
  - Row major: rows are stored contiguously in data vector
- All constructors default to column major storage format if not specified
- Inherits from abstract base class `Matrix` 

### Constructors
- Creates matrix with given data vector, number of rows and columns, and storage format; throws `InvalidDimensions` exception if the size of the data vector doesn't equal the number of rows times the number of columns
```cpp
DenseMatrix::DenseMatrix(const std::vector<DataType>& data_in,
	const size_t rows_in,
	const size_t cols_in,
	const StorageType storage_type_in = StorageType::ColumnMajor);
```
<br>

- Creates matrix with given number of rows and columns and storage format; default initializes all elements in matrix
```cpp
DenseMatrix::DenseMatrix(const size_t rows_in,
	const size_t cols_in,
	const StorageType storage_type_in = StorageType::ColumnMajor);
```
<br>

- Default constructor with optional storage type parameter; creates matrix with 0 elements, rows, and columns
```cpp
DenseMatrix::DenseMatrix(
	const StorageType storage_type_in = StorageType::ColumnMajor);
```
<br>

### Public methods
- Returns data vector where the elements of the matrix are stored
```cpp
std::vector<DataType> DenseMatrix::getData() const;
```
<br>

- Sets data vector to given vector; throws `InvalidDimensions` exception if size of given vector isn't equal to size of matrix
```cpp
void DenseMatrix::setData(const std::vector<DataType>& data_in);
```
<br>

- Returns storage type of matrix, either row major or column major
```cpp
StorageType DenseMatrix::getStorageType() const;
```
<br>

- Converts storage type from column major to row major by rearranging data vector; if storage type is already row major, does nothing
```cpp
void DenseMatrix::convertToRowMajor();
```
<br>

- Const version; returns this matrix in row major storage type
```cpp
DenseMatrix<DataType> DenseMatrix::convertToRowMajor() const;
```
<br>

- Converts storage type from row major to column major by rearranging data vector; if storage type is already column major, does nothing
```cpp
void DenseMatrix::convertToColMajor();
```
<br>

- Const version; returns this matrix in column major storage type
```cpp
DenseMatrix<DataType> DenseMatrix::convertToColMajor() const;
```
<br>

- Returns element in matrix at location (row, col), const version; throws `OutOfBounds` exception if row >= the number of rows or col >= the number of columns in the matrix
```cpp
DataType DenseMatrix::at(const size_t row, const size_t col) const override;
```
<br>

- Returns reference to element at location (row, col), non-const version; throws `OutOfBounds` exception if row >= the number of rows or col >= the number of columns in the matrix
```cpp
DataType& DenseMatrix::at(const size_t row, const size_t col) override;
```
<br>

- Returns row pos as a MathVector; throws `OutOfBounds` exception if pos is >= the number of rows in the matrix
```cpp
MathVector<DataType> DenseMatrix::row(const size_t pos) const override;
```
<br>

- Returns column pos as a MathVector; throws `OutOfBounds` exception if pos is >= the number of columns in the matrix
```cpp
MathVector<DataType> DenseMatrix::col(const size_t pos) const override;
```
<br>

- Sets row pos to given MathVector; throws `OutOfBounds` exception if pos is >= the number of rows in the matrix; throws `InvalidDimensions` if the size of new_row != the number of columns in the matrix
```cpp
void DenseMatrix::setRow(const size_t pos,
  const MathVector<DataType>& new_row) override;
```

- Sets col pos to given MathVector; throws `OutOfBounds` exception if pos is >= the number of columns in the matrix; throws `InvalidDimensions` if the size of new_col != the number of rows in the matrix
```cpp
void DenseMatrix::setCol(const size_t pos,
  const MathVector<DataType>& new_col) override;
```
<br>

- Adds given row to the matrix above row pos; throws `OutOfBounds` exception if pos is > the number of rows in the matrix; throws `InvalidDimensions` if the size of new_row != the number of columns in the matrix
```cpp
void DenseMatrix::addRow(const size_t pos, 
  const MathVector<DataType>& new_row) override;
```
<br>

- Adds given col to the matrix to the left of col pos; throws `OutOfBounds` exception if pos is > the number of columns in the matrix; throws `InvalidDimensions` if the size of new_col != the number of rows in the matrix
```cpp
void DenseMatrix::addCol(const size_t pos, 
	const MathVector<DataType>& new_col) override;
```
<br>

- Removes row pos from the matrix entirely; throws `OutOfBounds` exception if pos is >= the number of rows in the matrix
```cpp
void DenseMatrix::removeRow(const size_t pos) override;
```
<br>

- Removes col pos from the matrix entirely; throws `OutOfBounds` exception if pos is >= the number of columns in the matrix
```cpp
void DenseMatrix::removeCol(const size_t pos) override;
```
<br>

- Swaps the two rows at given positions; throws `OutOfBounds` exception if pos1 or pos2 is >= the number of rows in the matrix
```cpp
void DenseMatrix::swapRows(const size_t pos1, const size_t pos2) override;
```
<br>

- Swaps the two columns at given positions; throws `OutOfBounds` exception if pos1 or pos2 is >= the number of columns in the matrix
```cpp
void DenseMatrix::swapCols(const size_t pos1, const size_t pos2) override;
```
<br>

- Scales row pos by the given factor; throws `OutOfBounds` exception if pos is >= the number of rows in the matrix
```cpp
void DenseMatrix::scaleRow(const size_t pos, const DataType factor) override;
```
<br>

- Scales col pos by the given factor; throws `OutOfBounds` exception if pos is >= the number of columns in the matrix
```cpp
void DenseMatrix::scaleCol(const size_t pos, const DataType factor) override;
```
<br>

- Returns matrix containing rows [first_row, last_row) and columns [first_col, last_col); throws `OutOfBounds` exception if first_row or last_row > the number of rows, or if first_col or last_col > the number of columns
```cpp
DenseMatrix<DataType> DenseMatrix::getSubMatrix(const size_t first_row,
  const size_t last_row,
  const size_t first_col,
  const size_t last_col) const override;
```
<br>

- Sets section of matrix including rows [first_row, last_row) and columns [first_col, last_col) to given matrix; throws `OutOfBounds` exception if first_row or last_row > the number of rows, or if first_col or last_col > the number of columns; throws `InvalidDimensions` exception if the number of rows in new_sub_matrix != last_row - first_col or if the number of columns in new_sub_matrix != last_col - first_col
```cpp
void DenseMatrix::setSubMatrix(const size_t first_row,
  const size_t last_row,
  const size_t first_col,
  const size_t last_col,
  const DenseMatrix<DataType>& new_sub_matrix) override;
```
<br>

### Operator overloads and other operations
- == operator overload for DenseMatrix class; only use with integral data types
```cpp
inline bool operator==(const DenseMatrix<DataType>& lhs,
	const DenseMatrix<DataType>& rhs);
```
<br>

- != operator overload for DenseMatrix class
```cpp
inline bool operator!=(const DenseMatrix<DataType>& lhs,
	const DenseMatrix<DataType>& rhs);
```
<br>

- Insertion operator overload for DenseMatrix class; outputs DenseMatrix in row major format
- Ensures columns are aligned, even with different amounts of digits
```cpp
inline std::ostream& operator<<(std::ostream& stream,
	const DenseMatrix<DataType>& mat);
```
<br>

- Addition overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
```cpp
inline DenseMatrix<DataType> operator+(const DenseMatrix<DataType>& mat1,
	const DenseMatrix<DataType>& mat2);
```
<br>

- Subtraction overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
```cpp
inline DenseMatrix<DataType> operator-(const DenseMatrix<DataType>& mat1,
	const DenseMatrix<DataType>& mat2);
```
<br>

- Matrix multiplication overload for DenseMatrix class; returns a DenseMatrix with the same StorageType as mat1
```cpp
inline DenseMatrix<DataType> operator*(const DenseMatrix<DataType>& mat1,
	const DenseMatrix<DataType>& mat2);
```
<br>

## Linear Equation Solver
- Given a matrix A and vector b representing a system Ax = b, tries to find a unique
solution x to the system; if successful, returns true and puts the solution vector 
into the output parameter x; if not, returns false
- Will only find solution if A is invertible
```cpp
inline bool solveLinearEquation(const DenseMatrix<DataType>& A,
	const MathVector<DataType>& b, 
	MathVector<double>& x);
```
<br>
