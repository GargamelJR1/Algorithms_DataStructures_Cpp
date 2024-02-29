#pragma once
#include <string>

class negative_distance_exception : std::exception {};

class Dijkstra
{
	double* distances;
	int* predecessors;
	double** adj_array;
	int number_of_vertices;
	int source;

	void print_current_matrixes() const;

public:
	Dijkstra(double** adj_array, int number_of_vertices, int source);

	void calculate_matrixes();

	void relaxation(int vertex_index);

	void print_adjacency_matrix() const;

	void print_patch(int destination);

	~Dijkstra();
};

void prepare_arrays_from_file(double**& adj_array, int& number_of_vertices, std::string filename);