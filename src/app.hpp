#pragma once

#include "graph.hpp"
class App {
public:
  App();

  void update();
  void draw();

private:
  std::vector<Graph> frames_;
  float time_per_graph = 10;
  int prev_frame_ = -1;
};
