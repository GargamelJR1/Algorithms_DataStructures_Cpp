#include "Dijkstra.h"
#include <iostream>

int main() {
	try {
		double** adj_array = nullptr;
		int number_of_vertices = 0;
		prepare_arrays_from_file(adj_array, number_of_vertices, "adj_matrix.txt");
		Dijkstra dijk(adj_array, number_of_vertices, 1);
		dijk.print_adjacency_matrix();
		dijk.calculate_matrixes();
		std::cout << "\nFor which vertex print path?: ";
		int vertex_number(1);
		std::cin >> vertex_number;
		dijk.print_patch(vertex_number);
	}
	catch (std::invalid_argument& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "ERROR: There are negative distances in graph\n";
	}
	std::cout << "\nPress any key to continue ...";
	std::cin.get();
	return 0;
}