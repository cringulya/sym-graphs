#pragma once

#include "graph.hpp"
#include <filesystem>

class App {
public:
  void init(std::filesystem::path const &);
  void update();
  void draw();

private:
  std::vector<Graph> frames_;
  float time_per_graph = 10;
  int prev_frame_ = -1;
  float max_time_ = 100.f;
};
