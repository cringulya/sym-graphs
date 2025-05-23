#include "app.hpp"
#include "graph.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

App::App() {
  Parser parser;
  history_ = parser.parse("../../SerializedEpisodes/adjoint_0");
  for (auto &g : history_) {
    g.init();
  }
}

void App::update() {
  draw();
}

void App::draw() {
  float time = GetTime();
  float max_time = 20;
  float time_per_graph = max_time / history_.size();

  int id = fmin(history_.size() - 1, time / time_per_graph);
  std::cout << time << std::endl;
  std::cout << id << std::endl;

  history_[id].draw();
}
