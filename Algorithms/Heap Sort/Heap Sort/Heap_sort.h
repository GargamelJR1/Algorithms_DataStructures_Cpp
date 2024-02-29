#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void replace(int& el1, int& el2);

class Heap_sort
{
	int* array;
	int number_of_elements;

public:

	Heap_sort(int* array, int count) : array(array), number_of_elements(count) {
		std::cout << "INPUT ARRAY\n";
		print_array();

		build_heap(); // build heap from input array

		std::cout << "\nHEAP ARRAY\n";
		print_array();
		std::cout << "\nSORTING\n";

		// sorting
		for (int i = (number_of_elements - 1); i >= 1; i--) {
			replace(array[i], array[0]); // put biggest element at the end
			move_down(0, i - 1); // repair heap
			print_array(); // print array on screen
		}

		std::cout << "\nSORTED ARRAY\n";
		print_array();
	}

	void build_heap() {
		for (int i = (number_of_elements / 2); i >= 0; i--) {
			move_down(i, number_of_elements);
		}
	}

	void move_down(int el_index, int max_index) {
		int child_index(0);
		child_index = 2 * el_index; // set left child index
		if (child_index > max_index) return; // if there are no children of current node, break
		if ((child_index + 1) <= max_index) // check if right child exist 
			if (array[child_index + 1] > array[child_index]) // check which child is bigger
				child_index = child_index + 1; // set child index to right child if it is bigger than left child
		if (array[el_index] >= array[child_index]) return; // if element is in right place, break
		replace(array[el_index], array[child_index]); // replace parent with child
		move_down(child_index, max_index); // recursive execution of function for remaining part of heap
	}

	void print_array() {
		for (int i = 0; i < number_of_elements; i++) std::cout << array[i] << " ";
		std::cout << "\n";
	}

	void save_array_to_file(std::string out_name) {
		std::ofstream ofile(out_name);
		for (int i = 0; i < number_of_elements; i++) ofile << array[i] << " ";
	}

	~Heap_sort() {
		delete[] array;
	}
};

std::pair<int*, int> prepare_array_from_file(std::string filename);