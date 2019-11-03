#pragma once
#include "listiterator.h"

template <typename T>
class ForwardIterator : public ListIterator<T>
{
	friend class List<T>;
public:
	ForwardIterator();
	virtual ~ForwardIterator();
	ForwardIterator(const ForwardIterator & copy);
	ForwardIterator & operator=(const ForwardIterator & rhs);
	void MoveNext();
	void Reset();
private:
	ForwardIterator(Node<T> * const copy);
};

template <typename T>
inline ForwardIterator<T>::ForwardIterator() : ListIterator<T>()
{}

template <typename T>
inline ForwardIterator<T>::~ForwardIterator()
{}

template <typename T>
inline ForwardIterator<T>::ForwardIterator(const ForwardIterator & copy) : ListIterator<T>(copy)
{}

template <typename T>
inline ForwardIterator<T>::ForwardIterator(Node<T> * const copy)
{
	this->m_iter = copy;
}

template <typename T>
inline ForwardIterator<T> & ForwardIterator<T>::operator=(const ForwardIterator & rhs)
{
	if (&rhs != this)
	{
		ListIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void ForwardIterator<T>::MoveNext()
{
	if (!this->m_iter)
		throw Exception("Cannot move nullptr Iterator");
	this->m_iter = this->m_iter->GetNext();
}

template <typename T>
inline void ForwardIterator<T>::Reset()
{
	if (!this->m_iter)
		throw Exception("Cannot reset nullptr Iterator");
	while (this->m_iter->GetPrevious()) //Move iter until it is at the head
		this->m_iter = this->m_iter->GetPrevious();
}
