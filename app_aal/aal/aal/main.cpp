#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Graph.h"

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


int main(/*int argc, char **argv*/) {

	const char *nameOfFile = "data\\test5.txt";//"aal/aal/data/test7.txt"; //then I change it to read from args //delete const
/*
	if (argc != 2)
	{
		std::cout << "Add files!" << std::endl;
		return 0;
	}

	nameOfFile = argv[1];
*/
	Graph graph;
	read(graph, nameOfFile);

	graph.findWay(); // here must be variable which will have way and length of way


	std::cout << std::endl << "Hello world";

	int a;
	std::cin >> a;

	return 0;
}
