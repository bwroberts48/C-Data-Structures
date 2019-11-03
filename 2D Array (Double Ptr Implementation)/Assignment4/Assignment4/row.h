#pragma once
#include "exception.h"

template <typename T>
class Array2D;

template <typename T>
class Row
{
public:
	Row(Array2D<T> & array, int row);
	Row(const Array2D<T> & array, int row);
	T & operator [](int column);
	const T & operator [](int column) const;
private:
	const int m_row;
	const Array2D<T> & m_array2D;
};

template <typename T>
Row<T>::Row(Array2D<T> & array, int row) : m_array2D(array), m_row(row)
{}

template <typename T>
Row<T>::Row(const Array2D<T> & array, int row)
{}

template <typename T>
T & Row<T>::operator [](int column)
{
	if (column > m_array2D.GetColumns())
		throw Exception("Column out of bounds");
	return const_cast<T&>(m_array2D.Select(m_row, column));
}

template <typename T>
const T & Row<T>::operator [](int column) const
{
	if (column > m_array2D.GetColumns())
		throw Exception("Column out of bounds");
	return m_array2D.Select(m_row, column);
}