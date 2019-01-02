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

void Graph::resize(unsigned int number_of_vertices, unsigned int size)
{
	this->size = size;
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

unsigned int Graph::lengthOfEulerianCycle() {
	unsigned int length = 0;
	std::vector< std::vector<bool> >visited;
	visited.resize(size);

	for (unsigned int i = 0; i < visited.size(); ++i)
		for (unsigned int j = 0; j < visited[i].size(); ++j)
			visited[i][j] = false;

	for (unsigned int i = 0; i < number_of_vertices; ++i)
		for (unsigned int j = 0; j < vertices[i].size(); ++j) {
			if (visited[i][j] == false) {
				visited[i][j] = true;
				visited[j][i] = true;
				length += vertices[i][j].second;
			}
		}
	
	return length;
}

void Graph::DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >visited)
{
	for (unsigned int i = 0; i < number_of_vertices; i++)          // we're reviewing vertices and their neighbours;
		while (visited[v][i])
		{
			visited[v][i] = true;                  // "delete" edge
			visited[i][v] = true;
			DFSEuler(i, euler, visited);                // Rekurencja
		}
	euler.push_back(v);                  // add vertice to eulerian cycle
}

std::vector<unsigned int> Graph::findEulerianCycle() {
	std::vector<unsigned int> euler;
	std::vector< std::vector<bool> >visited;
	visited.resize(size);

	for (unsigned int i = 0; i < visited.size(); ++i)
		for (unsigned int j = 0; j < visited[i].size(); ++j)
			visited[i][j] = false;

	DFSEuler(0, euler, visited);

	return euler;
}


