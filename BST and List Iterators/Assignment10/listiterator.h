#pragma once
#include "abstractiterator.h"
#include "node.h"

template <typename T>
class ListIterator : public AbstractIterator<T, Node<T>>
{
public:
	ListIterator();
	virtual ~ListIterator();
	ListIterator(const ListIterator & copy);
	ListIterator & operator=(const ListIterator & rhs);
	bool IsDone() const;
	T & GetCurrent();
	T GetCurrent() const;
};

template <typename T>
inline ListIterator<T>::ListIterator() : AbstractIterator<T, Node<T>>()
{}

template <typename T>
inline ListIterator<T>::~ListIterator()
{}

template <typename T>
inline ListIterator<T>::ListIterator(const ListIterator & copy) : AbstractIterator<T, Node<T>>(copy)
{}

template <typename T>
inline ListIterator<T> & ListIterator<T>::operator=(const ListIterator & rhs)
{
	if (&rhs != this)
	{
		AbstractIterator<T, Node<T>>::operator=(rhs);
	}
	return *this;
}

template<typename T>
inline bool ListIterator<T>::IsDone() const
{
	return this->m_iter == nullptr ? true : false;
}

template<typename T>
inline T & ListIterator<T>::GetCurrent()
{
	if (IsDone())
		throw Exception("Cannot return nullptr iter");
	return this->m_iter->GetData();
}

template<typename T>
inline T ListIterator<T>::GetCurrent() const
{
	if (IsDone())
		throw Exception("Cannot return nullptr iter");
	return this->m_iter->GetData();
}