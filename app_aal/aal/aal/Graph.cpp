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

void Graph::resize(unsigned int number_of_vertices, unsigned int number_of_edges)
{
	this->number_of_edges = number_of_edges;
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
	std::vector<unsigned int> euler;
	unsigned int lengthOfEulerianCycle;
	unsigned int oddVertices = countOddVertices(); // 0 - 0 odd; 2 - 2 odd, 3 - more than 2 odd
	std::cout << "FIND WAY: oddVertices = " << oddVertices << std::endl;

	/*std::cout << " GRAPH:" << std::endl;
	for (int i = 0; i < number_of_vertices; ++i) {
		for (int j = 0; j < vertices[i].size(); ++j) {
			std::cout << "first: " << i << " neighbour: " << vertices[i][j].first << " length: " << vertices[i][j].second << std::endl;
		}
	}*/

	if (oddVertices == 0) {
		std::cout << "FIND WAY: 0 odd" << std::endl;
		lengthOfEulerianCycle = lengthOfAllEdges();
		euler = findEulerianCycle();

	}
	else if (oddVertices == 2) {
		std::cout << "FIND WAY: 2 odd" << std::endl;
	}
	else {
		std::cout << "FIND WAY: more than 2 odd" << std::endl;
	}



	//writing information out will be in main function
	std::cout << "FIND WAY: length of eulerian cycle " << lengthOfEulerianCycle << std::endl;

	unsigned int eulerSize = euler.size();
	std::cout << "FIND WAY: cycle: ";
	for (unsigned int i = 0; i < eulerSize; ++i)
		std::cout << euler[i] << " ";
}

unsigned int Graph::lengthOfAllEdges() {
	unsigned int length = 0;
	std::vector< std::vector<bool> >visited = createVisitedVector();
	unsigned int number_of_neighbours;
	unsigned int end_of_edge_coord, begin_of_edge_coord;

	for (unsigned int i = 0; i < number_of_vertices; ++i) { // we're reviewing vertices and their neighbours;
		number_of_neighbours = visited[i].size();
		for (unsigned int j = 0; j < number_of_neighbours; ++j) {
			if (visited[i][j] == false) {// "delete" edge
				visited[i][j] = true;
				end_of_edge_coord = vertices[i][j].first; //get end of edge which is the coord in matrix in the next step

				for (int k = 0; k < visited[end_of_edge_coord].size(); ++k) { //find coord in matrix with begin from the edge
					if (vertices[end_of_edge_coord][k].first == i) {
						begin_of_edge_coord = k;
						break;
					}
				}

				visited[end_of_edge_coord][begin_of_edge_coord] = true; //end "delete" edge
				length += vertices[i][j].second;						// add length of the edge to entire length
			}
		}
	}
	
	return length;
}

std::vector<unsigned int> Graph::findEulerianCycle() {
	std::vector<unsigned int> euler;
	std::vector< std::vector<bool> >visited = createVisitedVector();
	
	DFSEuler(0, euler, visited);

	return euler;
}

void Graph::DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >&visited)
{
	unsigned int end_of_edge_coord, begin_of_edge_coord;
	unsigned int number_of_neighbours = visited[v].size();
	for (unsigned int i = 0; i < number_of_neighbours; i++)          // we're reviewing vertices and their neighbours;
		while (!visited[v][i])
		{							// "delete" edge
			visited[v][i] = true;
			end_of_edge_coord = vertices[v][i].first;
			for (int k = 0; k < visited[end_of_edge_coord].size(); ++k) {
				if (vertices[end_of_edge_coord][k].first == v) {
					begin_of_edge_coord = k;
					break;
				}
			}
			visited[end_of_edge_coord][begin_of_edge_coord] = true; //end "delete" edge
			DFSEuler(vertices[v][i].first, euler, visited); //recursion
		}

	euler.push_back(v);                  // add vertice to eulerian cycle
}

std::vector < std::vector<bool> > Graph::createVisitedVector() {
	std::vector< std::vector<bool> >visited;
	visited.resize(number_of_vertices);
	unsigned int number_of_neighbours;

	for (unsigned int i = 0; i < number_of_vertices; ++i) {
		number_of_neighbours = vertices[i].size();
		for (unsigned int j = 0; j < number_of_neighbours; ++j) {
			visited[i].push_back(false);
		}
	}

	return visited;
}
