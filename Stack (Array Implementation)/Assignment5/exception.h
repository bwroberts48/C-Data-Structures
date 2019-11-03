/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		exception.h
* Date Created: 1/7/2019
*
* Class: Exception
*
* Purpose: Meant to be thrown in the case that something warranting an exception has occured
*
* Manager functions:
*	Exception();
*		Sets the exception message to nullptr
*	Exception(const char * msg);
*		Sets the exception message to the passed through variable
*	Exception(const Exception & copy);
*	~Exception();
*	Exception & operator =(const Exception & rhs);
* Methods:
*	const char * GetMessage();
*	void SetMessage(char * msg);
*	friend ostream & operator <<(ostream & stream, const Exception & except);
*		Outputs the Exception message
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include  <iostream>
using std::ostream;
class Exception
{
public:
	Exception();
	Exception(const char * msg);
	Exception(const Exception & copy);
	~Exception();
	Exception & operator =(const Exception & rhs);
	const char * GetMessage();
	void SetMessage(char * msg);
	friend ostream & operator <<(ostream & stream, const Exception & except);

private:
	char * m_msg;
};