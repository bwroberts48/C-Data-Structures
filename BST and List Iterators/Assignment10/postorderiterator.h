#pragma once
#include "bstiterator.h"

template <typename T>
class PostOrderIterator : public BSTIterator<T>
{
	friend class BST<T>;
public:
	PostOrderIterator();
	~PostOrderIterator();
	PostOrderIterator(const PostOrderIterator & copy);
	PostOrderIterator & operator=(const PostOrderIterator & rhs);
	void MoveNext();
	void Reset();
private:
	PostOrderIterator(BSTNode<T>* root);
	void InitQueue(BSTNode<T> * root);
};

template <typename T>
inline PostOrderIterator<T>::PostOrderIterator() : BSTIterator<T>()
{}

template <typename T>
inline PostOrderIterator<T>::~PostOrderIterator()
{}
template <typename T>
inline PostOrderIterator<T>::PostOrderIterator(const PostOrderIterator & copy) : BSTIterator<T>(copy)
{}

template <typename T>
inline PostOrderIterator<T>::PostOrderIterator(BSTNode<T> * root)
{
	if (!root)
		throw Exception("Cannot iterate empty tree");
	this->m_root = root;
	InitQueue(root);
	this->m_iter = this->m_storage.Front();
}

template<typename T>
inline void PostOrderIterator<T>::InitQueue(BSTNode<T> * root)
{
	if (root)
	{
		InitQueue(root->GetLeft());
		InitQueue(root->GetRight());
		this->m_storage.Enqueue(root);
	}
}

template <typename T>
inline PostOrderIterator<T> & PostOrderIterator<T>::operator=(const PostOrderIterator & rhs)
{
	if (&rhs != this)
	{
		BSTIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void PostOrderIterator<T>::MoveNext()
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
inline void PostOrderIterator<T>::Reset()
{
	if (!this->m_root)
		throw Exception("Cannot reset empty tree");
	InitQueue(this->m_root);
	this->m_iter = this->m_storage.Front();
}