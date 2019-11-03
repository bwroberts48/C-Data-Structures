/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		graph.h
* Date Created: 3/6/2019
*
* Class: Graph
*
* Purpose: Makes a Graph data structure
*
* Manager functions:
*	Graph()
*		Its vertex list and vertex list iterator stays as default
*	~Graph()
*	Graph(const Graph & copy)
*	Graph & operator=(const Graph & rhs)
* Methods:
*	void InsertVertex(V data)
*		Inserts a Vertex at the end of the list
*	void DeleteVertex(V data)
*		Deletes a vertex with the specified data
*	void InsertEdge(V start, V end, E data, int weight, bool insertOnlyArc = false)
*		Inserts an edge between the specified vertices. Only creates an arc between start and end if insertOnlyArc is set to true
*	void DeleteEdge(V start, V end, E data)
*		Removes the edge between the specified vertices
*	void DepthFirst(void(*visit)(V data))
*		Executes the passed through visit function on each vertex in a depthfirst order
*	void BreadthFirst(void(*visit)(V data))
*		Executes the passed through visit funciton on each vertex in a breadth-first order
*	void ResetVertices()
*		Sets every vertex's m_processed to false
*	inline bool isEmpty()
*	list<Vertex<V, E>> GetVertices() const
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include "vertex.h"


template <typename V, typename E>
class Graph
{
public:
	Graph();
	~Graph();
	Graph(const Graph & copy);
	Graph & operator=(const Graph & rhs);
	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertEdge(V start, V end, E data, int weight, bool insertOnlyArc = false);
	void DeleteEdge(V start, V end, E data);
	void DepthFirst(void(*visit)(V data));
	void BreadthFirst(void(*visit)(V data));
	void ResetVertices();
	inline bool isEmpty() { return m_vertices.empty() ? true : false; }
	list<Vertex<V, E>> GetVertices() const{ return m_vertices; }
private:

	list<Vertex<V, E>> m_vertices;
	typename list<Vertex<V, E>>::iterator m_vertexIter;
};


template<typename V, typename E>
Graph<V, E>::Graph()
{}

template<typename V, typename E>
Graph<V, E>::~Graph()
{}

template<typename V, typename E>
Graph<V, E>::Graph(const Graph & copy)
{
	typename list<Vertex<V, E>>::const_iterator vertIter;
	typename list<Edge<V, E>>::const_iterator edgeIter;
	list<Edge<V, E>> edges;
	for (vertIter = copy.m_vertices.begin(); vertIter != copy.m_vertices.end(); ++vertIter) //Copy vertices (without edges) into the new vertex list
		InsertVertex(vertIter->GetData());

	for (vertIter = copy.m_vertices.begin(); vertIter != copy.m_vertices.end(); ++vertIter) // Step through copy's vertex list
	{
		if (!vertIter->isEdgesEmpty()) //Only work with edges if the current edge list is not empty
		{
			edges = vertIter->GetEdges();
			for (edgeIter = edges.begin(); edgeIter != edges.end(); ++edgeIter)	//Step through the given edge list of copy's vertex and insert an Arc into the new graph pointing to a new vert
				InsertEdge(vertIter->GetData(), edgeIter->GetVertex()->GetData(), edgeIter->GetData(), edgeIter->GetWeight(), true);
		}
	}
}

template<typename V, typename E>
Graph<V, E> & Graph<V, E>::operator=(const Graph & rhs)
{
	if (&rhs != this)
	{
		typename list<Vertex<V, E>>::const_iterator vertIter;
		typename list<Edge<V, E>>::const_iterator edgeIter;
		list<Edge<V, E>> edges;
		for (vertIter = rhs.m_vertices.begin(); vertIter != rhs.m_vertices.end(); ++vertIter) //Copy vertices (without edges) into the new vertex list
			InsertVertex(vertIter->GetData());

		for (vertIter = rhs.m_vertices.begin(); vertIter != rhs.m_vertices.end(); ++vertIter) // Step through copy's vertex list
		{
			if (!vertIter->isEdgesEmpty()) //Only work with edges if the current edge list is not empty
			{
				edges = vertIter->GetEdges();
				for (edgeIter = edges.begin(); edgeIter != edges.end(); ++edgeIter)	//Step through the given edge list of copy's vertex and insert an Arc into the new graph pointing to a new vert
					InsertEdge(vertIter->GetData(), edgeIter->GetVertex()->GetData(), edgeIter->GetData(), edgeIter->GetWeight(), true);
			}
		}
	}
	return *this;
}

/********************************************************************************************************************************************************************
* Purpose: Appends a vertex to the vertex list of the specified data
*
* Precondition:
*	The vertex data must not already exist otherwise an exception is thrown
*
* Postcondition:
*	A vertex is created with an empty edge list at the end of the vertex list
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertVertex(V data)
{
	for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end(); ++m_vertexIter) //Throw an exception the vertex list has the same data as another vertex to force unique keys
	{
		if ((*m_vertexIter).GetData() == data)
			throw Exception("Cannot have duplicate vertex data\n");
	}
	Vertex<V, E> newVertex(data);
	m_vertices.push_back(newVertex);
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to remove a vertex with the specified data
*
* Precondition:
*	A vertex with the specified data must exist otherwise an exception is thrown
*
* Postcondition:
*	The Vertex is removed from the list and any edges in the list that pointed to that vertex are erased as well
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(V data)
{
	bool found = false;
	m_vertexIter = m_vertices.begin();
	while (m_vertexIter != m_vertices.end() && !found)
	{
		if ((*m_vertexIter).GetData() == data)
		{
			typename list<Vertex<V, E>>::iterator tempIter = m_vertexIter;
			for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end(); ++m_vertexIter)
				(*m_vertexIter).DeleteEdgeIfExists(data);
			m_vertexIter = m_vertices.erase(tempIter);
			found = true;
		}
		else
			++m_vertexIter;
	}
	if (!found)
		throw Exception("Could not find vertex data for deletion");
}

/********************************************************************************************************************************************************************
* Purpose: Inserts an edge between two the vertices with matching data. The edge has the specified data and weight. If insertOnlyArc is true then only an arc is created
*			from the start to end vertex
*
* Precondition:
*	Vertices with the start and end vertex must exist, otherwise an exception is thrown
*
* Postcondition:
*	Inserts an edge (or arc from start to end if flagged)
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertEdge(V start, V end, E data, int weight, bool insertOnlyArc)
{
	bool startFound = false;
	bool endFound = false;
	Vertex<V, E> * startVert;
	Vertex<V, E> * endVert;
	typename list<Vertex<V, E>>::iterator findStart; //Iters to hold the location of the start and end vertex's
	typename list<Vertex<V, E>>::iterator findEnd;
	for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end() && (!startFound || !endFound); ++m_vertexIter) //Iterate until the end or until both desired vertices are found
	{
		if ((*m_vertexIter).GetData() == start)
		{
			startVert = &(*m_vertexIter);
			findStart = m_vertexIter;
			startFound = true;
		}
		if ((*m_vertexIter).GetData() == end)
		{
			endVert = &(*m_vertexIter);
			findEnd = m_vertexIter;
			endFound = true;
		}
	}
	if (!startFound || !endFound)
		throw Exception("Could not find start and/or end for edge insertion");

	Edge<V, E> startToEnd(data, endVert, weight);	//Construct edges and insert them at the locations saved in findStart and findEnd
	(*findStart).InsertEdge(startToEnd);
	if (!insertOnlyArc)
	{
		Edge<V, E> endToStart(data, startVert, weight);
		if (findStart != findEnd)						//Do not insert both edges if it is a loop
			(*findEnd).InsertEdge(endToStart);
	}
}

/********************************************************************************************************************************************************************
* Purpose: Removes an edge with the specified data
*
* Precondition:
*	Removes the edge that is between vertices matching the data start and end.
*
* Postcondition:
*	The connection between the vertices are removed
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteEdge(V start, V end, E data)
{
	bool startFound = false;
	bool endFound = false;
	Vertex<V, E> * startVert;
	Vertex<V, E> * endVert;
	typename list<Vertex<V, E>>::iterator findStart; //Iters to hold the location of the start and end vertices
	typename list<Vertex<V, E>>::iterator findEnd;
	for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end() && (!startFound || !endFound); ++m_vertexIter) //Iterate until the end or until both desired vertices are found
	{
		if ((*m_vertexIter).GetData() == start)
		{
			startVert = &(*m_vertexIter);
			findStart = m_vertexIter;
			startFound = true;
		}
		if ((*m_vertexIter).GetData() == end)
		{
			endVert = &(*m_vertexIter);
			findEnd = m_vertexIter;
			endFound = true;
		}
	}
	if (!startFound || !endFound)
		throw Exception("Could not find start and/or end for edge insertion");
	(*findStart).DeleteEdge(data);
	(*findEnd).DeleteEdge(data);
}

/********************************************************************************************************************************************************************
* Purpose: Executes the passed through Visit function on each piece of data in the graph
*
* Precondition:
*	The graph cannot be empty otherwise an exception is thrown
*
* Postcondition:
*	Executes visit on each data piece in the graph depthfirst
*********************************************************************************************************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::DepthFirst(void(*visit)(V data))
{
	typename list<Edge<V, E>>::iterator edgeIter;
	list<Edge<V, E>> edges;
	stack<Vertex<V, E>> depthStack;
	Vertex<V, E>  temp;

	if (isEmpty())
		throw Exception("Cannot traverse empty graph");
	depthStack.push(m_vertices.front());
	m_vertices.front().SetProcessed(true);
	while (!depthStack.empty())
	{
		temp = depthStack.top();
		depthStack.pop();
		visit(temp.GetData());
		if(!temp.isEdgesEmpty())
			edges = temp.GetEdges();
		for (edgeIter = edges.begin(); edgeIter != edges.end(); ++edgeIter)
		{
			if (!(*edgeIter).GetVertex()->isProcessed())
			{
				depthStack.push(*((*edgeIter).GetVertex()));
				(*edgeIter).GetVertex()->SetProcessed(true);
			}
		}
	}
	ResetVertices();
}

/********************************************************************************************************************************************************************
* Purpose: Executes the passed through Visit function on each piece of data in the graph
*
* Precondition:
*	The graph cannot be empty otherwise an exception is thrown
*
* Postcondition:
*	Executes visit on each data piece in the graph breadth-first
*********************************************************************************************************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::BreadthFirst(void(*visit)(V data))
{
	typename list<Edge<V, E>>::iterator edgeIter;
	list<Edge<V, E>> edges;
	queue<Vertex<V, E>> breQueue;
	Vertex<V, E>  temp;

	if (isEmpty())
		throw Exception("Cannot traverse empty graph");
	breQueue.push(m_vertices.front());
	m_vertices.front().SetProcessed(true);
	while (!breQueue.empty())
	{
		temp = breQueue.front();
		breQueue.pop();
		visit(temp.GetData());
		if(!temp.isEdgesEmpty())
			edges = temp.GetEdges();
		for (edgeIter = edges.begin(); edgeIter != edges.end(); ++edgeIter)
		{
			if (!(*edgeIter).GetVertex()->isProcessed())
			{
				breQueue.push(*((*edgeIter).GetVertex()));
				(*edgeIter).GetVertex()->SetProcessed(true);
			}
		}
	}
	ResetVertices();
}

/********************************************************************************************************************************************************************
* Purpose: Sets every vertex to be not processed (For use after a traversal)
*
* Precondition:
*	None
*
* Postcondition:
*	Each vertex in the graph is set to not being processed through setting their m_processed to false
*********************************************************************************************************************************************************************/
template<typename V, typename E>
void Graph<V, E>::ResetVertices()
{
	for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end(); ++m_vertexIter)
		(*m_vertexIter).SetProcessed(false);
}