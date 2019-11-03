/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		avlnode.h
* Date:			2/20/2019
* Class: AVLNode (friend of the AVL class)
*
* Purpose: Is the node for the AVL class
*
* Manager functions:
*		AVLNode()
*			Sets data, left and right to nullptr
*		AVLNode(T data)
*			Sets the nodes data to the data passed through
*		~Node()
*		Node(const Node & copy)
*		Node & operator =(const Node & rhs)
*
* Methods:
*		const T & GetData()
*			Returns the data from the given node
***********************************************************************************************************************************************************************************************************************/
#pragma once
enum Balance_Factor
{
	LEFT_HEAVY,
	EVEN_HEIGHT,
	RIGHT_HEAVY
};

template <typename T> class AVL;

template <typename T>
class AVLNode
{
	friend class AVL<T>;
public:
	inline const T & GetData() { return m_data; }
private:
	AVLNode();
	AVLNode(T data);
	~AVLNode();
	AVLNode(const AVLNode & copy);
	AVLNode & operator= (const AVLNode & rhs);

	T m_data;
	AVLNode * m_left;
	AVLNode * m_right;
	Balance_Factor m_balance;
};

template <typename T>
inline AVLNode<T>::AVLNode() : m_data(nullptr), m_left(nullptr), m_right(nullptr), m_balance(EVEN_HEIGHT)
{}

template <typename T>
inline AVLNode<T>::AVLNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr), m_balance(EVEN_HEIGHT)
{}

template <typename T>
inline AVLNode<T>::~AVLNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_balance = EVEN_HEIGHT;
}

template <typename T>
inline AVLNode<T>::AVLNode(const AVLNode & copy) : m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right), m_balance(copy.m_balance)
{}

template <typename T>
inline AVLNode<T> & AVLNode<T>::operator= (const AVLNode & rhs)
{
	if (&rhs != this)
	{
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
		m_balance = rhs.m_balance;
	}
	return *this;
}
