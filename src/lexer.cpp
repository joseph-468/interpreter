#include "../include/lexer.h"

#include <iostream>
#include <string>

Lexer::Lexer(std::string& code) noexcept : code(code), curr(0)  {}

std::optional<char> Lexer::peek(const size_t offset) const noexcept {
	if (curr + offset >= code.length()) {
		return std::nullopt;
	}
	return code.at(curr + offset);
}

char Lexer::consume() noexcept {
	return code.at(curr++);
}

std::vector<Token> Lexer::tokenize() noexcept {
	std::vector<Token> tokens;
	std::string buf;
	while (peek().has_value()) {
		if (isspace(peek().value())) {
			consume();
		}
		else if (isalpha(peek().value())) {
			buf.push_back(consume());
			while (peek().has_value() && isalnum(peek().value())) {
				buf.push_back(consume());
			}

			TokenType type;
			std::optional<std::string> value = std::nullopt;
			if (buf == "IF") {
				type = TokenType::IF;
			}
			else if (buf == "THEN") {
				type = TokenType::THEN;
			}
			else if (buf == "ELSE") {
				type = TokenType::ELSE;
			}
			else if (buf == "WHILE") {
				type = TokenType::WHILE;
			}
			else if (buf == "FOR") {
				type = TokenType::FOR;
			}
			else if (buf == "GOTO") {
				type = TokenType::GOTO;
			}
			else {
				type = TokenType::IDENTIFIER;
				value = buf;
			}

			tokens.emplace_back(type, value);
			buf.clear();
		}
		// Temporary
		else {
			consume();
		}
	}

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
		case TokenType::GOTO: tokenStr = "GOTO"; break;
		case TokenType::INTEGER: tokenStr = "IntLiteral"; break;
		case TokenType::FLOAT: tokenStr = "FloatLiteral"; break;
		case TokenType::STRING: tokenStr = "StringLiteral"; break;
		case TokenType::IDENTIFIER: tokenStr = "Identifier"; break;
		case TokenType::LBRACKET: tokenStr = "["; break;
		case TokenType::RBRACKET: tokenStr = "]"; break;
		case TokenType::LPAREN: tokenStr = "("; break;
		case TokenType::RPAREN: tokenStr = ")"; break;
	}
	if (token.value.has_value()) {
		tokenStr += ": " + token.value.value();
	}
	return tokenStr;
}