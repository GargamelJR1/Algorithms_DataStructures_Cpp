#pragma once
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <map>
#include <iostream>

struct node {
	node(char symbol, int weight) :data(std::make_pair(symbol, weight)), left(nullptr), right(nullptr) {};
	node(char symbol, int weight, std::shared_ptr<node> left_, std::shared_ptr<node> right_) :data(std::make_pair(symbol, weight)), left(left_), right(right_) {};
	std::pair<char, int> data;
	std::shared_ptr<node> left;
	std::shared_ptr<node> right;
};

struct compare {
	bool operator()(std::shared_ptr<node> n1, std::shared_ptr<node> n2) {
		return (n1->data.second > n2->data.second);
	}
};

class huffman
{
	std::vector<char> alphabet;
	std::vector<char> input;
	std::string encoded_output;
	std::map<char, std::string> symbols_and_codes;
	std::shared_ptr<node> top;

	void create_tree() {
		std::map<char, int> symbols_and_weights;
		for (int i = 0; i < alphabet.size(); i++) {
			symbols_and_weights.emplace(alphabet[i], 0);
		}

		for (int i = 0; i < input.size(); i++) {
			symbols_and_weights[input[i]]++;
		}

		std::priority_queue<std::shared_ptr<node>, std::vector<std::shared_ptr<node>>, compare> nodes;
		for (const auto& t : symbols_and_weights) {
			nodes.push(std::make_shared<node>(node(t.first, t.second)));
		}

		while (nodes.size() > 1) {
			std::shared_ptr<node> left(nodes.top());
			nodes.pop();
			std::shared_ptr<node> right(nodes.top());
			nodes.pop();
			top = std::make_shared<node>(node('\0', left->data.second + right->data.second, left, right));
			nodes.push(top);
		}
		nodes.pop();
	}

	void make_codes(std::shared_ptr<node> tree_node, std::string code) {
		if (tree_node != nullptr) {
			if (tree_node->data.first != '\0')
				symbols_and_codes.insert(std::make_pair(tree_node->data.first, code));
			make_codes(tree_node->left, code + "0");
			make_codes(tree_node->right, code + "1");
		}
	}

	void encode_input() {
		for (const auto t : input) {
			encoded_output.append(symbols_and_codes[t]);
		}
	}

	void load_alphabet(std::string alphabet_name) {
		std::string line;
		std::ifstream alphabet_file(alphabet_name);
		std::getline(alphabet_file, line);

		if (line.find(" ") != std::string::npos)
			for (int i = 0; i < line.length(); i += 2)
				alphabet.push_back(line[i]);
		else
			for (int i = 0; i < line.length(); i++)
				alphabet.push_back(line[i]);

		alphabet_file.close();
	}

public:
	huffman(std::string input_filename, std::string alphabet_filename) :top(nullptr), encoded_output("") {
		load_input(input_filename);
		load_alphabet(alphabet_filename);
		create_tree();
		std::string temp("");
		make_codes(top, temp);
		encode_input();
	}

	void save_output(std::string output_name) const {
		std::ofstream output_file(output_name);
		output_file << encoded_output;
		output_file.close();
	}

	void print_symbols_and_codes() {
		std::cout << "Symbols and their codes: \n";
		for (const auto& t : symbols_and_codes) {
			std::cout << t.first << " " << t.second << "\n";
		}
	}

	void load_input(std::string input_filename) {
		std::string line;
		std::ifstream input_file(input_filename);
		std::getline(input_file, line);
		for (int i = 0; i < line.length(); i++) {
			input.push_back(line[i]);
		}
		input_file.close();
	}

	void decode(std::string decode_filename) {
		std::map<std::string, char> codes_and_symbols;
		for (const auto& t : symbols_and_codes) {
			codes_and_symbols.insert(make_pair(t.second, t.first));
		}

		std::string line;
		std::ifstream decode_input_file(decode_filename);
		if (decode_input_file.good()) {
			getline(decode_input_file, line);
			decode_input_file.close();

			std::vector<char> decoded_text;
			std::string temp;
			for (int i = 0; i < line.length(); i++) {
				temp += line[i];
				if (codes_and_symbols.find(temp) != codes_and_symbols.end()) {
					decoded_text.push_back(codes_and_symbols.at(temp));
					temp.clear();
				}
			}

			std::cout << "\nEncoded text: ";
			for (const auto t : decoded_text)
				std::cout << t;
			std::cout << ", from file: " << decode_filename << "\n";
		}
		else
			std::cout << "There is a problem with the file or it doesn't exist\n";
	}

	void calculate_compression_rate() {
		int input_size = input.size();
		int i = 0;
		int pow_of_two = 1;
		while (true) {
			int no_bytes_symbol = pow(2, i);
			if (input_size <= no_bytes_symbol) break;
			i++;
		}
		int min_number_of_bytes = input_size * i;
		double compression_rate = min_number_of_bytes / (double)encoded_output.size();
		std::cout << "Compression rate is: " << compression_rate << "\n";
	}

	void print_input() {
		std::cout << "Input: ";
		for (const auto& t : input)
			std::cout << t;
		std::cout << "\nEncoded input: " << encoded_output << "\n";
	}

	void print_alphabet() {
		std::cout << "Alphabet: ";
		for (const auto& t : alphabet)
			std::cout << t << " ";
		std::cout << "\n";
	}
};

