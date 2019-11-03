#include <crtdbg.h>
#include "listStack.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ListStack<int> myStack;
	ListStack<int> myStack2(myStack);
	ListStack<int> myStack3 = myStack2;
	/********************* Push and Pop Test **************/
	int stackData[5];
	for (int i = 0; i < 5; i++)
	{
		myStack.Push(i);
		stackData[i] = i;
	}
	int counter = 0;
	for (int i = 4; i >= 0; i--)
	{
		if (stackData[i] == myStack.Pop())
			counter++;
	}
	if (counter == 5)
		cout << "Push and Pop Work!\n";

	/*************************** Underflow Test ***********************/
	try
	{
		for (int i = 0; i < 20; i++)
			myStack.Pop();
	}
	catch (Exception &exception)
	{
		cout << "Underflow Test Passed\n";
	}

	/*************************** Peek Test ****************************/
	for (int i = 0; i < 6; i++)
	{
		myStack.Push(i);
		stackData[i] == myStack.Peek();
	}
	counter = 0;
	for (int i = 5; i >= 0; i--)
	{
		if (stackData[i] == myStack.Pop())
			counter++;
	}
	if (counter == 5)
		cout << "Peek Works\n";

	/*************************** Empty Test ****************************/
	while (!myStack.isEmpty())
		myStack.Pop();
	bool eBefore = myStack.isEmpty();
	for (int i = 0; i < 10; i++)
	{
		myStack.Push(i);
	}
	bool eAfter = myStack.isEmpty();
	if (eBefore == true && eAfter == false)
		cout << "isEmpty checks passed\n";
	return 0;
}