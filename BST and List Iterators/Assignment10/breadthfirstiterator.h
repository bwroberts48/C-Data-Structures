#pragma once
#include "bstiterator.h"

template <typename T>
class BreadthFirstIterator : public BSTIterator<T>
{
	friend class BST<T>;
public:
	BreadthFirstIterator();
	~BreadthFirstIterator();
	BreadthFirstIterator(const BreadthFirstIterator & copy);
	BreadthFirstIterator & operator=(const BreadthFirstIterator & rhs);
	void MoveNext();
	void Reset();
private:
	BreadthFirstIterator(BSTNode<T>* root);
	void InitQueue();
};

template <typename T>
inline BreadthFirstIterator<T>::BreadthFirstIterator() : BSTIterator<T>()
{}

template <typename T>
inline BreadthFirstIterator<T>::~BreadthFirstIterator()
{}

template <typename T>
inline BreadthFirstIterator<T>::BreadthFirstIterator(const BreadthFirstIterator & copy) : BSTIterator<T>(copy)
{}

template <typename T>
inline BreadthFirstIterator<T>::BreadthFirstIterator(BSTNode<T> * root)
{
	if (!root)
		throw Exception("Cannot iterate empty tree");
	this->m_root = root;
	InitQueue();
	this->m_iter = this->m_storage.Front();
}

template<typename T>
inline void BreadthFirstIterator<T>::InitQueue()
{
	BSTNode<T> * root = this->m_root;
	ListQueue<BSTNode<T>*> queue;
	if (root != nullptr)
	{
		queue.Enqueue(root);
		while (!queue.isEmpty()) //Continues until the entire tree has been visited and each has been queued once
		{
			root = queue.Dequeue();
			this->m_storage.Enqueue(root);
			if (root->GetLeft() != 0)
				queue.Enqueue(root->GetLeft());
			if (root->GetRight() != 0)
				queue.Enqueue(root->GetRight());
		}
	}
}

template <typename T>
inline BreadthFirstIterator<T> & BreadthFirstIterator<T>::operator=(const BreadthFirstIterator & rhs)
{
	if (&rhs != this)
	{
		BSTIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void BreadthFirstIterator<T>::MoveNext()
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
inline void BreadthFirstIterator<T>::Reset()
{
	if (!this->m_root)
		throw Exception("Cannot reset empty tree");
	InitQueue();
	this->m_iter = this->m_storage.Front();
}