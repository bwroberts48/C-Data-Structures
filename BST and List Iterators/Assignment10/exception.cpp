#include "exception.h"

Exception::Exception() : m_msg(nullptr)
{}

Exception::Exception(const char* msg) : m_msg(nullptr)
{
	if (msg != nullptr)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

Exception::Exception(const Exception & copy) : m_msg(nullptr)
{
	m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy(m_msg, copy.m_msg);
}

Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
}

Exception & Exception::operator =(const Exception & rhs)
{
	if (&rhs != this)
	{
		delete[] m_msg;
		m_msg = new char[strlen(rhs.m_msg) + 1];
		strcpy(m_msg, rhs.m_msg);
	}
	return *this;
}

const char * Exception::GetMessage() const
{
	return m_msg;
}

void Exception::SetMessage(const char * msg)
{
	delete[] m_msg;
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

ostream & operator <<(ostream & stream, const Exception & except)
{
	stream << except.m_msg << std::endl;
	return stream;
}