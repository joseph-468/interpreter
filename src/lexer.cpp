#include "../include/lexer.h"

#include <iostream>
#include <string>

Lexer::Lexer(std::string& code) noexcept : code(code)  {
	std::cout << code << std::endl;
}

std::vector<Token> Lexer::tokenize() noexcept {
	std::vector<Token> tokens;


	return tokens;
}

std::string Lexer::tokenToString(const Token& token) noexcept {
	std::string tokenStr;
	switch (token.type) {
		case TokenType::ASSIGNMENT: tokenStr = "="; break;
		case TokenType::EQUALITY: tokenStr = "=="; break;
		case TokenType::INEQUALITY: tokenStr = "!="; break;
		case TokenType::OR: tokenStr = "OR"; break;
		case TokenType::AND: tokenStr = "AND"; break;
		case TokenType::PLUS: tokenStr = "+"; break;
		case TokenType::MINUS: tokenStr = "-"; break;
		case TokenType::MULTIPLY: tokenStr = "*"; break;
		case TokenType::DIVIDE: tokenStr = "/"; break;
		case TokenType::LESSER: tokenStr = "<"; break;
		case TokenType::GREATER: tokenStr = ">"; break;
		case TokenType::IF: tokenStr = "IF"; break;
		case TokenType::THEN: tokenStr = "THEN"; break;
		case TokenType::ELSE: tokenStr = "ELSE"; break;
		case TokenType::WHILE: tokenStr = "WHILE"; break;
		case TokenType::FOR: tokenStr = "FOR"; break;
		case TokenType::RETURN: tokenStr = "RETURN"; break;
		case TokenType::INTEGER: tokenStr = "IntLiteral"; break;
		case TokenType::FLOAT: tokenStr = "FloatLiteral"; break;
		case TokenType::STRING: tokenStr = "StringLiteral"; break;
		case TokenType::IDENTIFIER: tokenStr = "Identifier"; break;
		case TokenType::LBRACKET: tokenStr = "["; break;
		case TokenType::RBRACKET: tokenStr = "]"; break;
		case TokenType::LPAREN: tokenStr = "("; break;
		case TokenType::RPAREN: tokenStr = ")"; break;
	}
	tokenStr += ": " + token.value;
	return tokenStr;
}