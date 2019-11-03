/********************************************************************************************************************************************************************
* Lab/Assignment: Lab 6 - Hash Table
*
* Overview:
*	This program creates a Hash Table data structure
*
* Input:
*	None
* Output:
*	The program outputs the results of a series of tests for the Hash Table
*********************************************************************************************************************************************************************/
#include <iostream>
#include <string>
#include "hashtable.h"
using std::cout;
using std::endl;
using std::string;

const int TABLE_SIZE = 27;

struct Book
{
	string m_title;
	string m_author;
	int m_pages;
};

int HashFunc(string key)
{
	int hashVal = 0;
	for (int i = 0; i < key.length(); ++i)
		hashVal += key[i];
	return hashVal % TABLE_SIZE;
}

template<typename V>
void Visit(V value)
{
	cout << value.m_title << endl;
}

int main()
{
	HashTable<string, Book> table(HashFunc, TABLE_SIZE);
	Book temp = { "C++: An Active Learning Approach", "Randal Albert", 635 };
	table.Insert("0763757233", temp);
	Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp1);
	Book temp3 = { "And That n There", "Ralph Carestia", 1 };
	table.Insert("7063757234", temp3);
	cout << table["0763757233"].m_title << endl;
	cout << table["7063757233"].m_title << endl;
	cout << table["7063757234"].m_title << endl;
	cout << "\n\nTraversal testing\n";
	table.Traverse(Visit);
	cout << "\n\n";

	try
	{
		table.Insert("7063757234", temp3);
	}
	catch (Exception &except)
	{
		cout << "Reinsertion exception caught\n";
	}
	try
	{
		table.Delete("70");
	}
	catch (Exception &except)
	{
		cout << "Invalid deletion key exception caught\n";
	}
	try
	{
		table["70"];
	}
	catch (Exception &except)
	{
		cout << "Invalid access key exception caught\n";
	}
	return 0;
}