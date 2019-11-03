/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		hashtable.h
* Date Created: 3/12/2019
*
* Class: HashTable
*
* Purpose: Makes a HashTable data structure
*
* Manager functions:
*	HashTable()
*		Sets the hashfunction to nullptr by default
*	HashTable(int(*hashFunc)(K key), int size)
*		Sets the hashfunction and size to the passed through hashfunction and size
*	~HashTable()
*	HashTable(const HashTable & copy)
*	HashTable & operator=(const HashTable & rhs)
* Methods:
*	void Insert(K key, V value)
*		Inserts a hashnode into the specifed hashed bucket
*	void SetHash(int(*hashFunc)(K key))
*		Sets the hashfunction to the one given and rehashes the table
*	V operator[](K key)
*		Returns the value of the node with the specified key
*	void Delete(K key)
*		Deletes the node with the specified key
*	void Traverse(void(*visit)(V value))
*		Traverses the HashTable calling the visit function on all nodes
*	inline void SetSize(int size)
*	inline int GetSize() const
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include <vector>
#include <list>
#include "exception.h"
#include "hashnode.h"
using std::vector;
using std::list;

template <typename K, typename V>
class HashTable
{
public:
	HashTable();
	HashTable(int(*hashFunc)(K key), int size);
	~HashTable();
	HashTable(const HashTable & copy);
	HashTable & operator=(const HashTable & rhs);
	void Insert(K key, V value);
	void SetHash(int(*hashFunc)(K key));
	V operator[](K key);
	void Delete(K key);
	void Traverse(void(*visit)(V value));
	inline void SetSize(int size) { m_table.resize(size); }
	inline int GetSize() const { return m_table.size(); }
private:
	vector<list<HashNode<K, V>>> m_table;
	int(*m_hashFunc)(K key);
	typename list<HashNode<K, V>>::iterator m_bucketIter;
};

template<typename K, typename V>
inline HashTable<K, V>::HashTable() : m_hashFunc(nullptr)
{}

/********************************************************************************************************************************************************************
* Purpose: Allows initalization of a hashtable with a given size and hashfunction
*
* Precondition:
*	None
*
* Postcondition:
*	Creates a hashtable object with the specified size and hashfunction
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(int(*hashFunc)(K key), int size) : m_hashFunc(hashFunc), m_table(size)
{}

template<typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
	m_hashFunc = nullptr;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable & copy) : m_table(copy.m_table), m_hashFunc(copy.m_hashFunc)
{}

template<typename K, typename V>
inline HashTable<K, V> & HashTable<K, V>::operator=(const HashTable & rhs)
{
	if (&rhs != this)
	{
		m_hashFunc = rhs.m_hashFunc;
		m_table = rhs.m_table;
	}
	return *this;
}

/********************************************************************************************************************************************************************
* Purpose: Inserts the given value and key into the hashtable at the index hashed from the given key
*
* Precondition:
*	The hashnode key must not already exist otherwise an exception is thrown
*
* Postcondition:
*	Creates a hashnode with the specified key and value then places it in the appropriate hashed spot within the table
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	bool foundDupKey = false;
	int index = m_hashFunc(key);
	HashNode<K, V> newNode(key, value);
	m_bucketIter = m_table[index].begin();
	while (!foundDupKey && m_bucketIter != m_table[index].end())
	{
		if (m_bucketIter->m_key == key)
			foundDupKey = true;
		else
			++m_bucketIter;
	}
	if (foundDupKey)
		throw Exception("Cannot insert duplicate key");
	m_table[index].push_back(newNode);
}

/********************************************************************************************************************************************************************
* Purpose: Sets the hash function to the one passed through and rehashes the table with the new function
*
* Precondition:
*	None
*
* Postcondition:
*	Sets *this to a new hashtable where the data from the original hashtable was reinserted with the new function
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::SetHash(int(*hashFunc)(K key))
{
	if (hashFunc != m_hashFunc) //Only rehash if the new hashFunc is the same as the current one
	{
		HashTable<K, V> newTable(hashFunc, m_table.size());
		for (int i = 0; i < m_table.size(); ++i) //For each table index
		{
			for (m_bucketIter = m_table[i].begin(); m_bucketIter != m_table[i].end(); ++m_bucketIter) //Rehash all items in the bucket
			{
				newTable.Insert(m_bucketIter->m_key, m_bucketIter->m_value);
			}
		}
		*this = newTable; //Set the current object to the newly hashed one
	}
}

/********************************************************************************************************************************************************************
* Purpose: Returns the value of the node from the table with the specified key
*
* Precondition:
*	The hashnode key must exist otherwise an exception is thrown
*
* Postcondition:
*	Returns the V value of the found hashnode with the matching key
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline V HashTable<K, V>::operator[](K key)
{
	bool found = false;
	int index = m_hashFunc(key);
	m_bucketIter = m_table[index].begin();
	while (!found && m_bucketIter != m_table[index].end()) //Search until the key is found or until the whole bucket has been searched
	{
		if (m_bucketIter->m_key == key)
			found = true;
		else
			++m_bucketIter;
	}
	if (!found)
		throw Exception("Could not find specified key");
	return m_bucketIter->m_value;
}

/********************************************************************************************************************************************************************
* Purpose: Deletes the node with the given key from the table
*
* Precondition:
*	The hashnode key must exist otherwise an exception is thrown
*
* Postcondition:
*	Removes the hashnode from the table with the specified key
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::Delete(K key)
{
	bool found = false;
	int index = m_hashFunc(key);
	m_bucketIter = m_table[index].begin();
	while (!found && m_bucketIter != m_table[index].end())
	{
		if (m_bucketIter->m_key == key)
			found = true;
		else
			++m_bucketIter;
	}
	if (!found)
		throw Exception("Could not find specified key");
	m_table[index].erase(m_bucketIter);
}

/********************************************************************************************************************************************************************
* Purpose: Calls the passed through visit function on each hashnode
*
* Precondition:
*	None
*
* Postcondition:
*	Calls visit on each node in the table
*********************************************************************************************************************************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::Traverse(void(*visit)(V value))
{
	for (int i = 0; i < m_table.size(); ++i) //For each table index
	{
		for (m_bucketIter = m_table[i].begin(); m_bucketIter != m_table[i].end(); ++m_bucketIter) //Visit each node in the bucket
		{
			visit(m_bucketIter->m_value);
		}
	}
}