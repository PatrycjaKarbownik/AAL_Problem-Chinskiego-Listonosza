//Author: Patrycja Karbownik
//Problem: AAL.8 - Przygotowanie pod maraton (Problem chinskiego listonosza)

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

#include "Graph.h"
#include "Generator.h"

void read(Graph& graph, char *nameOfFile) //then delete const
{
	std::fstream file;
	std::string name = "data//" + std::string(nameOfFile);
	file.open(name, std::ios::in);

	unsigned int first, second, length;
	unsigned int number_of_edges, number_of_vert;
	std::vector<unsigned int> first_vect, second_vect, length_vect;

	while (file >> first >> second >> length)
	{
		first_vect.push_back(first);
		second_vect.push_back(second);
		length_vect.push_back(length);
	}

	number_of_edges = first_vect.size();

	number_of_vert = 0;
	for (unsigned int i = 0; i < number_of_edges; ++i) {
		if (number_of_vert < first_vect[i]) number_of_vert = first_vect[i];
		if (number_of_vert < second_vect[i]) number_of_vert = second_vect[i];
	}
	++number_of_vert;

	graph.resize(number_of_vert);
	   
	for(unsigned int i = 0; i < number_of_edges; ++i)
		graph.add(first_vect[i], second_vect[i], length_vect[i]);

	file.close();
}

void write(std::pair<std::vector<unsigned int>, unsigned int> path) {
	std::vector<unsigned int> euler = path.first;

	std::cout << "Length of eulerian cycle: " << path.second << std::endl;

	unsigned int eulerSize = euler.size();
	std::cout << "cycle: ";
	for (unsigned int i = 0; i < eulerSize; ++i)
		std::cout << euler[i] << " ";
}

void showOptions() {
	std::cout << "Program finds the shortest path in a graph. Path begins and ends at the same vertice and includes all of the edges." << std::endl;
	std::cout << "You should set one of flags and parameters: " << std::endl
	<< "	-file <in.txt>  -- program analyses graph from file. File has to be in \"data\" folder" << std::endl
	<< "	-eulerian <number_of_vertices> <number_of_edges>  -- program generates eulerian graph and analyses it. Set number of vertices and edges in new graph (number of edges >= number of vertices)" << std::endl
	<< "	-2odd <number_of_vertices> <number_of_edges>  -- program generates graph with 2 odd vertices and analyses it. Set number of vertices and edges in new graph (number of edges >= number of vertices - 1)" << std::endl
	<< "	-moreOdd <number_of_vertices> <number_of_edges> <number_of_odd_vertices>  -- program generates graph with more than 2 odd vertices and analyses it. Set number of vertices, edges and odd vertices in new graph (number of edges >= number of vertices)" << std::endl;
}

int main(int argc, char **argv) {

	char *nameOfFile;

	if ( argc == 3 ){
		if ( strcmp(argv[1], "-file") == 0 ) {
			Graph graph;
			nameOfFile = argv[2];

			read(graph, nameOfFile);
			std::cout << std::endl << "Graph before adding edges in order to create eulerian graph" << std::endl;
			graph.showGraph();

			//writing information out of eulerian cycle
			write(graph.findWay());

			return 0;
		}
		else {
			showOptions();
			return 0;
		}
	}
	else if ( argc == 4 ) {
		if ( strcmp(argv[1], "-eulerian") == 0 ) {
			Graph graph;
			unsigned int number_of_vertices, number_of_edges;
			Generator generator;
			number_of_vertices = atoi(argv[2]);
			number_of_edges = atoi(argv[3]);

			if (number_of_vertices <= 1 || number_of_edges <= 1)
			{
				std::cout << "Numbers have to be more than 1" << std::endl;
			}
			else if (number_of_edges < number_of_vertices) {
				std::cout << "Number of edges has to be equal or more than number of vertices" << std::endl;
			}
			else {
				generator.eulerianGraph(graph, number_of_vertices, number_of_edges);
				std::cout << std::endl << "Graph before adding edges in order to create eulerian graph" << std::endl;
				graph.showGraph();

				//writing information out of eulerian cycle
				write(graph.findWay());
			}

			return 0;
		}
		else if ( strcmp(argv[1], "-2odd") == 0 ) {
			Graph graph;
			unsigned int number_of_vertices, number_of_edges;
			Generator generator;
			number_of_vertices = atoi(argv[2]);
			number_of_edges = atoi(argv[3]);

				if (number_of_vertices < 1 || number_of_edges < 1)
				{
					std::cout << "Numbers have to be more than 0" << std::endl;
				}
				else if (number_of_edges < number_of_vertices - 1) {
					std::cout << "Number of edges has to be equal or more than number of vertices - 1" << std::endl;
				}
				else {
				generator.graphWith2OddVertices(graph, number_of_vertices, number_of_edges);
				std::cout << std::endl << "Graph before adding edges in order to create eulerian graph" << std::endl;
				graph.showGraph();

				//writing information out of eulerian cycle
				write(graph.findWay());
			}

			return 0;
		}
		else {
			showOptions();
			return 0;
		}

	}
	else if ( argc == 5 ) {
		if ( strcmp(argv[1], "-moreOdd") == 0 ) {
			Graph graph;
			unsigned int number_of_vertices, number_of_edges, number_of_odd_vertices;
			Generator generator;
			number_of_vertices = atoi(argv[2]);
			number_of_edges = atoi(argv[3]);
			number_of_odd_vertices = atoi(argv[4]);

			if (number_of_vertices < 4 || number_of_edges < 4 || number_of_odd_vertices < 4)
			{
				std::cout << "Numbers have to be more than 3" << std::endl;
			}
			else if (number_of_edges < number_of_vertices) {
				std::cout << "Number of edges has to be equal or more than number of vertices" << std::endl;
			}
			else if (number_of_odd_vertices % 2 != 0) {
				std::cout << "Number of odd vertices has to be even" << std::endl;
			}
			else if (number_of_vertices % 2 == 0 && number_of_odd_vertices > number_of_vertices) {
				std::cout << "Number of odd vertices has to be equal or less than number of vertices" << std::endl;
			}
			else if (number_of_vertices % 2 == 1 && number_of_odd_vertices > number_of_vertices - 1) {
				std::cout << "If number of vertices is odd, number of odd vertices has to be equal or less than number of vertices - 1" << std::endl;
			}
			else if (number_of_edges - (number_of_vertices - 1) < (number_of_odd_vertices-2)/2) {
				std::cout << "Number of edges has to be equal or more than (number of vertices - 1 + (number of odd vertices-2)/2 )" << std::endl;
			}
			else {
				generator.graphWithMoreThan2OddVertices(graph, number_of_vertices, number_of_edges, number_of_odd_vertices);
				std::cout << std::endl << "Graph before adding edges in order to create eulerian graph" << std::endl;
				graph.showGraph();

				//writing information out of eulerian cycle
				write(graph.findWay());
			}

			return 0;
		}
		else {
			showOptions();
			return 0;
		}
	}
	else {
		showOptions();
		return 0;
	}

	return 0;
}
