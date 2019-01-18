//Author: Patrycja Karbownik
//Problem: AAL.8 - Przygotowanie pod maraton (Problem chinskiego listonosza)

#include "Generator.h"

int Generator::myRandom(int mod) {
	return std::rand() % mod;
}

Graph Generator::eulerianGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges) {
	//generates new eurelian graph
	unsigned int addedEdges = 0;
	std::vector<unsigned int> vertices = beginningOfGenerateGraph(graph, number_of_vertices, number_of_edges, addedEdges);

	unsigned int mod = 4 * (number_of_edges / 5) + 1;
	unsigned int length;
	length = myRandom(mod) + 7;
	graph.add(vertices[number_of_vertices-1], vertices[0], length); //connecting first and last vertice in shuffled vector
	++addedEdges;

	if(addedEdges < number_of_edges)
		addRemainingEdges(graph, number_of_edges - addedEdges);

	return graph;
}

Graph Generator::graphWith2OddVertices(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges) {
	//generate new graph with 2 odd vertices
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
		graph.add(vertices[losEven], vertices[losOdd], length); //connecting one of odd vertices with one of even vertices
	
		++addedEdges;

		if (addedEdges < number_of_edges)
			addRemainingEdges(graph, number_of_edges - addedEdges);
	}
	return graph;
}

Graph Generator::graphWithMoreThan2OddVertices(Graph & graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int number_of_odd_vertices) {
	//generate new graph with more than 2 odd vertices
	unsigned int addedEdges = 0;
	std::vector<unsigned int> vertices = beginningOfGenerateGraph(graph, number_of_vertices, number_of_edges, addedEdges);
	std::vector<unsigned int> oddVertices = graph.getOddVertices();
	std::vector<unsigned int> evenVertices = graph.getEvenVertices();
	unsigned int mod = 6 * (number_of_edges / 9) + 1;
	unsigned int length, first, second, firstCoord, secondCoord;
	bool firstBool, secondBool;

	while (oddVertices.size() != number_of_odd_vertices) { //connecting two even vertices makes one edge and changes them to odd vertices
		std::random_shuffle(evenVertices.begin(), evenVertices.end());
		length = myRandom(mod) + 4;
		first = evenVertices[0];
		second = evenVertices[1];
		firstBool = false;
		secondBool = false;

		for (int i = 0; i < vertices.size(); ++i) { //finding coords of the vertices in vector, which is "shuffled", i.g.: 3, 5, 1, 0, 2, 4
			if (vertices[i] == first) {
				firstCoord = i;
				firstBool = true;
			}
			if (vertices[i] == second) {
				secondCoord = i;
				secondBool = true;
			}
			if (firstBool && secondBool) break;
		}

		graph.add(vertices[firstCoord], vertices[secondCoord], length);
		++addedEdges;

		//delete from even and add to odd
		oddVertices.push_back(first); //adding two even connected with each other vertices to oddVertices
		oddVertices.push_back(second);
		evenVertices.erase(evenVertices.begin()); //erasing two even connected with each other vertices from evenVertices
		evenVertices.erase(evenVertices.begin());
	}

	if (addedEdges < number_of_edges)
		addRemainingEdges(graph, number_of_edges - addedEdges);

	return graph;
}

std::vector<unsigned int> Generator::beginningOfGenerateGraph(Graph& graph, unsigned int number_of_vertices, unsigned int number_of_edges, unsigned int& addedEdges) {
	//it's used in every generate method at the beginning. It shuffles elements in vector and connects the next two in pairs (creates edges)
	std::vector<unsigned int> vertices;
	unsigned int mod = 3 * (number_of_edges / 4) + 1;

	graph.resize(number_of_vertices/*, number_of_edges*/);

	for (unsigned int i = 0; i < number_of_vertices; ++i)
		vertices.push_back(i);

	std::random_shuffle(vertices.begin(), vertices.end());

	//WRITING vertices shuffle. It helps in analysis of propriety
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
	//is used in methods, when we have to add more edges - the last step (randomizing 3 vertices and connecting them / randomizing 2 vertices, creating and double edge / randomizing 1 vertice and creating loop)
	unsigned int rest = number_of_edges % 3;
	unsigned int mod = 4 * (number_of_edges / 3) + 1;

	if (rest == 1) { //creating loop
		unsigned int length = myRandom(mod) + 9;
		unsigned int vertice = myRandom(graph.getNumberOfVertices());
		graph.add(vertice, vertice, length);

		number_of_edges -= 1;
	}
	else if (rest == 2) { //creating double edge
		unsigned int vertice1 = myRandom(graph.getNumberOfVertices());
		unsigned int vertice2 = myRandom(graph.getNumberOfVertices());
		unsigned int length = myRandom(mod) + 3;
		while (vertice2 == vertice1)
			vertice2 = myRandom(graph.getNumberOfVertices());

		graph.add(vertice1, vertice2, length);
		length = myRandom(mod) + 2;
		graph.add(vertice1, vertice2, length);

		number_of_edges -= 2;
	}

	rest = number_of_edges % 3;
	if (rest == 0) {
		while (number_of_edges > 0) { //creating 3 edges between 3 random vertices
			unsigned int vertice1 = myRandom(graph.getNumberOfVertices());
			unsigned int vertice2 = myRandom(graph.getNumberOfVertices());
			unsigned int vertice3 = myRandom(graph.getNumberOfVertices());
			unsigned int length = myRandom(mod) + 5;
			while (vertice2 == vertice1)
				vertice2 = myRandom(graph.getNumberOfVertices());
			while (vertice3 == vertice1 || vertice3 == vertice2)
				vertice3 = myRandom(graph.getNumberOfVertices());

			graph.add(vertice1, vertice2, length);
			length = myRandom(mod) + 7;
			graph.add(vertice1, vertice3, length);
			length = myRandom(mod) + 1;
			graph.add(vertice2, vertice3, length);

			number_of_edges -= 3;
		}
	}
}
