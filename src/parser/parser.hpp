#pragma once

#include <filesystem>

#include "graph.hpp"

class Parser {
public:
  std::vector<Graph> parse(std::filesystem::path path);
};
