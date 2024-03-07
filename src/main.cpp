#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "../include/utils.h"
#include "../include/lexer.h"

int main() {
	auto result = readFile("tests/basic.txt");
	if (!result.has_value()) {
		std::cerr << "Failed to read file" << std::endl;
		return EXIT_FAILURE;
	}
	std::string code = result.value();

	std::vector<Token> tokens;
	Lexer lexer(code);
	tokens = lexer.tokenize();

	for (Token& i : tokens) {
		std::cout << Lexer::tokenToString(i) << std::endl;
	}

	std::getchar();
	return EXIT_SUCCESS;
}