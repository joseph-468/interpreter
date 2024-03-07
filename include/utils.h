#pragma once

#include <string>
#include <optional>

std::optional<std::string> readFile(const std::string& filename) noexcept;
