#pragma once
#include "bstnode.h"
#include "listqueue.h"
#include "exception.h"
template <typename T> class BST
{
public:
	BST();
	~BST();
	BST(const BST & copy);
	BST & operator= (const BST & rhs);

	inline void Insert(T data) { Insert(m_root, data); }
	void Delete(T target);
	inline int Height() { return Height(m_root) - 1; }
	void BreadthFirst(void(*Visit)(BSTNode<T>*));
	inline void InOrderTrav(void(*Visit)(BSTNode<T>*)) { InOrderTrav(Visit, m_root); }
	inline void PreOrderTrav(void(*Visit)(BSTNode<T>*)) { PreOrderTrav(Visit, m_root); }
	inline void PostOrderTrav(void(*Visit)(BSTNode<T>*)) { PostOrderTrav(Visit, m_root); }
private:
	void CopyTree(BSTNode<T> * root);
	void Insert(BSTNode<T> *& root, T data);
	int Height(BSTNode<T> * root);
	void Purge(BSTNode<T> * root);
	void InOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T> * root);
	void PreOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T> * root);
	void PostOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T> * root);

	BSTNode<T> * m_root;
};

template<typename T>
inline BST<T>::BST() : m_root(nullptr)
{}

template<typename T>
inline BST<T>::~BST()
{
	Purge(m_root);
	m_root = nullptr;
}

template<typename T>
inline BST<T>::BST(const BST & copy) : m_root(nullptr)
{
	CopyTree(copy.m_root);
}

template<typename T>
inline BST<T> & BST<T>::operator= (const BST<T> & rhs)
{
	if (&rhs != this)
	{
		m_root = nullptr;
		CopyTree(rhs.m_root);
	}
	return *this;
}

template<typename T>
inline void BST<T>::CopyTree(BSTNode<T> * root)
{
	if (root != nullptr) //Perform a pre order traversal inserting data from the original tree into the copy
	{
		Insert(root->m_data);
		CopyTree(root->m_left);
		CopyTree(root->m_right);
	}
}

template<typename T>
inline void BST<T>::Insert(BSTNode<T> *& root, T data)
{
	if (!root)
		root = new BSTNode<T>(data);
	else if (data < root->m_data)
		Insert(root->m_left, data);
	else
		Insert(root->m_right, data);
}

template<typename T>
inline void BST<T>::Delete(T target)
{
	BSTNode<T> * targetNode = nullptr;
	BSTNode<T> * root = m_root;
	BSTNode<T> * temp = nullptr;
	while (root != nullptr) //Find the node with the target data
	{
		if (target == root->m_data)
		{
			targetNode = root;
			root = nullptr;
		}
		else if (target < root->m_data)
		{
			temp = root;
			root = root->m_left;
		}
		else
		{
			temp = root;
			root = root->m_right;
		}
	}
	if (targetNode == nullptr)
		throw Exception("Data not found for Deletion");

	if (targetNode == m_root && !m_root->m_left && !m_root->m_right) //If the node is the root
	{
		delete m_root;
		m_root = nullptr;
	}

	else if (targetNode->m_left && targetNode->m_right) //If the node has two children
	{
		temp = targetNode->m_right;
		BSTNode<T> * trail = nullptr;
		while (temp->m_left) //Travel to the left-most data from the right subtree
		{
			trail = temp;
			temp = temp->m_left;
		}
		targetNode->m_data = temp->m_data; //Copy the data over
		if (trail == nullptr)
			targetNode->m_right = temp->m_right;
		else
			trail->m_left = temp->m_right;
		delete temp;
	}

	else if (targetNode->m_left) //If the node only has a left child
	{	
		if (temp->m_left == targetNode)
			temp->m_left = targetNode->m_left;
		else
			temp->m_right = targetNode->m_left;
		delete targetNode;
	}

	else if (targetNode->m_right) //If the node only has a right child
	{
		if (temp->m_left == targetNode)
			temp->m_left = targetNode->m_right;
		else
			temp->m_right = targetNode->m_right;
		delete targetNode;
	}

	else //If the target is a leaf node
	{
		if (temp->m_left == targetNode)
			temp->m_left = nullptr;
		else
			temp->m_right = nullptr;
		delete targetNode;
	}
}

template<typename T>
inline int BST<T>::Height(BSTNode<T> * root) //Calculates height + 1. Public function will return this value - 1
{
	if (!root)
		return 0;
	return 1 + (Height(root->m_left) < Height(root->m_right) ? Height(root->m_right) : Height(root->m_left));
}

template<typename T>
inline void BST<T>::Purge(BSTNode<T> * root)
{
	if (root) //Perform a post order traversal deleting nodes as it continues up the tree
	{
		Purge(root->m_left);
		Purge(root->m_right);
		delete root;
	}
}

template<typename T>
inline void BST<T>::BreadthFirst(void(*Visit)(BSTNode<T>*))
{
	BSTNode<T> * root = m_root;
	ListQueue<BSTNode<T>*> queue;
	if (root != nullptr)
	{
		queue.Enqueue(root);
		while (!queue.isEmpty()) //Continues until the entire tree has been visited and each has been queued once
		{
			root = queue.Dequeue();
			Visit(root);
			if (root->m_left != 0)
				queue.Enqueue(root->m_left);
			if (root->m_right != 0)
				queue.Enqueue(root->m_right);
		}
	}
}

template<typename T>
inline void BST<T>::InOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T>* root)
{
	if (root != nullptr)
	{
		InOrderTrav(Visit, root->m_left);
		Visit(root);
		InOrderTrav(Visit, root->m_right);
	}
}

template<typename T>
inline void BST<T>::PreOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T>* root)
{
	if (root != nullptr)
	{
		Visit(root);
		PreOrderTrav(Visit, root->m_left);
		PreOrderTrav(Visit, root->m_right);
	}
}

template<typename T>
inline void BST<T>::PostOrderTrav(void(*Visit)(BSTNode<T>*), BSTNode<T>* root)
{
	if (root != nullptr)
	{
		PostOrderTrav(Visit, root->m_left);
		PostOrderTrav(Visit, root->m_right);
		Visit(root);
	}
}