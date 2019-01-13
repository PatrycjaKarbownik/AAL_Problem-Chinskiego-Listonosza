#pragma once

#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Graph.h"
class Generator
{
private:
	unsigned int myRandom(unsigned int mod);

public:
	Generator();
	~Generator();

	Graph eulerianGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges); //generates new eurelian graph
	Graph graphWith2OddVertices(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges); //generate new graph with 2 odd vertices

	std::vector<unsigned int> beginningOfGenerateGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int& addedEdges);
	void addRemainingEdges(Graph& graph, unsigned int number_of_edges); //is used in methods, when we have to add more edges - the last step
		//(los 3 vertices and couple them / los 2 vertices, create and double edge / los 1 vertice and create loop)


};

