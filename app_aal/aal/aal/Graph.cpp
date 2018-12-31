#include "Graph.h"




Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::add(unsigned int first, unsigned int second, unsigned int length)
{
	vertices[first].push_back(std::make_pair(second, length));
	vertices[second].push_back(std::make_pair(first, length));
}

void Graph::resize(unsigned int number_of_vertices)
{
	this->number_of_vertices = number_of_vertices;
	vertices.resize(number_of_vertices);
}

unsigned int Graph::countOddVertices() //if number of odd vertices is more than 3, function stop counting
{
	unsigned int result = 0;

	for (int i = 0; i < number_of_vertices; ++i) {
		if (vertices[i].size() % 2 != 0) ++result;
		if (result == 3) break;
	}

	return result;
}

void Graph::findWay()
{
	unsigned int oddVertices = countOddVertices(); // 0 - 0 odd; 2 - 2 odd, 3 - more than 2 odd
	std::cout << "FIND WAY oddVertices = " << oddVertices << std::endl;
	if (oddVertices == 0) {
		std::cout << "FIND WAY 0 odd" << std::endl;
	}
	else if (oddVertices == 2) {
		std::cout << "FIND WAY 2 odd" << std::endl;
	}
	else {
		std::cout << "FIND WAY more than 2 odd" << std::endl;
	}


}


