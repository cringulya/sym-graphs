#pragma once

#include "raylib.h"
#include <vector>

class Graph {
public:
  struct Vertex {
    int id;
    bool in_coverage_zone;
    int basic_block_size;
    bool covered_by_test;
    bool visited_by_state;
    bool touched_by_state;
    bool contains_call;
    bool contains_throw;
    std::vector<int> states;

    Vector2 pos;
    Vector2 disp;
  };

  struct Edge {
    int from, to;
  };

  std::vector<Vertex> vertecies;
  std::vector<Edge> edges;

  void init();
  void draw();
  void apply_force_layout(int iterations = 100);

private:
  size_t frame = 0;
  float temperature_ = 0.f;
};
