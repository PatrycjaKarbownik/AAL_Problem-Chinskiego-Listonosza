#pragma once

#include <vector>
#include <iostream>
#include <string>

class Graph
{
private:
	std::vector<std::vector <std::pair <unsigned int, unsigned int> > > vertices;
	unsigned int number_of_vertices;
	unsigned int number_of_edges; //number of edges

	unsigned int countOddVertices(); //if number of odd vertices is more than 3, function stop counting
	void DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >&visited);
	std::vector<std::vector<bool>> createVisitedVector();
	std::vector<unsigned int> findEulerianCycle();
	unsigned int lengthOfAllEdges(); //is used, when graph has an eulerian cycle. it gets length of the cycle

public:
	Graph();
	~Graph();
	void add(unsigned int first, unsigned int second, unsigned int length);
	void resize(unsigned int number_of_vertices, unsigned int number_of_edges);

	void findWay();//then not void type
};

