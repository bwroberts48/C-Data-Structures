#pragma once
#include "abstractiterator.h"
#include "BST.h"

template <typename T>
class BSTIterator : public AbstractIterator<T, BSTNode<T>>
{
public:
	BSTIterator();
	virtual ~BSTIterator();
	BSTIterator(const BSTIterator & copy);
	BSTIterator & operator=(const BSTIterator & rhs);
	bool IsDone() const;
	T & GetCurrent();
	T GetCurrent() const;
protected:
	BSTNode<T> * m_root;
	ListQueue<BSTNode<T>*> m_storage;
};

template <typename T>
inline BSTIterator<T>::BSTIterator() : AbstractIterator<T, BSTNode<T>>(), m_storage(), m_root(nullptr)
{}

template <typename T>
inline BSTIterator<T>::~BSTIterator()
{
	m_root = nullptr;
}

template <typename T>
inline BSTIterator<T>::BSTIterator(const BSTIterator & copy) : AbstractIterator<T, BSTNode<T>>(copy), m_storage(copy.m_storage), m_root(copy.m_root)
{}

template <typename T>
inline BSTIterator<T> & BSTIterator<T>::operator=(const BSTIterator & rhs)
{
	if (&rhs != this)
	{
		AbstractIterator<T, BSTNode<T>>::operator=(rhs);
		m_storage = rhs.m_storage;
		m_root = rhs.m_root;
	}
	return *this;
}

template <typename T>
bool BSTIterator<T>::IsDone() const
{
	return this->m_iter == nullptr ? true : false;
}

template<typename T>
inline T & BSTIterator<T>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot return nullptr iter");
	return this->m_iter->GetData();
}

template<typename T>
inline T BSTIterator<T>::GetCurrent() const
{
	if (IsDone())
		throw Exception("Cannot return nullptr iter");
	return this->m_iter->GetData();
}