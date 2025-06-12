#include "app.hpp"
#include "graph.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cassert>
#include <format>
#include <iostream>

App::App() {
  Parser parser;
  frames_ = parser.parse("../../SerializedEpisodes/adjoint_0");

  for (auto &f : frames_) {
    for (auto &[id, v] : f.vertices) {
      assert(id != 877);
    }
  }
  if (!frames_.empty()) {
    frames_.front().init();
  }
  for (auto &f : frames_) {
    for (auto &[id, v] : f.vertices) {
      assert(id != 877);
    }
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

  std::cout << id << std::endl;
  if (id != 0 && id < frames_.size() && id != prev_frame_) {
    auto &g = frames_[id];
    auto &prev = frames_[prev_frame_];
    for (auto &[vid, v] : g.vertices) {
      v.pos = prev.vertices[vid].pos;
    }
    for (auto &[sid, s] : g.states) {
      s.pos = prev.states[sid].pos;
    }
  }

  prev_frame_ = id;

  frames_[id].update();
  frames_[id].draw();
}
