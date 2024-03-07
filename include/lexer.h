#pragma once

#include <string>
#include <vector>
#include <optional>

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
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
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
	std::optional<char> peek(const size_t offset = 0) const noexcept; 
	char consume() noexcept;

	std::string code;
	size_t curr;
};