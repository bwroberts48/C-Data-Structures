#pragma once
#include "bstiterator.h"

template <typename T>
class PreOrderIterator : public BSTIterator<T>
{
	friend class BST<T>;
public:
	PreOrderIterator();
	~PreOrderIterator();
	PreOrderIterator(const PreOrderIterator & copy);
	PreOrderIterator & operator=(const PreOrderIterator & rhs);
	void MoveNext();
	void Reset();
private:
	PreOrderIterator(BSTNode<T>* root);
	void InitQueue(BSTNode<T> * root);
};

template <typename T>
inline PreOrderIterator<T>::PreOrderIterator() : BSTIterator<T>()
{}

template <typename T>
inline PreOrderIterator<T>::~PreOrderIterator()
{}

template <typename T>
inline PreOrderIterator<T>::PreOrderIterator(const PreOrderIterator & copy) : BSTIterator<T>(copy)
{}

template <typename T>
inline PreOrderIterator<T>::PreOrderIterator(BSTNode<T> * root)
{
	if (!root)
		throw Exception("Cannot iterate empty tree");
	this->m_root = root;
	InitQueue(root);
	this->m_iter = this->m_storage.Front();
}

template<typename T>
inline void PreOrderIterator<T>::InitQueue(BSTNode<T> * root)
{
	if (root)
	{
		this->m_storage.Enqueue(root);
		InitQueue(root->GetLeft());
		InitQueue(root->GetRight());
	}
}

template <typename T>
inline PreOrderIterator<T> & PreOrderIterator<T>::operator=(const PreOrderIterator & rhs)
{
	if (&rhs != this)
	{
		BSTIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void PreOrderIterator<T>::MoveNext()
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
inline void PreOrderIterator<T>::Reset()
{
	if (!this->m_root)
		throw Exception("Cannot reset empty tree");
	InitQueue(this->m_root);
	this->m_iter = this->m_storage.Front();
}