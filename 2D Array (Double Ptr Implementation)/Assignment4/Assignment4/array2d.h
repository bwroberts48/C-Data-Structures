#pragma once
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
	T** m_array;
	int m_row;
	int m_col;
};

template <typename T>
Array2D<T>::Array2D() : m_array(nullptr), m_row(0), m_col(0)
{}

template <typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col), m_array(nullptr)
{
	if (row < 0)
	{
		throw Exception("Rows cannot be less than Zero");
		m_row = 0;
	}
	if (col < 0)
	{
		throw Exception("Columns cannot be less than Zero");
		m_col = 0;
	}
	m_array = new T*[m_row];
	for (int i = 0; i < m_row; i++)
		m_array[i] = new T[m_col];
}

template <typename T>
Array2D<T>::Array2D(const Array2D & copy) : m_array(nullptr), m_row(copy.m_row), m_col(copy.m_col)
{
	m_array = new T*[m_row]; //Resize m_array
	for (int i = 0; i < m_row; i++)
		m_array[i] = new T[m_col];
	
	for (int j = 0; j < m_row; j++)	//Copy over data to m_array
	{
		for (int k = 0; k < m_col; k++)
		{
			m_array[j][k] = copy.m_array[j][k];
		}
	}
	
}

template <typename T>
Array2D<T>::~Array2D()
{
	for (int i = 0; i < m_row; i++)
		delete[] m_array[i];
	delete[] m_array;
	m_array = nullptr;
	m_row = 0;
	m_col = 0;
}

template <typename T>
Array2D<T> & Array2D<T>::operator =(const Array2D & rhs)
{
	if (&rhs != this)
	{
		for (int i = 0; i < m_row; i++)	//Wipe current array and set member vars to default
			delete[] m_array[i];
		m_array = nullptr;
		m_row = rhs.m_row;
		m_col = rhs.m_col;

		m_array = new T*[m_row]; //Resize m_array
		for (int i = 0; i < m_row; i++)
			m_array[i] = new T[m_col];

		for (int j = 0; j < m_row; j++)	//Copy over data to m_array
		{
			for (int k = 0; k < m_col; k++)
			{
				m_array[j][k] = rhs.m_array[j][k];
			}
		}
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

	else
	{
		T** temp = new T*[rows];	//Set rows and columns for new T**
		for (int i = 0; i < rows; i++) 
			temp[i] = new T[m_col];

		for (int j = 0; j < (m_row < rows ? m_row : rows); j++) //Scan rows
		{
			for (int k = 0; k < m_col; k++) //Scan columns
				temp[j][k] = m_array[j][k]; //Copy data
		}

		for (int i = 0; i < m_row; i++) //Delete memory allocated to original m_array
			delete[] m_array[i];
		delete[] m_array;
		m_array = temp;
		m_row = rows;
		
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

	else
	{
		T** temp = new T*[m_row];	//Set rows and columns for new T**
		for (int i = 0; i < m_row; i++)
			temp[i] = new T[columns];

		for (int j = 0; j < m_row; j++) //Scan rows
		{
			for (int k = 0; k < (m_col < columns ? m_col : columns); k++) //Scan columns
				temp[j][k] = m_array[j][k]; //Copy data
		}

		for (int l = 0; l < m_row; l++) //Delete memory allocated to original m_array
			delete[] m_array[l];
		delete[] m_array;
		m_array = temp;
		m_col = columns;
	}

}

template <typename T>
T & Array2D<T>::Select(int row, int column)
{
	if (row < 0 || row > m_row)
		throw Exception("Row out bounds");
	else if (column < 0 || column > m_col)
		throw Exception("Columns out bounds");

	return m_array[row][column];
}

template <typename T>
const T & Array2D<T>::Select(int row, int column) const
{
	if (row < 0 || row > m_row)
		throw Exception("Row out bounds");
	else if (column < 0 || column > m_col)
		throw Exception("Columns out bounds");

	return m_array[row][column];
}