#pragma once

#include "array.h"
#include "exception.h"
template <typename T>
class ArrQueue
{
public:
	ArrQueue(int size);
	~ArrQueue();
	ArrQueue(const ArrQueue & copy);
	ArrQueue & operator =(const ArrQueue & copy);
	void Enqueue(const T & data);
	T Dequeue();
	T & Front();
	bool isFull();
	inline bool isEmpty() { return m_tail_index == -1 ? true : false; }
	inline int Size() { return m_size; }
private:
	Array<T> m_array;
	int m_size;
	int m_front_index;
	int m_tail_index;
};

template<typename T>
ArrQueue<T>::ArrQueue(int size) : m_array(size), m_size(size), m_front_index(-1), m_tail_index(-1)
{}

template<typename T>
ArrQueue<T>::~ArrQueue()
{
	m_size = 0;
	m_front_index = -1;
	m_tail_index = -1;
}

template<typename T>
ArrQueue<T>::ArrQueue(const ArrQueue & copy) : m_array(copy.m_array), m_size(copy.m_size), m_front_index(copy.m_front_index), m_tail_index(copy.m_tail_index)
{}

template<typename T>
ArrQueue<T> & ArrQueue<T>::operator=(const ArrQueue & rhs)
{
	if (&rhs != this)
	{
		m_array = rhs.m_array;
		m_size = rhs.m_size;
		m_front_index = rhs.m_front_index;
		m_tail_index = rhs.m_tail_index;
	}
	return *this;
}

template<typename T>
void ArrQueue<T>::Enqueue(const T & data)
{
	if (isFull())
		throw Exception("Overflow Occured");
	if (isEmpty())
	{
		m_tail_index = 0;
		m_front_index = 0;
	}
	else if (m_tail_index == 0 && m_front_index != 0) //If the tail is at the end of the array
		m_tail_index = m_size - 1; //Wrap it around to the last index
	else
		m_tail_index++;

	m_array[m_tail_index] = data;
}

template<typename T>
T ArrQueue<T>::Dequeue()
{
	if (isEmpty())
		throw Exception("Underflow Occured");
	T data = m_array[m_front_index];
	int tarIndex;
	if (m_front_index == m_tail_index)
	{
		tarIndex = m_tail_index;
		m_tail_index = -1;
		m_front_index = -1;
	}
	else if (m_front_index == m_size - 1) //If the head is at the end of the array wrap it around to the first index
	{
		m_front_index = 0;
		tarIndex = m_size - 1;
	}
	else
	{
		tarIndex = m_front_index;
		m_front_index++;
	}

	return m_array[tarIndex];
}

template<typename T>
T & ArrQueue<T>::Front()
{
	if (isEmpty())
		throw Exception("Cannot Return from Empty Stack");
	return m_array[m_front_index];
}

template<typename T>
bool ArrQueue<T>::isFull()
{
	bool full = false;
	if (m_front_index < m_tail_index && m_tail_index - m_front_index == m_size - 1) //If the head and tail are at the start and end (respectively) of the array indices
		full = true;
	else if (m_front_index > m_tail_index && m_front_index == m_tail_index + 1) //If the head has circled to be larger than the tail it must be directly infront of the tail for the queue to be full
		full = true;
	return full;
}