#include "app.hpp"
#include "graph.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

App::App() {
  Parser parser;
  frames_ = parser.parse("../../SerializedEpisodes/adjoint_0");

  if (!frames_.empty()) {
    frames_.front().update();
  }
}

void App::update() {
  draw();
}

void App::draw() {
  float time = GetTime();
  float max_time = 100;
  float time_per_graph = max_time / frames_.size();

  int id = fmin(frames_.size() - 1, time / time_per_graph);

  if (id > 0 && id < frames_.size()) {
    for (auto &[vid, v] : frames_[id].vertices) {
      v.pos = frames_[id - 1].vertices[vid].pos;
    }
    for (auto &[sid, s] : frames_[id].states) {
      s.pos = frames_[id - 1].states[sid].pos;
    }
  }

  frames_[id].update();
  frames_[id].draw();
}
