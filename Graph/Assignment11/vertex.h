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
	list<Edge<V, E>> GetEdges() const;
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

template<typename V, typename E>
void Vertex<V, E>::InsertEdge(Edge<V, E> edge)
{
	m_edges.push_back(edge);
}

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

template<typename V, typename E>
list<Edge<V, E>> Vertex<V, E>::GetEdges() const
{
	if (m_edges.empty())
		throw Exception("Cannot fetch empty edge list");
	return m_edges;
}