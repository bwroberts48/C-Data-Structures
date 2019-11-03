#include <crtdbg.h>
#include "arrstack.h"
#include <iostream>
using std::cout;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ArrStack<int> myStack(5);
	ArrStack<int> myStack2(myStack);
	ArrStack<int> myStack3 = myStack2;
	ArrStack<int> defaultStack;
	/********************* Push and Pop Test **************/
	int stackData[5];
	for (int i = 0; i < myStack.Size(); i++)
	{
		myStack.Push(i);
		stackData[i] = i;
	}
	int counter = 0;
	for (int i = myStack.Size() - 1; i >= 0; i--)
	{
		if (stackData[i] == myStack.Pop())
			counter++;
	}
	if (counter == 5)
		cout << "Push and Pop Work!\n";

	/*************************** Overflow Test **********************/
	for (int i = 0; i < myStack.Size(); i++)
		myStack.Push(i);
	try
	{
		myStack.Push(50);
	}
	catch (Exception &exception)
	{
		cout << "Overflow Test Passed\n";
	}

	/*************************** Underflow Test ***********************/
	for (int i = 0; i < myStack.Size(); i++)
		myStack.Pop();
	try
	{
		myStack.Pop();
	}
	catch (Exception &exception)
	{
		cout << "Underflow Test Passed\n";
	}

	/*************************** Peek Test ****************************/
	for (int i = 0; i < myStack.Size(); i++)
	{
		myStack.Push(i);
		stackData[i] == myStack.Peek();
	}
	counter = 0;
	for (int i = myStack.Size() - 1; i >= 0; i--)
	{
		if (stackData[i] == myStack.Pop())
			counter++;
	}
	if (counter == 5)
		cout << "Peek Works\n";

	/*************************** Empty and Full Test ****************************/
	bool fBefore = myStack.isFull();
	bool eBefore = myStack.isEmpty();
	for (int i = 0; i < myStack.Size(); i++)
	{
		myStack.Push(i);
	}
	bool fAfter = myStack.isFull();
	bool eAfter = myStack.isEmpty();
	if (fBefore == false && fAfter == true && eBefore == true && eAfter == false)
		cout << "isFull and isEmpty checks passed\n";
	/*************************** Resize Test ****************************/
	bool passed = true;
	myStack.SetSize(3);
	if (myStack.Peek() != 2)
		passed = false;
	myStack.SetSize(0);
	if (!myStack.isEmpty())
		passed = false;
	while (!myStack.isEmpty())
		myStack.Pop();
	myStack.SetSize(100);
	try
	{
		for (int i = 0; i < myStack.Size(); i++)
			myStack.Push(i);
	}
	catch (Exception &exception)
	{
		passed = false;
	}
	if (passed == true)
		cout << "Resize tests passed\n";
	return 0;
}