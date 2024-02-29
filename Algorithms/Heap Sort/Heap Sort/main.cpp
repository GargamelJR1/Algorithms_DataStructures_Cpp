#include "Heap_sort.h"
#include <iostream>

int main() {
	auto array_to_sort = prepare_array_from_file("array.txt");
	Heap_sort sort(array_to_sort.first, array_to_sort.second);
	sort.save_array_to_file("sorted_array.txt");

	std::cout << "\nPress any key to continue ...";
	std::cin.get();
	return 0;
}