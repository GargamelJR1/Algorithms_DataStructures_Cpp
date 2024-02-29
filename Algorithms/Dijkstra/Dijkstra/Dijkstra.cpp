#include "Dijkstra.h"
#include <fstream>
#include <map>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm> // for function reverse

using namespace std;

void prepare_arrays_from_file(double**& adj_array, int& number_of_vertices, string filename) {
	string line;

	ifstream file(filename);
	getline(file, line);
	stringstream ss(line);
	{
		string temp;
		while (ss >> temp) number_of_vertices++;
		number_of_vertices--;
	}
	adj_array = new double* [number_of_vertices + 1];
	for (int i = 0; i < number_of_vertices; i++) {
		adj_array[i] = new double[number_of_vertices];
	}

	int i = 0;

	while (getline(file, line)) {
		int j = 0;
		stringstream ssx(line);

		string temp;
		ssx >> temp;
		while (ssx >> temp) {
			if (temp == "i")
				adj_array[i][j] = numeric_limits<double>::infinity();
			else {
				double dist = stof(temp);
				if (dist < 0) throw negative_distance_exception();
				adj_array[i][j] = dist;
			}
			j++;
		}
		i++;
	}
	file.close();
}

void Dijkstra::print_current_matrixes() const {
	const int szer_double = 5;
	cout << "\n\ni    ";
	for (int j = 0; j < number_of_vertices; j++) {
		cout << setw(szer_double) << j + 1 << " ";
	}
	cout << "\nC[i] ";
	for (int j = 0; j < number_of_vertices; j++) {
		cout << setw(szer_double) << distances[j] << " ";
	}
	cout << "\nP[i] ";
	for (int j = 0; j < number_of_vertices; j++) {
		cout << setw(szer_double) << predecessors[j] << " ";
	}
	cout << endl;
}

Dijkstra::Dijkstra(double** adj_array, int number_of_vertices, int source) :
	distances(nullptr), predecessors(nullptr), adj_array(adj_array), number_of_vertices(number_of_vertices), source(source) {
	if (source < 1 || source > number_of_vertices) throw invalid_argument("Source vertex does not exist");

	distances = new double[number_of_vertices];
	predecessors = new int[number_of_vertices];

	for (int j = 0; j < number_of_vertices; j++) {
		distances[j] = adj_array[0][j];
		if (j == source - 1 || adj_array[0][j] == numeric_limits<double>::infinity())
			predecessors[j] = 0;
		else
			predecessors[j] = source;
	}
}

void Dijkstra::calculate_matrixes() {
	map<double, int> remaining_verticles; // verticles sorted by distances
	for (int j = 0; j < number_of_vertices; j++)
		remaining_verticles.emplace(distances[j], j + 1);
	remaining_verticles.erase(0); // remove source from map

	while (!remaining_verticles.empty()) {
		print_current_matrixes();
		int current_nearest = remaining_verticles.begin()->second;
		relaxation(current_nearest);
		remaining_verticles.erase(remaining_verticles.begin()->first);
	}
}

void Dijkstra::relaxation(int vertex_index) {
	double dist_to_current = distances[vertex_index - 1];
	for (int j = 0; j < number_of_vertices; j++) {
		if (vertex_index == j + 1) continue; // distance from vertex to the same vertex is 0
		if (distances[j] > dist_to_current + adj_array[vertex_index - 1][j]) {
			distances[j] = dist_to_current + adj_array[vertex_index - 1][j];
			predecessors[j] = vertex_index;
		}
	}
}

void Dijkstra::print_adjacency_matrix() const {
	for (int i = 0; i < number_of_vertices; i++) {
		for (int j = 0; j < number_of_vertices; j++) {
			cout << adj_array[i][j] << " ";
		}
		cout << endl;
	}
}

void Dijkstra::print_patch(int destination) {
	destination = destination - 1;
	if (destination == source - 1) {
		cout << "Destination is the same as source";
		return;
	}
	if (destination >= number_of_vertices || destination < 0) {
		cout << "Vertex no " << destination + 1 << " does not exist";
		return;
	}
	string path("Path from " + to_string(source) + " to " + to_string(destination + 1) + " is:  " + to_string(source));
	if (predecessors[destination] == source)
		path.append(" -> " + to_string(destination + 1));
	else {
		string path_reverse;
		while (predecessors[destination] != source) {
			path_reverse.append(to_string(destination + 1) + " >- ");
			destination = predecessors[destination] - 1;
		}
		path_reverse.append(to_string(destination + 1) + " >- ");
		reverse(path_reverse.begin(), path_reverse.end());
		path.append(path_reverse);
	}
	cout << path;
}

Dijkstra::~Dijkstra() {
	for (int i = 0; i < number_of_vertices; i++) {
		delete[] adj_array[i];
	}
	delete[] adj_array;

	delete[] distances;
	delete[] predecessors;
}
