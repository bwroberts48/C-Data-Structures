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

	//Test Functions
	void PrintForwards();
	void PrintBackwards();
	inline Node<T> * GetHead() const { return m_head; }
	inline Node<T> * GetTail() const { return m_tail; }
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

template <typename T>
void List<T>::PrintForwards()
{
	Node<T> * travel = m_head;
	while (travel)
	{
		cout << travel->m_data << " ";
		travel = travel->m_next;
	}
	cout << endl;
}

template <typename T>
void List<T>::PrintBackwards()
{
	Node<T> * travel = m_tail;
	while (travel)
	{
		cout << travel->m_data << " ";
		travel = travel->m_prev;
	}
	cout << endl;
}

template <typename T>
bool List<T>::isEmpty()
{
	return m_head == nullptr ? true : false;
}