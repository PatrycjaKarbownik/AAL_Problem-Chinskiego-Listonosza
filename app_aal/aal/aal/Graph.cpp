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

std::vector<unsigned int> Graph::getOddVertices() //if number of odd vertices is more than 3, function stop counting
{
	std::vector<unsigned int> oddVertices;

	for (int i = 0; i < number_of_vertices; ++i) {
		if (vertices[i].size() % 2 != 0)
			oddVertices.push_back(i);
	}

	return oddVertices;
}

void Graph::findWay()
{
	std::vector<unsigned int> euler;
	unsigned int lengthOfEulerianCycle;
	std::vector<unsigned int> oddVertices = getOddVertices(); // 0 - 0 odd; 2 - 2 odd, 3 - more than 2 odd
	std::cout << "FIND WAY: oddVertices = " << oddVertices.size() << std::endl;

	showGraph();

	//done
	if (oddVertices.size() == 0) {
		std::cout << "FIND WAY: 0 odd" << std::endl;
		lengthOfEulerianCycle = lengthOfAllEdges();
		euler = findEulerianCycle();
	}
	//done
	else if (oddVertices.size() == 2) {
		std::cout << "FIND WAY: 2 odd" << std::endl;
		
		makeEulerianGraph(oddVertices);
		//showGraph();
		lengthOfEulerianCycle = lengthOfAllEdges();
		euler = findEulerianCycle();
	}
	//todo
	else {
		std::cout << "FIND WAY: more than 2 odd" << std::endl;

		return;
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
				//std::cout << "change [i], [j]: " << i << " " << j << std::endl;
				end_of_edge_coord = vertices[i][j].first; //get end of edge which is the coord in matrix in the next step

				for (int k = 0; k < visited[end_of_edge_coord].size(); ++k) { //find coord in matrix with begin from the edge
					if (visited[end_of_edge_coord][k] == false && vertices[end_of_edge_coord][k].first == i) {
						begin_of_edge_coord = k;
						break;
					}
				}

				visited[end_of_edge_coord][begin_of_edge_coord] = true; //end "delete" edge
				//std::cout << "change [i], [j]: " << end_of_edge_coord << " " << begin_of_edge_coord << std::endl;
				length += vertices[i][j].second;						// add length of the edge to entire length

			}
		}
	}
	
	/*std::cout << " VISITED:" << std::endl;
	for (int i = 0; i < number_of_vertices; ++i) {
		for (int j = 0; j < visited[i].size(); ++j) {
			std::cout << "[i]: " << i << " [j] " << j << " bool: " << visited[i][j] << std::endl;
		}
	}*/

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
				if (visited[end_of_edge_coord][k] == false && vertices[end_of_edge_coord][k].first == v) {
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

void Graph::makeEulerianGraph(std::vector<unsigned int>& oddVertices) {

	if(oddVertices.size() == 2)
		addNewPath(oddVertices[0], oddVertices[1]);
	else {
		return;
	}

}

void Graph::addNewPath(unsigned int v1, unsigned int v2) {
	std::vector<unsigned int> shortestPath = findShortestPath(v1, v2);
	unsigned int length;

	std::cout << "ADD NEW PATH: shortest path: " <<std::endl;
	for (int i = 0; i < shortestPath.size() - 1; ++i) {
		for (int j = 0; j < vertices[i].size(); ++j) {
			if (vertices[shortestPath[i]][j].first == shortestPath[i + 1]) {
				length = vertices[shortestPath[i]][j].second;
				break;
			}
		}
		std::cout << shortestPath[i] << " " << shortestPath[i+1] << " length: " << length << std::endl;
		add(shortestPath[i], shortestPath[i + 1], length);
	}

	std::cout << std::endl;
}

std::vector<unsigned int> Graph::findShortestPath(unsigned int v1, unsigned int v2) {
	std::vector<int> prev = dijsktra(v1);
	std::vector<unsigned int> path;

	unsigned int vert = v2;
	
	while (prev[vert] != -1) {
		path.push_back(vert);
		vert = prev[vert];
	}
	path.push_back(v1);

	return path;
}

std::vector<int> Graph::dijsktra(unsigned int start_vert) {
	//const int MAX_INT = 2147483647;
	std::vector<int> cost;
	cost.resize(number_of_vertices);
	std::vector<int> prev;
	prev.resize(number_of_vertices);
	std::vector<bool> NUset; // Not use/Use set:  0 for not use, 1 for use
	NUset.resize(number_of_vertices);
	unsigned int cheapVertice;
	unsigned int number_of_neighbours;
	unsigned int coord_of_neighbour;

	for (unsigned int i = 0; i < number_of_vertices; ++i) {
		cost[i] = INT_MAX;
		prev[i] = -1;
		NUset[i] = false;
	}

	cost[start_vert] = 0; // cost of get from start_vert to start_vert is 0. always

	//we're finding paths
	for (unsigned int i = 0; i < number_of_vertices; ++i) {
		//we're finding index of the cheapest vertice
		cheapVertice = findCheapVertice(cost, NUset);

		NUset[cheapVertice] = true;
		number_of_neighbours = vertices[cheapVertice].size();

		//modify all of neighbours, which didn't used earlier
		for (unsigned int i = 0; i < number_of_neighbours; ++i) {
			coord_of_neighbour = vertices[cheapVertice][i].first;
			if (NUset[coord_of_neighbour] == false && cost[coord_of_neighbour] > cost[cheapVertice] + vertices[cheapVertice][i].second) {
				cost[coord_of_neighbour] = cost[cheapVertice] + vertices[cheapVertice][i].second;
				prev[coord_of_neighbour] = cheapVertice;
			}
		}
	}

	return prev;
}

unsigned int Graph::findCheapVertice(std::vector<int>& cost, std::vector<bool>& NUset) {
	int min = INT_MAX;
	unsigned int min_index;

	for (int v = 0; v < number_of_vertices; ++v)
		if (NUset[v] == false && cost[v] <= min) {
			min = cost[v];
			min_index = v;
		}

	return min_index;
}

void Graph::showGraph() {
	std::cout << " GRAPH:" << std::endl;
	for (int i = 0; i < number_of_vertices; ++i) {
		for (int j = 0; j < vertices[i].size(); ++j) {
			std::cout << "[i]: " << i << " [j] " << j << " first: " << i << " neighbour: " << vertices[i][j].first << " length: " << vertices[i][j].second << std::endl;
		}
	}
}