#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "../include/utils.h"
#include "../include/lexer.h"

int main(int argc, char* argv[]) {
	std::string filename;
	if (argc == 1) {
		filename = "tests/default.txt";
	}
	else if (argc == 2) {
		filename = argv[1];
	}
	else {
		std::cerr << "Error. Invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}

	auto result = readFile(filename);
	if (!result.has_value()) {
		std::cerr << "Error. Failed to read file" << std::endl;
		return EXIT_FAILURE;
	}
	std::string code = result.value();

	std::vector<Token> tokens;
	tokens = Lexer::tokenize(code);

	for (Token& i : tokens) {
		std::cout << Lexer::tokenToString(i) << std::endl;
	}

	return EXIT_SUCCESS;
}