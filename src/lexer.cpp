#include "../include/lexer.h"
#include "../include/utils.h"

#include <iostream>
#include <string>


namespace Lexer {
	// Private
	std::string code;
	size_t curr;

	inline std::optional<char> peek(const size_t offset = 0) noexcept {
		if (curr + offset >= code.length()) {
			return std::nullopt;
		}
		return code.at(curr + offset);
	}

	inline char consume() noexcept {
		return code.at(curr++);
	}

	// Public
	std::vector<Token> tokenize(const std::string& source) noexcept {
		code = source;
		curr = 0;
		std::vector<Token> tokens;
		std::string buf;
		while (peek().has_value()) {
			if (isspace(peek().value())) {
				consume();
			}
			else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
				while (peek().has_value() && peek().value() != '\n') {
					consume();
				}
			}
			else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
				while (peek().has_value()) {
					if (peek().value() == '*' && peek(1).has_value() && peek(1).value() == '/') {
						consume();
						consume();
						break;
					}
					consume();
				}
			}
			else if (peek().value() == '=' && peek(1).has_value() && peek(1).value() == '=') {
				consume();
				consume();
				tokens.emplace_back(TokenType::EQUALITY, std::nullopt);
			}
			else if (peek().value() == '!' && peek(1).has_value() && peek(1).value() == '=') {
				consume();
				consume();
				tokens.emplace_back(TokenType::INEQUALITY, std::nullopt);
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
				else if (buf == "OR") {
					type = TokenType::OR;
				}
				else if (buf == "AND") {
					type = TokenType::AND;
				}
				else {
					type = TokenType::IDENTIFIER;
					value = buf;
				}
				tokens.emplace_back(type, value);
				buf.clear();
			}
			else if (isdigit(peek().value())) {
				TokenType type;
				buf.push_back(consume());
				while (peek().has_value() && isdigit(peek().value())) {
					buf.push_back(consume());
				}
				if (peek().value() == '.') {
					type = TokenType::FLOAT;
					buf.push_back(consume());
					while (peek().has_value() && isdigit(peek().value())) {
						buf.push_back(consume());
					}
				}
				else {
					type = TokenType::INTEGER;
				}
				tokens.emplace_back(type, buf);
				buf.clear();
			}
			else if (peek().value() == '"') {
				consume();
				while (peek().has_value()) {
					if (peek().value() == '\\') {
						consume();
						buf.push_back(consume());
					}
					else {
						if (peek().value() == '"') {
							consume();
							break;
						}
						buf.push_back(consume());
					}
				}
				tokens.emplace_back(TokenType::STRING, buf);
				buf.clear();
			}
			else if (peek().value() == '[') {
				consume();
				tokens.emplace_back(TokenType::LBRACKET, std::nullopt);
			}
			else if (peek().value() == ']') {
				consume();
				tokens.emplace_back(TokenType::LBRACKET, std::nullopt);
			}
			else if (peek().value() == '(') {
				consume();
				tokens.emplace_back(TokenType::LPAREN, std::nullopt);
			}
			else if (peek().value() == ')') {
				consume();
				tokens.emplace_back(TokenType::RPAREN, std::nullopt);
			}
			else if (peek().value() == '{') {
				consume();
				tokens.emplace_back(TokenType::LBRACE, std::nullopt);
			}
			else if (peek().value() == '}') {
				consume();
				tokens.emplace_back(TokenType::LBRACE, std::nullopt);
			}
			else if (peek().value() == '=') {
				consume();
				tokens.emplace_back(TokenType::ASSIGNMENT, std::nullopt);
			}
			else if (peek().value() == '+') {
				consume();
				tokens.emplace_back(TokenType::PLUS, std::nullopt);
			}
			else if (peek().value() == '-') {
				consume();
				tokens.emplace_back(TokenType::MINUS, std::nullopt);
			}
			else if (peek().value() == '*') {
				consume();
				tokens.emplace_back(TokenType::MULTIPLY, std::nullopt);
			}
			else if (peek().value() == '/') {
				consume();
				tokens.emplace_back(TokenType::DIVIDE, std::nullopt);
			}
			else if (peek().value() == '<') {
				consume();
				tokens.emplace_back(TokenType::LESSER, std::nullopt);
			}
			else if (peek().value() == '>') {
				consume();
				tokens.emplace_back(TokenType::GREATER, std::nullopt);
			}
			else {
				std::cerr << "Invalid token \"" << peek().value() << "\"found" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		return tokens;
	}

	std::string tokenToString(const Token& token) noexcept {
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
		case TokenType::LBRACE: tokenStr = "{"; break;
		case TokenType::RBRACE: tokenStr = "}"; break;
		}
		if (token.value.has_value()) {
			tokenStr += ": " + token.value.value();
		}
		return tokenStr;
	}
}