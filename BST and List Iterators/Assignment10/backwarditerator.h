#pragma once
#include "listiterator.h"

template <typename T>
class BackwardIterator : public ListIterator<T>
{
	friend class List<T>;
public:
	BackwardIterator();
	~BackwardIterator();
	BackwardIterator(const BackwardIterator & copy);
	BackwardIterator & operator=(const BackwardIterator & rhs);
	void MoveNext();
	void Reset();
private:
	BackwardIterator(Node<T> * const copy);
};

template <typename T>
inline BackwardIterator<T>::BackwardIterator() : ListIterator<T>()
{}

template <typename T>
inline BackwardIterator<T>::~BackwardIterator()
{
	ListIterator<T>::~ListIterator();
}

template <typename T>
inline BackwardIterator<T>::BackwardIterator(const BackwardIterator & copy) : ListIterator<T>(copy)
{}

template <typename T>
inline BackwardIterator<T>::BackwardIterator(Node<T> * const copy)
{
	this->m_iter = copy;
}

template <typename T>
inline BackwardIterator<T> & BackwardIterator<T>::operator=(const BackwardIterator & rhs)
{
	if (&rhs != this)
	{
		ListIterator<T>::operator=(rhs);
	}
	return *this;
}

template <typename T>
inline void BackwardIterator<T>::MoveNext()
{
	if (!this->m_iter)
		throw Exception("Cannot move nullptr Iterator");
	this->m_iter = this->m_iter->GetPrevious();
}

template <typename T>
inline void BackwardIterator<T>::Reset()
{
	if (!this->m_iter)
		throw Exception("Cannot reset nullptr Iterator");
	while (this->m_iter->GetNext()) //Move iter until it is at the tail
		this->m_iter = this->m_iter->GetNext();
}
