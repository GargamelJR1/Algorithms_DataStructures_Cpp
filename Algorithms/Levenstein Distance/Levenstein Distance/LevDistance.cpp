#include "LevDistance.h"

int mini(int a, int b, int c) {
	return std::min(a, std::min(b, c));
}

int mini_which(int a, int b, int c) {
	int min = mini(a, b, c);
	if (min == a) return 1;
	if (min == b) return 2;
	if (min == c) return 3;
}