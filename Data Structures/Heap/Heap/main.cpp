#include "heap.h"
#include <iostream>
#include <string>
#include <utility>

template <typename T>
void print_array(std::pair<T*, int> array) {
	for (int i = 0; i < array.second; i++) {
		std::cout << array.first[i] << " ";
	}
	std::cout << "\n";
}

int main() {
	std::cout << "HEAP INT\n";
	heap<int> h1;// { 1, 3, 8, 0, 2, 4, 6 };
	print_array(h1.get_array());
	for (int i = 0; i < 10; i++) {
		h1.push((2 * i + 1) * std::pow(-1, i));
		print_array(h1.get_array());
	}
	h1.push(0);
	print_array(h1.get_array());

	std::cout << std::endl;
	int size = h1.size();
	for (int i = 0; i < size; i++) {
		std::cout << "EL: " << h1.pop_top() << "\n";
		print_array(h1.get_array());
	}
	std::cout << "\n\nHEAP STRING\n";

	heap<std::string> hs{ "aaa","kotki","dwa","aaa" };
	print_array(hs.get_array());
	std::cout << "\n\n";

	int size_s = hs.size();
	for (int i = 0; i < size_s; i++) {
		std::cout << "EL: " << hs.pop_top() << "\n";
		print_array(hs.get_array());
	}

	return 0;
}