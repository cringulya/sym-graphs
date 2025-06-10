#pragma once

#include "raylib.h"
#include <unordered_map>
#include <vector>

#include "ogdf/basic/Graph.h"
#include "ogdf/energybased/SpringForceModel.h"

class Graph {
public:
  struct Vertex {
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

  std::unordered_map<size_t, Vertex> vertecies;
  std::vector<Edge> edges;

  void update();
  void draw();
  void apply_force_layout(int iterations = 100);

private:
  size_t frame = 0;
  float temperature_ = 0.f;
};
