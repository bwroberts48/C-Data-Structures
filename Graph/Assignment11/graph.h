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

template<typename V, typename E>
void Graph<V, E>::ResetVertices()
{
	for (m_vertexIter = m_vertices.begin(); m_vertexIter != m_vertices.end(); ++m_vertexIter)
		(*m_vertexIter).SetProcessed(false);
}