#include "bellman_ford.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void bellman_ford::print_current_matrixes() {
	const int szer_double = 5;
	cout << "\ni    ";
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

void bellman_ford::load_edges() {
	for (int i = 0; i < number_of_vertices; i++) {
		for (int j = 0; j < number_of_vertices; j++) {
			if (i != j && adj_array[i][j] != numeric_limits<double>::infinity())
				edges.push_back(make_pair(i, j));
		}
	}
}

void bellman_ford::calculate_matrixes() {
	bool change = 0;
	for (int i = 0; i < number_of_vertices - 1; i++) {
		change = 0;
		cout << "\n" << i + 1 << " Iteration\n";
		for (const auto& t : edges) {
			print_current_matrixes();
			relaxation(t.first, t.second, change);
		}
		if (!change) break;
	}
	change = 0;
	cout << "\nAdditional Iteration\n";
	for (const auto& t : edges) {
		print_current_matrixes();
		relaxation(t.first, t.second, change);
	}
	if (change == 1)
		cout << "\nThere are negative cycles in graph\n" << endl;
}

void bellman_ford::relaxation(int source, int destination, bool& change) {
	double dist_to_current = distances[source];
	if (destination == source) return; // distance from vertex to the same vertex is 0
	if (distances[destination] > dist_to_current + adj_array[source][destination]) {
		distances[destination] = dist_to_current + adj_array[source][destination];
		predecessors[destination] = source + 1;
		change = 1;
	}
}

void bellman_ford::print_adjacency_matrix() {
	for (int i = 0; i < number_of_vertices; i++) {
		for (int j = 0; j < number_of_vertices; j++) {
			cout << adj_array[i][j] << " ";
		}
		cout << endl;
	}
}

bellman_ford::~bellman_ford() {
	for (int i = 0; i < number_of_vertices; i++) {
		delete[] adj_array[i];
	}
	delete[] adj_array;

	delete[] distances;
	delete[] predecessors;
}

void prepare_adjacency_matrix(double**& adj_array, int& number_of_verticles, string filename) {
	string line;

	ifstream file(filename);
	getline(file, line);
	stringstream ss(line);
	{
		string temp;
		while (ss >> temp) number_of_verticles++;
		number_of_verticles--;
	}
	adj_array = new double* [number_of_verticles + 1];
	for (int i = 0; i < number_of_verticles; i++) {
		adj_array[i] = new double[number_of_verticles];
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
			else
				adj_array[i][j] = stof(temp);
			j++;
		}
		i++;
	}
	file.close();
}