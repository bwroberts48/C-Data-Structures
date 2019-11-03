#pragma once
#include "list.h"
#include "exception.h"

template <typename T>
class ListQueue
{
public:
	ListQueue();
	~ListQueue();
	ListQueue(const ListQueue & copy);
	ListQueue & operator =(const ListQueue & rhs);
	void Enqueue(const T & data);
	T Dequeue();
	T & Front();
	inline int Size() { return m_size; }
	inline bool isEmpty() const { return m_list.IsEmpty(); }
private:
	List<T> m_list;
	int m_size;
};

template <typename T>
ListQueue<T>::ListQueue() : m_list(), m_size(0)
{}

template <typename T>
ListQueue<T>::~ListQueue()
{
	m_size = 0;
}

template <typename T>
ListQueue<T>::ListQueue(const ListQueue & copy) : m_list(copy.m_list), m_size(copy.m_size)
{}

template <typename T>
ListQueue<T> & ListQueue<T>::operator =(const ListQueue & rhs)
{
	if (&rhs != this)
	{
		m_list = rhs.m_list;
		m_size = rhs.m_size;
	}
	return *this;
}

template <typename T>
void ListQueue<T>::Enqueue(const T & data)
{
	m_list.Append(data);
	m_size++;
}

template <typename T>
T ListQueue<T>::Dequeue()
{
	if (isEmpty())
		throw Exception("Underflow Occured\n");
	T data = m_list.First();
	m_list.Extract(m_list.First());
	m_size--;
	return data;
}

template <typename T>
T & ListQueue<T>::Front()
{
	if (isEmpty())
		throw Exception("Cannot Look at the Front of an Empty Queue");
	return const_cast<T&>(m_list.First());
}
