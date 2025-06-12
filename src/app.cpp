#include "app.hpp"
#include "graph.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include <cassert>
#include <iostream>

void App::init(std::filesystem::path const &path) {
  static Parser parser;
  frames_ = parser.parse(path);

  if (!frames_.empty()) {
    frames_.front().init();
  }
}

void App::update() {
  draw();
}

void App::draw() {
  float time = GetTime();
  float time_per_graph = max_time_ / frames_.size();

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
