#pragma once

#include "graph.hpp"
class App {
public:
  App();

  void update();
  void draw();

private:
  std::vector<Graph> history_;
  float time_per_graph = 10;
};
