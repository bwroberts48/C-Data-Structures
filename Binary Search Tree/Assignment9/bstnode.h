#pragma once
template <typename T> class BST;

template <typename T>
class BSTNode
{
	friend class BST<T>;
public:
	/******* TEST FUNCTION(S) ******/
	inline const T & GetData() { return m_data; }
private:
	BSTNode();
	BSTNode(T data);
	~BSTNode();
	BSTNode(const BSTNode & copy);
	BSTNode & operator= (const BSTNode & rhs);

	T m_data;
	BSTNode * m_left;
	BSTNode * m_right;
};

template <typename T>
inline BSTNode<T>::BSTNode() : m_data(nullptr), m_left(nullptr), m_right(nullptr)
{}

template <typename T>
inline BSTNode<T>::BSTNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr)
{}

template <typename T>
inline BSTNode<T>::~BSTNode()
{
	m_left = nullptr;
	m_right = nullptr;
}

template <typename T>
inline BSTNode<T>::BSTNode(const BSTNode & copy) : m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right)
{}

template <typename T>
inline BSTNode<T> & BSTNode<T>::operator =(const BSTNode & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
	}
	return *this;
}
