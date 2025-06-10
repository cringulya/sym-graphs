#include <cmath>
#include <iostream>
#include <ostream>
#include <string>

#include "graph.hpp"
#include "raylib.h"
#include "raymath.h"

void Graph::update() {
  temperature_ = GetScreenWidth() / 10.0f;
  const float scale = 10000.f;
  for (auto &[id, v] : vertecies) {
    if (v.pos == Vector2Zero()) {
      v.pos.x =
          ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenWidth();
      v.pos.y =
          ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenHeight();
    }
  }
  apply_force_layout(10);
}

void Graph::draw() {
  for (auto &e : edges) {
    DrawLineV(vertecies[e.from].pos, vertecies[e.to].pos, LIGHTGRAY);
  }

  for (auto &[id, v] : vertecies) {
    Color color = RED;
    if (v.covered_by_test) {
      color = GREEN;
    } else if (v.touched_by_state) {
      color = YELLOW;
    }
    DrawCircleV(v.pos, 20.f, color);
    DrawText(std::to_string(id).c_str(), v.pos.x, v.pos.y, 10, WHITE);
  }
}

void Graph::apply_force_layout(int iterations) {
  float width = GetScreenWidth() / 2.f;
  float height = GetScreenHeight() / 2.f;

  const int n = vertecies.size();
  if (n == 0) return;

  const float area = width * height;
  const float k = std::sqrt(area / n);
  const float cooling = 0.95f;

  const float lambda = 100.0f;
  for (int it = 0; it < iterations; ++it) {
    for (auto &[id, node] : vertecies) {
      node.disp = {0.0f, 0.0f};
    }

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        Vector2 delta = Vector2Subtract(vertecies[i].pos, vertecies[j].pos);
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y + 1e-4f);
        float force = (k * k) / dist;
        Vector2 repulse = Vector2Scale(Vector2Normalize(delta), force);

        vertecies[i].disp = Vector2Add(vertecies[i].disp, repulse);
        vertecies[j].disp = Vector2Subtract(vertecies[j].disp, repulse);
      }
    }

    for (const auto &e : edges) {
      auto &u = vertecies[e.from];
      auto &v = vertecies[e.to];
      Vector2 delta = Vector2Subtract(u.pos, v.pos);
      float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y + 1e-4f);
      float force = (dist * dist) / k * 2.f;
      Vector2 attract = Vector2Scale(Vector2Normalize(delta), force);

      u.disp = Vector2Subtract(u.disp, attract);
      v.disp = Vector2Add(v.disp, attract);
    }

    for (auto &[id, node] : vertecies) {
      float disp_len =
          std::sqrt(node.disp.x * node.disp.x + node.disp.y * node.disp.y);
      if (disp_len > 0.0f) {
        Vector2 move = Vector2Scale(Vector2Normalize(node.disp),
                                    std::min(disp_len, temperature_));
        node.pos = Vector2Add(node.pos, move);
      }

      node.pos.x = Clamp(node.pos.x, -width / 2.0f, width / 2.0f);
      node.pos.y = Clamp(node.pos.y, -height / 2.0f, height / 2.0f);
    }

    float delta_time = GetFrameTime();
    temperature_ *= std::pow(cooling, delta_time);

    if (temperature_ < 0.1f) temperature_ = 0.1f;
  }
}
