/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		node.h
* Date:			1/10/2019
* Class: Node (friend of the List class)
*
* Purpose: Is the node for the List class(doubly linked)
*
* Manager functions:
*		Node()
*			Sets data, next, and previous to nullptr
*		Node(T data)
*			Sets the nodes data to the data passed through
*		~Node()
*		Node(const Node & copy)
*		Node & operator =(const Node & rhs)
*
* Methods:
*		None
***********************************************************************************************************************************************************************************************************************/
#pragma once
template <typename T> class List;

template <typename T> 
class Node
{
friend class List<T>;

private:
	Node();
	Node(T data);
	~Node();
	Node(const Node & copy);
	Node & operator =(const Node & rhs);

	T m_data;
	Node * m_next;
	Node * m_prev;
};

template <typename T>
Node<T>::Node() : m_data(nullptr), m_next(nullptr), m_prev(nullptr)
{}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to construct an object with a given state
*
* Precondition:
*	None
*
* Postcondition:
*	A Node object is created with data
*********************************************************************************************************************************************************************/
template <typename T>
Node<T>::Node(T data) : m_data(data), m_next(nullptr), m_prev(nullptr)
{}

template <typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_prev = nullptr;
}

template <typename T>
Node<T>::Node(const Node & copy) : m_data(copy.m_data), m_next(copy.m_next), m_prev(copy.m_prev)
{}

template <typename T>
Node<T> & Node<T>::operator =(const Node & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
	}
	return *this;
}


