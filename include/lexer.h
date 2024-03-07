#pragma once

#include <string>
#include <vector>

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
	RETURN,
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
};

struct Token {
	TokenType type;
	std::string value;
};

class Lexer {
public:
	Lexer() = delete;
	Lexer(const Lexer& other) = delete;
	Lexer(const Lexer&& other) = delete;
	Lexer operator=(const Lexer& other) = delete;
	Lexer operator=(const Lexer&& other) = delete;

	explicit Lexer(std::string& code) noexcept;
	std::vector<Token> tokenize() noexcept;

	static std::string tokenToString(const Token& token) noexcept;

private:
	std::string code;
};