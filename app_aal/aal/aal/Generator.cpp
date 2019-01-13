#include "Generator.h"



Generator::Generator()
{
	std::srand(unsigned(std::time(0)));
}

Generator::~Generator()
{
}

unsigned int Generator::myRandom(unsigned int mod) {
	return std::rand() % mod;
}

Graph Generator::eulerianGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges)
{
	unsigned int addedEdges = 0;
	std::vector<unsigned int> vertices = beginningOfGenerateGraph(graph, number_of_vertices, number_of_edges, addedEdges);

	unsigned int mod = 4 * (number_of_edges / 5) + 1;
	unsigned int length;
	length = myRandom(mod) + 7;
	graph.add(vertices[number_of_vertices-1], vertices[0], length);
	++addedEdges;

	if(addedEdges < number_of_edges)
		addRemainingEdges(graph, number_of_edges - addedEdges);

	return graph;
}

Graph Generator::graphWith2OddVertices(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges) {
	unsigned int addedEdges = 0;
	std::vector<unsigned int> vertices = beginningOfGenerateGraph(graph, number_of_vertices, number_of_edges, addedEdges);

	if (number_of_edges > number_of_vertices - 1) {
		unsigned int mod = 4 * (number_of_edges / 5) + 1;
		unsigned int length;
		unsigned int losOdd = myRandom(2);
		unsigned int losEven = myRandom(number_of_vertices);
		while(losEven == 0 || losEven == number_of_vertices - 1)
			losEven = myRandom(number_of_vertices);
		if (losOdd != 0) losOdd = number_of_vertices - 1;

		length = myRandom(mod) + 7;
		graph.add(vertices[losEven], vertices[losOdd], length);
	
		++addedEdges;

		if (addedEdges < number_of_edges)
			addRemainingEdges(graph, number_of_edges - addedEdges);
	}

	return graph;
}

std::vector<unsigned int> Generator::beginningOfGenerateGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int& addedEdges) {
	std::vector<unsigned int> vertices;
	unsigned int mod = 3 * (number_of_edges / 4) + 1;

	graph.resize(number_of_vertices, number_of_edges);

	for (unsigned int i = 0; i < number_of_vertices; ++i)
		vertices.push_back(i);

	std::random_shuffle(vertices.begin(), vertices.end());

	//WRITING vertices shuffle
	for (std::vector<unsigned int>::iterator it = vertices.begin(); it != vertices.end(); ++it)
		std::cout << *it << " ";

	unsigned int length;
	for (unsigned int i = 0; i < number_of_vertices - 1; ++i) {
		length = myRandom(mod) + 4;
		graph.add(vertices[i], vertices[i + 1], length);
		++addedEdges;
	}

	return vertices;
}

void Generator::addRemainingEdges(Graph& graph, unsigned int number_of_edges) {
	unsigned int rest;
	unsigned int mod = 4 * (number_of_edges / 3) + 1;

	std::cout << "addRemainingEdges" << std::endl;
	
	rest = number_of_edges % 3;
	if (rest == 1) {
		std::cout << "loop ";
		unsigned int length = myRandom(mod) + 9;
		unsigned int vertice = myRandom(graph.getNumberOfVertices());
		std::cout << vertice << std::endl;//
		graph.add(vertice, vertice, length);

		number_of_edges -= 1;
	}
	else if (rest == 2) {
		std::cout << "double ";
		unsigned int vertice1 = myRandom(graph.getNumberOfVertices());
		unsigned int vertice2 = myRandom(graph.getNumberOfVertices());
		unsigned int length = myRandom(mod) + 3;
		while (vertice2 == vertice1)
			vertice2 = myRandom(graph.getNumberOfVertices());

		std::cout << vertice1 << " " << vertice2 << std::endl;//
		graph.add(vertice1, vertice2, length);
		length = myRandom(mod) + 2;
		graph.add(vertice1, vertice2, length);

		number_of_edges -= 2;
	}

	rest = number_of_edges % 3;
	if (rest == 0) {
		while (number_of_edges > 0) {
			std::cout << "triangle";

			unsigned int vertice1 = myRandom(graph.getNumberOfVertices());
			unsigned int vertice2 = myRandom(graph.getNumberOfVertices());
			unsigned int vertice3 = myRandom(graph.getNumberOfVertices());
			unsigned int length = myRandom(mod) + 5;
			while (vertice2 == vertice1)
				vertice2 = myRandom(graph.getNumberOfVertices());
			while (vertice3 == vertice1 || vertice3 == vertice2)
				vertice3 = myRandom(graph.getNumberOfVertices());

			std::cout << vertice1 << " " << vertice2 << " " << vertice3 << std::endl;//

			graph.add(vertice1, vertice2, length);
			length = myRandom(mod) + 7;
			graph.add(vertice1, vertice3, length);
			length = myRandom(mod) + 1;
			graph.add(vertice2, vertice3, length);

			number_of_edges -= 3;
		}
	}
}
