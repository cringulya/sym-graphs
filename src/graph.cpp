#include <cassert>
#include <cmath>
#include <ctime>
#include <string>

#include "graph.hpp"
#include "raylib.h"
#include "raymath.h"

void Graph::init() {
  temperature_ = GetScreenWidth() / 10.0f;
  const float scale = 10000.f;
  for (auto &[id, v] : vertices) {
    v.pos.x =
        ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenWidth();
    v.pos.y =
        ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenHeight();
  }
  for (auto &[id, s] : states) {
    s.pos.x =
        ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenWidth();
    s.pos.y =
        ((float)GetRandomValue(0, scale) / scale - 0.5f) * GetScreenHeight();
  }
  apply_force_layout();
}

void Graph::update() {
  apply_force_layout();
}

void Graph::draw() {
  for (auto &e : edges) {
    DrawLineV(vertices[e.from].pos, vertices[e.to].pos, LIGHTGRAY);
  }

  for (auto &[id, v] : vertices) {
    Color color = RED;
    assert(id != 887);
    if (v.covered_by_test) {
      color = GREEN;
    } else if (v.touched_by_state) {
      color = ORANGE;
    }
    DrawCircleV(v.pos, radius_, color);
    DrawText(std::to_string(id).c_str(), v.pos.x, v.pos.y, fontsize_, WHITE);
  }

  for (auto &[id, s] : states) {
    for (auto &hv : s.history) {
      DrawLineV(s.pos, vertices[hv.id].pos, PINK);
    }
    Color color = BLUE;
    DrawCircleV(s.pos, radius_, color);
    DrawText(std::to_string(id).c_str(), s.pos.x, s.pos.y, fontsize_, WHITE);
  }
}

void Graph::apply_force_layout() {
  float dt = GetFrameTime();

  const float kAttract = 0.1f;
  const float kRepulse = 1000.0f;
  const float damping = 0.5f;
  const float eps = 0.01f;
  const int n = vertices.size();
  if (n == 0) return;

  for (auto &e : edges) {
    Vector2 force = Vector2Zero();
    Vector2 delta = vertices[e.from].pos - vertices[e.to].pos;
    force += delta * kAttract;
    vertices[e.to].vel += force * dt;
    vertices[e.from].vel -= force * dt;
  }

  for (auto &[id, s] : states) {
    for (auto &v : s.history) {
      Vector2 force = Vector2Zero();
      Vector2 delta = s.pos - vertices[v.id].pos;
      force += delta * kAttract;
      vertices[v.id].vel += force * dt;
      s.vel -= force * dt;
    }
  }

  for (auto &[id_a, a] : vertices) {
    Vector2 force = Vector2Zero();
    for (auto &[id_b, b] : vertices) {
      if (id_a == id_b) continue;
      Vector2 delta = a.pos - b.pos;
      float dist2 = Vector2DistanceSqr(a.pos, b.pos) + eps;
      force += delta * (kRepulse / dist2);
    }
    for (auto &[id_s, s] : states) {
      if (id_a == id_s) continue;
      Vector2 delta = a.pos - s.pos;
      float dist2 = Vector2DistanceSqr(a.pos, s.pos) + eps;
      force += delta * (kRepulse / dist2);
    }
    a.vel += force * dt;
    a.vel *= damping;
  }

  for (auto &[id_a, a] : states) {
    Vector2 force = Vector2Zero();
    for (auto &[id_b, b] : vertices) {
      if (id_a == id_b) break;
      Vector2 delta = a.pos - b.pos;
      float dist2 = Vector2DistanceSqr(a.pos, b.pos) + eps;
      force += delta * (kRepulse / dist2);
    }
    for (auto &[id_s, s] : states) {
      if (id_a == id_s) break;
      Vector2 delta = a.pos - s.pos;
      float dist2 = Vector2DistanceSqr(a.pos, s.pos) + eps;
      force += delta * (kRepulse / dist2);
    }
    a.vel += force * dt;
    a.vel *= damping;
  }

  for (auto &[_, s] : states) {
    s.pos += s.vel;
  }

  for (auto &[_, v] : vertices) {
    v.pos += v.vel;
  }
}
