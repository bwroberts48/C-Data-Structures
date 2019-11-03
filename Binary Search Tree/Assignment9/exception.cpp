/********************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		exception.cpp
* Date Created: 1/7/2019
*********************************************************************************************************************************************************************/
#include "exception.h"

Exception::Exception() : m_msg(nullptr)
{}

/********************************************************************************************************************************************************************
* Purpose: Takes a msg to build the exception that will be thrown
*
* Precondition:
*	An exception will occur
*
* Postcondition:
*	An Exception object is the created with the passed through message
*********************************************************************************************************************************************************************/
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

/********************************************************************************************************************************************************************
* Purpose: Allows the Exception message to be easily outputted
*
* Precondition:
*	The Exception object must have a message
*
* Postcondition:
*	The Exception message is outputted to the console followed by a new line
*********************************************************************************************************************************************************************/
ostream & operator <<(ostream & stream, const Exception & except)
{
	stream << except.m_msg << std::endl;
	return stream;
}