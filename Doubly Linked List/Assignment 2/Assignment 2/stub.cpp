#include "List.h"
#include "Exception.h"
#include <crtdbg.h>
#include <string>
#include <iostream>
#include <iomanip>
using std::setw;
using std::left;
using std::right;
using std::cout;
using std::cin;
using std::string;

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

bool Test_IsEmpty_Empty();
bool Test_IsEmpty_NotEmpty();
bool Test_First();
bool Test_Last();
bool Test_Prepend_Empty();
bool Test_Prepend_NotEmpty();
bool Test_Append_Empty();
bool Test_Append_NotEmpty();
bool Test_Purge();
bool Test_Extract_Head();
bool Test_Extract_Tail();
bool Test_Extract_Middle();
bool Test_Extract_Doesnt_Exist();
bool Test_InsertBefore_Head();
bool Test_InsertBefore_Middle();
bool Test_InsertBefore_DoesntExist();
bool Test_InsertAfter_Tail();
bool Test_InsertAfter_Middle();
bool Test_InsertAfter_DoesntExist();
bool Test_GetHead();
bool Test_GetTail();
bool Test_OpEqual();
bool Test_Cpy_Constructor();


// Array of test functions
FunctionPointer test_functions[] = { Test_IsEmpty_Empty, Test_IsEmpty_NotEmpty,Test_First,
Test_Last, Test_Prepend_Empty, Test_Prepend_NotEmpty, Test_Append_Empty,
Test_Append_NotEmpty, Test_Purge, Test_Extract_Head, Test_Extract_Tail,
Test_Extract_Middle, Test_Extract_Doesnt_Exist, Test_InsertBefore_Head,
Test_InsertBefore_Middle, Test_InsertBefore_DoesntExist, Test_InsertAfter_Tail,
Test_InsertAfter_Middle, Test_InsertAfter_DoesntExist, Test_GetHead,
Test_GetTail, Test_OpEqual, Test_Cpy_Constructor };


int main()
{
	bool all_tests_passed = true;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "Passed!!\n";
		}
		else
		{
			all_tests_passed = false;
			cout << "***** Failed :( *****\n";
		}
	}

	all_tests_passed ? (cout << "\nAll Tests Passed! :) \n") : (cout << "\nAll Tests NOT Passed! :(\n");
	system("pause");
	return 0;
}

bool Test_IsEmpty_Empty()
{
	bool pass = false;
	List<int> empty_list;
	pass = empty_list.IsEmpty();

	cout << "* IsEmpty on empty list test... ";

	return pass;
}

bool Test_IsEmpty_NotEmpty()
{
	bool pass = false;

	List<int> list;
	list.Append(1);
	list.Append(2);

	pass = list.IsEmpty();

	cout << "* IsEmpty on empty list test... ";

	return pass ? false : true;
}

bool Test_First()
{
	int first = 1;

	List<int> list;
	list.Append(first);
	list.Append(2);

	cout << "* Get reference to first test... ";
	return list.First() == first ? true : false;
}

bool Test_Last()
{
	int last = 2;

	List<int> list;
	list.Append(1);
	list.Append(last);

	cout << "* Get reference to last test... ";
	return list.Last() == last ? true : false;
}

bool Test_Prepend_Empty()
{
	int prepend_val = 1;

	List<int> list;
	list.Prepend(prepend_val);

	cout << "* Prepend on empty list test... ";
	return (!list.IsEmpty() && list.First() == prepend_val) ? true : false;
}

bool Test_Prepend_NotEmpty()
{
	int prev_val = 1;
	int prepend_val = 2;

	List<int> list;
	list.Prepend(prev_val);
	list.Prepend(prepend_val);

	cout << "* Prepend on non-empty list test... ";
	return (!list.IsEmpty() && list.First() == prepend_val
		&& list.GetHead()->GetNext()->GetData() == prev_val) ? true : false;
}

bool Test_Append_Empty()
{
	int append_val = 1;

	List<int> list;
	list.Append(append_val);

	cout << "* Append on empty list test... ";
	return (!list.IsEmpty() && list.Last() == append_val) ? true : false;
}

bool Test_Append_NotEmpty()
{
	int prev_val = 1;
	int append_val = 2;

	List<int> list;
	list.Append(prev_val);
	list.Append(append_val);

	cout << "* Append on non-empty list test... ";
	return (!list.IsEmpty() && list.Last() == append_val
		&& list.GetTail()->GetPrevious()->GetData() == prev_val) ? true : false;
}

bool Test_Purge()
{
	List<int> list;
	for (int i = 0; i < 10; i++)
	{
		list.Append(i);
	}

	list.Purge();
	cout << "* Purge list test... ";
	return (list.IsEmpty() && list.GetHead() == nullptr && list.GetTail() == nullptr) ? true : false;
}

bool Test_Extract_Head()
{
	List<int> list;
	int head = 1;

	list.Append(head);
	list.Append(2);

	list.Extract(head);

	cout << "* Extract head test... ";
	return (list.GetHead()->GetData() == 2 && list.GetTail()->GetData() == 2) ? true : false;
}

bool Test_Extract_Tail()
{
	List<int> list;
	int tail = 2;

	list.Append(1);
	list.Append(tail);

	list.Extract(tail);

	cout << "* Extract tail test... ";
	return (list.GetTail()->GetData() == 1 && list.GetHead()->GetData() == 1) ? true : false;
}

bool Test_Extract_Middle()
{
	List<int> list;

	list.Append(1);
	list.Append(2);
	list.Append(3);

	list.Extract(2);

	cout << "* Extract from middle test... ";
	return (list.GetHead()->GetData() == 1 && list.GetTail()->GetData() == 3) ? true : false;
}

bool Test_Extract_Doesnt_Exist()
{
	//should throw an exception if not found
	bool pass = false;

	List<int> list;
	list.Append(1);
	list.Append(2);

	try {
		list.Extract(5);
	}
	catch (Exception &e) {
		pass = true;
	}

	cout << "* Extract value not found test... ";

	return pass;
}

bool Test_InsertBefore_Head()
{
	List<int> list;
	list.Append(2);

	list.InsertBefore(1, 2);

	cout << "* Insert before head test... ";
	return (list.GetHead()->GetData() == 1 && list.GetTail()->GetData() == 2) ? true : false;
}

bool Test_InsertBefore_Middle()
{
	List<int> list;
	list.Append(2);
	list.Append(4);

	list.InsertBefore(3, 4);

	cout << "* Insert before test... ";
	return (list.GetHead()->GetData() == 2 && list.GetTail()->GetData() == 4 &&
		list.GetHead()->GetNext()->GetData() == 3) ? true : false;
}

bool Test_InsertBefore_DoesntExist()
{
	bool pass = false;

	List<int> list;
	list.Append(2);

	try {
		list.InsertBefore(3, 7);
	}
	catch (Exception & e) {
		pass = true;
	}

	cout << "* Insert before value not found test... ";
	return pass;
}

bool Test_InsertAfter_Tail()
{
	List<int> list;
	list.Append(1);

	list.InsertAfter(2, 1);

	cout << "* Insert after tail test... ";
	return (list.GetHead()->GetData() == 1 && list.GetTail()->GetData() == 2) ? true : false;
}

bool Test_InsertAfter_Middle()
{
	List<int> list;
	list.Append(2);
	list.Append(4);

	list.InsertAfter(3, 2);

	cout << "* Insert after test... ";
	return (list.GetHead()->GetData() == 2 && list.GetTail()->GetData() == 4 &&
		list.GetHead()->GetNext()->GetData() == 3) ? true : false;
}

bool Test_InsertAfter_DoesntExist()
{
	bool pass = false;

	List<int> list;
	list.Append(2);

	try {
		list.InsertAfter(3, 7);
	}
	catch (Exception & e) {
		pass = true;
	}

	cout << "* Insert after value not found test... ";
	return pass;
}


bool Test_GetHead()
{
	List<int> list;
	int head = 1;

	list.Append(head);
	list.Append(2);

	cout << "* Get head test... ";
	return (list.GetHead()->GetData() == 1) ? true : false;
}

bool Test_GetTail()
{
	List<int> list;
	int tail = 2;

	list.Append(1);
	list.Append(tail);

	cout << "* Get tail test... ";
	return (list.GetTail()->GetData() == tail) ? true : false;
}

bool Test_OpEqual()
{
	bool pass = true;

	List<int> list;
	for (int i = 0; i < 10; i++)
	{
		list.Append(i);
	}

	List<int> listCpy;
	listCpy = list;

	//Check data integrity
	Node<int> * travler;
	Node<int> * travlerCpy;

	//via next pointers
	travler = list.GetHead();
	travlerCpy = listCpy.GetHead();

	while (travler != nullptr && travlerCpy != nullptr)
	{
		if (travler->GetData() != travlerCpy->GetData())
		{
			pass = false;
		}
		travler = travler->GetNext();
		travlerCpy = travlerCpy->GetNext();
	}

	//via previous pointers
	travler = list.GetTail();
	travlerCpy = listCpy.GetTail();

	while (travler != nullptr && travlerCpy != nullptr)
	{
		if (travler->GetData() != travlerCpy->GetData())
		{
			pass = false;
		}
		travler = travler->GetPrevious();
		travlerCpy = travlerCpy->GetPrevious();
	}

	cout << "* Operator= test... ";
	return pass;
}

bool Test_Cpy_Constructor()
{
	bool pass = true;

	List<int> list;
	for (int i = 0; i < 10; i++) {
		list.Append(i);
	}

	List<int> listCpy(list);

	//Check data integrity
	Node<int> * travler;
	Node<int> * travlerCpy;

	//via next pointers
	travler = list.GetHead();
	travlerCpy = listCpy.GetHead();

	while (travler != nullptr && travlerCpy != nullptr)
	{
		if (travler->GetData() != travlerCpy->GetData())
		{
			pass = false;
		}
		travler = travler->GetNext();
		travlerCpy = travlerCpy->GetNext();
	}

	//via previous pointers
	travler = list.GetTail();
	travlerCpy = listCpy.GetTail();

	while (travler != nullptr && travlerCpy != nullptr)
	{
		if (travler->GetData() != travlerCpy->GetData())
		{
			pass = false;
		}
		travler = travler->GetPrevious();
		travlerCpy = travlerCpy->GetPrevious();
	}

	cout << "* Copy constructor test... ";
	return pass;
}