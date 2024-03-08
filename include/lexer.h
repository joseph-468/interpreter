#pragma once

#include "../include/utils.h"

#include <string>
#include <vector>
#include <optional>
#include <utility>

enum class TokenType {
	// Operators
	ASSIGNMENT,
	EQUALITY,
	INEQUALITY,
	OR,
	AND,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LESSER,
	GREATER,
	// Control flow
	IF,
	THEN,
	ELSE,
	WHILE,
	FOR,
	GOTO,
	// Literals
	INTEGER,
	FLOAT,
	STRING,
	// Misc
	IDENTIFIER,
	LBRACKET,
	RBRACKET,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
};

namespace Lexer {
	std::vector<Token> tokenize(const std::string& source) noexcept;
	std::string tokenToString(const Token& token) noexcept;
}