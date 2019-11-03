/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		vertex.h
* Date Created: 3/6/2019
*
* Class: Vertex
*
* Purpose: Makes a vertex to be held within the graph data structure
*
* Manager functions:
*	Vertex()
*		At default, the edgelist is empty, and processed is set to false
*	Vertex(V data);
*		Creates a vertex with the specified data
*	~Vertex();
*	Vertex(const Vertex & copy);
*	Vertex & operator=(const Vertex & rhs);
* Methods:
*	void InsertEdge(Edge<V, E> edge)
*		Inserts an edge into the vertex's edge list
*	void DeleteEdge(E data)
*		Deletes an edge from the vertex's edge list
*	bool DeleteEdgeIfExists(V data);
*		Deletes an edge that points to a vertex with the specified data from the vertex's edge list
*	inline void SetProcessed(bool processed)
*	inline bool isProcessed()
*	inline V GetData() const
*	inline bool isEdgesEmpty() const
*	list<Edge<V, E>> GetEdges() const
*	inline typename list<Edge<V, E>>::iterator GetEdgeIter()
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include <list>
#include <stack>
#include <queue>
#include <iterator>
#include "exception.h"
#include "edge.h"
using std::list;
using std::stack;
using std::queue;

template <typename V, typename E>
class Vertex
{
public:
	Vertex();
	Vertex(V data);
	~Vertex();
	Vertex(const Vertex & copy);
	Vertex & operator=(const Vertex & rhs);
	void InsertEdge(Edge<V, E> edge);
	void DeleteEdge(E data);
	bool DeleteEdgeIfExists(V data);
	inline void SetProcessed(bool processed) { m_processed = processed; }
	inline bool isProcessed() { return m_processed; }
	inline V GetData() const { return m_data; }
	inline bool isEdgesEmpty() const { return m_edges.empty(); }
	list<Edge<V, E>> GetEdges() const { return m_edges; };
	inline typename list<Edge<V, E>>::iterator GetEdgeIter() { return m_edgeIter; }
private:
	V m_data;
	list<Edge<V, E>> m_edges;
	typename list<Edge<V, E>>::iterator m_edgeIter;
	bool m_processed;
};

template<typename V, typename E>
Vertex<V, E>::Vertex() : m_processed(false)
{}

/********************************************************************************************************************************************************************
* Purpose: Creates a vertex with the specified data
*
* Precondition:
*	None
*
* Postcondition:
*	The vertex is given the passed through data
*********************************************************************************************************************************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(V data) : m_data(data), m_processed(false)
{}


template<typename V, typename E>
Vertex<V, E>::~Vertex()
{
	m_processed = false;
}

template<typename V, typename E>
Vertex<V, E>::Vertex(const Vertex & copy) : m_data(copy.m_data), m_edges(copy.m_edges), m_edgeIter(copy.m_edgeIter), m_processed(copy.m_processed)
{}

template<typename V, typename E>
Vertex<V, E> & Vertex<V, E>::operator=(const Vertex & rhs)
{
	if (&rhs != this)
	{
		m_data = rhs.m_data;
		m_edges = rhs.m_edges;
		m_edgeIter = rhs.m_edgeIter;
		m_processed = rhs.m_processed;
	}
	return *this;
}

/********************************************************************************************************************************************************************
* Purpose: Appends an edge to the edge list with the specified data
*
* Precondition:
*	None
*
* Postcondition:
*	The edge list of the current vertex is given an additional edge
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::InsertEdge(Edge<V, E> edge)
{
	m_edges.push_back(edge);
}

/********************************************************************************************************************************************************************
* Purpose: Deletes an edge with the specified edge data
*
* Precondition:
*	The edge data must exist to be deleted from the graph, otherwise an exception is thrown
*
* Postcondition:
*	Erases an edge form the current edge list
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::DeleteEdge(E data)
{
	bool found = false;
	m_edgeIter = m_edges.begin();
	while (m_edgeIter != m_edges.end() && !found)	//Deletes the first instance of the desired data if it exists
	{
		if ((*m_edgeIter).GetData() == data)
		{
			m_edgeIter = m_edges.erase(m_edgeIter);
			found = true;
		}
		else
			++m_edgeIter;
	}
	if (!found)
		throw Exception("Could not find edge data for deletion");
}

/********************************************************************************************************************************************************************
* Purpose: Deletes an edge that points to a vertex that has the specified data
*
* Precondition:
*	None
*
* Postcondition:
*	If an edge exists it is deleted and the function returns true
*	Otherwise, if the edge does not exist the function returns false
*********************************************************************************************************************************************************************/
template<typename V, typename E>
bool Vertex<V, E>::DeleteEdgeIfExists(V data)
{
	m_edgeIter = m_edges.begin();
	bool found = false;
	while (m_edgeIter != m_edges.end())
	{
		if (data == m_edgeIter->GetVertex()->m_data)
		{
			m_edgeIter = m_edges.erase(m_edgeIter);
			found = true;
		}
		else
			++m_edgeIter;
	}
	return found;
}