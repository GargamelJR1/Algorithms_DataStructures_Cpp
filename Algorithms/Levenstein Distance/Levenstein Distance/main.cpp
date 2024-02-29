#include "LevDistance.h"
#include <iostream>

int main() {
	std::string f("");
	std::string s("");
	std::cout << "Please give words to calculate Levenstein distance (put space between them and confirm with enter): ";
	std::cin >> f >> s;
	LevDistance edist(f, s);
	edist.print_array();
	std::cout << "\n\n";
	edist.print_array_with_arrows();
	std::cout << "\nLevenstein distance of " << f << " and " << s << " is: " << edist.get_distance();

	std::cout << "\nPress any key to continue ...";
	std::cin.get();
	return 0;
}