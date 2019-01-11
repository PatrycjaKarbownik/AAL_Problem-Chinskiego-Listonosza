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

void Graph::showGraph() {
	std::cout << " GRAPH:" << std::endl;
	for (int i = 0; i < number_of_vertices; ++i) {
		for (int j = 0; j < vertices[i].size(); ++j) {
			std::cout << "[i]: " << i << " [j] " << j << " first: " << i << " neighbour: " << vertices[i][j].first << " length: " << vertices[i][j].second << std::endl;
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
		makeEulerianGraph(oddVertices);
		//showGraph();
		//lengthOfEulerianCycle = lengthOfAllEdges();
		//euler = findEulerianCycle();
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
	for (unsigned int i = 0; i < number_of_neighbours; i++)  // we're reviewing vertices and their neighbours;
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

	euler.push_back(v);  // add vertice to eulerian cycle
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
		std::vector< std::vector< std::pair< std::vector<unsigned int>, int> > > shortestPaths;
		std::vector< std::vector< std::pair<unsigned int, unsigned int> > > oddVerticesNeighbours;
		shortestPaths = findShortestPaths(oddVertices);

		unsigned int number_of_oddVertices = oddVertices.size();
		oddVerticesNeighbours.resize(number_of_oddVertices);

		for (unsigned int i = 0; i < number_of_oddVertices; ++i) {
			for (unsigned int j = 0; j < shortestPaths[i].size(); ++j) {

				oddVerticesNeighbours[i].push_back(std::make_pair(shortestPaths[i][j].first[0], shortestPaths[i][j].second));
			}
		}
		
		//writing
		std::cout << "ODD GRAPH:" << std::endl;
		for (int i = 0; i < number_of_oddVertices; ++i) {
			for (int j = 0; j < oddVerticesNeighbours[i].size(); ++j) {
				std::cout << "[i]: " << i << " [j] " << j << " first: " << oddVertices[i] << " neighbour: " << oddVerticesNeighbours[i][j].first << " length: " << oddVerticesNeighbours[i][j].second << std::endl;
			}
		}
		//end writing

		//writing
		std::cout << "MAKE EULERIAN GRAPH: the shortest paths:" << std::endl;
		for (int i = 0; i < shortestPaths.size(); ++i) {
			for (int j = 0; j < shortestPaths[i].size(); ++j) {
				std::cout << "odd vertice: begin:" << oddVertices[i] << std::endl << "path: ";
				for (int k = 0; k < shortestPaths[i][j].first.size(); ++k) {
					std::cout << shortestPaths[i][j].first[k] << " ";
				}
				std::cout <<" length: " << shortestPaths[i][j].second << std::endl << std::endl;
			}
		}
		//end writing

		std::vector<bool> visited;
		for (unsigned int i = 0; i < number_of_oddVertices; ++i)
			visited.push_back(false);

		std::vector<std::pair<unsigned int, unsigned int> > oddEdges, edges;
		int minimum = INT_MAX;
		int licznik = 0;

		DFSMinimalMatching(oddVertices, oddVerticesNeighbours, oddEdges, visited, minimum, edges, 0, licznik);//////////////////////////////////

		//writing
		std::cout << std::endl << "ODD EDGES:" << std::endl;
		for (unsigned int i = 0; i < oddEdges.size(); ++i) {
			std::cout << "first: " << oddEdges[i].first << " second: " << oddEdges[i].second << std::endl;
		} //end writing



		/*
		unsigned int begin, end, length;

		std::cout << "ADD ODD EDGES:" << std::endl;
		for (unsigned int i = 0; i < oddEdges.size(); ++i) { //oddEdges - pair<begin, end>
			for (int k = 0; k < shortestPaths[oddEdges[i].first][oddEdges[i].second].first.size(); ++k) { 
				begin = shortestPaths[oddEdges[i].first][oddEdges[i].second].first[k];
				end = shortestPaths[oddEdges[i].first][oddEdges[i].second].first[k + 1];
				
				for(int j = 0; j < vertices[begin].size(); ++j) {
					if (vertices[begin][j].first == end) {
						length = vertices[begin][j].second;
						break;
					}
				}

				std::cout << "begin " << begin << " end " << end << " length " << length << std::endl;
				add(begin, end, length);
			}
		}
		*/
		
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
		std::cout << "odd: " << oddVertices[i] << std::endl;
		dijsktra_pairs.push_back(dijsktra(oddVertices[i]));
	}

	result.resize(number_of_odd_vertices);
	for (int i = 0; i < number_of_odd_vertices; ++i) {
		
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

	return std::make_pair(prev, cost);
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

//////////////////////////////////////////////

void Graph::DFSMinimalMatching(//1st line - variables which will use to get data of vertices and set edges; 2nd - 
	std::vector<unsigned int>& oddVertices, std::vector< std::vector< std::pair<unsigned int, unsigned int> > >& oddVerticesNeighbours, std::vector<std::pair<unsigned int, unsigned int> >& oddEdges,
	std::vector<bool> visited, int& minimum, std::vector<std::pair<unsigned int, unsigned int> > edges, unsigned int length_of_edges, int& licznik)
{
	unsigned int oddVerticesSize = oddVertices.size();
	unsigned int visitedSize = 0, notVisitedSize = 0;
	unsigned int number_of_neighbours;
	unsigned int first_not_visited_vertice;

	for (int i = oddVerticesSize - 1; i >= 0; i--) {
		//std::cout << "DFSminimal: i = " << i << std::endl;
		if (visited[i] == false) {
			//std::cout << "DFSminimal FALSE: i = " << i << std::endl;
			++notVisitedSize;
			first_not_visited_vertice = i;
		}
		else {
			//std::cout << "DFSminimal TRUE: i = " << i << std::endl;
			++visitedSize;
		}
	}

	/*std::cout << "DFSminimal: juz za" << std::endl;
	std::cout << "Not Visited Size = " << notVisitedSize << std::endl;
	std::cout << "Visited Size = " << visitedSize << std::endl;
	std::cout << "Odd Vertices Size = " << oddVerticesSize << std::endl;*/

	/*//writing
	std::cout << std::endl << "EDGES:" << std::endl;
	std::cout << "LICZNIK = " << licznik << std::endl;
	for (unsigned int i = 0; i < edges.size(); ++i) {
		std::cout << "first: " << edges[i].first << " second: " << edges[i].second << std::endl;
	} //end writing */

	if (visitedSize == oddVerticesSize) {
		++licznik;
		if (length_of_edges < minimum) {
			std::cout << "minimum = " << minimum << " length_of_edges = " << length_of_edges << std::endl;
			minimum = length_of_edges;
			oddEdges = edges;
		}
		return;
	}

	int i = 0;
	unsigned int index_of_vertice = first_not_visited_vertice;
	unsigned int index_of_neighbour;
//	std::cout << "while i < notVisitedSize:  i = " << i << " notVisitedSize = " << notVisitedSize << std::endl;
	while (visited[index_of_vertice] != false) {
	//	std::cout << "finding index of not visited vertice: " << index_of_vertice << std::endl;
		++index_of_vertice;
	}
	//std::cout << "finding index of not visited vertice FINISH: " << index_of_vertice << std::endl;
		
	number_of_neighbours = oddVerticesNeighbours[index_of_vertice].size();
	//std::cout << "number_of_neighbours = " << number_of_neighbours << std::endl;
	for (int j = 0; j < number_of_neighbours; ++j){
		index_of_neighbour = 0;
		while (oddVertices[index_of_neighbour] != oddVerticesNeighbours[index_of_vertice][j].first) {
			//std::cout << "finding index of not visited neighbour: " << index_of_neighbour << std::endl;
			++index_of_neighbour;
		}
		//std::cout << "finding index of not visited neighbour FINISH: " << index_of_neighbour << std::endl;



		/*for (int i = oddVerticesSize - 1; i >= 0; i--) {
			std::cout << "DFSminimal: i = " << i << std::endl;
			if (visited[i] == false) {std::cout << "DFSminimal FALSE: i = " << i << std::endl;}
			else {std::cout << "DFSminimal TRUE: i = " << i << std::endl;}
		}*/


	
		if (visited[index_of_neighbour] == false) {//nieodwiedzone[i][j] nie jest na liscie odwiedzone)
			visited[index_of_vertice] = true;
			visited[index_of_neighbour] = true;
			//std::cout << "NEW EDGE: " << oddVertices[index_of_vertice] << "  " << oddVertices[index_of_neighbour] << "  length: " << oddVerticesNeighbours[index_of_vertice][j].second << std::endl;
			edges.push_back(std::make_pair(oddVertices[index_of_vertice], oddVertices[index_of_neighbour]));
			length_of_edges += oddVerticesNeighbours[index_of_vertice][j].second;
			//std::cout << "length of edges = " << length_of_edges << std::endl;

			DFSMinimalMatching(oddVertices, oddVerticesNeighbours, oddEdges, visited, minimum, edges, length_of_edges, licznik);
			visited[index_of_neighbour] = false;
			length_of_edges -= oddVerticesNeighbours[index_of_vertice][j].second;
			edges.pop_back();
		}
	}
	visited[index_of_vertice] = false;
	++index_of_vertice;
}


//////////////////////////////////////////////

