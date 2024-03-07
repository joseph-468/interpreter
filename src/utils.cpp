#include "../include/utils.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <optional>

std::optional<std::string> readFile(const std::string& filename) noexcept {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return std::nullopt;
	} 
	std::stringstream fileStrStream;
	fileStrStream << file.rdbuf();
	std::string fileStr = fileStrStream.str();

	return fileStr;
}