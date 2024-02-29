#pragma once
#include <concepts>
#include <utility>
#include <initializer_list>
#include <cmath>

template <typename T>
void replace(T& a, T& b) {
	T copy = a;
	a = b;
	b = copy;
}

template <typename T>
	requires std::equality_comparable<T>
class heap
{
	T* array;
	int number_of_elements;
	int max_number_of_elements;

	void alloc_new_memory() {
		if (array != nullptr) {
			T* temp = new T[2 * max_number_of_elements];
			for (int i = 0; i < max_number_of_elements; i++) {
				temp[i] = array[i];
			}
			max_number_of_elements *= 2;
			delete[] array;
			array = temp;
		}
		else {
			array = new T[2];
			max_number_of_elements = 2;
		}
	}

	void move_down(int current_index, int max_index) {
		int child_index(0);
		while (true) {
			if ((2 * current_index) + 1 > max_index) break; // break if there is no sons of current node
			child_index = 2 * current_index + 1; // set child_index to left son
			if (child_index + 1 <= max_index && array[child_index] > array[child_index + 1])
				child_index++; // set child_index to right son if it exists and has lower value than left son
			if (array[current_index] < array[child_index]) break; // node is in right place
			replace(array[current_index], array[child_index]);
			current_index = child_index;
		}
	}

	void move_up(int current_index) {
		int parent_index(0);
		while (true) {
			parent_index = (current_index - 1) / 2; // set parent index
			if (current_index == 0) break; // if current node is root then break
			if (array[current_index] > array[parent_index]) break; // node is in right place
			replace(array[current_index], array[parent_index]);
			current_index = parent_index;
		}
	}

	void shrink_memory() {
		if (number_of_elements < (0.4 * max_number_of_elements)) {
			if (number_of_elements != 0) {
				int x(0);
				while ((std::pow(2, x)) <= number_of_elements)
					x++;

				max_number_of_elements = std::pow(2, x);
				T* temp = new T[max_number_of_elements];
				for (int i = 0; i < number_of_elements; i++) {
					temp[i] = array[i];
				}
				delete[] array;
				array = temp;
			}
			else {
				max_number_of_elements = 0;
				delete[] array;
				array = nullptr;
			}
		}
	}

public:

	heap() :array(nullptr), number_of_elements(0), max_number_of_elements(0) {};

	heap(std::initializer_list<T> il) :array(nullptr), number_of_elements(0), max_number_of_elements(0) {
		for (const T& el : il) {
			push(el);
		}
	}

	void push(const T& new_el) {
		if (number_of_elements + 1 > max_number_of_elements) {
			alloc_new_memory();
		}
		array[number_of_elements] = new_el;
		number_of_elements++;
		move_up(number_of_elements - 1);
	}

	T pop_top() {
		if (array != nullptr) {
			if (number_of_elements > 1) {
				T top_element = array[0];
				pop();
				return top_element;
			}
			else {
				number_of_elements = 0;
				T temp_return = array[0];
				shrink_memory();
				return temp_return;
			}
		}
	}

	void pop() {
		if (array != nullptr) {
			if (number_of_elements > 1) {
				replace(array[0], array[number_of_elements - 1]);
				number_of_elements--;
				move_down(0, number_of_elements - 1);
			}
			else
				number_of_elements = 0;

			shrink_memory();
		}
	}

	int size() {
		return number_of_elements;
	}

	T top() {
		if (array != nullptr)
			return array[0];
	}

	std::pair<T*, int> get_array() {
		return std::make_pair(array, number_of_elements);
	}

	~heap() {
		delete[] array;
	}
};