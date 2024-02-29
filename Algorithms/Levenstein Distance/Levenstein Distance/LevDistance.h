#pragma once
#include <string>
#include <iostream>

int mini(int a, int b, int c);
int mini_which(int a, int b, int c);

class LevDistance
{
	std::string source, destination;
	int del, ins, rev;
	int** array2D; // array with distances
	std::string** arrayArrows; // array with distances and arrows (direction and operation)
	int M, N; // lenghts of words, number of rows and columns
	int distance;

public:

	LevDistance(std::string first, std::string second, int del = 1, int ins = 1, int rev = 1) :source(first), destination(second), del(1), ins(1), rev(1) {
		M = static_cast<int>(source.size() + 1);
		N = static_cast<int>(destination.size() + 1);
		calculate_distance();
	};

	void calculate_distance() {
		array2D = new int* [M];
		for (int i = 0; i < M; i++) {
			array2D[i] = new int[N];
		}

		arrayArrows = new std::string * [M];
		for (int i = 0; i < M; i++) {
			arrayArrows[i] = new std::string[N];
		}

		int direction = 0;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (i == 0) array2D[i][j] = j;
				else if (j == 0) array2D[i][j] = i;
				else {
					int reve = rev;
					if (source[i - 1] == destination[j - 1]) reve = 0; // checks if symbols are identical
					direction = mini_which(array2D[i - 1][j - 1] + reve, array2D[i][j - 1] + ins, array2D[i - 1][j] + del);
					array2D[i][j] = mini(array2D[i - 1][j - 1] + reve, array2D[i][j - 1] + ins, array2D[i - 1][j] + del);
				}

				// fill arrow array
				char arrow(' ');
				switch (direction) {
				case 1:
					arrow = '\\';
					break;
				case 2:
					arrow = '<';
					break;
				case 3:
					arrow = '^';
					break;
				}
				arrayArrows[i][j] = std::to_string(array2D[i][j]) + arrow;
			}
		}

		distance = array2D[M - 1][N - 1];
	}

	void print_array() const {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << array2D[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	void print_array_with_arrows() const {
		std::cout << "\\ is substitution, ^ is deletion and < is insertion of symbol\n";
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << arrayArrows[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	int get_distance() const {
		return distance;
	}

	~LevDistance() {
		if (array2D != nullptr) {
			for (int i = 0; i < M; i++) {
				delete[] array2D[i];
			}
			delete[] array2D;
		}
	}
};

