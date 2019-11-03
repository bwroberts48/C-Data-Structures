#pragma once
#include "array.h"
#include "exception.h"

template <typename T>
class ArrStack
{
public:
	ArrStack();
	ArrStack(int size);
	~ArrStack();
	ArrStack(const ArrStack & copy);
	ArrStack & operator = (const ArrStack & rhs);
	void Push(const T & data);
	T Pop();
	T Peek();
	int Size();
	bool isEmpty();
	bool isFull();
	void SetSize(int size);
private:
	Array<T> m_array;
	int m_topIndex;
};

template <typename T>
ArrStack<T>::ArrStack() : m_topIndex(-1)
{}

template <typename T>
ArrStack<T>::ArrStack(int size) : m_array(size), m_topIndex(-1)
{}

template <typename T>
ArrStack<T>::~ArrStack()
{
	m_topIndex = -1;
}

template <typename T>
ArrStack<T>::ArrStack(const ArrStack & copy) : m_array(copy.m_array), m_topIndex(copy.m_topIndex)
{}

template <typename T>
ArrStack<T> & ArrStack<T>::operator = (const ArrStack & rhs)
{
	if (&rhs != this)
	{
		m_array = rhs.m_array;
		m_topIndex = rhs.m_topIndex;
	}
	return *this;
}
template <typename T>
void ArrStack<T>::Push(const T & data)
{
	if (m_topIndex == m_array.GetLength() - 1) 
		throw Exception("Overflow Occured");
	m_topIndex++;
	m_array[m_topIndex] = data;
}

template <typename T>
T ArrStack<T>::Pop()
{
	if (isEmpty())
		throw Exception("Underflow Occured");
	m_topIndex--;			//Move the top of the stack down and return the data that was the top previously
	return m_array[m_topIndex + 1];
}
template <typename T>
T ArrStack<T>::Peek()
{
	if (!isEmpty())
	{
		return m_array[m_topIndex];
	}
}

template <typename T>
int ArrStack<T>::Size()
{
	return m_array.GetLength();
}

template <typename T>
bool ArrStack<T>::isEmpty()
{
	bool empty = false;
	if (m_topIndex == -1) //If top index doesn't point to a valid index
		empty = true;
	return empty;
}

template <typename T>
bool ArrStack<T>::isFull()
{
	bool full = false;
	if (m_topIndex == m_array.GetLength() - 1) //If the top of the stack is the last index of the array it is full
		full = true;
	return full;
}

template <typename T>
void ArrStack<T>::SetSize(int size)
{
	if (size - 1 < m_topIndex) // If the new size doesn't allow for the current index move m_topIndex to the new top of the resized stack
		m_topIndex = size - 1;

	m_array.SetLength(size);
}
