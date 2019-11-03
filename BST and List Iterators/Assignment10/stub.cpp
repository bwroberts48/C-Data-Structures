#include <iostream>
#include "list.h"
#include "bst.h"

int main()
{
	bool success;
	List<int> myList;
	myList.Append(1);
	myList.Append(2);
	myList.Append(3);
	myList.Append(4);
	myList.Append(5);
	/************************************************** Iterator Creation ********************************************************************/
	ForwardIterator<int> forw = myList.ForwardBegin();
	BackwardIterator<int> back(myList.BackwardBegin());
	if (forw.GetCurrent() == myList.First() && back.GetCurrent() == myList.Last())
		cout << "Creation test passed\n";
	/**************************************************** Iteration Tests *****************************************************************/
	while (!forw.IsDone())
		forw.MoveNext();
	success = true;
	for (int i = 5; i > 3 && success; --i)
	{
		if (back.GetCurrent()!= i)
			success = false;
		back.MoveNext();
	}

	if (success)
		cout << "Base iteration tests complete\n";


	/******************************************************* Reset Tests ***************************************************************/
	success = false;
	try
	{
		forw.Reset();
	}
	catch (Exception &except)
	{
		cout << "Reset exception caught\n";
		success = true;
	}

	forw = myList.ForwardBegin();
	back.Reset();
	 
	if (forw.GetCurrent() == myList.First() && back.GetCurrent() == myList.Last() && success)
		cout << "Reset Tests passed\n";
	/******************************************************* Change Data Test ***************************************************************/
	forw.GetCurrent() = 500;
	back.GetCurrent() = 250;
	if (forw.GetCurrent() - back.GetCurrent() == 250)
		cout << "Change Data Test passed\n";

	/******************************************************* IsDone Tests ***************************************************************/
	success = true;
	if (forw.IsDone() || back.IsDone())
		success = false;
	forw = myList.ForwardEnd();
	back = myList.BackwardEnd();
	if (!forw.IsDone() || !back.IsDone())
		success = false;
	if (success)
		cout << "IsDone Tests passed\n";
	/******************************************************* GetCurrent Exception Tests ***************************************************************/
	success = true;
	try
	{
		forw.GetCurrent();
		success = false;
	}
	catch (Exception &except)
	{}

	try
	{
		back.GetCurrent();
		success = false;
	}
	catch (Exception  &except)
	{}

	if (success)
		cout << "GetCurrent Exceptions caught\n\n\n\n";

	/******************************************************************************************************************************************/
	/************************************************** BST Iterator Tests ********************************************************************/
	/******************************************************************************************************************************************/
	cout << "----------------BST ITERATOR TESTS------------\n\n";
	BST<int> myTree;
	myTree.Insert(3);
	myTree.Insert(2);
	myTree.Insert(4);
	myTree.Insert(1);
	myTree.Insert(5);
	/************************************************** Iterator Creation ********************************************************************/
	InOrderIterator<int> orde = myTree.InOrderIterBegin();
	PreOrderIterator<int> pre = myTree.PreOrderIterBegin();
	PostOrderIterator<int> post = myTree.PostOrderIterBegin();
	BreadthFirstIterator<int> brea = myTree.BreadthFirstIterBegin();
	/**************************************************** Iteration Tests *****************************************************************/
	success = true;
	for (int i = 1; !orde.IsDone(); i++)
	{
		if (orde.GetCurrent() != i)
			success = false;
		orde.MoveNext();
	}
	if (success)
		cout << "In Order Iteration passed. Examine the following numbers to confirm pre, post and breadth first orders\n\n";
	else
		cout << "In Order Iteration FAILED. Examine the following numbers to confirm pre, post and breadth first orders\n\n";
	cout << "Pre Order Test: ";
	for (int i = 1; !pre.IsDone(); i++)
	{
		cout << pre.GetCurrent() << " ";
		pre.MoveNext();
	}
	cout << "\nPost Order Test: ";
	for (int i = 1; !post.IsDone(); i++)
	{
		cout << post.GetCurrent() << " ";
		post.MoveNext();
	}
	cout << "\nBreadth First Order Test: ";
	for (int i = 1; !brea.IsDone(); i++)
	{
		cout << brea.GetCurrent() << " ";
		brea.MoveNext();
	}
	cout << "\n\n\n";
	/**************************************************** Reset Tests *****************************************************************/
	success = true;
	orde.Reset();
	pre.Reset();
	post.Reset();
	brea.Reset();
	for (int i = 1; !orde.IsDone(); i++)
	{
		if (orde.GetCurrent() != i)
			success = false;
		orde.MoveNext();
	}
	if (success)
		cout << "In Order Reset passed. Examine the following numbers to confirm pre, post and breadth first orders\n\n";
	else
		cout << "In Order Reset FAILED. Examine the following numbers to confirm pre, post and breadth first orders\n\n";

	cout << "\nPre Order Test: ";
	for (int i = 1; !pre.IsDone(); i++)
	{
		cout << pre.GetCurrent() << " ";
		pre.MoveNext();
	}
	cout << "\nPost Order Test: ";
	for (int i = 1; !post.IsDone(); i++)
	{
		cout << post.GetCurrent() << " ";
		post.MoveNext();
	}
	cout << "\nBreadth First Order Test: ";
	for (int i = 1; !brea.IsDone(); i++)
	{
		cout << brea.GetCurrent() << " ";
		brea.MoveNext();
	}
	cout << "\n\n\n";
	/******************************************************* GetCurrent Exception Tests ***************************************************************/
	try
	{
		orde.GetCurrent();
	}
	catch (Exception &except)
	{
		cout << "InOrder GetCurrent exception caught\n";
	}
	try
	{
		pre.GetCurrent();
	}
	catch (Exception &except)
	{
		cout << "PreOrder GetCurrent exception caught\n";
	}
	try
	{
		post.GetCurrent();
	}
	catch (Exception &except)
	{
		cout << "PostOrder GetCurrent exception caught\n";
	}
	try
	{
		brea.GetCurrent();
	}
	catch (Exception &except)
	{
		cout << "Breadth First GetCurrent exception caught\n";
	}
	return 0;
}