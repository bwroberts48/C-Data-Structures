/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		array.h
* Date Created: 1/7/2019
*
* Class: Array
*
* Purpose: Makes a 1D templated dynamic array 
*
* Manager functions:
*	Array();
*		The default length and start index is 0
*	Array(int length, int start_index = 0)
*		Creates an array based on given length and a default start_index of 0 with the option to base it on a given value
*	Array(const Array & copy)	
*	~Array()
*	Array & operator =(const Array & rhs)
* Methods:
*	T & operator [](int index) const
*	int GetStartIndex() const
*	void SetStartIndex(int start_index)
*	int GetLength() const
*	void SetLength(int length)
*		Creates a temp Array object of the specified length and copies data over to it from the current array, either cutting off data or adding blank indicies
***********************************************************************************************************************************************************************************************************************/
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

/********************************************************************************************************************************************************************
* Purpose: Allows the user to construct an object with a given start_index and length instead of forcing them to use multiple functions after the object is made
*
* Precondition:
*	None	
*
* Postcondition:
*	Array object is created with given characteristics
*********************************************************************************************************************************************************************/
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

/********************************************************************************************************************************************************************
* Purpose: Lets the user access an element of the array as they would a normal array
*
* Precondition:
*	Array object must be instantiated to access its bounds
*
* Postcondition:
*	If the index is out of the array's bounds an exception will be thrown that needs to be handeled
*	Otherwise, it returns the data at the wanted index of the array
*********************************************************************************************************************************************************************/
template <typename T>
inline T & Array<T>::operator [](int index) const
{
	if (index < m_start_index || index >= m_start_index + m_length)
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

/********************************************************************************************************************************************************************
* Purpose: Allows the user to alter the bounds of the array
*
* Precondition:
*	None
*
* Postcondition:
*	If the length given is negative, an Exception will be thrown that needs to be handeled
*	Otherwise, it will set m_array equal to a new array where all data is copied. If the new length is larger than m_array was than new indicies are made otherwise
*		indicies are cut off the end of the original.
*********************************************************************************************************************************************************************/
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
