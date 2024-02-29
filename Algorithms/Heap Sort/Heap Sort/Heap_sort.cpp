#include "Heap_sort.h"

void replace(int& el1, int& el2) {
	int temp = el1;
	el1 = el2;
	el2 = temp;
}

std::pair<int*, int> prepare_array_from_file(std::string filename) {
	int* array;
	int number_of_elements(0);
	std::ifstream file(filename);
	std::string line;

	std::getline(file, line);
	file.close();
	std::stringstream ss(line);
	std::string temp;
	while (ss >> temp) number_of_elements++; // count number of elements in array

	ss.clear();
	ss.str(line);

	array = new int[number_of_elements];
	for (int i = 0; i < number_of_elements; i++) {
		ss >> array[i];
	}
	return std::make_pair(array, number_of_elements);
}