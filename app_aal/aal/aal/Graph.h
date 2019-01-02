#pragma once

#include <vector>
#include <iostream>
#include <string>

class Graph
{
private:
	std::vector<std::vector <std::pair <unsigned int, unsigned int> > > vertices;
	unsigned int number_of_vertices;
	unsigned int size;

	unsigned int countOddVertices(); //if number of odd vertices is more than 3, function stop counting
	void DFSEuler(unsigned int v, std::vector<unsigned int>& euler, std::vector< std::vector<bool> >visited);
	std::vector<unsigned int> findEulerianCycle();
	unsigned int lengthOfEulerianCycle();

public:
	Graph();
	~Graph();
	void add(unsigned int first, unsigned int second, unsigned int length);
	void resize(unsigned int number_of_vertices, unsigned int size);

	void findWay();//then not void type
};

