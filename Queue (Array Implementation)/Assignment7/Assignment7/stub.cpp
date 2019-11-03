#include <crtdbg.h>
#include <iostream>
#include "arrqueue.h"
using std::cout;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ArrQueue<int> myQ(5);
	ArrQueue<int> myQ2(myQ);
	ArrQueue<int> myQ3 = myQ;
	/********************* Enqueue and Dequeue Test **************/
	int qData[5];
	for (int i = 0; i < myQ.Size(); i++)
	{
		myQ.Enqueue(i);
		qData[i] = i;
	}
	int counter = 0;
	for (int i = 0; i < myQ.Size(); i++)
	{
		if (qData[i] == myQ.Dequeue())
			counter++;
	}
	if (counter == myQ.Size())
		cout << "Enqueue and Dequeue Work!\n";
	/*********************** Exception Tests ***************************************/
	try
	{
		myQ.Dequeue();
	}
	catch (Exception &exception)
	{
		cout << "Underflow Test Passed\n";
	}
	try
	{
		myQ.Front();
	}
	catch (Exception &exception)
	{
		cout << "Front Exception Passed\n";
	}
	for (int i = 0; i < myQ.Size(); i++)
		myQ.Enqueue(i);
	try
	{
		myQ.Enqueue(5);
	}
	catch (Exception &exception)
	{
		cout << "Overflow Test Passed\n";
	}
	while (!myQ.isEmpty())
		myQ.Dequeue();
	for (int i = 0; i < 3; i++)
		myQ.Enqueue(i);

	if (myQ.Front() == 0)
		cout << "Checked Front Successfully\n";
	myQ.Front() = 6;
	if (myQ.Front() == 6)
		cout << "Changed Front Successfully\n";
	return 0;
}