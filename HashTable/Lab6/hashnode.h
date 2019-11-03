/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		hashnode.h
* Date Created: 3/12/2019
*
* Class: HashNode
*
* Purpose: The node's that are stored in a hash bucket list
*
* Manager functions:
*	HashNode()
*		Has key and value set to default
*	HashNode(K key, V value)
*		Sets the key and value to the given key and value
*	~HashNode()
*	HashNode(const HashNode & copy)
*	HashNode & operator=(const HashNode & rhs)
* Methods:
*	None
***********************************************************************************************************************************************************************************************************************/
#pragma once
template<typename K, typename V>
class HashTable;

template<typename K, typename V>
class HashNode
{
	friend HashTable<K, V>;
public:
	HashNode();
	HashNode(K key, V value);
	~HashNode();
	HashNode(const HashNode & copy);
	HashNode & operator=(const HashNode & rhs);
private:
	K m_key;
	V m_value;
};

template<typename K, typename V>
HashNode<K, V>::HashNode()
{}

template<typename K, typename V>
HashNode<K, V>::HashNode(K key, V value) : m_key(key), m_value(value)
{}

template<typename K, typename V>
HashNode<K, V>::~HashNode()
{}

template<typename K, typename V>
HashNode<K, V>::HashNode(const HashNode & copy) : m_key(copy.m_key), m_value(copy.m_value)
{}

template<typename K, typename V>
HashNode<K, V> & HashNode<K, V>::operator=(const HashNode & rhs)
{
	if (&rhs != this)
	{
		m_key = rhs.m_key;
		m_value = rhs.m_value;
	}
	return *this;
}