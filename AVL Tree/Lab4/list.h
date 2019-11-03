/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		list.h
* Date:			1/10/2019
* Class: List
*
* Purpose: Creates a doubly linked list
*
* Manager functions:
*	List()
*		Sets the head and tail pointers to nullptr
*	~List()
*	List(const List & copy)
*	List & operator =(const List & rhs)
* Methods:
*	void Purge()
*		Deletes each node of the LinkedList
*	void Prepend(T data)
*		Adds a node to the beginning of the list
*	void Append(T data)
*		Adds a node to the end of the list
*	void Extract(T target)
*		Extracts the given data from the list
*	void InsertAfter(T newData, T target)
*		Inserts given data after the target data passed through
*	void InsertBefore(T newData, T target)
*		Inserts given data before the target data passed through
*	bool isEmpty()
*		Checks if the list is empty
*	const T & First()
*		returns the data stored in the head of the list
*   const T & Last()
*		returns the data stored in the tail of the list
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include <iostream>
#include "node.h"
#include "exception.h"
using std::cout;
using std::endl;

template <typename T> 
class List
{
public:
	List();
	~List();
	void Purge();
	List(const List & copy);
	List & operator = (const List & rhs);
	void Prepend(T data);
	void Append(T data);
	void Extract(T target);
	void InsertAfter(T newData, T target);
	void InsertBefore(T newData, T target);
	bool isEmpty();
	inline const T & First() { return m_head->m_data; }
	inline const T & Last() { return m_tail->m_data; }

private:
	Node<T> * m_head;
	Node<T> * m_tail;
};

template <typename T>
List<T>::List() : m_head(nullptr), m_tail(nullptr)
{}

template <typename T>
List<T>::~List()
{
	Purge();
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: To delete all Nodes from the list
*
* Precondition:
*		None
*
* Postcondition:
*		The LinkedList no longer has any nodes and the node memory is freed
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::Purge()
{
	Node<T> * trail = m_head;

	while (m_head != nullptr)
	{
		m_head = m_head->m_next;
		delete trail;
		trail = m_head;
	}
	m_head = nullptr;
	m_tail = nullptr;
}

template <typename T>
List<T>::List(const List & copy) : m_head(nullptr), m_tail(nullptr)
{
	Node<T> * travel = copy.m_head;
	Node<T> * new_travel = m_head;
	Node<T> * new_trail = nullptr;

	if (copy.m_head != nullptr)
	{
		m_head = new Node<T>(travel->m_data);
		new_travel = m_head;
		travel = travel->m_next;

		while (travel != nullptr)
		{
			new_travel->m_next = new Node<T>(travel->m_data);
			new_trail = new_travel;
			new_travel = new_travel->m_next;
			new_travel->m_prev = new_trail;
			travel = travel->m_next;
		}
		m_tail = new_travel;
	}
}

template <typename T>
List<T> & List<T>::operator = (const List & rhs)
{
	if (this != &rhs)
	{
		Purge();

		Node<T> * travel = rhs.m_head;
		Node<T> * new_travel = m_head;
		Node<T> * new_trail = nullptr;

		if (rhs.m_head != nullptr)
		{
			m_head = new Node<T>(travel->m_data);
			new_travel = m_head;
			travel = travel->m_next;

			while (travel != nullptr)
			{
				new_travel->m_next = new Node<T>(travel->m_data);
				new_trail = new_travel;
				new_travel = new_travel->m_next;
				new_travel->m_prev = new_trail;
				travel = travel->m_next;
			}
			m_tail = new_travel;
		}
	}

	return *this;
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: To add data at the start of the list
*
* Precondition:
*		None
*
* Postcondition:
*		Adds a new Node object to be the new m_head of the list and makes the next Node's previous pointer to be equal to it
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::Prepend(T data)
{

	Node<T> * new_node = new Node<T>(data);
	if (isEmpty())
	{
		m_head = new_node;
		m_tail = new_node;
	}
	else
	{
		new_node->m_next = m_head;
		m_head->m_prev = new_node;
		m_head = new_node;
	}
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: To add data at the end of the list
*
* Precondition:
*		None
*
* Postcondition:
*		Adds a new Node object to be the new m_tail of the list and makes the previous Node's next pointer to be equal to it
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::Append(T data)
{
	Node<T> * new_node = new Node<T>(data);
	if (isEmpty())
	{
		m_head = new_node;
		m_tail = new_node;
	}
	else
	{
		m_tail->m_next = new_node;
		new_node->m_prev = m_tail;
		m_tail = new_node;
	}
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: To rid of the first node with the passed through data
*
* Precondition:
*		None
*
* Postcondition:
*		Gets rid of the first node with the target data and relinks the list
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::Extract(T target)
{
	Node<T> * travel = m_head;

	if (m_head->m_data == target) //If first node is the target move over the head
	{
		m_head = m_head->m_next;
		delete travel;
		travel = nullptr;
	}

	else
	{
		bool targetFound = false;	//Flag for if the target was found, will throw an exception at the end of the function if this remains false
		while (travel != nullptr && targetFound == false)
		{
			if (travel->m_data == target)
			{
				targetFound = true;
				Node<T> * trail = travel->m_prev;
				trail->m_next = travel->m_next;
				delete travel;
				travel = trail->m_next;
				if (travel) //If it is not the last node and travel is not nullptr
					travel->m_prev = trail;
				else
					m_tail = trail;
			}
			else
				travel = travel->m_next;
		}
		if (targetFound == false)
			throw Exception("Target not found for extraction");
	}
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Inserts data after the given target
*
* Precondition:
*		None
*
* Postcondition:
*		Adds a node with the data after the target then relinks the list
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::InsertAfter(T newData, T target)
{
	if (m_head->m_data == target && m_head == m_tail) //If the only node is the target
	{
		Node<T> * new_node = new Node<T>(newData);
		m_head->m_next = new_node;
		new_node->m_prev = m_head;
		m_tail = new_node;
	}
	else
	{
		bool targetFound = false; //Flag for if the target was found, will throw an exception at the end of the function if this remains false
		Node<T> * travel = m_head;
		while (travel != nullptr && targetFound == false)
		{
			if (travel->m_data == target)
			{
				targetFound = true;
				Node<T> * new_node = new Node<T>(newData);
				new_node->m_next = travel->m_next;
				new_node->m_prev = travel;
				travel->m_next = new_node;

				if (travel != m_tail) //If the target data is not at the end of the list
				{
					new_node = new_node->m_next;
					new_node->m_prev = travel->m_next;
				}
				else //If the data is the last in the list the new_node is now the last
					m_tail = new_node;
			}
			else
				travel = travel->m_next;
		}
		if (targetFound == false)
			throw Exception("Target not found for extraction");
	}
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Inserts data before the given target
*
* Precondition:
*		None
*
* Postcondition:
*		Adds a node with the data before the target then relinks the list
***********************************************************************************************************************************************************************************************************************/
template <typename T>
void List<T>::InsertBefore(T newData, T target)
{
	if (m_head->m_data == target && m_head == m_tail) //If the only node is the target
	{
		Node<T> * new_node = new Node<T>(newData);
		m_head->m_prev = new_node;
		new_node->m_next = m_head;
		m_head = new_node;
	}
	else
	{
		bool targetFound = false; //Flag for if the target was found, will throw an exception at the end of the function if this remains false
		Node<T> * travel = m_head;
		while (travel != nullptr && targetFound == false)
		{
			if (travel->m_data == target)
			{
				targetFound = true;
				Node<T> * new_node = new Node<T>(newData);
				new_node->m_next = travel;
				new_node->m_prev = travel->m_prev;
				travel->m_prev = new_node;



				if (travel != m_head) //If the target data is not at the end of the list
				{
					new_node = new_node->m_prev;
					new_node->m_next = travel->m_prev;
				}
				else //If the data is the last in the list the new_node is now the last
					m_head = new_node;
			}
			else
				travel = travel->m_next;
		}
		if (targetFound == false)
			throw Exception("Target not found for extraction");
	}
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Checks if the list is empty
*
* Precondition:
*		None
*
* Postcondition:
*		Returns true if there is no head and so there is no list
*		Returns false otherwise
***********************************************************************************************************************************************************************************************************************/
template <typename T>
bool List<T>::isEmpty()
{
	return m_head == nullptr ? true : false;
}