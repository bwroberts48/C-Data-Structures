#pragma once
#pragma once
#include "array.h"
#include "row.h"
template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int col = 0);
	Array2D(const Array2D & copy);
	~Array2D();
	Array2D & operator =(const Array2D & rhs);
	Row<T> operator [](int index);
	const Row<T> operator [](int index) const;
	int GetRow() const;
	void SetRows(int rows);
	int GetColumns() const;
	void SetColumns(int columns);
	T & Select(int row, int column);
	const T & Select(int row, int column) const;
private:
	Array<T> m_array;
	int m_row;
	int m_col;
};

template <typename T>
Array2D<T>::Array2D() : m_row(0), m_col(0)
{}

template <typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col), m_array(row * col)
{
	if (row < 0)
		throw Exception("Rows cannot be less than Zero");
	if (col < 0)
		throw Exception("Columns cannot be less than Zero");
}

template <typename T>
Array2D<T>::Array2D(const Array2D & copy) : m_array(copy.m_array), m_row(copy.m_row), m_col(copy.m_col)
{}

template <typename T>
Array2D<T>::~Array2D()
{}

template <typename T>
Array2D<T> & Array2D<T>::operator =(const Array2D & rhs)
{
	if (&rhs != this)
	{
		m_array = rhs.m_array;
		m_row = rhs.m_row;
		m_col = rhs.m_col;
	}
	return *this;
}

template <typename T>
Row<T> Array2D<T>::operator [](int index)
{
	return Row<T>(*this, index);
}

template <typename T>
const Row<T> Array2D<T>::operator [](int index) const
{
	return Row<T>(*this, index);
}

template <typename T>
int Array2D<T>::GetRow() const
{
	return m_row;
}

template <typename T>
void Array2D<T>::SetRows(int rows)
{
	if (rows < 0)
		throw Exception("Cannot set rows to less than 0");
	else if (rows == 0)// Clears the list if rows are equal to 0 and sets m_row to zero
	{
		m_row = 0;
		m_array.SetLength(0);
	}
	else
	{
		m_row = rows;
		m_array.SetLength(m_row * m_col);
	}
}

template <typename T>
int Array2D<T>::GetColumns() const
{
	return m_col;
}

template <typename T>
void Array2D<T>::SetColumns(int columns)
{
	if (columns < 0)
		throw Exception("Cannot set columns to less than 0");
	if (columns == 0)
		m_array.SetLength(0);
	else
	{
		Array<T> newArr(m_row * columns);

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < (m_col < columns ? m_col : columns); j++)
			{
				newArr[i * columns + j] = m_array[i * m_col + j];
			}
		}
		m_array = newArr;
		m_col = columns;
	}

}

template <typename T>
T & Array2D<T>::Select(int row, int column)
{
	if (row < 0)
		throw Exception("Rows cannot be less than 0");
	else if (column < 0)
		throw Exception("Columns cannot be less than 0");

	return m_array[row * m_col + column];
}

template <typename T>
const T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0)
		throw Exception("Rows cannot be less than 0");
	else if (column < 0)
		throw Exception("Columns cannot be less than 0");
	return m_array[row * m_col + column];
}