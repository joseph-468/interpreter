#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "../include/lexer.h"

int main() {
	std::ifstream file("tests/basic.txt");
	if (!file.is_open()) {
		std::cerr << "Unable to open file" << std::endl;
		return -1;
	}

	std::stringstream codeStream;
	codeStream << file.rdbuf();
	std::string code = codeStream.str();

	std::vector<Token> tokens;
	Lexer lexer(code);
	tokens = lexer.tokenize();

	std::getchar();
	return 0;
}