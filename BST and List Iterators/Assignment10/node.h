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

public:
	Node * GetNext() const { return m_next; }
	Node * GetPrevious() const { return m_prev; }
	const T & GetData() const{ return m_data; } //Const and non-const getters
	T & GetData() { return m_data; }
};

template <typename T>
Node<T>::Node() : m_data(nullptr), m_next(nullptr), m_prev(nullptr)
{}

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


