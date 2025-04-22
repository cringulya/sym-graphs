#include <cmath>

#include "Core/gl.h"
#include "graph.h"

void Graph::init() {
  for (auto &v : vertecies) {
    v.x = (rand() / (float)RAND_MAX - 0.5f) * 2.0f;
    v.y = (rand() / (float)RAND_MAX - 0.5f) * 2.0f;
  }

  apply_force_layout();
}

void Graph::Vertex::draw(float t, float dt) {
  glPointSize(10.0f);
  glColor3f(0.2f, 0.6f, 1.0f);
  glBegin(GL_POINTS);
  glVertex2f(x, y);
  glEnd();
}

void Graph::draw(float t, float dt) {
  for (auto &v : vertecies) {
    v.draw(t, dt);
  }

  glColor3f(0.7f, 0.7f, 0.7f);
  glBegin(GL_LINES);
  for (auto &e : edges) {
    glVertex2f(vertecies[e.from].x, vertecies[e.from].y);
    glVertex2f(vertecies[e.to].x, vertecies[e.to].y);
  }
  glEnd();
}

void Graph::apply_force_layout(int iterations, float width, float height) {
  const int n = vertecies.size();
  const float area = width * height;
  const float k = std::sqrt(area / n);
  float temperature = width / 10.0f;
  const float cooling = 0.95f;

  for (int it = 0; it < iterations; ++it) {
    for (auto &node : vertecies) {
      node.dx = 0;
      node.dy = 0;
    }

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        float dx = vertecies[i].x - vertecies[j].x;
        float dy = vertecies[i].y - vertecies[j].y;
        float dist = std::sqrt(dx * dx + dy * dy + 1e-4f);
        float force = k * k / dist;

        float fx = (dx / dist) * force;
        float fy = (dy / dist) * force;

        vertecies[i].dx += fx;
        vertecies[i].dy += fy;
        vertecies[j].dx -= fx;
        vertecies[j].dy -= fy;
      }
    }

    for (const auto &e : edges) {
      auto &u = vertecies[e.from];
      auto &v = vertecies[e.to];
      float dx = u.x - v.x;
      float dy = u.y - v.y;
      float dist = std::sqrt(dx * dx + dy * dy + 1e-4f);
      float force = dist * dist / k;

      float fx = (dx / dist) * force;
      float fy = (dy / dist) * force;

      u.dx -= fx;
      u.dy -= fy;
      v.dx += fx;
      v.dy += fy;
    }

    for (auto &node : vertecies) {
      float dx = node.dx;
      float dy = node.dy;
      float disp = std::sqrt(dx * dx + dy * dy);

      if (disp > 0.0f) {
        dx = dx / disp * std::min(disp, temperature);
        dy = dy / disp * std::min(disp, temperature);
      }

      node.x += dx;
      node.y += dy;

      node.x = std::max(-width / 2.0f, std::min(width / 2.0f, node.x));
      node.y = std::max(-height / 2.0f, std::min(height / 2.0f, node.y));
    }

    temperature *= cooling;
  }
}
