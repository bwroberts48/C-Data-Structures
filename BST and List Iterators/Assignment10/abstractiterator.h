#pragma once
#include "exception.h"

template <typename T, typename U> //T is the data type within a container (ex. int), whereas U is the container type for a data structure (ex. ListNode)
class AbstractIterator
{
public:
	AbstractIterator();
	virtual ~AbstractIterator();
	AbstractIterator(const AbstractIterator & copy);
	AbstractIterator & operator=(const AbstractIterator & rhs);
	virtual bool IsDone() const = 0;
	virtual T & GetCurrent() = 0;
	virtual T GetCurrent() const = 0;
	virtual void MoveNext() = 0;
	virtual void Reset() = 0;
protected:
	U * m_iter;
};

template <typename T, typename U>
inline AbstractIterator<T, U>::AbstractIterator() : m_iter(nullptr)
{}

template <typename T, typename U>
inline AbstractIterator<T, U>::~AbstractIterator()
{
	m_iter = nullptr;
}

template<typename T, typename U>
inline AbstractIterator<T, U>::AbstractIterator(const AbstractIterator & copy) : m_iter(copy.m_iter)
{}

template<typename T, typename U>
inline AbstractIterator<T, U> & AbstractIterator<T, U>::operator=(const AbstractIterator & rhs)
{
	if (&rhs != this)
	{
		m_iter = rhs.m_iter;
	}
	return *this;
}