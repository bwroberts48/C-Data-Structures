#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <iostream>
#include "bst.h"
using std::cout;
using std::endl;

template <typename T>
void Visit(BSTNode<T> * root)
{
	cout << root->GetData() << " ";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	BST<int> test;


	BST<int> other;
	other.Insert(1);
	other.Insert(2);
	other.Insert(3);
	other.Insert(4);
	other.Insert(5);
	other.PostOrderTrav(Visit);
	cout << endl;
	other.PreOrderTrav(Visit);
	cout << endl;
	/*********** Height Test 0 ***************/
	if (test.Height() == -1)
		cout << "Height of empty tree was correct\n";

	/************** Variety Insertion and Deletion Tests ****************/
	test.Insert(10);
	test.Insert(20);
	test.Insert(5);
	test.Insert(4);
	test.Insert(7);
	test.Insert(18);
	test.Insert(19);
	test.Insert(9);
	test.Insert(8);
	test.Insert(3);

	/**************** Height Test 1 **************/
	if (test.Height() == 4)
		cout << "Height after insertion was correct\n";

	test.InOrderTrav(Visit);
	cout << endl;
	test.Delete(3);
	test.Delete(9);
	test.Delete(20);
	test.Delete(5);
	test.Delete(10);
	test.InOrderTrav(Visit);
	/******************** Height Test 2 ***********************/
	if (test.Height() == 2)
		cout << "\nHeight after deletion was correct\n";

	/************************* Testing Traversals ***********************************/
	cout << "Breadth First: ";
	test.BreadthFirst(Visit);
	cout << endl;
	cout << "In Order: ";
	test.InOrderTrav(Visit);
	cout << endl;
	cout << "Pre Order: ";
	test.PreOrderTrav(Visit);
	cout << endl;
	cout << "Post Order: ";
	test.PostOrderTrav(Visit);
	cout << endl;

	/******************************** Testing "Data not Found for Deletion" Exception ******************************************************/
	try
	{
		test.Delete(500);
	}
	catch (Exception &except)
	{
		cout << "Deletion Exception Caught\n";
	}

	/***************************************** Testing OP= and Copy Constructor ***********************************************************************************************/
	BST<int> copy(test);
	BST<int> op = test;
	copy.Delete(4);
	op.Delete(4);
	test.Delete(4);
	cout << "Deletions of the same data in op=, copy constructor and original BST did not result in program failure\n";

	return 0;
}