#pragma once
#include "bstiterator.h"

template <typename T>
class InOrderIterator : public BSTIterator<T>
{
	friend class BST<T>;
public:
	InOrderIterator();
	~InOrderIterator();
	InOrderIterator(const InOrderIterator & copy);
	InOrderIterator & operator=(const InOrderIterator & rhs);
	void MoveNext();
	void Reset();
private:
	InOrderIterator(BSTNode<T>* root);
	void InitQueue(BSTNode<T> * root);
};

template <typename T>
inline InOrderIterator<T>::InOrderIterator() : BSTIterator<T>()
{}

template <typename T>
inline InOrderIterator<T>::~InOrderIterator()
{
	BSTIterator<T>::~BSTIterator();
}

template <typename T>
inline InOrderIterator<T>::InOrderIterator(const InOrderIterator & copy) : BSTIterator<T>(copy)
{}

template <typename T>
inline InOrderIterator<T>::InOrderIterator(BSTNode<T> * root)
{
	if (!root)
		throw Exception("Cannot iterate empty tree");
	this->m_root = root;
	InitQueue(root);
	this->m_iter = this->m_storage.Front();
}

template<typename T>
inline void InOrderIterator<T>::InitQueue(BSTNode<T> * root)
{
	if (root)
	{
		InitQueue(root->GetLeft());
		this->m_storage.Enqueue(root);
		InitQueue(root->GetRight());
	}
}

template <typename T>
inline InOrderIterator<T> & InOrderIterator<T>::operator=(const InOrderIterator & rhs)
{
	if (&rhs != this)
	{
		BSTIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void InOrderIterator<T>::MoveNext()
{
	if (!this->m_iter)
		throw Exception("Cannot move nullptr Iterator");
	this->m_storage.Dequeue();
	try
	{
		this->m_iter = this->m_storage.Front();
	}
	catch (Exception &except)
	{
		this->m_iter = nullptr;
	}
}

template <typename T>
inline void InOrderIterator<T>::Reset()
{
	if (!this->m_root)
		throw Exception("Cannot reset empty tree");
	InitQueue(this->m_root);
	this->m_iter = this->m_storage.Front();
}