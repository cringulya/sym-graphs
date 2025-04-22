#pragma once

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

    float x, y;
    float dx, dy;

    void draw(float t, float dt);
  };

  struct Edge {
    int from, to;
  };

  std::vector<Vertex> vertecies;
  std::vector<Edge> edges;

  void init();
  void draw(float t, float dt);
  void apply_force_layout(int iterations = 100, float width = 1.0f,
                          float height = 1.0f);
};
