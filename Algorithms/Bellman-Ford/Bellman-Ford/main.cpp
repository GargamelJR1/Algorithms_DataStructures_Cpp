#include "bellman_ford.h"

int main() {
	double** adj_matrix = nullptr;
	int num_of_vertices = 0;
	prepare_adjacency_matrix(adj_matrix, num_of_vertices, "adj_matrix.txt");
	bellman_ford bf(adj_matrix, num_of_vertices, 1);
	bf.print_adjacency_matrix();
	bf.calculate_matrixes();

	return 0;
}