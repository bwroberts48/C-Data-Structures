/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		edge.h
* Date Created: 3/6/2019
*
* Class: Edge
*
* Purpose: Makes an edge to be in a graph's vertex's edge list.
*
* Manager functions:
*	Edge()
*		By default, weight is 0 and m_vertex is set to nullptr
*	Edge(E data, Vertex<V, E> * dest, int weight)
*		Creates an edge that points to the specified vertex and has the specified data and weight
*	~Edge();
*	Edge(const Edge & copy);
*	Edge & operator=(const Edge & rhs);
* Methods:
*	E GetData() const { return m_data; }
*	int GetWeight() const { return m_weight; }
*	Vertex<V, E> * GetVertex() const { return m_vertex; }
*	void SetVertex(Vertex<V, E> vert) { m_vertex = &vert; }
***********************************************************************************************************************************************************************************************************************/
#pragma once

template<typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge
{
public:
	Edge();
	Edge(E data, Vertex<V, E> * dest, int weight);
	~Edge();
	Edge(const Edge & copy);
	Edge & operator=(const Edge & rhs);
	inline E GetData() const { return m_data; }
	inline int GetWeight() const { return m_weight; }
	inline Vertex<V, E> * GetVertex() const { return m_vertex; }
	inline void SetVertex(Vertex<V, E> vert) { m_vertex = &vert; }
private:
	E m_data;
	Vertex<V, E> * m_vertex;
	int m_weight;
};

template<typename V, typename E>
Edge<V, E>::Edge() : m_data(nullptr), m_vertex(nullptr), m_weight(0)
{}

/********************************************************************************************************************************************************************
* Purpose: Creates an edge that points to the specified vertex and has the specified data and weight
*
* Precondition:
*	None
*
* Postcondition:
*	Creates an edge with the specified data
*********************************************************************************************************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(E data, Vertex<V, E> * dest, int weight) : m_data(data), m_vertex(dest), m_weight(weight)
{}

template<typename V, typename E>
Edge<V, E>::~Edge()
{
	m_vertex = nullptr;
	m_weight = 0;
}

template<typename V, typename E>
Edge<V,E>::Edge(const Edge & copy) : m_data(copy.m_data), m_vertex(copy.m_vertex), m_weight(copy.m_weight)
{}

template<typename V, typename E>
Edge<V, E> & Edge<V, E>::operator=(const Edge & rhs)
{
	if (&rhs != this)
	{
		m_data = rhs.m_data;
		m_vertex = rhs.m_vertex;
		m_weight = rhs.m_weight;
	}
	return *this;
}