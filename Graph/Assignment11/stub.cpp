#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "graph.h"
using std::cout;
using std::endl;


template <typename V>
void Visit(V data)
{
	cout << data << " ";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Graph<char, int> test;
	test.InsertVertex('a');
	test.InsertVertex('b');
	test.InsertEdge('a', 'b', 4, 0, true);
	test.DeleteEdge('a', 'b', 4);
	///********************************************** Empty Traversal Tests **************************************************************************************/
	//try
	//{
	//	test.BreadthFirst(Visit);
	//}
	//catch (Exception &except)
	//{
	//	cout << "Empty BreadthFirst attempt exception caught\n";
	//}
	//try
	//{
	//	test.DepthFirst(Visit);
	//}
	//catch (Exception &except)
	//{
	//	cout << "Empty DepthFirst attempt exception caught\n";
	//}
	///********************************************** Insertion Data and Edges Tests **************************************************************************************/
	//test.InsertVertex('A');
	//test.InsertVertex('X');
	//test.InsertVertex('G');
	//test.InsertVertex('P');
	//test.InsertVertex('H');
	//test.InsertVertex('E');
	//test.InsertVertex('Y');
	//test.InsertVertex('M');
	//test.InsertVertex('J');
	//test.InsertEdge('A', 'X', 1, 0);
	//test.InsertEdge('X', 'G', 2, 0);
	//test.InsertEdge('X', 'H', 3, 0);
	//test.InsertEdge('H', 'E', 4, 0);
	//test.InsertEdge('H', 'P', 5, 0);
	//test.InsertEdge('G', 'P', 6, 0);
	//test.InsertEdge('E', 'M', 7, 0);
	//test.InsertEdge('E', 'Y', 8, 0);
	//test.InsertEdge('M', 'J', 9, 0);
	//try
	//{
	//	test.InsertVertex('A');
	//}
	//catch (Exception &except)
	//{
	//	cout << "Duplicate vertex exception caught\n";
	//}
	//try
	//{
	//	test.InsertEdge('M', 'B', 10, 0);
	//}
	//catch (Exception &except)
	//{
	//	cout << "Non-Existant vertex edge connection attempt exception caught\n";
	//}

	///********************************************** Traversal and Deletion Tests **************************************************************************************/
	//Graph<char, int> copy(test);
	//Graph<char, int> op(test);
	//cout << "DepthFirst Traversal: ";
	//test.DepthFirst(Visit);
	//cout << endl;
	//cout << "BreadthFirst Traversal: ";
	//test.BreadthFirst(Visit);
	//cout << endl << endl;
	//test.DeleteVertex('A');
	//test.DeleteEdge('H', 'E', 4);
	//cout << "After Deletion DepthFirst: ";
	//test.DepthFirst(Visit);
	//cout << endl;
	//cout << "After Deletion BreadthFirst: ";
	//test.BreadthFirst(Visit);
	//cout << endl;
	//try
	//{
	//	test.DeleteVertex('A');
	//}
	//catch (Exception &except)
	//{
	//	cout << "Unfound vertex deletion exception caught\n";
	//}
	//try
	//{
	//	test.DeleteEdge('H', 'E', 4);
	//}
	//catch (Exception &except)
	//{
	//	cout << "Unfound edge deletion exception caught\n";
	//}
	//cout << endl << endl << endl;
	///********************************************** Copy and OP= Integrity Tests **************************************************************************************/
	//cout << "The following traversals should match the one's outputted prior to deletion exactly\n";
	//cout << "Copy DepthFirst Traversal: ";
	//copy.DepthFirst(Visit);
	//cout << endl;
	//cout << "Copy BreadthFirst Traversal: ";
	//copy.BreadthFirst(Visit);
	//cout << endl;
	//cout << "OP= DepthFirst Traversal: ";
	//op.DepthFirst(Visit);
	//cout << endl;
	//cout << "OP= BreadthFirst Traversal: ";
	//op.BreadthFirst(Visit);

	return 0;
}