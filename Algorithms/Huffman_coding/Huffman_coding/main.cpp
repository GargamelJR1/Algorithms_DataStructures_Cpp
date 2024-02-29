#include "huffman.h"
#include <iostream>

int main() {
	huffman hc("input.txt", "alphabet.txt");
	hc.print_alphabet();
	hc.print_input();
	hc.print_symbols_and_codes();
	hc.save_output("output.txt");
	std::cout << "If you want to decode file, write filename with extension or write 0 to end program:  ";
	std::string a;
	std::cin >> a;
	if (a != "0")
		hc.decode(a);
	hc.calculate_compression_rate();

	std::cout << "\nPress any key to continue ...";
	std::cin.get();
	return 0;
}