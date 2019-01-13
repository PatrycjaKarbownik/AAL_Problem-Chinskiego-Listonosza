#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Graph.h"
#include "Generator.h"

void read(Graph& graph, const char *nameOfFile) //then delete const
{
	std::fstream file;

	file.open(nameOfFile, std::ios::in);

	unsigned int first, second, length;
	std::vector<unsigned int> first_vect, second_vect, length_vect;

	while (file >> first >> second >> length)
	{
		first_vect.push_back(first);
		second_vect.push_back(second);
		length_vect.push_back(length);
	}

	/*if (!(first_vect.size() == second_vect.size() && first_vect.size() == length_vect.size())) {
		throw std::exception("size of vectors aren't equal");
		std::cout << "size of vectors aren't equal" << std::endl;
	}*/

	unsigned int number_of_edges = first_vect.size();

	unsigned int number_of_vert = 0;
	for (unsigned int i = 0; i < number_of_edges; ++i) {
		if (number_of_vert < first_vect[i]) number_of_vert = first_vect[i];
		if (number_of_vert < second_vect[i]) number_of_vert = second_vect[i];
	}
	++number_of_vert;
	//std::cout << "number of vertices " << number_of_vert << std::endl;

	graph.resize(number_of_vert, number_of_edges);
	   
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


int main(/*int argc, char **argv*/) {

/*
	if (argc != 2)
	{
		std::cout << "Add files!" << std::endl;
		return 0;
	}

	nameOfFile = argv[1];
*/
	Graph graph;

	// (1)
	//read from file. I have to edit this
	/*
	const char *nameOfFile = "data\\test5.txt";//"aal/aal/data/test7.txt"; //then I change it to read from args //delete const
	read(graph, nameOfFile);
	*/


	//(2)
	//generator
	// -eulerian
	/*unsigned int number_of_vertices, number_of_edges;
	Generator generator;
	while (true) {
		std::cout << "Set number of vertices and edges in new graph (with eulerian cycle at the beginning) (number of edges >= number of vertices)" << std::endl;
		std::cin >> number_of_vertices;
		std::cin >> number_of_edges;

		if (number_of_vertices <= 1 || number_of_edges <= 1)
		{
			std::cout << "Numbers have to be more than 1" << std::endl;
		}
		else if (number_of_edges < number_of_vertices) {
			std::cout << "Number of edges have to be equal or more than number of vertices" << std::endl;
		}
		else break;
	}
	generator.eulerianGraph(graph, number_of_vertices, number_of_edges);
	graph.showGraph();*/

	// -2odd
	
	unsigned int number_of_vertices, number_of_edges;
	Generator generator;
	while (true) {
		std::cout << "Set number of vertices and edges in new graph (with 2 odd vertices at the beginning) (number of edges >= number of vertices - 1)" << std::endl;
		std::cin >> number_of_vertices;
		std::cin >> number_of_edges;

		if (number_of_vertices < 1 || number_of_edges < 1)
		{
			std::cout << "Numbers have to be more than 0" << std::endl;
		}
		else if (number_of_edges < number_of_vertices - 1) {
			std::cout << "Number of edges have to be more than number of vertices - 1" << std::endl;
		}
		else break;
	}
	generator.graphWith2OddVertices(graph, number_of_vertices, number_of_edges);
	graph.showGraph();

	
	//writing information out of eulerian cycle
	write(graph.findWay());

	std::cout << std::endl << "Hello world";

	int a;
	std::cin >> a;

	return 0;
}
