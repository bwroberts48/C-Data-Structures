/********************************************************************************************************************************************************************
* Lab/Assignment: Lab 4 - AVL Tree
*
* Overview:
*	This program is an AVL Tree data structure
*
* Input:
*	N/A
*
* Output:
*	The program runs a series of tests that will output the susccess of the AVL tree to rotate when items are deleted and inserted
*********************************************************************************************************************************************************************/
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include "exception.h"
#include "avl.h"
using std::cout;
using std::endl;

template <typename T>
void Visit(AVLNode<T> * root)
{
	cout << root->GetData() << " ";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	AVL<int> test;
	/******************* Traversal Exception Tests **************************************/
	bool notCaught = false;
	try
	{
		test.InOrderTrav(Visit);
		notCaught = true;
	}
	catch (Exception &except)
	{}

	try
	{
		test.PreOrderTrav(Visit);
		notCaught = true;
	}
	catch (Exception &except)
	{}

	try
	{
		test.PostOrderTrav(Visit);
		notCaught = true;
	}
	catch (Exception &except)
	{}

	try
	{
		test.BreadthFirst(Visit);
		notCaught = true;
	}
	catch (Exception &except)
	{}

	if (!notCaught)
		cout << "Traversal Exception Checks passed\n";

	/**************************************** Testing Deletion Exception ***********************************************************************************/
	try
	{
		test.Delete(6);
	}
	catch(Exception &except)
	{
		cout << "Deletion Exception Caught\n";
	}
	/**************************************** Insertion Tests and Traversal Tests ***********************************************************/
	test.Insert(8);
	test.Insert(9);
	test.Insert(10);
	test.Insert(2);
	test.Insert(1);
	test.Insert(5);
	test.Insert(3);
	test.Insert(6);
	test.Insert(4);
	test.Insert(7);
	test.Insert(11);
	test.Insert(13);

	test.InOrderTrav(Visit);
	cout << endl;
	test.PostOrderTrav(Visit);
	cout << endl;
	test.PreOrderTrav(Visit);
	cout << endl;
	test.BreadthFirst(Visit);

	cout << endl;
	test.Delete(8);
	test.Delete(9);
	test.Delete(13);
	test.Delete(10);
	test.Delete(5);
	test.InOrderTrav(Visit); //Testing traversal after deletion

	/********************************* Testing insertion after Deletion ****************************************************/
	test.Insert(0);
	test.Insert(9);
	
	/*********************************** Testing Height ***************************************************************************/
	if (test.Height() == 3)
		cout << "\nHeight was accurate\n";

	
	return 0;
}