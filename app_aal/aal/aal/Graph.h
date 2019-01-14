#pragma once

#include <vector>
#include <iostream>
#include <string>

class Graph
{
private:
	std::vector<std::vector <std::pair <unsigned int, unsigned int> > > vertices;
	unsigned int number_of_vertices;
	unsigned int number_of_edges;

	void DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >&visited);
	std::vector<std::vector<bool>> createVisitedVector();
	std::vector<unsigned int> findEulerianCycle();
	unsigned int lengthOfAllEdges(); //is used, when graph has an eulerian cycle. it gets length of the cycle
	void makeEulerianGraph(std::vector<unsigned int>& oddVertices); //graph isn't eulerian? we have to make it
	void addNewPath(unsigned int v1, unsigned int v2); //add new path between two vertices which we set in arguments. is used, when graph has odd vertices
	std::vector<unsigned int> findShortestPath(unsigned int v1, unsigned int v2);
	std::vector< std::vector<std::pair<std::vector<unsigned int>, int> > > findShortestPaths(std::vector<unsigned int> oddVertices);
	std::pair<std::vector<int>, std::vector<int> > dijsktra(unsigned int start_vert); //then not void type
	unsigned int findCheapVertice(std::vector<int>& cost, std::vector<bool>& NUset); // is used in dijsktra algorithm
	void DFSMinimalMatching( // finding the minimal matching in graph, which has more than 2 odd vertices
		std::vector<unsigned int>& oddVertices, std::vector< std::vector< std::pair<unsigned int, unsigned int> > >& oddVerticesNeighbours, std::vector<std::pair<unsigned int, unsigned int> >& oddEdges,
		std::vector<bool> visited, int& minimum, std::vector<std::pair<unsigned int, unsigned int> > edges, unsigned int length_of_edges, int& licznik);



public:
	Graph();
	~Graph();
	void add(unsigned int first, unsigned int second, unsigned int length);
	void resize(unsigned int number_of_vertices, unsigned int number_of_edges);
	void showGraph();
	unsigned int getNumberOfVertices() { return number_of_vertices; };
	unsigned int getNumberOfEdges() { return number_of_edges; };
	std::vector<unsigned int> getOddVertices();
	std::vector<unsigned int> getEvenVertices();

	std::pair<std::vector<unsigned int>, unsigned int> findWay();
};

