/********************************************************************************************************************************************************************
* Lab/Assignment: Lab 5 - Dijkstra's Shortest Path
*
* Overview:
*	This program reads a file and creates a graph data structure from it. Then, using Dijkstra's shortest path algorithm, it calculates the fastest path
*		between user specified points on the graph.
*
* Input:
*	The user will input a starting destination and an ending destination. Their input must correspond to destinations on the map (vertices on the graph)
*	The map (graph) will be built off of the input file "map.txt"
* Output:
*	The program will output the shortest path between the starting destination and ending destination in the form of steps:
*	For example if the user specified Klamath Falls as the start and Klamath Falls as the destination it would output:
*		To go from Klamath Falls to Ashland take the following directions:
*		1. Take Hwy 66 to Keno
*		2. Take Hwy 66 to Ashland
*
*		The route is a total distance of 57 miles and will take at least 1 hour(s) 2 minute(s) and 10 second(s)
*********************************************************************************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "graph.h"
using std::string;
using std::ifstream;
using std::getline;
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::vector;
using std::stack;

int IGNORE = 1000;

/**********************************************************************************************************************************************************************************************************************
* Purpose: Checks if the vertex with the specified data exists in the passed through graph
*
* Precondition:
*		None
*
* Postcondition:
*		Returns true if the vertex exists
*		Returns false otherwise
***********************************************************************************************************************************************************************************************************************/
bool DoesVertexExist(Graph<string, string> * graph, string data)
{
	bool isFound = false;
	list<Vertex<string, string>> vertices = graph->GetVertices();
	list<Vertex<string, string>>::iterator iter;
	for (iter = vertices.begin(); iter != vertices.end() && !isFound; ++iter)
	{
		if (iter->GetData() == data)
			isFound = true;
	}
	return isFound;
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Loads a graph from the file "map.txt"
*
* Precondition:
*		None
*
* Postcondition:
*		Loads data from the file into the passed through graph. Returns true if the file was opened successfully
*		Returns false otherwise
***********************************************************************************************************************************************************************************************************************/
bool LoadGraph(Graph<string, string> * graph)
{
	bool success = true;
	ifstream inFile;
	inFile.open("map.txt");
	string vertexData, endVertData, edgeData;
	int weight;
	if (inFile.is_open())
	{
		while (!inFile.eof()) //Fill in all vertices
		{
			getline(inFile, vertexData, ',');
			if (!DoesVertexExist(graph, vertexData)) //If the vertex has not yet be inserted, insert it
				graph->InsertVertex(vertexData);//Insert vertex
			getline(inFile, vertexData, ',');
			if (!DoesVertexExist(graph, vertexData)) //Check the if the destination is unincluded as a vertex
				graph->InsertVertex(vertexData); //Insert vertex
			inFile.ignore(IGNORE, '\n');
		}
		inFile.seekg(0, std::ios::beg); //Go back to the start of the file to fill in all edges
		while (!inFile.eof()) //Gather the data for each edge
		{
			getline(inFile, vertexData, ',');
			getline(inFile, endVertData, ',');
			getline(inFile, edgeData, ',');
			inFile >> weight;
			inFile.ignore();
			graph->InsertEdge(vertexData, endVertData, edgeData, weight); //Insert edges that represent the found data
		}


	}
	inFile.close();
	return success;
}


/**********************************************************************************************************************************************************************************************************************
* Purpose: Displays the shortest path
*
* Precondition:
*		A shortest was calculated
*
* Postcondition:
*		Outputs the console the path from start to end in addition to given total distance (edge weight) and time to cross the path
***********************************************************************************************************************************************************************************************************************/
void DisplayPath(vector<int> & distance, vector<int> & predecessor, vector<Vertex<string, string>> & vertArr, string end)
{
	list<Edge<string, string>> edgeList;
	list<Edge<string, string>>::iterator edgeIter;
	stack <int> routeStack;
	int currVert, nextVert;
	bool done = false;


	for (int i = 0; !done; ++i) //Find the end vertex index to start from
	{
		if (vertArr[i].GetData() == end)
		{
			done = true;
			currVert = i;
		}
	}
	done = false;

	routeStack.push(currVert);
	while (!done)	// Creates a stack of the route for the purpose of reversal (as the shortest path algorithm gives the path from destination to start)
	{
		currVert = predecessor[currVert];
		if (currVert == -1) //We are at the last 
			done = true;
		else
			routeStack.push(currVert);
	}

	currVert = routeStack.top();
	routeStack.pop();
	cout << "To go from " << vertArr[0].GetData() << " to " << end << " take the following directions:\n";
	int directionNum = 1;
	int totalDistance = 0;
	double totalTime = 0;
	while (!routeStack.empty())
	{
		done = false;
		nextVert = routeStack.top();
		routeStack.pop();
		
		edgeList = vertArr[currVert].GetEdges();
		edgeIter = edgeList.begin();

		while (!done)	//Loop to find the edge that links the current vertex to the next vertex
		{
			if (edgeIter->GetVertex()->GetData() == vertArr[nextVert].GetData())
				done = true;
			else
				++edgeIter;
		}
		cout << directionNum << ". Take " << edgeIter->GetData() << " to " << vertArr[nextVert].GetData() << endl;
		++directionNum;
		totalDistance += edgeIter->GetWeight();

		if (edgeIter->GetData() == "I-5")	//Increase the total time by the time it takes to cross the edge. I-5 is 65 mph and others are 55 mph
			totalTime += static_cast<double>(edgeIter->GetWeight()) / 65;
		else
			totalTime += static_cast<double>(edgeIter->GetWeight()) / 55;

		currVert = nextVert;
	}
	int hours = totalTime; //Cut off the decimal place to give hours
	int minutes = totalTime * 60; //Cut off decimal place * 60 for total minutes then subtract the hours in minutes for remainder minutes
	minutes = minutes - (hours * 60);
	int seconds = (totalTime * 3600); //Cut off decimal place * 3600 for total seconds then subtract the hours in minutes and the minutes in seconds for remainder minutes
	seconds = seconds - ((hours * 3600) + (minutes * 60));
	cout << "\nThe route is " << totalDistance << " miles and will take at least " << hours << " hour(s) " << minutes
		<< " minute(s) and " << seconds << " second(s)\n";
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Finds the shortest path between vertices "start" and "end"
*
* Precondition:
*		None
*
* Postcondition:
*		Returns true if there is no head and so there is no list
*		Returns false otherwise
***********************************************************************************************************************************************************************************************************************/
void FindShortestPath(Graph<string, string> * graph, string start, string end)
{
	vector<int> distance(graph->GetVertices().size(), -1);
	vector<int> predecessor(graph->GetVertices().size(), -1);
	vector<Vertex<string, string>> vertArr(graph->GetVertices().size());
	list<Vertex<string, string>> vertList = graph->GetVertices();
	list<Edge<string, string>> edgeList;
	list<Vertex<string, string>>::iterator vertIter;
	list<Edge<string, string>>::iterator edgeIter;

	int currVert, vertNum;
	vertIter = vertList.begin();
	bool found = false;
	while (!found)
	{
		if (vertIter->GetData() == start) //Find the start and set it as index 0
		{
			vertArr[0] = *vertIter;
			found = true;
		}
		++vertIter;
	}
	for (vertNum = 1; vertIter != vertList.end(); ++vertIter, ++vertNum) //Place all vertices past the starting vertex in the array. Putting vertices in this array gives them a numeric "key"
	{
		vertArr[vertNum] = *vertIter;
	}
	found = false;
	for (vertIter = vertList.begin(); !found; ++vertIter, ++vertNum) //Wrap around. Placing all vertices from the beginning of the vertex list up to the start vertex into the array
	{
		if (vertIter->GetData() == start)
			found = true;
		else
			vertArr[vertNum] = *vertIter;
	}

	currVert = 0;
	distance[0] = 0; //Distance of the start from itself is zero
	int smallest; //Used for finding the next vertex to calculate

	for (int i = 0; i < vertArr.size(); ++i) //For every vertex
	{
		edgeList = vertArr[currVert].GetEdges(); //Stores the edges of the current vertex
		for (edgeIter = edgeList.begin(); edgeIter != edgeList.end(); ++edgeIter) //For each edge of the current vertex
		{
			for (int j = 0; j < vertArr.size(); ++j) //Go through each vertex to check for match between what the edge points to and an index for a vertex in vertArr
			{
				if (vertArr[j].GetData() == edgeIter->GetVertex()->GetData()) //When the matching vertex is found
				{
					if (distance[j] > (distance[currVert] + edgeIter->GetWeight()) || distance[j] == -1)
					{
						distance[j] = distance[currVert] + edgeIter->GetWeight();
						predecessor[j] = currVert;
					}
				}
			}
		}
		vertArr[currVert].SetProcessed(true);
		smallest = -1;
		for (int k = 0; k < vertArr.size(); ++k) //Calculate the next vertex
		{
			if (!vertArr[k].isProcessed() && distance[k] != -1) //Ensure the vertex hasn't been processed but also that it has been mentioned
			{
				if (smallest == -1 || distance[k] < distance[smallest]) //Find the vertex with the smallest distance and use that as the current
					smallest = k;
			}
		}
		currVert = smallest;
	}

	DisplayPath(distance, predecessor, vertArr, end);
}

/**********************************************************************************************************************************************************************************************************************
* Purpose: Formats entered strings so they will match up with Vertex data strings
*
* Precondition:
*		None
*
* Postcondition:
*		Returns strings in a form where the first letter of each word is capitalized and all else is lower case
*			Ex. kLAmatH fALLs -> -> -> Klamath Falls
***********************************************************************************************************************************************************************************************************************/
void FormatString(string & str)
{
	int length = str.length();
	if (length > 0)
		str[0] = toupper(str[0]);
	for (int i = 1; i < length; ++i)
	{
		if (str[i] == ' ' && str.substr(i + 1, 3) != "and" && str.substr(i + 1, 3) != "And" && str.substr(i + 1, 3) != "ANd" && str.substr(i + 1, 3) != "AND" && str.substr(i + 1, 3) != "aNd"
			&& str.substr(i + 1, 3) != "AnD")
		{
			str[i + 1] = toupper(str[i + 1]);
			++i;
		}
		else
			str[i] = tolower(str[i]);
	}
}

template <typename V>
void Visit(V data)
{
	cout << data << " ";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	string start;
	string end;
	Graph<string, string> map;
	bool validIn = false;
	string input;
	int cat = 1;
	if (LoadGraph(&map))
	{

		while (!validIn)
		{
			cout << "Enter where you would like to start: ";
			getline(cin, start);
			FormatString(start);
			if (!DoesVertexExist(&map, start))
			{
				cout << "The location you entered does not exist\n";
			}
			else
				validIn = true;
		}

		validIn = false;
		while (!validIn)
		{
			cout << "Enter your destination: ";
			getline(cin, end);
			FormatString(end);
			if (!DoesVertexExist(&map, end))
			{
				cout << "The location you entered does not exist\n";
			}
			else if (start == end)
				cout << "You are already there!\n";
			else
				validIn = true;
		}

		FindShortestPath(&map, start, end);
	}
	else
		cout << "Could not load map.txt\n";

	return 0;
}