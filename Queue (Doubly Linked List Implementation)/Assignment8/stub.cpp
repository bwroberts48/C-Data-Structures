#include <crtdbg.h>
#include <iostream>
#include "listqueue.h"
using std::cout;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ListQueue<int> myQ;
	ListQueue<int> myQ2(myQ);
	ListQueue<int> myQ3 = myQ;
	/********************* Enqueue and Dequeue Test **************/
	int qData[5];
	for (int i = 0; i < 5; i++)
	{
		myQ.Enqueue(i);
		qData[i] = i;
	}
	int counter = 0;
	for (int i = 0; i < 5; i++)
	{
		if (qData[i] == myQ.Dequeue())
			counter++;
	}
	if (counter == 5)
		cout << "Enqueue and Dequeue Work!\n";
	/*********************** Underflow Test ***************************************/
	try
	{
		myQ.Dequeue();
	}
	catch (Exception &exception)
	{
		cout << "Underflow Test Passed\n";
	}
	/************************* Front Tests *****************************/
	int i;
	for (i = 0; i < 3; i++)
		myQ.Enqueue(i);
	if (myQ.Front() == 0)
		cout << "Checked Front Successfully\n";
	myQ.Front() = 6;
	if (myQ.Front() == 6)
		cout << "Changed Front Successfully\n";
	/************************* Size and Empty Tests *****************************/
	if (myQ.Size() == i)
		cout << "Checked Size Successfully\n";
	bool emptyCheckPassed = true;
	if (myQ.isEmpty())
		emptyCheckPassed = false;
	while (myQ.Size())
		myQ.Dequeue();
	if (!myQ.isEmpty())
		emptyCheckPassed = false;
	if (emptyCheckPassed)
		cout << "Checked Emptiness Successfully\n";
	return 0;
}