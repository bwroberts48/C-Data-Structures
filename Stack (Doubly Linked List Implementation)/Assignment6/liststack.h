#pragma once
#include "list.h"
#include "exception.h"

template <typename T>
class ListStack
{
public:
	ListStack();
	~ListStack();
	ListStack(const ListStack & copy);
	ListStack & operator = (const ListStack & rhs);
	void Push(const T & data);
	T Pop();
	T Peek();
	int Size();
	bool isEmpty();
private:
	List<T> m_list;
	int m_size;
};

template <typename T>
ListStack<T>::ListStack() : m_list(), m_size(0)
{}

template <typename T>
ListStack<T>::~ListStack()
{
	m_size = 0;
}

template <typename T>
ListStack<T>::ListStack(const ListStack & copy) : m_list(copy.m_list), m_size(copy.m_size)
{}

template <typename T>
ListStack<T> & ListStack<T>::operator =(const ListStack & rhs)
{
	if (&rhs != this)
	{
		m_list = rhs.m_list;
		m_size = rhs.m_size;
	}
	return *this;
}

template <typename T>
void ListStack<T>::Push(const T & data)
{
	m_list.Prepend(data);
	m_size++;
}

template <typename T>
T ListStack<T>::Pop()
{
	if (m_list.isEmpty())
		throw Exception("Underflow Occured");

	T data = m_list.First();
	m_list.Extract(m_list.First());
	m_size--;
	return data;
}

template <typename T>
T ListStack<T>::Peek()
{
	return m_list.First();
}

template <typename T>
int ListStack<T>::Size()
{
	return m_size;
}

template <typename T>
bool ListStack<T>::isEmpty()
{
	return m_list.isEmpty();
}