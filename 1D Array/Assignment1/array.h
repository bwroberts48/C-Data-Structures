#pragma once
#include "exception.h"
template <typename T> 
class Array
{
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & copy);
	~Array();
	Array & operator =(const Array & rhs);
	T & operator [](int index) const;
	int GetStartIndex() const;
	void SetStartIndex(int start_index);
	int GetLength() const;
	void SetLength(int length);
private:
	T * m_array;
	int m_length;
	int m_start_index;
};

template <typename T>
inline Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{}

template <typename T>
inline Array<T>::Array(int length, int start_index) : m_array(nullptr), m_length(length), m_start_index(start_index)
{
	m_array = new T[length];
}

template <typename T>
inline Array<T>::Array(const Array & copy) : m_length(copy.m_length), m_start_index(copy.m_start_index), m_array(nullptr)
{
	m_array = new T[copy.m_length];
	for (int i = copy.m_start_index; i < copy.m_length; i++)
	{
		m_array[i] = copy.m_array[i];
	}

}

template <typename T>
inline Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

template <typename T>
inline Array<T> & Array<T>::operator =(const Array & rhs)
{
	if (&rhs != this)
	{
		delete[] m_array;
		m_array = nullptr;

		m_array = new T[rhs.m_length];
		for (int i = 0; i < rhs.m_length; i++)
		{
			m_array[i] = rhs.m_array[i];
		}
		m_start_index = rhs.m_start_index;
		m_length = rhs.m_length;
	}
	return *this;
}

template <typename T>
inline T & Array<T>::operator [](int index) const
{
	if (index < m_start_index || index > m_start_index + m_length)
	{
		throw Exception("Index out of bounds");
	}

	return m_array[index - m_start_index];
}

template <typename T>
inline int Array<T>::GetStartIndex() const
{
	return m_start_index;
}

template <typename T>
inline void Array<T>::SetStartIndex(int start_index)
{
	m_start_index = start_index;
}

template <typename T>
inline int Array<T>::GetLength() const
{
	return m_length;
}

template <typename T>
inline void Array<T>::SetLength(int length)
{
	if (length < 0)
		throw Exception("Length must be non-negative");
	else
	{
		T * temp = new T[length];
		int smallerLength = length > m_length ? m_length : length;
		for (int i = 0; i < smallerLength; i++) 
			{
				temp[i] = m_array[i];
			}
		delete[] m_array;
		m_length = length;
		m_array = temp;
	}
}
