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

