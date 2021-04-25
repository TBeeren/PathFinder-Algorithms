#include <cassert>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <utility>
#include <iomanip>

/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(T value)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at(row).at(column) = value;
		}
	}
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(const std::initializer_list<T> &aList)
{
	// Check the arguments
	assert(aList.size() == M * N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column, ++row_iter)
		{
			matrix.at(row).at(column) = *row_iter;
		}
	}
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(const std::initializer_list<std::initializer_list<T>> &aList)
{
	// Check the arguments, the static assert assures that there is at least 1 M and 1 N!
	assert(aList.size() == M);
	assert((*aList.begin()).size() == N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < aList.size(); ++row, ++row_iter)
	{
		auto column_iter = (*row_iter).begin();
		for (std::size_t column = 0; column < (*row_iter).size(); ++column, ++column_iter)
		{
			matrix.at(row).at(column) = *column_iter;
		}
	}
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N>::Matrix(const Matrix<T, M, N> &aMatrix) : matrix(aMatrix.matrix)
{
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
std::array<T, N> &Matrix<T, M, N>::at(std::size_t aRowIndex)
{
	return matrix.at(aRowIndex);
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
const std::array<T, N> &Matrix<T, M, N>::at(std::size_t aRowIndex) const
{
	return matrix.at(aRowIndex);
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
T &Matrix<T, M, N>::at(std::size_t aRowIndex,
					   std::size_t aColumnIndex)
{
	return matrix.at(aRowIndex).at(aColumnIndex);
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
const T &Matrix<T, M, N>::at(std::size_t aRowIndex,
							 std::size_t aColumnIndex) const
{
	return matrix.at(aRowIndex).at(aColumnIndex);
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
std::array<T, N> &Matrix<T, M, N>::operator[](std::size_t aRowIndex)
{
	return matrix[aRowIndex];
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
const std::array<T, N> &Matrix<T, M, N>::operator[](std::size_t aRowIndex) const
{
	return matrix[aRowIndex];
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator=(const Matrix<T, M, N> &rhs)
{
	if (this != &rhs)
	{
		matrix = rhs.matrix;
	}
	return *this;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
bool Matrix<T, M, N>::operator==(const Matrix<T, M, N> &rhs) const
{
	return matrix == rhs.matrix;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
template <class T2>
Matrix<T, M, N> &Matrix<T, M, N>::operator*=(const T2 &scalar)
{
	static_assert(std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at(row).at(column) *= scalar;
		}
	}

	return *this;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
template <class T2>
Matrix<T, M, N> Matrix<T, M, N>::operator*(const T2 &scalar) const
{
	static_assert(std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix<T, M, N> result(*this);
	return result *= scalar;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
template <class T2>
Matrix<T, M, N> &Matrix<T, M, N>::operator/=(const T2 &aScalar)
{
	static_assert(std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at(row).at(column) /= aScalar;
		}
	}
	return *this;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
template <class T2>
Matrix<T, M, N> Matrix<T, M, N>::operator/(const T2 &aScalar) const
{
	static_assert(std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix<T, M, N> result(*this);
	return result /= aScalar;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const Matrix<T, M, N> &rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] += rhs.at(row, column);
		}
	}
	return *this;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix<T, M, N> &rhs) const
{
	Matrix<T, M, N> result(*this);
	return result += rhs;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const Matrix<T, M, N> &rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] -= rhs.at(row, column);
		}
	}
	return *this;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix<T, M, N> &rhs) const
{
	Matrix<T, M, N> result(*this);
	return result -= rhs;
}
/** TODO: MAybe sucks
 * (M, N) * (N, P) -> (M, P)
 */
template <typename T, std::size_t M, std::size_t N>
template <std::size_t columns>
Matrix<T, M, columns> Matrix<T, M, N>::operator*(const Matrix<T, N, columns> &rhs) const
{
	Matrix<T, M, columns> result;
	
	//loop through all result columns
	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < columns; ++column)
		//loop thrugh all result rows
		{
			float cellResult = 0.0;
			for (int i = 0; i < N; ++i)
			{
				cellResult += this->at(row, i) * rhs.at(i, column);
			}
			result.at(row, column) = cellResult;
		}
	}
	return result;
}
/**
 * TODO: might suck
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, N, M> Matrix<T, M, N>::transpose() const
{
	Matrix<T, N, M> result;
	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			result.at(column, row) = this->at(row, column);
		}
	}
	return result;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::identity() const
{
	Matrix<T, N, M> result(0);
	for (int i = 0; i < M; ++i)
	{
		result.at(i, i) = 1;
	}
	return result;
}
/**
 * TODO: naamgeving and no way this is efficient
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::gauss() const
{
	Matrix<T, M, N> result = *this;
	for (int pivot_itr = 0; pivot_itr < M; ++pivot_itr)
	{
		T pivotValue = result.at(pivot_itr, pivot_itr);
		//pivotValue can't be zero, if it is we swap
		if (pivotValue == 0)
		{
			int swapRow = pivot_itr;
			for (int i = pivot_itr; i < M; ++i)
			{
				if (fabs(result.at(i, pivot_itr)) > pivotValue)
				{
					pivotValue = result.at(i, pivot_itr);
					swapRow = i;
				}
			}
			for (int i = 0; i < N; ++i)
			{
				T tempValue = result.at(pivot_itr, i);
				result.at(pivot_itr, i) = result.at(swapRow, i);
				result.at(swapRow, i) = tempValue;
			}
		}

		for (int column = 0; column < N; ++column)
		{
			result.at(pivot_itr, column) = result.at(pivot_itr, column) / pivotValue;
		}

		for (int row = pivot_itr + 1; row < M; ++row)
		{
			T amount = result.at(row, pivot_itr);
			for (int column = 0; column < N; ++column)
			{
				result.at(row, column) = result.at(row, column) - (amount * result.at(pivot_itr, column));
			}
		}
	}
	return result;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::gaussJordan() const
{
	Matrix<T, M, N> result = *this;
	for (int pivot_itr = 0; pivot_itr < M; ++pivot_itr)
	{
		T pivotValue = result.at(pivot_itr, pivot_itr);
		//pivotValue can't be zero, if it is we swap
		if (pivotValue == 0)
		{
			int swapRow = pivot_itr;
			for (int i = pivot_itr; i < M; ++i)
			{
				if (fabs(result.at(i, pivot_itr)) > pivotValue)
				{
					pivotValue = result.at(i, pivot_itr);
					swapRow = i;
				}
			}
			for (int i = 0; i < N; ++i)
			{
				T tempValue = result.at(pivot_itr, i);
				result.at(pivot_itr, i) = result.at(swapRow, i);
				result.at(swapRow, i) = tempValue;
			}
		}

		for (int column = 0; column < N; ++column)
		{
			result.at(pivot_itr, column) = result.at(pivot_itr, column) / pivotValue;
		}

		for (int row = 0; row < M; ++row)
		{
			if (row != pivot_itr)
			{
				T amount = result.at(row, pivot_itr);
				for (int column = 0; column < N; ++column)
				{
					result.at(row, column) = result.at(row, column) - (amount * result.at(pivot_itr, column));
				}
			}
		}
	}
	return result;
}
/**
 *

 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, 1> Matrix<T, M, N>::solve() const
{
	// TODO Implement this function
	Matrix<T, M, 1> result;
	Matrix<T, M, N> jordaned = this->gaussJordan();

	for(int i = 0; i < M; ++i)
	{
		result.at(i,0) = jordaned.at(i, N - 1);
	}

	return result;
}
/**
 * TODO: check if square?
 */
template <class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::inverse() const
{
	Matrix<T, M, 2 * N> extendedMatrix;

	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			extendedMatrix.at(row, column) = this->at(row, column);
		}
	}

	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			if (row == column)
			{
				extendedMatrix.at(row, column + N) = 1;
			}
			else
			{
				extendedMatrix.at(row, column + N) = 0;
			}
		}
	}
	extendedMatrix = extendedMatrix.gaussJordan();
	Matrix<T, M, N> result;
	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			result.at(row, column) = extendedMatrix.at(row, column + N);
		}
	}

	return result;
}
/**
 *
 */
template <class T, std::size_t M, std::size_t N>
std::string Matrix<T, M, N>::to_string() const
{
	std::string result = "Matrix<" + std::to_string(N) + "," + std::to_string(M) + ">\n{\n";
	for (std::size_t i = 0; i < M; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			result += std::to_string(matrix[i][j]) + ",";
		}
		result += "\n";
	}
	result += "}";
	return result;
}
/**
 *
 */
template <typename T, const std::size_t N>
bool equals(const Matrix<T, 1, N> &lhs,
			const Matrix<T, 1, N> &rhs,
			const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
			const unsigned long aFactor /*= 1*/)
{
	for (int column = 0; column < N; ++column)
	{
		if (lhs.at(0, column) <= rhs.at(0, column) - aPrecision * aFactor || lhs.at(0, column) >= rhs.at(0, column) + aPrecision * aFactor)
		{
			return false;
		}
	}
	return true;
}
/**
 *
 */
template <typename T, const std::size_t M>
bool equals(const Matrix<T, M, 1> &lhs,
			const Matrix<T, M, 1> &rhs,
			const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
			const unsigned long aFactor /*= 1*/)
{
	for (int row = 0; row < M; ++row)
	{
		if (lhs.at(row, 0) <= rhs.at(row, 0) - aPrecision * aFactor || lhs.at(row, 0) >= rhs.at(row, 0) + aPrecision * aFactor)
		{
			return false;
		}
	}
	return true;
}
/**
 *
 */
template <typename T, const std::size_t M, const std::size_t N>
bool equals(const Matrix<T, M, N> &lhs,
			const Matrix<T, M, N> &rhs,
			const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
			const unsigned long aFactor /*= 1*/)
{
	for (int row = 0; row < M; ++row)
	{
		for (int column = 0; column < N; ++column)
		{
			if (lhs.at(row, column) <= rhs.at(row, column) - aPrecision * aFactor || lhs.at(row, column) >= rhs.at(row, column) + aPrecision * aFactor)
			{
				return false;
			}
		}
	}
	return true;
}
