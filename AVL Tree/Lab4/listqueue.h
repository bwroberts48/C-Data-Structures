/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		listqueue.h
* Date:			1/10/2019
* Class: ListQueue
*
* Purpose: Creates a queue based on a doubly linked list
*
* Manager functions:
*	ListQueue()
*		Intializes the list to a default list (no nodes) and size to 0
*	~ListQueue()
*	ListQueue(const ListQueue & copy)
*	ListQueue & operator =(const ListQueue & rhs)
* Methods:
*	void Enqueue(const T & data)
*		Enqueues the given data onto the end of the queue
*	T Dequeue()
*		Dequeues data off the front of the stack
*	T & Front()
*		Returns the data at the front of the queue
*	int Size()
*		Returns the size of the stack
*	bool isEmpty()
*		Checks if the stack is empty or not
***********************************************************************************************************************************************************************************************************************/
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
	inline bool isEmpty() { return m_list.isEmpty(); }
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

/********************************************************************************************************************************************************************
* Purpose: Allows the user to move data to the end of the stack
*
* Precondition:
*	None
*
* Postcondition:
*	Adds the data to the end of the queue and increases size
*********************************************************************************************************************************************************************/
template <typename T>
void ListQueue<T>::Enqueue(const T & data)
{
	m_list.Append(data);
	m_size++;
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to move data off the front of the queue
*
* Precondition:
*	The stack must not be empty so that there is data to take off
*
* Postcondition:
*	Returns the data from the top of the stack and takes the data off of the stack
*	If the queue is empty an Underflow exception occurs
*********************************************************************************************************************************************************************/
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

/********************************************************************************************************************************************************************
* Purpose: Allows the user to look at the data from the front of the queue
*
* Precondition:
*	The queue must not be empty so that there is data to peek at
*
* Postcondition:
*	Returns the data from the top of the queue
*	If the queue is empty an exception occurs
*********************************************************************************************************************************************************************/
template <typename T>
T & ListQueue<T>::Front()
{
	if (isEmpty())
		throw Exception("The Queue is Empty");
	return const_cast<T&>(m_list.First());
}
