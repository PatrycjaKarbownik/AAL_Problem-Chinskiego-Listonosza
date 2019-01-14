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
	std::vector<unsigned int> beginningOfGenerateGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int& addedEdges);
		//it's used in every generate method on the beginning. It shuffles elements in vector and connects the next two in pairs (creates edges)
	void addRemainingEdges(Graph& graph, unsigned int number_of_edges); //is used in methods, when we have to add more edges - the last step
		//(los 3 vertices and connect them / los 2 vertices, create and double edge / los 1 vertice and create loop)

public:
	Generator();
	~Generator();

	Graph eulerianGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges); //generates new eurelian graph
	Graph graphWith2OddVertices(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges); //generate new graph with 2 odd vertices
	Graph graphWithMoreThan2OddVertices(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int number_of_odd_vertices); //generate new graph with more than 2 odd vertices
};

