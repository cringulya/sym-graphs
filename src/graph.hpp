#pragma once

#include "raylib.h"
#include "raymath.h"
#include <unordered_map>
#include <vector>

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

    Vector2 pos = Vector2Zero();
    Vector2 vel = Vector2Zero();
  };

  struct State {
    struct HistoryVertex {
      size_t id;
      int num_of_visits;
      int step_when_visited_last_time;
    };

    size_t id;
    int position;
    int visited_again_vertices;
    int visited_not_covered_vertices_in_zone;
    int visited_not_covered_vertices_out_of_zone;
    int step_when_moved_last_time;
    int instructions_visited_in_current_block;
    std::vector<HistoryVertex> history;

    Vector2 pos = Vector2Zero();
    Vector2 vel = Vector2Zero();
  };

  struct Edge {
    int from, to;
  };

  std::unordered_map<size_t, Vertex> vertices;
  std::unordered_map<size_t, State> states;
  std::vector<Edge> edges;

  void init();
  void update();
  void draw();
  void apply_force_layout();

private:
  size_t frame = 0;
  float temperature_ = 0.f;
  const float radius_ = 10.f;
  const int fontsize_ = 50;
  double time_;
};
