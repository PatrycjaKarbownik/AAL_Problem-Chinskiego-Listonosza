//Author: Patrycja Karbownik
//Problem: AAL.8 - Przygotowanie pod maraton (Problem chinskiego listonosza)

#include "Graph.h"

void Graph::add(unsigned int first, unsigned int second, unsigned int length) {
	//adding new edge
	vertices[first].push_back(std::make_pair(second, length));
	vertices[second].push_back(std::make_pair(first, length));
}

void Graph::resize(unsigned int number_of_vertices) {
	//resizing vector with vertices
	this->number_of_vertices = number_of_vertices;
	vertices.resize(number_of_vertices);
}

void Graph::showGraph() {
	std::cout << "GRAPH:" << std::endl;
	for (int i = 0; i < number_of_vertices; ++i) {
		for (int j = 0; j < vertices[i].size(); ++j) {
			std::cout << "first: " << i << " neighbour: " << vertices[i][j].first << " length: " << vertices[i][j].second << std::endl;
		}
	}
}

std::vector<unsigned int> Graph::getOddVertices()
{
	std::vector<unsigned int> oddVertices;

	for (int i = 0; i < number_of_vertices; ++i) {
		if (vertices[i].size() % 2 != 0)
			oddVertices.push_back(i);
	}

	return oddVertices;
}

std::vector<unsigned int> Graph::getEvenVertices()
{
	std::vector<unsigned int> evenVertices;

	for (int i = 0; i < number_of_vertices; ++i) {
		if (vertices[i].size() % 2 != 1)
			evenVertices.push_back(i);
	}

	return evenVertices;
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

std::pair<std::vector<unsigned int>, unsigned int> Graph::findWay()
{
	std::pair<std::vector<unsigned int>, unsigned int> result;
	std::vector<unsigned int> euler;
	unsigned int lengthOfEulerianCycle;
	std::vector<unsigned int> oddVertices = getOddVertices();

	if (oddVertices.size() == 0) { //eulerian graph
		lengthOfEulerianCycle = lengthOfAllEdges();
		euler = findEulerianCycle();
	}
	else { //2 or more odd vertices
		makeEulerianGraph(oddVertices);
			//std::cout << std::endl << "Graph after changing to eulerian graph:" << std::endl;
			//showGraph();
		lengthOfEulerianCycle = lengthOfAllEdges();
		euler = findEulerianCycle();
	}

	result = std::make_pair(euler, lengthOfEulerianCycle);
	return result;
}

unsigned int Graph::lengthOfAllEdges() {
	//is used, when graph has an eulerian cycle. it gets length of the cycle
	unsigned int length = 0;
	std::vector< std::vector<bool> >visited = createVisitedVector();
	unsigned int number_of_neighbours;
	unsigned int end_of_edge_coord, begin_of_edge_coord;

	for (unsigned int i = 0; i < number_of_vertices; ++i) { //reviewing vertices and their neighbours;
		number_of_neighbours = visited[i].size();
		for (unsigned int j = 0; j < number_of_neighbours; ++j) {
			if (visited[i][j] == false) {// "delete" edge
				visited[i][j] = true;
				end_of_edge_coord = vertices[i][j].first; //getting end of edge which is the coord in matrix in the next step

				for (int k = 0; k < visited[end_of_edge_coord].size(); ++k) { //finding coord in matrix with begin from the edge
					if (visited[end_of_edge_coord][k] == false && vertices[end_of_edge_coord][k].first == i) {
						begin_of_edge_coord = k;
						break;
					}
				}

				visited[end_of_edge_coord][begin_of_edge_coord] = true; //end "delete" edge
				length += vertices[i][j].second;						// adding length of the edge to entire length
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

void Graph::DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >&visited) { 
	//is used to find eulerian cycle
	unsigned int end_of_edge_coord, begin_of_edge_coord;
	unsigned int number_of_neighbours = visited[v].size();
	for (unsigned int i = 0; i < number_of_neighbours; i++)  //reviewing vertices and their neighbours;
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

	euler.push_back(v);  // adding vertice to eulerian cycle
}

void Graph::makeEulerianGraph(std::vector<unsigned int>& oddVertices) {
	//graph isn't eulerian? we have to make it
	if (oddVertices.size() == 2) { // 2 odd vertices
		addNewPath(oddVertices[0], oddVertices[1]);
	}
	else { // more than 2 odd vertices
		std::vector< std::vector< std::pair< std::vector<unsigned int>, int> > > shortestPaths;
		std::vector< std::vector< std::pair<unsigned int, unsigned int> > > oddVerticesNeighbours;
		shortestPaths = findShortestPaths(oddVertices);

		unsigned int number_of_oddVertices = oddVertices.size();
		oddVerticesNeighbours.resize(number_of_oddVertices);

		for (unsigned int i = 0; i < number_of_oddVertices; ++i) { // creating new vector with neighbours of odd vertices
			for (unsigned int j = 0; j < shortestPaths[i].size(); ++j) {
				oddVerticesNeighbours[i].push_back(std::make_pair(shortestPaths[i][j].first[0], shortestPaths[i][j].second));
			}
		}
		
		//preparing variables to DFSMinimalMatching method
		std::vector<bool> visited;
		for (unsigned int i = 0; i < number_of_oddVertices; ++i)
			visited.push_back(false);
		std::vector<std::pair<unsigned int, unsigned int> > oddEdges, edges;
		int minimum = INT8_MAX;

		DFSMinimalMatching(oddVertices, oddVerticesNeighbours, oddEdges, visited, minimum, edges, 0);

		//adding new edges (graph has to be eulerian)
		addNewPaths(oddVertices, oddEdges, shortestPaths);
	}
}

void Graph::addNewPath(unsigned int v1, unsigned int v2) {
	//adding new path between two vertices which we set in arguments. is used, when graph has 2 odd vertices
	std::vector<unsigned int> shortestPath = findShortestPath(v1, v2);
	unsigned int length;

	for (int i = 0; i < shortestPath.size() - 1; ++i) {
		for (int j = 0; j < vertices[shortestPath[i]].size(); ++j) { //finding length of new edge
			if (vertices[shortestPath[i]][j].first == shortestPath[i + 1]) {
				length = vertices[shortestPath[i]][j].second;
				break;
			}
		}
		add(shortestPath[i], shortestPath[i + 1], length);
	}
}

void Graph::addNewPaths(std::vector<unsigned int>& oddVertices, std::vector<std::pair<unsigned int, unsigned int> >& oddEdges,
	std::vector< std::vector< std::pair< std::vector<unsigned int>, int> > >& shortestPaths)
{	//adding new paths between odd vertices, which create the minimal matching
	unsigned int begin, end, length, firstIndex, secondIndex;

	for (unsigned int i = 0; i < oddEdges.size(); ++i) {
		for (int j = 0; j < shortestPaths.size(); ++j) { //finding index of begin of the edge
			if (oddVertices[j] == oddEdges[i].first) {
				firstIndex = j;
				break;
			}
		}
		for (int j = 0; j < shortestPaths[firstIndex].size(); ++j) { //finding index of end of the edge
			if (shortestPaths[firstIndex][j].first[0] == oddEdges[i].second) {
				secondIndex = j;
				break;
			}
		}

		for (int k = 0; k < shortestPaths[firstIndex][secondIndex].first.size() - 1; ++k) {
			begin = shortestPaths[firstIndex][secondIndex].first[k];
			end = shortestPaths[firstIndex][secondIndex].first[k + 1];

			for (int l = 0; l < vertices[begin].size(); ++l) { //finding length of the edge
				if (vertices[begin][l].first == end) {
					length = vertices[begin][l].second;
					break;
				}
			}
			add(begin, end, length); // adding the edge
		}
	}
}

std::vector<unsigned int> Graph::findShortestPath(unsigned int v1, unsigned int v2) {
	std::pair <std::vector<int>, std::vector<int> > dijsktra_pair = dijsktra(v1);
	std::vector<int> prev = dijsktra_pair.first;
	std::vector<unsigned int> path;

	unsigned int vert = v2;
	
	while (prev[vert] != -1) {
		path.push_back(vert);
		vert = prev[vert];
	}
	path.push_back(v1);

	return path;
}

std::vector< std::vector<std::pair<std::vector<unsigned int>, int> > > Graph::findShortestPaths(std::vector<unsigned int> oddVertices) {
	std::vector< std::vector<std::pair<std::vector<unsigned int>, int> > > result;
	unsigned int number_of_odd_vertices = oddVertices.size();
	std::vector< std::pair <std::vector<int>, std::vector<int> > > dijsktra_pairs;
	std::vector<int> prev;
	std::vector<int> cost;
	
	int length_of_path = 0;

	for (int i = 0; i < number_of_odd_vertices; ++i) {
		dijsktra_pairs.push_back(dijsktra(oddVertices[i]));
	}

	result.resize(number_of_odd_vertices);
	for (int i = 0; i < number_of_odd_vertices; ++i) { // finding the shortest paths between each of odd vertices
		prev = dijsktra_pairs[i].first;
		cost = dijsktra_pairs[i].second;

		for (int j = 0; j < number_of_odd_vertices; ++j) {
			if (oddVertices[j] > oddVertices[i]) {
				std::vector<unsigned int> path;
				unsigned int vert = oddVertices[j];

				while (prev[vert] != -1) {
					path.push_back(vert);
					vert = prev[vert];
				}
				path.push_back(oddVertices[i]);
				length_of_path = cost[oddVertices[j]];

				result[i].push_back(std::make_pair(path, length_of_path));
			}
		}
	}
	return result;
}

std::pair<std::vector<int>, std::vector<int> > Graph::dijsktra(unsigned int start_vert) {
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
		cost[i] = INT8_MAX;
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
	return std::make_pair(prev, cost);
}

unsigned int Graph::findCheapVertice(std::vector<int>& cost, std::vector<bool>& NUset) {
	// is used in dijsktra algorithm
	int min = INT8_MAX;
	unsigned int min_index;

	for (int v = 0; v < number_of_vertices; ++v)
		if (NUset[v] == false && cost[v] <= min) {
			min = cost[v];
			min_index = v;
		}

	return min_index;
}

void Graph::DFSMinimalMatching(//1st line - variables which will use to get data of vertices and set edges
	std::vector<unsigned int>& oddVertices, std::vector< std::vector< std::pair<unsigned int, unsigned int> > >& oddVerticesNeighbours, std::vector<std::pair<unsigned int, unsigned int> >& oddEdges,
	std::vector<bool> visited, int& minimum, std::vector<std::pair<unsigned int, unsigned int> > edges, unsigned int length_of_edges)
{// finding the minimal matching in graph, which has more than 2 odd vertices
	unsigned int oddVerticesSize = oddVertices.size(), visitedSize = 0, notVisitedSize = 0;
	unsigned int number_of_neighbours, first_not_visited_vertice;

	for (int i = oddVerticesSize - 1; i >= 0; i--) {
		if (visited[i] == false) {
			++notVisitedSize;
			first_not_visited_vertice = i;
		}
		else ++visitedSize;
	}

	if (visitedSize == oddVerticesSize) { //checking if method came to the end of branch
		if (length_of_edges < minimum) { //updating minimum length of edges
			std::cout << "minimum = " << minimum << " length_of_edges = " << length_of_edges << std::endl;
			minimum = length_of_edges;
			oddEdges = edges;
		}
		return;
	}

	int i = 0;
	unsigned int index_of_vertice = first_not_visited_vertice;
	unsigned int index_of_neighbour;
		
	number_of_neighbours = oddVerticesNeighbours[index_of_vertice].size();
	for (int j = 0; j < number_of_neighbours; ++j){ //combinating first not visited vertice with its not visited neighbours
		index_of_neighbour = 0;
		while (oddVertices[index_of_neighbour] != oddVerticesNeighbours[index_of_vertice][j].first) { //finding index of neighbour
			++index_of_neighbour;
		}
	
		if (visited[index_of_neighbour] == false) {
			visited[index_of_vertice] = true;
			visited[index_of_neighbour] = true;
			edges.push_back(std::make_pair(oddVertices[index_of_vertice], oddVertices[index_of_neighbour])); //createing new edge on analyse path
			length_of_edges += oddVerticesNeighbours[index_of_vertice][j].second;

			DFSMinimalMatching(oddVertices, oddVerticesNeighbours, oddEdges, visited, minimum, edges, length_of_edges); //recursion

			//fixing changes in order that the next loops can be correct (without changes in recursion)
			visited[index_of_neighbour] = false;
			length_of_edges -= oddVerticesNeighbours[index_of_vertice][j].second;
			edges.pop_back();
		}
	}
	visited[index_of_vertice] = false; //the next loop requires updating this vertice, because in this method will be find a new path with other combination
	++index_of_vertice;
}
