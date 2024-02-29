#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class bellman_ford
{
	double* distances;
	int* predecessors;
	double** adj_array;
	int number_of_vertices;
	int source;
	vector <pair<int, int>> edges;

	void print_current_matrixes();

	void load_edges();

public:
	bellman_ford(double** adj_array, int number_of_vertices, int source) :
		distances(nullptr), predecessors(nullptr), adj_array(adj_array), number_of_vertices(number_of_vertices), source(source) {

		distances = new double[number_of_vertices];
		predecessors = new int[number_of_vertices];

		for (int j = 0; j < number_of_vertices; j++) {
			distances[j] = adj_array[0][j];
			if (source - 1 == j)
				predecessors[j] = 0;
			else {
				if (adj_array[0][j] == numeric_limits<double>::infinity())
					predecessors[j] = 0;
				else
					predecessors[j] = source;
			}
		}

		load_edges();
	};

	void calculate_matrixes();

	void relaxation(int source, int destination, bool& change);

	void print_adjacency_matrix();

	~bellman_ford();

};

void prepare_adjacency_matrix(double**& adj_array, int& number_of_verticles, string filename);